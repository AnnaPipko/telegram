#include "bot.h"
#include "exceptions.h"
#include "logger.h"

#include <fstream>

Logger& GetLogger() {
    static Logger logger("bot_log.txt");
    return logger;
}

void Bot::ResetTry() {
    std::ofstream file;
    file.open ("try.txt");
    file << 0;
    file.close();
}

void Bot::StartTry() {
    std::ifstream input;
    input.open ("try.txt");
    int try_counter = 0;
    if (input.peek() != EOF) {
        input >> try_counter;
    }
    ++try_counter;
    input.close();
    std::ofstream file;
    file.open ("try.txt");
    file << try_counter;
    file.close();
}

int Bot::GetOffset() {
    std::ifstream file;
    file.open ("offset.txt");
    int offset = 0;
    if (file.peek() != EOF) {
        file >> offset;
    }
    file.close();
    return offset;
}

void Bot::SetOffset(int offset) {
    std::ofstream file;
    file.open ("offset.txt");
    file << offset;
    crash_counter_ = crash_limit_;
    ResetTry();
    file.close();
}

std::vector<Update> Bot::GetUpdates() {
    int offset = GetOffset() + 1;
    return client_->GetUpdates(timeout_, offset);
}

Bot::Bot(const std::string &token) : token_(token),
                                     crash_counter_(crash_limit_),
                                     message_handler_(std::make_shared<MessageHandler>()),
                                     client_(std::make_shared<Client>("https://api.telegram.org", token)) {
    auto updates = GetUpdates();
    if (!updates.empty()){
        int first_update = updates[0].GetId();
        if (GetOffset() < first_update - 1) {
            std::ofstream file;
            file.open("offset.txt");
            file << first_update - 1;
            file.close();
        }
    }
    GetLogger().Information("Bot started");
}

void Bot::Run() {
    try {
        while (true) {
            auto updates = GetUpdates();
            for (const auto &update : updates) {
                GetLogger().Information("Process update " + std::to_string(update.GetId()));
                StartTry();
                message_handler_->Process(update, client_);
                SetOffset(update.GetId());
            }
        }
    } catch (const StopBotError&){
        SetOffset(GetOffset() + 1);
        client_->GetUpdates(0, GetOffset() + 1);
        GetLogger().Information("Stopped");
        return;
    } catch (const std::exception& exception){
        --crash_counter_;
        if (crash_counter_ == 0) {
            std::rethrow_exception(std::current_exception());
        }
        GetLogger().Error(std::string(exception.what()) + " ...restarting");
        Run();
    }
}

void Bot::SkipCrash() {
    std::ifstream input;
    input.open ("try.txt");
    int try_counter = 0;
    if (input.peek() != EOF) {
        input >> try_counter;
    }
    input.close();
    if (try_counter > 0){
        GetLogger().Error("Restarting after crash");
        SetOffset(GetOffset() + 1);
    }
}

void Bot::SetTimeout(int timeout) {
    timeout_ = timeout;
}
