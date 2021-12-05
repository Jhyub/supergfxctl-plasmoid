/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: MPL-2.0
*/

import QtQuick 2.1
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.components 3.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item {
    Plasmoid.icon: plasmoid.nativeInterface.iconName
    Plasmoid.toolTipSubText: i18n("Graphics mode: %1, dGPU power: %2", plasmoid.nativeInterface.vendorName, plasmoid.nativeInterface.powerName)
    Plasmoid.fullRepresentation: PlasmaComponents.Page {
        id: dialog
        header: PlasmaExtras.PlasmoidHeading {
            RowLayout {
                height: label.implicitBackgroundHeight
                Image {
                    height: parent.height
                    Layout.fillHeight: true
                    fillMode: Image.PreserveAspectFit
                    source: "../images/dgpu-" + plasmoid.nativeInterface.powerName
                }
                PlasmaComponents.Label {
                    id: label
                    text: i18n("dGPU is %1", plasmoid.nativeInterface.powerName)
                }
            }
        }
    }
}
