if(EXISTS "/Users/plut/CLionProject/game/life_test/cmake-build-debug/game_tests[1]_tests.cmake")
  include("/Users/plut/CLionProject/game/life_test/cmake-build-debug/game_tests[1]_tests.cmake")
else()
  add_test(game_tests_NOT_BUILT game_tests_NOT_BUILT)
endif()