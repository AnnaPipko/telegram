## Сценарий `Single getMe`

 1. Клиент делает единственный вызов `getMe`.
 2. Сервер возвращает ответ с `ok == true`.
 
```commandline
~/C/s/b/b/asan (master|✔ ) $ curl http://localhost:8080/bot123/getMe
{
   "ok" : true,
   "result" : {
      "username" : "test_bot",
      "is_bot" : true,
      "first_name" : "Test Bot",
      "id" : 1234567
   }
}
```

## Сценарий `getMe error handling`

 1. Клиент делает вызов `getMe`.
 2. Сервер отвечает с HTTP статусом 500.
 3. Клиент делает вызов `getMe`.
 4. Сервер отвечает со статусом 401 и ok == false.

```commandline
~/C/s/b/b/asan (master|✔ ) $ curl http://localhost:8080/bot123/getMe
Internal server error
~/C/s/b/b/asan (master|✔ ) $ curl http://localhost:8080/bot123/getMe
{
   "description" : "Unauthorized",
   "ok" : false,
   "error_code" : 401
}
```

## Сценарий `Single getUpdates and send messages`

 1. Клиент делает единственный вызов `getUpdates`
 2. Сервер присылает 2 приватных сообщения, одно сообщение о
    добавлении в группу и одно сообщение из группы.
 3. Клиент пишет `Hi!` в чат первого сообщения.
 4. Клиент посылает 2 ответа `Reply` на второе сообщение.
 5. Клиент игнорирует третье сообщение.

```commandline
~/C/s/b/b/asan (master|✔ ) $ curl -v http://localhost:8080/bot123/getUpdates
{
   "result" : [
      {
         "message" : {
            "entities" : [
               {
                  "offset" : 0,
                  "type" : "bot_command",
                  "length" : 6
               }
            ],
            "chat" : {
               "type" : "private",
               "username" : "darth_slon",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "date" : 1510493105,
            "text" : "/start",
            "message_id" : 1,
            "from" : {
               "is_bot" : false,
               "first_name" : "Fedor",
               "id" : 104519755,
               "username" : "darth_slon"
            }
         },
         "update_id" : 851793506
      },
      {
         "message" : {
            "entities" : [
               {
                  "offset" : 0,
                  "type" : "bot_command",
                  "length" : 6
               }
            ],
            "chat" : {
               "type" : "private",
               "username" : "darth_slon",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "date" : 1510493105,
            "text" : "/end",
            "message_id" : 2,
            "from" : {
               "is_bot" : false,
               "first_name" : "Fedor",
               "id" : 104519755,
               "username" : "darth_slon"
            }
         },
         "update_id" : 851793507
      },
      {
         "message" : {
            "from" : {
               "is_bot" : false,
               "username" : "darth_slon",
               "language_code" : "en-US",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "message_id" : 10,
            "date" : 1510519971,
            "chat" : {
               "id" : -274574250,
               "type" : "group",
               "title" : "bottest",
               "all_members_are_administrators" : true
            },
            "group_chat_created" : true
         },
         "update_id" : 851793507
      },
      {
         "message" : {
            "date" : 1510520023,
            "text" : "/1234",
            "chat" : {
               "all_members_are_administrators" : true,
               "title" : "bottest",
               "type" : "group",
               "id" : -274574250
            },
            "from" : {
               "is_bot" : false,
               "username" : "darth_slon",
               "language_code" : "en-US",
               "id" : 104519755,
               "first_name" : "Fedor"
            },
            "message_id" : 11,
            "entities" : [
               {
                  "offset" : 0,
                  "length" : 5,
                  "type" : "bot_command"
               }
            ]
         },
         "update_id" : 851793508
      }
   ],
   "ok" : true
}
~/C/s/b/b/asan (master|✔ ) $ curl -s -H "Content-Type: application/json" -X POST -d '{"chat_id": 104519755, "text": "Hi!"}' http://localhost:8080/bot123/sendMessage | json_pp
{
   "result" : {
      "message_id" : 15,
      "text" : "Hi!",
      "chat" : {
         "username" : "darth_slon",
         "type" : "private",
         "id" : 104519755,
         "first_name" : "Fedor"
      },
      "date" : 1510522717,
      "from" : {
         "username" : "test_bot",
         "is_bot" : true,
         "id" : 384306257,
         "first_name" : "Test Bot"
      }
   },
   "ok" : true
}
~/C/s/b/b/asan (master|✔ ) $ curl -s -H "Content-Type: application/json" -X POST -d '{"chat_id": 104519755, "text": "Reply", "reply_to_message_id": 2}' http://localhost:8080/bot123/sendMessage | json_pp
{
   "result" : {
      "date" : 1510523244,
      "chat" : {
         "username" : "darth_slon",
         "type" : "private",
         "first_name" : "Fedor",
         "id" : 104519755
      },
      "from" : {
         "username" : "test_bot",
         "first_name" : "Test Bot",
         "id" : 384306257,
         "is_bot" : true
      },
      "text" : "Reply",
      "message_id" : 16,
      "reply_to_message" : {
         "chat" : {
            "id" : 104519755,
            "first_name" : "Fedor",
            "type" : "private",
            "username" : "darth_slon"
         },
         "date" : 1510493105,
         "entities" : [
            {
               "offset" : 0,
               "type" : "bot_command",
               "length" : 6
            }
         ],
         "message_id" : 2,
         "text" : "/end",
         "from" : {
            "username" : "darth_slon",
            "language_code" : "en-US",
            "first_name" : "Fedor",
            "id" : 104519755,
            "is_bot" : false
         }
      }
   },
   "ok" : true
}
~/C/s/b/b/asan (master|✔ ) $ curl -s -H "Content-Type: application/json" -X POST -d '{"chat_id": 104519755, "text": "Reply", "reply_to_message_id": 2}' http://localhost:8080/bot123/sendMessage | json_pp
```

