add_executable(hello_rusty_audio
    "hello_rusty_audio.cpp"
)
set_property(TARGET hello_rusty_audio PROPERTY CXX_STANDARD 20)
target_include_directories(hello_rusty_audio PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(hello_rusty_audio PRIVATE rusty_audio)