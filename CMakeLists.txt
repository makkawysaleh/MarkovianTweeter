cmake_minimum_required(VERSION 3.7)
project(markotweet)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp markov/markov_chain.cpp markov/markov_chain.h twitter/twitter_client.cpp
        twitter/twitter_client.h dependencies/json/json.hpp dependencies/base64/base64.hpp dependencies/base64/base64.h
        dependencies/curl/curl.h dependencies/curl/curl.cpp)
add_executable(markotweet ${SOURCE_FILES})
target_link_libraries(markotweet -lcurl)