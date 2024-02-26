import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami

Kirigami.FormLayout {
    id: page
    property alias cfg_showUnsupported: showUnsupported.checked

    CheckBox {
        id: showUnsupported
        Kirigami.FormData.label: i18n("Modes:")
        text: i18n("Show unsupported modes")
    }
}