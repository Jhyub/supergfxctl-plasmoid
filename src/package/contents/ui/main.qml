/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: MPL-2.0
*/

import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.components 2.0 as PlasmaComponents2
import org.kde.plasma.components 3.0 as PlasmaComponents
import org.kde.plasma.extras 2.0 as PlasmaExtras

Item {
    Plasmoid.icon: plasmoid.nativeInterface.iconName
    Plasmoid.toolTipSubText: i18n("Graphics mode: %1, dGPU power: %2", plasmoid.nativeInterface.vendorName, plasmoid.nativeInterface.powerName)
    Plasmoid.fullRepresentation: PlasmaComponents.Page {
        id: dialog
        header: PlasmaExtras.PlasmoidHeading {
            RowLayout {
                PlasmaCore.IconItem {
                    Layout.preferredHeight: PlasmaCore.Units.iconSizes.small
                    Layout.preferredWidth: PlasmaCore.Units.iconSizes.small
                    source: "supergfxctl-plasmoid-dgpu-" + plasmoid.nativeInterface.powerName
                }
                PlasmaComponents.Label {
                    text: i18n("dGPU is %1", plasmoid.nativeInterface.powerName)
                }
            }
        }

        PlasmaExtras.ScrollArea {
            anchors.fill: parent

            visible: plasmoid.nativeInterface.isSelectEnabled

            ListView {
                id: listView
                anchors.fill: parent
                clip: true
                model: plasmoid.nativeInterface.vendorList
                boundsBehavior: Flickable.StopAtBounds
                currentIndex: -1
                spacing: PlasmaCore.Units.smallSpacing
                section.property: "section"
                section.delegate: Loader {
                    active: section != 0
                    height: active ? source.height : 0

                    sourceComponent: Item {
                        id: source
                        height: separatorLine.height
                        width: listView.width
                        PlasmaCore.SvgItem {
                            id: separatorLine
                            width: parent.width - 2 * PlasmaCore.Units.gridUnit
                            height: lineSvg.elementSize("horizontal-line").height
                            anchors.centerIn: parent
                            svg: PlasmaCore.Svg {
                                id: lineSvg
                                imagePath: "widgets/line"
                            }
                            elementId: "horizontal-line"
                        }
                    }
                }
                highlight: PlasmaComponents2.Highlight { }
                highlightMoveDuration: 0
                highlightResizeDuration: 0
                delegate: PlasmaExtras.ListItem {
                    width: listView.width
                    height: PlasmaCore.Units.gridUnit * 2
                    required property string name
                    required property string iconName
                    required property int requirement
                    required property int index
                    required property int section
                    RowLayout {
                        PlasmaCore.IconItem {
                            Layout.preferredHeight: PlasmaCore.Units.iconSizes.medium
                            Layout.preferredWidth: PlasmaCore.Units.iconSizes.medium
                            source: iconName
                        }
                        ColumnLayout {
                            PlasmaComponents.Label {
                                text: name
                                font.pixelSize: 12
                            }
                            PlasmaComponents.Label {
                                text: requirement == 2 ? "Switch to integrated is required" : (requirement == 1 ? "vfio is disabled in config" : "")
                                font.italic: true
                            }
                        }
                        PlasmaComponents.Button {
                            flat: true
                            text: i18n(section == 0 ? "Active" : (section == 1 ? "Switch" : "Unavailable"))
                            onClicked: plasmoid.nativeInterface.setVendor(index)
                            down: section == 0
                            highlighted: section == 2
                            checkable: section == 1
                            enabled: section == 1
                        }
                    }
                }
            }
        }

        PlasmaExtras.PlaceholderMessage {
            anchors.centerIn: parent
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: PlasmaCore.Units.largeSpacing

            visible: !plasmoid.nativeInterface.isSelectEnabled

            text: i18n("%1 is required to complete the switch", plasmoid.nativeInterface.actionName)
            helpfulAction: Action {
                id: revertAction
                text: i18n("Revert to %1", plasmoid.nativeInterface.vendorName)
                onTriggered: plasmoid.nativeInterface.revertVendor()
            }
        }
    }
}
