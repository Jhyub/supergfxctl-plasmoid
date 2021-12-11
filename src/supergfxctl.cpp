/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "supergfxctl.h"
#include <KLocalizedString>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QTimer>

QString vendorToName(GfxVendor vendor) {
    switch (vendor) {
        case GfxVendor::NVIDIA:
            return {"NVIDIA"};
        case GfxVendor::INTEGRATED:
            return {"integrated"};
        case GfxVendor::COMPUTE:
            return {"compute"};
        case GfxVendor::VFIO:
            return {"vfio"};
        case GfxVendor::EGPU:
            return {"eGPU"};
        case GfxVendor::HYBRID:
            return {"hybrid"};
        default: // whatever
            return {"NVIDIA"};
    }
}

SuperGfxCtl::SuperGfxCtl(QObject *parent, const QVariantList &args)
        : Plasma::Applet(parent, args) {
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SuperGfxCtl::gfxGet);
    timer->setInterval(1000);
    this->gfxGet();
    timer->start();
}

SuperGfxCtl::~SuperGfxCtl() {
}

QString SuperGfxCtl::gfxVendorName() {
    return vendorToName(vendor);
}

QString SuperGfxCtl::gfxPowerName() {
    switch (power) {
        case GfxPower::ACTIVE:
            return {"active"};
        case GfxPower::SUSPENDED:
            return {"suspended"};
        case GfxPower::OFF:
            return {"off"};
        case GfxPower::UNKNOWN:
            return {"unknown"};
        default: //whatever
            return {"unknown"};
    }
}

QString SuperGfxCtl::gfxIconName() {
    switch (vendor) {
        case GfxVendor::NVIDIA:
            return {"supergfxctl-plasmoid-gpu-nvidia"};
        case GfxVendor::INTEGRATED:
            if (power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-integrated-active"};
            else return {"supergfxctl-plasmoid-gpu-integrated"};
        case GfxVendor::COMPUTE:
            if (power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-compute-active"};
            else return {"supergfxctl-plasmoid-gpu-compute"};
        case GfxVendor::VFIO:
            if (power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-vfio-active"};
            else return {"supergfxctl-plasmoid-gpu-vfio"};
        case GfxVendor::EGPU:
            if (power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-egpu-active"};
            else return {"supergfxctl-plasmoid-gpu-egpu"};
        case GfxVendor::HYBRID:
            if (power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-hybrid-active"};
            else return {"supergfxctl-plasmoid-gpu-hybrid"};
    }
    return {"supergfxctl-plasmoid-gpu-nvidia"};
}

QString SuperGfxCtl::gfxActionName() {
    if (action == GfxAction::REBOOT)
        return {"Reboot"};
    if (action == GfxAction::LOGOUT)
        return {"Logout"};
    return {""};
}

void SuperGfxCtl::setVendor(GfxVendor vendor) {
    QDBusConnection bus = QDBusConnection::systemBus();
    auto *interface = new QDBusInterface("org.supergfxctl.Daemon",
                                         "/org/supergfxctl/Gfx",
                                         "org.supergfxctl.Daemon",
                                         bus,
                                         this);
    QDBusReply<quint32> reply = interface->call("SetVendor", static_cast<quint32>(vendor));
    if (reply.isValid()) {
        auto newAction = static_cast<GfxAction>(reply.value());
        if (action != newAction) {
            action = newAction;
            emit gfxActionChanged();
        }
    }
}

bool SuperGfxCtl::isSelectEnabled() {
    return action == GfxAction::REBOOT || action == GfxAction::LOGOUT;
}

void SuperGfxCtl::gfxGet() {
    QDBusConnection bus = QDBusConnection::systemBus();
    auto *interface = new QDBusInterface("org.supergfxctl.Daemon",
                                         "/org/supergfxctl/Gfx",
                                         "org.supergfxctl.Daemon",
                                         bus,
                                         this);
    QDBusReply<quint32> reply1 = interface->call("Vendor");
    if (reply1.isValid()) {
        auto newVendor = static_cast<GfxVendor>(reply1.value());
        if (vendor != newVendor) {
            vendor = newVendor;
            emit gfxStateChanged();
        }
    }
    QDBusReply<quint32> reply2 = interface->call("Power");
    if (reply2.isValid()) {
        auto newPower = static_cast<GfxPower>(reply2.value());
        if (power != newPower) {
            power = newPower;
            emit gfxStateChanged();
        }
    }
}

K_PLUGIN_CLASS_WITH_JSON(SuperGfxCtl, "metadata.json")

#include "supergfxctl.moc"
