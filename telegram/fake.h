#pragma once

#include <string>
#include <memory>

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>

namespace telegram {

class TestCase;

class FakeServer {
public:
    FakeServer(const std::string& testCase);

    ~FakeServer();

    void Start();

    std::string GetUrl();

    void Stop();

    void StopAndCheckExpectations();

private:
    std::shared_ptr<TestCase> TestCase_;
    std::unique_ptr<Poco::Net::ServerSocket> Socket_;
    std::unique_ptr<Poco::Net::HTTPServer> Server_;
};

} // namespace telegram