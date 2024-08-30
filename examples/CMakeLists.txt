add_executable(demo_buffer
    "demo_buffer.cpp"
)
set_property(TARGET demo_buffer PROPERTY CXX_STANDARD 20)
target_include_directories(demo_buffer PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_buffer PRIVATE rusty_audio)

add_executable(demo_builder
    "demo_builder.cpp"
)
set_property(TARGET demo_builder PROPERTY CXX_STANDARD 20)
target_include_directories(demo_builder PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_builder PRIVATE rusty_audio)

add_executable(demo_builder2
    "demo_builder2.cpp"
)
set_property(TARGET demo_builder2 PROPERTY CXX_STANDARD 20)
target_include_directories(demo_builder2 PRIVATE ${RUSTY_AUDIO_INCLUDE})
target_link_libraries(demo_builder2 PRIVATE rusty_audio)

add_executable(demo_miniaudio
    "demo_miniaudio.cpp"
)
set_property(TARGET demo_miniaudio PROPERTY CXX_STANDARD 20)
target_include_directories(demo_miniaudio PRIVATE ${RUSTY_AUDIO_INCLUDE} ${MINIAUDIO_INCLUDE})
target_link_libraries(demo_miniaudio PRIVATE rusty_audio)