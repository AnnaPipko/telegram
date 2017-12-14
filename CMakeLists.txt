cmake_minimum_required(VERSION 3.5)
project(telegram)

include(../common.cmake)

set(SOLUTION_SRC)
set(SOLUTION_TEST_SRC)
if (TEST_SOLUTION)
  include_directories(../private/bot)
  set(SOLUTION_SRC ../private/bot/telegram/api.cpp telegram/client.cpp telegram/client.h)
  set(SOLUTION_TEST_SRC ../private/bot/test/test_api.cpp)
endif()

if (UNIX AND NOT APPLE)
  include_directories(/usr/include/jsoncpp)
elseif (APPLE)
  link_directories(/usr/local/lib)
  link_directories(/usr/local/opt/openssl/lib)

  include_directories(/usr/local/include)
  include_directories(/usr/local/opt/openssl/include)
endif()

add_library(telegram
  ${SOLUTION_SRC}
  telegram/fake.cpp
  telegram/fake_data.cpp
        telegram/bot.cpp
        telegram/client.cpp
        telegram/exceptions.cpp telegram/logger.cpp telegram/logger.h telegram/message_handler.cpp telegram/message_handler.h)

target_link_libraries(telegram
  PocoNet
  PocoNetSSL
  PocoFoundation
  jsoncpp)

if (TEST_SOLUTION)
  add_executable(bot
    ../private/bot/telegram/main.cpp)
else()
  add_executable(bot
    telegram/main.cpp)
endif()

target_link_libraries(bot
  telegram)

add_executable(fake
  telegram/fake_main.cpp)

target_link_libraries(fake
  telegram)

# Add test files here
add_executable(test_telegram
  ${SOLUTION_TEST_SRC}
        test/test_client.cpp
        test/test_scenarios.cpp
  ../commons/catch_main.cpp )

target_link_libraries(test_telegram
  telegram)
