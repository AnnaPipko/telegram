#include <memory>
#include <unordered_map>

#include "client.h"
#include "exceptions.h"

#include <Poco/URI.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <json/json.h>

class Message::MessageImpl{
public:
    explicit MessageImpl(Json::Value value);
    int64_t GetChatId()  const;
    int GetId()  const;
    std::string GetText() const;
    bool IsEdited() const;
    std::vector<std::string> GetCommands() const;
    Message ToMessage() const;

private:
    Json::Value value_;

};

class Update::UpdateImpl{
public:
    explicit UpdateImpl(Json::Value value);
    UpdateType GetType() const;
    int GetId() const;
    Message GetMessage() const;
    Update ToUpdate() const;

private:
    Json::Value value_;
};

class Client::ClientImpl{
public:
    ClientImpl(const std::string& url, const std::string& token);

    void GetMe();

    std::vector<Update> GetUpdates(int offset = 0, int timeout = 0,
                                   const std::vector<std::string>& allowed_updates = {});

    void SendMessage(int64_t chat_id, const std::string& text, int64_t reply_to_message_id = 0);
    void SendSticker(int64_t chat_id, const std::string &sticker);
    void SendGif(int64_t chat_id, const std::string &file);
    void SendPhoto(int64_t chat_id, const std::string &file, const std::string& caption = "");

private:
    std::unique_ptr<Poco::Net::HTTPClientSession> session_;
    std::string path_;

    Json::Value URLQuery(const std::string& method,
                         const std::unordered_map<std::string, std::string>& params = {});
};


Message::MessageImpl::MessageImpl(Json::Value value) :value_(value) {}

int64_t Message::MessageImpl::GetChatId() const {
    auto result = value_.get("chat", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        result = result.get("id", Json::Value());
        if (result.type() != Json::ValueType::nullValue) {
            return result.asInt();
        }
    }
    throw JsonParseError("Invalid message json");
}

int Message::MessageImpl::GetId() const {
    auto result = value_.get("message_id", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return result.asInt();
    }
    throw JsonParseError("Invalid message json");
}

std::string Message::MessageImpl::GetText() const {
    auto result = value_.get("text", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return result.asString();
    }
    return "";
}

bool Message::MessageImpl::IsEdited() const {
    auto result = value_.get("edit_date", Json::Value());
    return result.type() != Json::ValueType::nullValue;
}

std::vector<std::string> Message::MessageImpl::GetCommands() const {
    auto result = value_.get("entities", Json::Value());
    std::vector<std::string> commands;
    if (result.type() != Json::ValueType::nullValue){
        std::string text = GetText();
        for (auto el : result){
            if (el["type"] == "bot_command") {
                int offset = el["offset"].asInt();
                int length = el["length"].asInt();
                commands.push_back(text.substr(offset, length));
            }
        }
    }
    return commands;
}

Message Message::MessageImpl::ToMessage() const {
    return Message(std::make_shared<Message::MessageImpl>(value_));
}


Update::UpdateImpl::UpdateImpl(Json::Value value) : value_(value) {}

UpdateType Update::UpdateImpl::GetType() const {
    auto result = value_.get("message", Json::Value());
    if (result.type() != Json::ValueType::nullValue) {
        return UpdateType::MESSAGE;
    }
    result = value_.get("edited_message", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return UpdateType::EDITED_MESSAGE;
    }
    result = value_.get("channel_post", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return UpdateType::CHANNEL_POST;
    }
    result = value_.get("edited_channel_post", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return UpdateType::EDITED_CHANNEL_POST;
    }
    return UpdateType::UNDEFINED;
}

Message Update::UpdateImpl::GetMessage() const {
    auto type = GetType();
    switch (type){
        case UpdateType::MESSAGE: {
            return Message::MessageImpl(value_["message"]).ToMessage();
        }
        case UpdateType::EDITED_MESSAGE: {
            return Message::MessageImpl(value_["edited_message"]).ToMessage();
        }
        case UpdateType::CHANNEL_POST: {
            return Message::MessageImpl(value_["channel_post"]).ToMessage();
        }
        case UpdateType::EDITED_CHANNEL_POST: {
            return Message::MessageImpl(value_["edited_channel_post"]).ToMessage();
        }
    }
    throw JsonParseError("Invalid update json");
}

int Update::UpdateImpl::GetId() const {
    auto result = value_.get("update_id", Json::Value());
    if (result.type() != Json::ValueType::nullValue){
        return result.asInt();
    }
    throw JsonParseError("Invalid update json");
}

Update Update::UpdateImpl::ToUpdate() const {
    return Update(std::make_shared<Update::UpdateImpl>(value_));
}


std::string VectorToString(std::vector<std::string> vector){
    std::string result = "[";
    for (auto const& el : vector){
        result += '"' + el + '"' + ',';
    }
    if (result.size() > 1) {
        result.pop_back();
    }
    result += "]";
    return result;
}

Client::ClientImpl::ClientImpl(const std::string &url, const std::string& token) {
    path_ = "/bot" + token + "/";
    Poco::URI uri(url);
    std::string scheme(uri.getScheme());
    std::string host(uri.getHost());
    auto port(uri.getPort());
    if (scheme == "http"){
        session_ = std::make_unique<Poco::Net::HTTPClientSession>(host, port);
    } else if (scheme == "https"){
        session_ = std::unique_ptr<Poco::Net::HTTPClientSession>(new Poco::Net::HTTPSClientSession(host, port));
    } else {
        throw RequestError("Unknown scheme");
    }
}

