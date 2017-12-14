#pragma once

#include <exception>
#include <string>
#include <stdexcept>

class StopBotError : public std::runtime_error {
public:
    explicit StopBotError(const std::string& what_arg);
};

class JsonParseError : public std::runtime_error {
public:
    explicit JsonParseError(const std::string& what_arg);
};

class RequestError : public std::runtime_error {
public:
    explicit RequestError(const std::string& what_arg);
};
