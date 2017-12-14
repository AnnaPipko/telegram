#pragma once

#include <memory>

class Logger{
public:
    explicit Logger(const std::string& file);
    void SetLevel(const std::string& level);
    void Debug(const std::string& message);
    void Information(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);

private:
    class LoggerImpl;
    std::shared_ptr<LoggerImpl> pimpl_;
};