## Сценарий `Handle getUpdates offset`

 1. Клиент вызывает метод `getUpdates` без параметра `offset` с `timeout == 5`.
 2. Сервер присылает 2 сообщения.
 3. Клиент вызывает метод `getUpdates` с параметром `offset == max(update_id) + 1` и `timeout == 5`.
 4. Сервер присылает 0 сообщений.
 3. Клиент вызывает метод `getUpdates` с параметром `offset == max(update_id) + 1` и `timeout == 5`.
 4. Сервер присылает 1 сообщение.

```commandline
~/C/s/bot (master|…) $ curl http://localhost:8080/bot123/getUpdates
{
   "result" : [
      {
         "message" : {
            "entities" : [
               {
                  "offset" : 0,
                  "type" : "bot_command",
                  "length" : 6
               }
            ],
            "chat" : {
               "type" : "private",
               "username" : "darth_slon",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "date" : 1510493105,
            "text" : "/start",
            "message_id" : 1,
            "from" : {
               "is_bot" : false,
               "first_name" : "Fedor",
               "id" : 104519755,
               "username" : "darth_slon"
            }
         },
         "update_id" : 851793506
      },
      {
         "message" : {
            "entities" : [
               {
                  "offset" : 0,
                  "type" : "bot_command",
                  "length" : 6
               }
            ],
            "chat" : {
               "type" : "private",
               "username" : "darth_slon",
               "first_name" : "Fedor",
               "id" : 104519755
            },
            "date" : 1510493105,
            "text" : "/end",
            "message_id" : 2,
            "from" : {
               "is_bot" : false,
               "first_name" : "Fedor",
               "id" : 104519755,
               "username" : "darth_slon"
            }
         },
         "update_id" : 851793507
      }
   ],
   "ok" : true
}                                                                                                                                                                                                                   ~/C/s/bot (master|…) $ curl 'http://localhost:8080/bot123/getUpdates?offset=851793508&timeout=5'
{
   "result" : [ ],
   "ok" : true
}                                                                                                                                                                                                                   ~/C/s/bot (master|…) $ curl 'http://localhost:8080/bot123/getUpdates?offset=851793508&timeout=5'
{
   "result" : [
      {
         "message" : {
            "date" : 1510520023,
            "text" : "/1234",
            "chat" : {
               "all_members_are_administrators" : true,
               "title" : "bottest",
               "type" : "group",
               "id" : -274574250
            },
            "from" : {
               "is_bot" : false,
               "username" : "darth_slon",
               "language_code" : "en-US",
               "id" : 104519755,
               "first_name" : "Fedor"
            },
            "message_id" : 11,
            "entities" : [
               {
                  "offset" : 0,
                  "length" : 5,
                  "type" : "bot_command"
               }
            ]
         },
         "update_id" : 851793508
      }
   ],
   "ok" : true
}
```