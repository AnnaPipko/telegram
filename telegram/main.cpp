#include "bot.h"

int main(int argc, char* argv[]) {
    try{
        std::string token = "509085195:AAHTWMhIjF9D9RLSzp2CDFtD_nzNaz4sj-g";
        Bot bot(token);
        bot.SkipCrash();
        bot.Run();
        return 0;
    } catch (const std::exception& exception){
        GetLogger().Error(exception.what());
    }
}
