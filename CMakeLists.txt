cmake_minimum_required(VERSION 3.15)

include(FetchContent)

FetchContent_Declare(JUCE
        GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
        GIT_TAG        7.0.2
        SOURCE_DIR     ${CMAKE_SOURCE_DIR}/JUCE
)

FetchContent_MakeAvailable(JUCE)

set(PROJECT_NAME "PngToFilmstrip")

project(${PROJECT_NAME} VERSION 1.0.11)

###########################################
#Enable this to build for Apple Intel based
#set(CMAKE_OSX_ARCHITECTURES "x86_64")
###########################################

juce_add_gui_app(${PROJECT_NAME}
    # VERSION ...
    ICON_BIG "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Assets/icon.png"
    PRODUCT_NAME "Png to Filmstrip Converter")

set(SOURCE_FILES
        Sources/Main.cpp
        Sources/MainComponent.cpp
        Sources/MainComponent.h
        Sources/CreateFilmstripThread.h
        )

target_sources(${PROJECT_NAME}
    PRIVATE
        ${SOURCE_FILES}
        )

target_compile_definitions(${PROJECT_NAME}
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

 juce_add_binary_data(GuiAppData SOURCES
         Sources/Assets/juqa_logo.png
         Sources/Assets/Search_Logo.png
         )

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        GuiAppData # If we'd created a binary data target, we'd link to it here
        juce::juce_gui_basics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)

#*************************
# Code For Catch2 Testing
#*************************

enable_testing()

Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests
        Tests/PngToFilmstripTest.cpp
        ${SOURCE_FILES}
        )

target_compile_definitions(tests
        PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:${PROJECT_NAME},JUCE_VERSION>")

target_link_libraries(tests PRIVATE  Catch2::Catch2WithMain juce::juce_gui_basics GuiAppData)

#include(${Catch2_SOURCE_DIR}/extras/Catch.cmake)
#catch_discover_tests(tests)