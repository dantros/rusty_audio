add_executable(hello_rusty_audio
    "hello_rusty_audio.cpp"
)
set_property(TARGET hello_rusty_audio PROPERTY CXX_STANDARD 20)
target_include_directories(hello_rusty_audio PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(hello_rusty_audio PRIVATE rusty_audio)

add_executable(demo_audio_buffer
    "demo_audio_buffer.cpp"
)
set_property(TARGET demo_audio_buffer PROPERTY CXX_STANDARD 20)
target_include_directories(demo_audio_buffer PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_audio_buffer PRIVATE rusty_audio)

add_executable(demo_sound_buffer
    "demo_sound_buffer.cpp"
)
set_property(TARGET demo_sound_buffer PROPERTY CXX_STANDARD 20)
target_include_directories(demo_sound_buffer PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_sound_buffer PRIVATE rusty_audio)