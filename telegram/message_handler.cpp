#include "message_handler.h"
#include "client.h"
#include "exceptions.h"

#include <cstdlib>
#include <codecvt>
#include <locale>


void MessageHandler::Process(const Update &update, std::shared_ptr<Client> client) {
    if (update.GetType() != UpdateType::UNDEFINED){
        auto message = update.GetMessage();
        auto commands = message.GetCommands();
        if (commands.empty()){
            auto text = message.GetText();
            if (!text.empty()){
                auto new_text = PerformText(text);
                client->SendMessage(message.GetChatId(), new_text);
            }
            return;
        }
        for (const auto& command : commands){
            if (command == "/random"){
                client->SendMessage(message.GetChatId(), std::to_string(std::rand()));
                return;
            }
            if (command == "/weather"){
                client->SendMessage(message.GetChatId(), "Winter is coming");
                return;
            }
            if (command == "/styleguide"){
                std::string joke("Тут может быть ваша шутка.");
                //client->SendMessage(message.GetChatId(), joke);
                client->SendPhoto(message.GetChatId(), "AgADAgADe6gxG-KFkElG8HeaOgvG1mTkDw4ABG19V0mtPYZgmPYDAAEC");
                return;
            }
            if (command == "/stop"){
                throw StopBotError("Stop");
            }
            if (command == "/crash"){
                abort();
                //throw std::runtime_error("Crash");
            }
            if (command == "/gif"){
                client->SendGif(message.GetChatId(), "CgADAgADXAEAAo02aEm5JyPR4dY_ewI");
                return;
            }
            if (command == "/sticker"){
                client->SendSticker(message.GetChatId(), "CAADAgADPQADzhenCzhROkfYXf-NAg");
                return;
            }
            std::string about = "Запрос /random. Бот посылает случайное число ответом на это сообщение.\n"
                    "Запрос /weather. Бот отвечает в чат Winter Is Coming.\n"
                    "Запрос /styleguide. Бот отвечает в чат смешной шуткой на тему code review (почти).\n"
                    "Запрос /sticker. Бот отправляет стикер.\n"
                    "Запрос /gif. Бот отправляет картинку.\n"
                    "Запрос /stop. Процесс бота завершается штатно.\n"
                    "Запрос /crash. Процесс бота завершается аварийно.\n";
            client->SendMessage(message.GetChatId(), about);
        }
    }
}

bool IsLatin(const std::string& text){
    std::wstring latin(L"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM");
    std::wstring cyrillic(L"йцукенгшщзхъфывапролджэячсмитьбюЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ");
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wtext = conv.from_bytes(text);
    for (auto letter : wtext){
        if (latin.find(letter) != std::string::npos){
            return true;
        }
        if (cyrillic.find(letter) != std::string::npos){
            return false;
        }
    }
    return false;
}

std::string PerformText(const std::string& text){
    std::wstring latin(L"qwertyuiop[]asdfghjkl;'zxcvbnm,./QWERTYUIOP{}ASDFGHJKL:\"ZXCVBNM<>?");
    std::wstring cyrillic(L"йцукенгшщзхъфывапролджэячсмитьбю.ЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ,");
    std::wstring result;
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::wstring wtext = conv.from_bytes(text);
    if (IsLatin(text)){
        for (auto letter : wtext){
            auto find = latin.find(letter);
            if (find != std::string::npos) {
                result += cyrillic[find];
            } else {
                result += letter;
            }
        }
    } else {
        for (auto letter : wtext){
            auto find = cyrillic.find(letter);
            if (find != std::string::npos) {
                result += latin[find];
            } else {
                result += letter;
            }
        }
    }
    std::string conv_result = conv.to_bytes(result);
    return conv_result;
}
