# bot

В этом задании вам нужно написать телеграм бота используя библиотеки POCO и jsoncpp.
Что именно будет делать этот бот не так важно. В задании будет оцениваться дизайн и
реализация клиента для общения с серверами телеграма.

## План

 1. Получите токен для работы с API.
 2. Потрогайте API из консоли, используя утилиту curl.
 3. Прочитайте документацию на релевантные классы из библиотек POCO и jsoncpp.
 4. Установите зависимости, убедитесь что все собирается и работает.
 5. Продумайте, какие классы понадобится написать. Какой у них будет интерфейс?
 6. Реализуйте запрос к api.telegram.org/getMe из C++
 7. Реализуйте цикл получения сообщений из /getUpdates
 8. Реализуйте возможность посылать сообщения из бота.
 9. Напишите логику бота.
 10. Допишите тесты, работающие с FakeServer.

## Знакомство с HTTP-API

HTTP протокол для общения с серверами описан
на [этой](https://core.telegram.org/bots/api) странице.

Чтобы воспользоваться HTTP-API
нужно [получить токен](https://core.telegram.org/bots#6-botfather).

После того как вы получили токен, нужно проверить что HTTP-API
работает. Для этого мы будем дёргать методы командой `curl`. Еще нам
понадобиться утилита `json_pp`.

 * [Метод](https://core.telegram.org/bots/api#getme) `/getMe`
   возвращает информацию о вашем боте. Его удобно использовать для
   проверки токена.

```
~/C/s/bot (master|…) $ curl https://api.telegram.org/bot<YOUR_TOKEN_HERE>/getMe
{"ok":true,"result":{"id":384306257,"is_bot":true,"first_name":"shad-cpp-test","username":"shad_shad_test_test_bot"}}
```

 * [Метод](https://core.telegram.org/bots/api#getting-updates)
   `/getUpdates` возвращает сообщения направленные вашему боту.
   
   - Чтобы этот метод вернул что-то осмысленное, нужно послать
   сообщение своему боту.
   - Обратите внимание на параметр `update_id`.
   - Почему команда возвращает те же самые сообщение при повторном
     запуске? Как сервера телеграмма понимают, что ваш бот обработал
     сообщения?
 
```
~/C/s/bot (master|…) $ curl -s https://api.telegram.org/bot<YOUR_TOKEN_HERE>/getUpdates | json_pp
{
   "ok" : true,
   "result" : [
      {
         "message" : {
            "date" : 1510493105,
            "entities" : [
               {
                  "length" : 6,
                  "offset" : 0,
                  "type" : "bot_command"
               }
            ],
            "from" : {
               "is_bot" : false,
               "username" : "darth_slon",
               "id" : 104519755,
               "first_name" : "Fedor"
            },
            "chat" : {
               "username" : "darth_slon",
               "type" : "private",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "text" : "/start",
            "message_id" : 1
         },
         "update_id" : 851793506
      }
   ]
}
```

 * [Метод](https://core.telegram.org/bots/api#sendmessage)
   `/sendMessage` позволяет послать сообщение.
 
```
curl -s -H "Content-Type: application/json" -X POST -d '{"chat_id": <CHAT_ID_FROM_GET_UPDATES>, "text": "Hi!"}' https://api.telegram.org/bot<YOUR_TOKEN_HERE>/sendMessage | json_pp
{
   "ok" : true,
   "result" : {
      "chat" : {
         "type" : "private",
         "id" : 104519755,
         "username" : "darth_slon",
         "first_name" : "Fedor"
      },
      "message_id" : 5,
      "from" : {
         "is_bot" : true,
         "first_name" : "shad-cpp-test",
         "id" : 384306257,
         "username" : "shad_shad_test_test_bot"
      },
      "date" : 1510500325,
      "text" : "Hi!"
   }
}
```

 * Запустите все три примера с флагом `-v`, чтобы посмотреть на сырые
   HTTP запросы и ответы.

## Требования к вашему Клиенту

 * Все методы клиента сильно типизированы. `Json::Value` нигде не торчит из интерфейса.

 * Ошибки HTTP-API транслируются в исключения.

 * Клиент созраняет текущий offset в файл и восстанавливает после перезапуска.

 * Клиент ничего не знает про логику вашего конкретного бота.
 
 * Константы можно конфигурировать. У всех параметров выставлены
   разумные значения по-умолчанию, так что для использования Клиента нужно
   предоставить только необходимые параметры.

## Что должен делать бот

 * Запрос `/random`. Бот посылает случайное число ответом на это сообщение.
 
 * Запрос `/weather`. Бот отвечает в чат `Winter Is Coming`.
 
 * Запрос `/styleguide`. Бот отвечает в чат смешной шуткой на тему code review.
 
 * Запрос `/stop`. Процесс бота завершается штатно.
 
 * Запрос `/crash`. Процесс бота завершается аварийно. Например выполняет `abort();`.

*Пожалуйста*, не добавляйте ботов в общий чат курса, чтобы избежать лишнего спама. 
Чтобы похвастаться своим ботом, можно использовать [специальный канал](https://t.me/joinchat/BjrYSxBxPwTTonfSoku7xQ)

### Обработка параметра offset и long poll

Вам нужно разобраться с тем, как работают параметры `offset` и `timeout` у метода `getUpdates`.
Во время работы бот должен сохранять своё состояние в файл, так чтобы после остановки или crash-а 
запросы пользователей не обрабатывались по второму разу.

Для того чтобы тестировать эту функциональность используйте запросы `/stop` и `/crash`, а так же 
супервизор для бедных:

```bash
$ while true; do ./bot; done
```

## Полезные классы из библиотеки POCO

 - `Poco::Net::HTTPClientSession`
 - `Poco::Net::HTTPSClientSession`
 - `Poco::Net::HTTPRequest`
 - `Poco::Net::HTTPResponse`
 - `Poco::URI`

## Полезные классы из библиотеки jsoncpp

 - `Json::Value`
 - `Json::CharReaderBuilder`
 - `Json::Writer`

## Установка зависимостей

 * На **Ubuntu**
   - 17.04 или 17.10: `sudo apt-get install libpoco-dev libjsoncpp-dev`
   - 16.04 в poco из репозитория есть баг, нужно установить нашу версию.
     - Удалите старую версию `sudo apt-get remove libpoco-dev libpocofoundation9v5`
     - Скачайте [пакет](https://drive.google.com/file/d/107AyXEoni9lMz7LzKu_60M6gRKi64Azx/view?usp=sharing)
     - Установите его `sudo dpkg -i libpoco-dev_1.8.0.1+shad16.04_amd64.deb && sudo ldconfig` 
     - Установите остальные зависимости `sudo apt-get install libssl-dev libjsoncpp-dev`
 * На **MacOS** `brew install --build-from-source poco jsoncpp` Собирать код нужно системным 
   clang-ом. gcc-7.2 использует другую версию стандартной библиотеки и не сможет
   слинковать ваш код с poco и jsoncpp
 * На **Windows** `TODO`

## Code Review

Чтобы получить оценку за эту задачу, нужно пройти Code Review. 
  1. Нужно послать код через submit.py в систему, как обычно.
  2. Нужно создать Merge Request через web интерфейс.
     - В качестве _Source Branch_ указать `submits/bot`
     - В качестве _Target Branch_ указать `initial`
     - В поле _reviewer_ поставить `prime@` 

## Автоматические тесты

Общаться с реальным сервером в тестах - не самая лучшая идея по многим
причинам. Вместо этого, мы даём вам класс `FakeServer` и просим
написать функциональные тесты, проверяющие набор сценариев.

`FakeServer` только прикидывается сервером и отвечает на все запросы
заранее заготовленными ответами.

Ваш код тестов должен выглядеть примерно так:

```c++
TEST_CASE("Checking getMe") {
    FakeServer fake("Single getMe")
    fake.Start();
       
    // Your code here. Doing requests to fake.GetUrl();
    
    fake.StopAndCheckExpectations();
}
```

Всего нужно проверить 4 сценария. Полное описание смотрите в 
[соседнем файле](TESTING_SCENARIOS.md).

# Бонусные баллы

 * `+100` используется идиома Pimpl. Заголовочный файл api не инклюдит хедеры из Poco.
 * `+200` клиент позволяет посылать картинки и стикеры. Бот поддерживает команды `/gif` и `/sticker`
 * `+100` бот пишет осмысленные логи.
 * `+200` бот запущен на виртуалке в digital ocean.
