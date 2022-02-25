import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import org.kde.kirigami 2.4 as Kirigami

Kirigami.FormLayout {
    id: page
    property alias cfg_showUnsupported: showUnsupported.checked

    CheckBox {
        id: showUnsupported
        Kirigami.FormData.label: i18n("Modes:")
        text: i18n("Show unsupported modes")
    }
}