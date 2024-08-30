add_executable(demo_sound_buffer
    "demo_sound_buffer.cpp"
)
set_property(TARGET demo_sound_buffer PROPERTY CXX_STANDARD 20)
target_include_directories(demo_sound_buffer PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_sound_buffer PRIVATE rusty_audio)

add_executable(demo_sound_builder
    "demo_sound_builder.cpp"
)
set_property(TARGET demo_sound_builder PROPERTY CXX_STANDARD 20)
target_include_directories(demo_sound_builder PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_sound_builder PRIVATE rusty_audio)

add_executable(demo_miniaudio
    "demo_miniaudio.cpp"
)
set_property(TARGET demo_miniaudio PROPERTY CXX_STANDARD 20)
target_include_directories(demo_miniaudio PRIVATE ${RUSTY_AUDIO_INCLUDE} ${MINIAUDIO_INCLUDE})
target_link_libraries(demo_miniaudio PRIVATE rusty_audio)