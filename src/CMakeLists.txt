add_definitions(-DTRANSLATION_DOMAIN=\"dev.jhyub.supergfxctl\")

add_library(plasma_applet_supergfxctl MODULE supergfxctl.cpp)

kcoreaddons_desktop_to_json(plasma_applet_supergfxctl package/metadata.desktop SERVICE_TYPES plasma-applet.desktop)

target_link_libraries(plasma_applet_supergfxctl
                      Qt5::Gui
                      KF5::Plasma
                      KF5::I18n)


install(TARGETS plasma_applet_supergfxctl DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/applets)

plasma_install_package(package dev.jhyub.supergfxctl)
