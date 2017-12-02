cmake_minimum_required(VERSION 3.7)
project(markotweet)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp markov/markov.cpp markov/markov.cpp twitter/twitter_client.cpp
        twitter/twitter_client.h dependencies/json/json.hpp dependencies/base64/base64.hpp
        dependencies/curl/curl.h dependencies/curl/curl.cpp markov/markov.h)
add_executable(markotweet ${SOURCE_FILES})
target_link_libraries(markotweet -lcurl)