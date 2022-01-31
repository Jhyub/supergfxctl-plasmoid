cmake_minimum_required(VERSION 3.16)

project(plasma-supergfxctl)

find_package(ECM 1.4.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

add_compile_definitions(REQUIRED_UPSTREAM_VERSION="4.0.1")

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)

find_package(KF5 REQUIRED COMPONENTS
        Plasma
        I18n
        )

find_package(Qt5 CONFIG REQUIRED COMPONENTS
        Quick
        Core
        DBus
        )

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/icons/status DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable FILES_MATCHING PATTERN "*.svg")
