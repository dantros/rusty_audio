cmake_minimum_required(VERSION 3.20)

project(rusty_audio_project CXX)

add_subdirectory("third_party/miniaudio_cmake")

file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")

add_library(rusty_audio
    "source/buffer_iterator.cpp"
    "source/buffer.cpp"
    "source/builder.cpp"
    "source/frame.cpp"
    "source/player_impl.cpp"
    "source/player.cpp"

    ${HEADERS}
)
set_property(TARGET rusty_audio PROPERTY CXX_STANDARD 20)
target_include_directories(rusty_audio
    PUBLIC "include"
    PRIVATE "third_party/miniaudio"
)
target_link_libraries(rusty_audio PRIVATE miniaudio)

set(MINIAUDIO_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/third_party/miniaudio")
get_directory_property(hasParent PARENT_DIRECTORY)
if(hasParent)
    set(MINIAUDIO_INCLUDE "${MINIAUDIO_INCLUDE}" PARENT_SCOPE)
endif()

option(RUSTY_AUDIO_BUILD_TESTS "Do you need tests?" OFF)
if (${RUSTY_AUDIO_BUILD_TESTS})
    add_subdirectory("third_party/Catch2")
    add_subdirectory("tests")
endif()

option(RUSTY_AUDIO_BUILD_EXAMPLES "Build RustyAudio examples?" OFF)
if (${RUSTY_AUDIO_BUILD_EXAMPLES})
    add_subdirectory("examples")
endif()

option(RUSTY_AUDIO_INSTALL "Do you whish to install RustyAudio static library?" ON)
if (${RUSTY_AUDIO_INSTALL})

    include(GNUInstallDirs)
    install(TARGETS rusty_audio
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            COMPONENT RustyAudio_Runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RustyAudio_Runtime
            NAMELINK_COMPONENT RustyAudio_Development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
            COMPONENT RustyAudio_Development
    )

    if (${RUSTY_AUDIO_BUILD_TESTS})
        install(TARGETS rusty_audio_tests
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT RustyAudioTests_Runtime
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT RustyAudioTests_Runtime
                NAMELINK_COMPONENT RustyAudioTests_Development
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT RustyAudioTests_Development
        )
    endif()

    if (${RUSTY_AUDIO_BUILD_EXAMPLES})
        install(TARGETS demo_buffer demo_builder demo_builder2
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                COMPONENT RustyAudioExamples_Runtime
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT RustyAudioExamples_Runtime
                NAMELINK_COMPONENT RustyAudioExamples_Development
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                COMPONENT RustyAudioExamples_Development
        )
    endif()

endif()