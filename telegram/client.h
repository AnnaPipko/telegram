#pragma once

#include <memory>
#include <vector>

class Message{
    class MessageImpl;

public:
    explicit Message(std::shared_ptr<MessageImpl> pimpl);
    int64_t GetChatId() const;
    int GetId() const;
    std::string GetText() const;
    bool IsEdited() const;
    std::vector<std::string> GetCommands() const;

private:
    friend class Update;
    std::shared_ptr<MessageImpl> pimpl_;
};

enum class UpdateType{
    UNDEFINED,
    MESSAGE, EDITED_MESSAGE,
    CHANNEL_POST, EDITED_CHANNEL_POST
//    INLINE_QUERY, CHOSEN_INLINE_RESULT,
//    CALLBACK_QUERY, SHIPPING_QUERY, PRE_CHECKOUT_QUERY
};

class Update{
    class UpdateImpl;
public:
    explicit Update(std::shared_ptr<UpdateImpl> pimpl);
    UpdateType GetType() const;
    int GetId() const;
    Message GetMessage() const;

private:
    friend class Client;
    std::shared_ptr<UpdateImpl> pimpl_;
};

class Client{
public:
    Client(const std::string& url, const std::string& token);

    void GetMe();

    std::vector<Update> GetUpdates(int timeout = 0, int offset = 0,
                                   const std::vector<std::string>& allowed_updates = {});

    void SendMessage(int64_t chat_id, const std::string& text, int64_t reply_to_message_id = 0);
    void SendSticker(int64_t chat_id, const std::string &sticker);
    void SendGif(int64_t chat_id, const std::string &file);
    void SendPhoto(int64_t chat_id, const std::string &file, const std::string& caption = "");

private:
    class ClientImpl;
    std::shared_ptr<ClientImpl> pimpl_;
};

std::string VectorToString(std::vector<std::string> vector);

