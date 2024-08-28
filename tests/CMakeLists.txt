
add_executable(rusty_audio_tests
    "sound_buffer_tests.cpp"
)
set_property(TARGET rusty_audio_tests PROPERTY CXX_STANDARD 20)
target_include_directories(rusty_audio_tests PRIVATE
    ${RUSTY_AUDIO_INCLUDE}
    ${GOOGLETEST_INCLUDE}
)
target_link_libraries(rusty_audio_tests PRIVATE
    rusty_audio
    GTest::gtest_main
)