#include "fake_data.h"

std::string FakeData::GetMeJson = R"(
{
   "ok" : true,
   "result" : {
      "username" : "test_bot",
      "is_bot" : true,
      "first_name" : "Test Bot",
      "id" : 1234567
   }
})" + 1;

std::string FakeData::GetMeErrorJson = R"(
{
   "description" : "Unauthorized",
   "ok" : false,
   "error_code" : 401
})" + 1;

std::string FakeData::GetUpdatesFourMessagesJson = R"(
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
})" + 1;

std::string FakeData::SendMessageHiJson = R"(
{
   "ok" : true,
   "result" : {
      "date" : 1510522717,
      "message_id" : 15,
      "chat" : {
         "username" : "darth_slon",
         "first_name" : "Fedor",
         "type" : "private",
         "id" : 104519755
      },
      "from" : {
         "id" : 384306257,
         "is_bot" : true,
         "username" : "test_bot",
         "first_name" : "Test Bot"
      },
      "text" : "Hi!"
   }
})" + 1;

std::string FakeData::SendMessageReplyJson = R"(
{
   "result" : {
      "text" : "Reply",
      "reply_to_message" : {
         "date" : 1510493105,
         "chat" : {
            "id" : 104519755,
            "username" : "darth_slon",
            "type" : "private",
            "first_name" : "Fedor"
         },
         "from" : {
            "id" : 104519755,
            "username" : "darth_slon",
            "is_bot" : false,
            "first_name" : "Fedor",
            "language_code" : "en-US"
         },
         "text" : "/end",
         "message_id" : 2,
         "entities" : [
            {
               "length" : 6,
               "type" : "bot_command",
               "offset" : 0
            }
         ]
      },
      "message_id" : 16,
      "chat" : {
         "type" : "private",
         "username" : "darth_slon",
         "id" : 104519755,
         "first_name" : "Fedor"
      },
      "date" : 1510523244,
      "from" : {
         "username" : "test_bot",
         "id" : 384306257,
         "first_name" : "Test Bot",
         "is_bot" : true
      }
   },
   "ok" : true
})" + 1;

std::string FakeData::GetUpdatesTwoMessages = R"(
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
})" + 1;

std::string FakeData::GetUpdatesZeroMessages = R"(
{
   "result" : [ ],
   "ok" : true
})" + 1;

std::string FakeData::GetupdatesOneMessage = R"(
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
})" + 1;
