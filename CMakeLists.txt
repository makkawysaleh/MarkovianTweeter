cmake_minimum_required(VERSION 3.7)
project(markotweet)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp markov/markov_chain.cpp markov/markov_chain.h dependencies/json/json.hpp)
add_executable(Geemail ${SOURCE_FILES} twitter/twitter_client.cpp twitter/twitter_client.h)
target_link_libraries(Geemail -lcurl)