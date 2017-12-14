#pragma once

#include "client.h"

class MessageHandler{
public:
    void Process(const Update& update, std::shared_ptr<Client> client);
};

bool IsLatin(const std::string& text);

std::string PerformText(const std::string& text);