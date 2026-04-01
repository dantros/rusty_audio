
add_executable(rusty_audio_tests
    "sound_buffer_tests.cpp"
)
set_property(TARGET rusty_audio_tests PROPERTY CXX_STANDARD 20)
target_link_libraries(rusty_audio_tests PRIVATE
    rusty_audio
    Catch2::Catch2WithMain
)