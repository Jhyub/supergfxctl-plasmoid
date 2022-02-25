import QtQuick 2.15
import org.kde.plasma.configuration 2.0 as PlasmaConfig

PlasmaConfig.ConfigModel {
    PlasmaConfig.ConfigCategory {
        name: i18n("General")
        icon: "preferences-desktop-plasma"
        source: "configGeneral.qml"
    }
}