add_executable(demo_buffer
    "demo_buffer.cpp"
)
set_property(TARGET demo_buffer PROPERTY CXX_STANDARD 20)
target_link_libraries(demo_buffer PRIVATE rusty_audio)

add_executable(demo_builder
    "demo_builder.cpp"
)
set_property(TARGET demo_builder PROPERTY CXX_STANDARD 20)
target_link_libraries(demo_builder PRIVATE rusty_audio)

add_executable(demo_builder2
    "demo_builder2.cpp"
)
set_property(TARGET demo_builder2 PROPERTY CXX_STANDARD 20)
target_link_libraries(demo_builder2 PRIVATE rusty_audio)

add_executable(demo_decode
    "demo_decode.cpp"
)
set_property(TARGET demo_decode PROPERTY CXX_STANDARD 20)
target_link_libraries(demo_decode PRIVATE rusty_audio)

# demo_miniaudio directly uses miniaudio APIs, so it is only available
# when the MINIAUDIO play backend is selected.
if(NOT RUSTY_AUDIO_PLAY_BACKEND STREQUAL "SDL3")
    add_executable(demo_miniaudio
        "demo_miniaudio.cpp"
    )
    set_property(TARGET demo_miniaudio PROPERTY CXX_STANDARD 20)
    target_include_directories(demo_miniaudio PRIVATE ${MINIAUDIO_INCLUDE})
    target_link_libraries(demo_miniaudio PRIVATE rusty_audio)
endif()
