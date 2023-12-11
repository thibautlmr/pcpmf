cmake_minimum_required(VERSION 3.14)

project(Parsers CXX)
find_package(nlohmann_json REQUIRED)
set(SOURCE_FILES CoreBarrierOptionInputParser.cpp CoreBlackScholesModelInputParser.cpp json_helper.cpp)
set(HEADERS BarrierOptionInputParser.hpp BlackScholesModelInputParser.hpp CoreBarrierOptionInputParser.hpp CoreBlackScholesModelInputParser.hpp json_helper.hpp)

add_library(parsers ${SOURCE_FILES} ${HEADERS})
target_link_libraries(parsers
	nlohmann_json::nlohmann_json
)
