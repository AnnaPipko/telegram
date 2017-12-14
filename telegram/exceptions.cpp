#include "exceptions.h"

StopBotError::StopBotError(const std::string &what_arg) :
        std::runtime_error("StopBotError: " + what_arg) {}

JsonParseError::JsonParseError(const std::string &what_arg) :
        std::runtime_error("JsonParseError: " + what_arg) {}

RequestError::RequestError(const std::string &what_arg) :
        std::runtime_error("RequestError: " + what_arg) {}
