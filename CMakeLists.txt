cmake_minimum_required(VERSION 3.16)

project(supergfxctl-plasmoid)

set(QT_MIN_VERSION "6.4.0")
set(KF6_MIN_VERSION "5.93.0")

find_package(ECM 1.4.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include(FindGettext)

find_package(KF6 REQUIRED COMPONENTS Plasma I18n)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Qml Gui Core DBus)

add_subdirectory(src)

add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/translation/install
        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/translation/build.sh
        COMMAND env TRANSLATION_PATH="${CMAKE_CURRENT_LIST_DIR}/translation" bash "${CMAKE_CURRENT_LIST_DIR}/translation/build.sh"
        )
add_custom_target(BuildTranslation ALL DEPENDS ${CMAKE_CURRENT_LIST_DIR}/translation/install)
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/icons/status
        DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/scalable
        FILES_MATCHING PATTERN "*.svg"
        )
install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/translation/install/ DESTINATION ${CMAKE_INSTALL_PREFIX})

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
