#include <telegram/client.h>
#include <iostream>
#include <exception>
#include "catch.hpp"
#include <vector>

TEST_CASE("GetMe OK", "[Bot]") {
    try {
        std::string host = "https://api.telegram.org";
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Client client(host, token);
        client.GetMe();
        REQUIRE(true);
    } catch (const std::exception& exception){
        std::cout << exception.what();
        REQUIRE(false);
    }
}

TEST_CASE("Scheme ERROR", "[Bot]") {
    try {
        std::string host = "ftp://api.telegram.org";
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Client client(host, token);
        client.GetMe();
        REQUIRE(false);
    } catch (const std::exception& exception){
        REQUIRE(exception.what() == std::string("RequestError: Unknown scheme"));
    }
}

TEST_CASE("GetMe 301 ERROR", "[Bot]") {
    try {
        std::string host = "http://api.telegram.org";
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Client client(host, token);
        client.GetMe();
        REQUIRE(false);
    } catch (const std::exception& exception){
        REQUIRE(exception.what() == std::string("RequestError: 301 Moved Permanently"));
    }
}

TEST_CASE("GetUpdates OK", "[Bot]") {
    try {
        std::string host = "https://api.telegram.org";
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Client client(host, token);
        int offset = 767531241;
        int timeout = 0;
        std::vector<std::string> params;
        client.GetUpdates();
        REQUIRE(true);
    } catch (const std::exception& exception){
        std::cout << exception.what();
        REQUIRE(false);
    }
}

TEST_CASE("GetUpdates get text", "[Bot]") {
    try {
        std::string host = "https://api.telegram.org";
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Client client(host, token);
        int offset = 767531241;
        int timeout = 0;
        std::vector<std::string> params;
        auto updates = client.GetUpdates(timeout, offset, params);
        for (auto el : updates){
//            std::cout << el.GetId() << " ";
//            std::cout << el.GetMessage().GetChatId() << " ";
            //std::cout << el.GetMessage().GetText() << std::endl;
//            std::cout << VectorToString(el.GetMessage().GetCommands());
//            std::cout << std::endl;
        }
        REQUIRE(true);
    } catch (const std::exception& exception){
        std::cout << exception.what();
        REQUIRE(false);
    }
}

//TEST_CASE("Send message OK", "[Bot]") {
//    try {
//        std::string host = "https://api.telegram.org";
//        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
//        Client client(host, token);
//        int chat_id = 208221580;
//        std::string text = "привет";
//        client.SendMessage(chat_id, text);
//        REQUIRE(true);
//    } catch (const std::exception& exception){
//        std::cout << exception.what();
//        REQUIRE(false);
//    }
//}
//
//
//TEST_CASE("Send sticker OK", "[Bot]") {
//    try {
//        std::string host = "https://api.telegram.org";
//        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
//        Client client(host, token);
//        int chat_id = 208221580;
//        std::string sticker = "CAADAgADPQADzhenCzhROkfYXf-NAg";
//        client.SendSticker(chat_id, sticker);
//        REQUIRE(true);
//    } catch (const std::exception& exception){
//        std::cout << exception.what();
//        REQUIRE(false);
//    }
//}
//
//TEST_CASE("Send gif OK", "[Bot]") {
//    try {
//        std::string host = "https://api.telegram.org";
//        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
//        Client client(host, token);
//        int chat_id = 208221580;
//        std::string file = "CgADAgADXAEAAo02aEm5JyPR4dY_ewI";
//        client.SendGif(chat_id, file);
//        REQUIRE(true);
//    } catch (const std::exception& exception){
//        std::cout << exception.what();
//        REQUIRE(false);
//    }
//}

//TEST_CASE("Scenario Single getUpdates and send messages") {
//    std::string host = "https://api.telegram.org";
//    std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
//    Client client(host, token);
//
//    try {
//        auto updates = client.GetUpdates();
//        auto message = updates[0].GetMessage();
//        client.SendMessage(message.GetChatId(), "Hi!");
//        message = updates[1].GetMessage();
//        client.SendMessage(message.GetChatId(), "Reply", message.GetId());
//        client.SendMessage(message.GetChatId(), "Reply", message.GetId());
//    } catch(...){}
//}

//TEST_CASE("Scenario Handle getUpdates offset") {
//    std::string host = "https://api.telegram.org";
//    std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
//    Client client(host, token);
//
//    try {
//        std::cout << "Handle getUpdates offset\n";
//        auto updates = client.GetUpdates(5);
//        REQUIRE(updates.size() == 4);
//        int max_update_id = updates[0].GetId();
//        for (auto& el : updates){
//            max_update_id = std::max(max_update_id, el.GetId());
//        }
//        updates = client.GetUpdates(5, max_update_id + 1);
//        REQUIRE(updates.size() == 0);
//        std::cout << "Send message\n";
//        updates = client.GetUpdates(15, max_update_id + 1);
//        REQUIRE(updates.size() == 1);
//
//    } catch(...){}
//}