void Client::ClientImpl::GetMe() {
    URLQuery("getMe");
}

std::vector<Update> Client::ClientImpl::GetUpdates(int timeout, int offset,
                                                   const std::vector<std::string>& allowed_updates) {
    std::unordered_map<std::string, std::string> params;
    if (offset > 0) {
        params["offset"] = std::to_string(offset);
    }
    if (timeout > 0) {
        params["timeout"] = std::to_string(timeout);
    }
    if (!allowed_updates.empty()) {
        params["allowed_updates"] = VectorToString(allowed_updates);
    }
    auto result = URLQuery("getUpdates", params);
    std::vector<Update> updates;
    for (const auto& el : result){
        updates.emplace_back(std::make_shared<Update::UpdateImpl>(el));
    }
    return updates;
}

void Client::ClientImpl::SendSticker(int64_t chat_id, const std::string &sticker) {
    std::unordered_map<std::string, std::string> params;
    params["chat_id"] = std::to_string(chat_id);
    params["sticker"] = sticker;
    URLQuery("sendSticker", params);
}

void Client::ClientImpl::SendGif(int64_t chat_id, const std::string &file) {
    std::unordered_map<std::string, std::string> params;
    params["chat_id"] = std::to_string(chat_id);
    params["document"] = file;
    URLQuery("sendDocument", params);
}

void Client::ClientImpl::SendPhoto(int64_t chat_id, const std::string &file, const std::string &caption) {
    std::unordered_map<std::string, std::string> params;
    params["chat_id"] = std::to_string(chat_id);
    params["photo"] = file;
    params["caption"] = caption;
    URLQuery("sendPhoto", params);
}

void Client::ClientImpl::SendMessage(int64_t chat_id, const std::string& text, int64_t reply_to_message_id) {
    std::unordered_map<std::string, std::string> params;
    params["chat_id"] = std::to_string(chat_id);
    params["text"] = text;
    if (reply_to_message_id > 0){
        params["reply_to_message_id"] = std::to_string(reply_to_message_id);
    }
    URLQuery("sendMessage", params);
}

Json::Value Client::ClientImpl::URLQuery(const std::string& method,
                                         const std::unordered_map<std::string, std::string>& params) {
    Poco::URI uri(path_ + method);
    Poco::URI::QueryParameters query_params;
    for (const auto& el : params){
        query_params.emplace_back(el);
    }
    uri.setQueryParameters(query_params);
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.toString());

    Poco::Net::HTTPResponse response;
    session_->sendRequest(request);
    std::istream& rs = session_->receiveResponse(response);
    auto status = response.getStatus();
    if (status != Poco::Net::HTTPResponse::HTTPStatus::HTTP_OK){
        throw RequestError(std::to_string(int(status)) + " " + response.getReason());
    }
    Json::CharReaderBuilder builder;
    Json::Value value;
    JSONCPP_STRING errs;
    bool ok = parseFromStream(builder, rs, &value, &errs);
    if (!ok) {
        throw JsonParseError(errs);
    }
    if (!value["ok"]){
        throw RequestError(method + " request error");
    }
    return value["result"];
}


Client::Client(const std::string &url, const std::string &token) :
        pimpl_(std::make_shared<ClientImpl>(url, token)){}

void Client::GetMe() {
    pimpl_->GetMe();
}

std::vector<Update> Client::GetUpdates(int timeout, int offset,
                                       const std::vector<std::string> &allowed_updates) {
    return pimpl_->GetUpdates(timeout, offset, allowed_updates);
}

void Client::SendMessage(int64_t chat_id, const std::string &text, int64_t reply_to_message_id) {
    pimpl_->SendMessage(chat_id, text, reply_to_message_id);
}

void Client::SendSticker(int64_t chat_id, const std::string &sticker) {
    pimpl_->SendSticker(chat_id, sticker);
}

void Client::SendGif(int64_t chat_id, const std::string &file) {
    pimpl_->SendGif(chat_id, file);
}

void Client::SendPhoto(int64_t chat_id, const std::string &file, const std::string &caption) {
    pimpl_->SendPhoto(chat_id, file, caption);
}

Message::Message(std::shared_ptr<MessageImpl> pimpl) : pimpl_(std::move(pimpl)) {}

int64_t Message::GetChatId() const {
    return pimpl_->GetChatId();
}

int Message::GetId() const {
    return pimpl_->GetId();
}

std::string Message::GetText() const {
    return pimpl_->GetText();
}

std::vector<std::string> Message::GetCommands() const {
    return pimpl_->GetCommands();
}

bool Message::IsEdited() const {
    return pimpl_->IsEdited();
}

Update::Update(std::shared_ptr<UpdateImpl> pimpl) : pimpl_(std::move(pimpl)) {}

int Update::GetId() const {
    return pimpl_->GetId();
}

Message Update::GetMessage() const {
    return pimpl_->GetMessage();
}

UpdateType Update::GetType() const {
    return pimpl_->GetType();
}