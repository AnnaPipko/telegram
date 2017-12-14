#include <memory>
#include "logger.h"
#include "Poco/Logger.h"
#include "Poco/FileChannel.h"
#include "Poco/AutoPtr.h"
#include "Poco/ConsoleChannel.h"

class Logger::LoggerImpl{
public:
    explicit LoggerImpl(const std::string& file);
    void SetLevel(const std::string& level);
    void Debug(const std::string& message);
    void Information(const std::string& message);
    void Warning(const std::string& message);
    void Error(const std::string& message);
private:
    Poco::Logger& logger_;
    Poco::AutoPtr<Poco::FileChannel> channel_;
};

Logger::LoggerImpl::LoggerImpl(const std::string &file) : channel_(new Poco::FileChannel),
                                                          logger_(Poco::Logger::get("BotLogger")){
    channel_->setProperty("path", file);
    channel_->setProperty("rotation", "weekly");
    channel_->setProperty("archive", "timestamp");
    logger_.setChannel(channel_);
}

void Logger::LoggerImpl::SetLevel(const std::string &level) {
    logger_.setLevel(level);
}

void Logger::LoggerImpl::Debug(const std::string &message) {
    logger_.debug(message);
}

void Logger::LoggerImpl::Information(const std::string &message) {
    logger_.information(message);
}

void Logger::LoggerImpl::Warning(const std::string &message) {
    logger_.warning(message);
}

void Logger::LoggerImpl::Error(const std::string &message) {
    logger_.error(message);
}

Logger::Logger(const std::string &file) : pimpl_(std::make_shared<Logger::LoggerImpl>(file)) {}

void Logger::SetLevel(const std::string &level) {
    pimpl_->SetLevel(level);
}

void Logger::Debug(const std::string &message) {
    pimpl_->Debug(message);
}

void Logger::Information(const std::string &message) {
    pimpl_->Information(message);
}

void Logger::Warning(const std::string &message) {
    pimpl_->Warning(message);
}

void Logger::Error(const std::string &message) {
    pimpl_->Error(message);
}