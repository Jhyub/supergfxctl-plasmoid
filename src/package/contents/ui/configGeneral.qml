import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import org.kde.kirigami as Kirigami
import org.kde.plasma.components as PlasmaComponents

Kirigami.FormLayout {
    id: page
    property alias cfg_showUnsupported: showUnsupported.checked
    property alias cfg_statusActiveOnDischargeDGPUActive: statusActiveOnDischargeDGPUActive.currentIndex
    property alias cfg_statusActiveOnDischargeDGPUInactive: statusActiveOnDischargeDGPUInactive.currentIndex
    property alias cfg_statusActiveOnChargeDGPUActive: statusActiveOnChargeDGPUActive.currentIndex
    property alias cfg_statusActiveOnChargeDGPUInactive: statusActiveOnChargeDGPUInactive.currentIndex

    CheckBox {
        id: showUnsupported
        Kirigami.FormData.label: i18n("Modes:")
        text: i18n("Show unsupported modes")
    }

    Kirigami.Separator {
        Kirigami.FormData.isSection: true
        Kirigami.FormData.label: "Plasmoid Status"
    }

    ComboBox {
        id: statusActiveOnDischargeDGPUActive
        Kirigami.FormData.label: i18n("dGPU active on battery:")
        model: [i18n("Active"), i18n("Passive")]
    }

    ComboBox {
        id: statusActiveOnDischargeDGPUInactive
        Kirigami.FormData.label: i18n("dGPU inactive on battery:")
        model: [i18n("Active"), i18n("Passive")]
    }

    ComboBox {
        id: statusActiveOnChargeDGPUActive
        Kirigami.FormData.label: i18n("dGPU active on AC:")
        model: [i18n("Active"), i18n("Passive")]
    }

    ComboBox {
        id: statusActiveOnChargeDGPUInactive
        Kirigami.FormData.label: i18n("dGPU inactive on AC:")
        model: [i18n("Active"), i18n("Passive")]
    }

    PlasmaComponents.Label {
        text: i18n("These options will work only when the plasmoid visibility is set to 'Shown when relevant'")
        Kirigami.FormData.isSection: true // For the sake of prettiness
        font.italic: true
        Layout.preferredWidth: Kirigami.Units.gridUnit * 8
        wrapMode: Text.WordWrap
        horizontalAlignment: Text.AlignHCenter
    }
}