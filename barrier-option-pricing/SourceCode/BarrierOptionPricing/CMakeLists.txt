cmake_minimum_required(VERSION 3.14)

project(BarrierOptionPricing CXX)
find_package(nlohmann_json REQUIRED)
set(SOURCE_FILES Main.cpp MonteCarloPricer.cpp MonteCarloRoutine.cpp)
set(HEADERS MonteCarloPricer.hpp MonteCarloRoutine.hpp)

add_executable(barrier_option_pricer ${SOURCE_FILES} ${HEADERS})

target_link_libraries(barrier_option_pricer models options parsers random_generation nlohmann_json::nlohmann_json ${LIBS})

pnl_add_postbuild(barrier_option_pricer)

