add_compile_definitions(REQUIRED_UPSTREAM_VERSION="5.0.1" TRANSLATION_DOMAIN="plasma_applet_dev.jhyub.supergfxctl")

add_library(plasma_applet_supergfxctl MODULE SuperGfxCtl.cpp GfxMode.cpp GfxMode.h GfxAction.h GfxModeCandidate.cpp GfxModeCandidate.h GfxPower.h DaemonController.cpp DaemonController.h GfxPower.cpp GfxAction.cpp)

kcoreaddons_desktop_to_json(plasma_applet_supergfxctl package/metadata.desktop SERVICE_TYPES plasma-applet.desktop)

target_link_libraries(plasma_applet_supergfxctl Qt5::Gui Qt5::DBus Qt5::Qml KF5::Plasma KF5::I18n)

install(TARGETS plasma_applet_supergfxctl DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

plasma_install_package(package dev.jhyub.supergfxctl)
