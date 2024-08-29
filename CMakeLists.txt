cmake_minimum_required(VERSION 3.20)

project(rusty_audio_project CXX)

add_subdirectory("third_party/miniaudio_cmake")

file(GLOB_RECURSE HEADERS "source/*.h" "include/*.h")

add_library(rusty_audio
    "source/rusty_audio.cpp"
    "source/sound_manager_impl.cpp"
    "source/audio_buffer.cpp"
    "source/audio_buffer_impl.cpp"

    "source/sound_frame.cpp"
    "source/sound_buffer_iterator.cpp"
    "source/sound_buffer.cpp"
    "source/sound_player.cpp"
    "source/sound_player_impl.cpp"

    ${HEADERS}
)
set_property(TARGET rusty_audio PROPERTY CXX_STANDARD 20)
target_include_directories(rusty_audio PRIVATE
    "include"
    "third_party/miniaudio"
)
target_link_libraries(rusty_audio PRIVATE miniaudio)

set(RUSTY_AUDIO_INCLUDE
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/third_party/miniaudio" #TODO remove this
    #PARENT_SCOPE
)

# TODO add options so this is not the default.
#[[option(BUILD_GMOCK "Builds the googlemock subproject" OFF)
option(INSTALL_GTEST "Enable installation of googletest. (Projects embedding googletest may want to turn this OFF.)" OFF)
option(GTEST_HAS_ABSL "Use Abseil and RE2. Requires Abseil and RE2 to be separately added to the build." OFF)
add_subdirectory("third_party/googletest")
set(GOOGLETEST_INCLUDE "third_party/googletest/googletest/include")
add_subdirectory("tests")
#]]

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

        #[[
        if (${RUSTY_AUDIO_BUILD_EXAMPLES})
            install(TARGETS demo_sound_buffer
                RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
                    COMPONENT RustyAudioExamples_Runtime
                LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
                    COMPONENT RustyAudioExamples_Runtime
                    NAMELINK_COMPONENT RustyAudioExamples_Development
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
                    COMPONENT RustyAudioExamples_Development
            )
        endif()
        #]]
    endif()
endif()