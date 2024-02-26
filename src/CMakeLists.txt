add_compile_definitions(REQUIRED_UPSTREAM_VERSION="5.1.0" TRANSLATION_DOMAIN="plasma_applet_dev.jhyub.supergfxctl")

add_library(dev.jhyub.supergfxctl MODULE SuperGfxCtl.cpp GfxMode.cpp GfxMode.h GfxAction.h GfxModeCandidate.cpp GfxModeCandidate.h GfxPower.h DaemonController.cpp DaemonController.h GfxPower.cpp GfxAction.cpp)

target_link_libraries(dev.jhyub.supergfxctl Qt6::Gui Qt6::DBus Qt6::Qml KF6::I18n)

install(TARGETS dev.jhyub.supergfxctl DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

plasma_install_package(package dev.jhyub.supergfxctl)
