#pragma once

#include "client.h"
#include "message_handler.h"
#include "logger.h"

Logger& GetLogger();

class Bot{
public:
    explicit Bot(const std::string &token);

    void Run();

    void SkipCrash();

    void SetTimeout(int timeout);

private:
    std::string token_;
    int timeout_ = 30;
    int crash_limit_ = 3;
    int crash_counter_;
    std::shared_ptr<MessageHandler> message_handler_;
    std::shared_ptr<Client> client_;

    std::vector<Update> GetUpdates();
    void SetOffset(int offset);
    int GetOffset();
    void ResetTry();
    void StartTry();
};

