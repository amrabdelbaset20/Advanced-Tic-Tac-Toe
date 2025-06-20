# tests/CMakeLists.txt
# Version: 4.0 (Manual Subdirectory)

# --- Core Logic Tests ---
add_executable(CoreTests
    core/test_game_logic.cpp
    ../src/core/src/Board.cpp
    ../src/core/src/Game.cpp
    ../src/core/src/Player.cpp
)

# Link against the Google Test libraries built from our local subdirectory
target_link_libraries(CoreTests PRIVATE gtest gtest_main)

# Include the headers from our core project
target_include_directories(CoreTests PUBLIC ../src/core/include)
include(GoogleTest)
gtest_add_tests(TARGET CoreTests)


# --- AI Logic Tests ---
add_executable(AITests
    ai/test_ai_logic.cpp
    ../src/ai/src/AI.cpp
    ../src/core/src/Board.cpp
)

# Link against the Google Test libraries
target_link_libraries(AITests PRIVATE gtest gtest_main)

# Include headers from our AI and Core projects
target_include_directories(AITests PUBLIC ../src/ai/include ../src/core/include)
gtest_add_tests(TARGET AITests)