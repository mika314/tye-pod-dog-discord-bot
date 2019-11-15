cmake_minimum_required(VERSION 3.7)
project(echo_bot)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/discordpp)          # discordpp
add_subdirectory(lib/rest-beast)         # discordpp-rest-beast
add_subdirectory(lib/websocket-beast)    # discordpp-websocket-beast

set(SOURCE_FILES
        base_redis.cpp
        bot.cpp
        direction.cpp
        gen_uuid.cpp
        guild.cpp
        hero.cpp
        main.cc
        player.cpp
        read_token.cpp
        redis_con.cpp
        room.cpp
        world.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(Boost REQUIRED system filesystem)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)

INCLUDE_DIRECTORIES(
        ${Boost_INCLUDE_DIRS}
        ${discordpp_SOURCE_DIR}
        ${discordpp-rest-beast_SOURCE_DIR}
        ${discordpp-websocket-beast_SOURCE_DIR}
        ${json_SOURCE_DIR}
        ${OPENSSL_INCLUDE_DIR}
)

TARGET_LINK_LIBRARIES(
        ${PROJECT_NAME}
        ${Boost_LIBRARIES}
        discordpp
        discordpp-rest-beast
        discordpp-websocket-beast
        Threads::Threads
        crypto
        ssl
        hiredis
        uuid
)

set(CMAKE_BUILD_TYPE Debug)
