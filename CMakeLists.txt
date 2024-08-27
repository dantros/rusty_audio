cmake_minimum_required(VERSION 3.20)

project(rusty_audio_project CXX)

file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")

add_library(rusty_audio
    "source/rusty_audio.cpp"
    ${HEADERS}
)
set_property(TARGET rusty_audio PROPERTY CXX_STANDARD 20)
target_include_directories(rusty_audio PRIVATE
    "include"
    "third_party/miniaudio"
)

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

    option(RUSTY_AUDIO_BUILD_EXAMPLES "Build RustyAudio examples?" OFF)
    if (${RUSTY_AUDIO_BUILD_EXAMPLES})
        add_subdirectory("examples")

        if (${RUSTY_AUDIO_BUILD_EXAMPLES})
            install(TARGETS hello_nothofagus
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
endif()