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
                anchors {
                    fill: parent
                    topMargin: PlasmaCore.Units.smallSpacing
                }
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
                    required property int gfxIndex
                    required property int section
                    required property int index
                    MouseArea {
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: listView.currentIndex = index
                        Item {
                            anchors.fill: parent
                            PlasmaCore.IconItem {
                                anchors {
                                    verticalCenter: parent.verticalCenter
                                    left: parent.left
                                }
                                id: iconItem
                                height: PlasmaCore.Units.iconSizes.medium
                                width: PlasmaCore.Units.iconSizes.medium
                                source: iconName
                                opacity: requirement != 0 ? 0.6 : 1
                            }
                            Item {
                                anchors {
                                    verticalCenter: requirement == 0 ? parent.verticalCenter : undefined
                                    top: requirement == 0 ? undefined : parent.top
                                    bottom: requirement == 0 ? undefined : parent.bottom
                                    left: iconItem.right
                                    right: button.left
                                    leftMargin: PlasmaCore.Units.smallSpacing
                                }
                                PlasmaComponents.Label {
                                    anchors {
                                        verticalCenter: requirement == 0 ? parent.verticalCenter : undefined
                                        top: requirement == 0 ? undefined : parent.top
                                        left: parent.left
                                    }
                                    id: nameLabel
                                    text: name
                                    font.bold: section == 0
                                    opacity: requirement != 0 ? 0.6 : 1
                                }
                                PlasmaComponents.Label {
                                    anchors {
                                        top: requirement == 0 ? undefined : nameLabel.bottom
                                        bottom: requirement == 0 ? undefined : parent.bottom
                                        left: parent.left
                                    }
                                    id: descriptionLabel
                                    visible: requirement != 0
                                    text: requirement == 2 ? "Switch to integrated is required" : (requirement == 1 ? "vfio is disabled in config" : "")
                                    font.pixelSize: PlasmaCore.Theme.smallestFont.pixelSize
                                    opacity: 0.6
                                }
                            }
                            PlasmaComponents.Button {
                                anchors {
                                    verticalCenter: iconItem.verticalCenter
                                    right: parent.right
                                }
                                id: button
                                flat: true
                                down: section == 0
                                checkable: section == 1
                                enabled: section == 1
                                onClicked: plasmoid.nativeInterface.setVendor(gfxIndex)
                                icon.name: section == 0 ? "supergfxctl-plasmoid-gpu-nvidia" : (section == 1 ? "supergfxctl-plasmoid-gpu-integrated-active" : "supergfxctl-plasmoid-gpu-integrated")
                                text: i18n(section == 0 ? "Active" : (section == 1 ? "Switch" : "Unavailable"))
                            }
                        }
                    }
                }
            }
        }

        PlasmaExtras.PlaceholderMessage {
            anchors {
                centerIn: parent
                left: parent.left
                right: parent.right
                margins: PlasmaCore.Units.largeSpacing
            }

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
