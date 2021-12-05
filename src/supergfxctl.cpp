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

GfxVendor vendorFromCode(quint32 code) {
    switch(code) {
        case 0:
            return GfxVendor::NVIDIA;
        case 1:
            return GfxVendor::INTEGRATED;
        case 2:
            return GfxVendor::COMPUTE;
        case 3:
            return GfxVendor::VFIO;
        case 4:
            return GfxVendor::EGPU;
        case 5:
            return GfxVendor::HYBRID;
        default: //whatever
            return GfxVendor::NVIDIA;
    }
}

GfxPower powerFromCode(quint32 code) {
    switch(code) {
        case 0:
            return GfxPower::ACTIVE;
        case 1:
            return GfxPower::SUSPENDED;
        case 2:
            return GfxPower::OFF;
        case 3:
            return GfxPower::UNKNOWN;
        default: // whatever
            return GfxPower::UNKNOWN;
    }
}

SuperGFXCtl::SuperGFXCtl(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args)
{
    gfxGet();
}

SuperGFXCtl::~SuperGFXCtl()
{
}

QString SuperGFXCtl::gfxVendorName() {
    switch(vendor) {
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

QString SuperGFXCtl::gfxPowerName() {
    switch(power) {
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

QString SuperGFXCtl::gfxIconName() {
    switch (vendor) {
        case GfxVendor::NVIDIA:
            return {"supergfxctl-plasmoid-gpu-nvidia"};
        case GfxVendor::INTEGRATED:
            if(power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-integrated-active"};
            else return {"supergfxctl-plasmoid-gpu-integrated"};
        case GfxVendor::COMPUTE:
            if(power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-compute-active"};
            else return {"supergfxctl-plasmoid-gpu-compute"};
        case GfxVendor::VFIO:
            if(power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-vfio-active"};
            else return {"supergfxctl-plasmoid-gpu-vfio"};
        case GfxVendor::EGPU:
            if(power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-egpu-active"};
            else return {"supergfxctl-plasmoid-gpu-egpu"};
        case GfxVendor::HYBRID:
            if(power == GfxPower::ACTIVE) return {"supergfxctl-plasmoid-gpu-hybrid-active"};
            else return {"supergfxctl-plasmoid-gpu-hybrid"};
    }
    return {"supergfxctl-plasmoid-gpu-nvidia"};
}

void SuperGFXCtl::gfxGet() {
    QDBusConnection bus = QDBusConnection::systemBus();
    auto *interface = new QDBusInterface("org.supergfxctl.Daemon",
                                                   "/org/supergfxctl/Gfx",
                                                   "org.supergfxctl.Daemon",
                                                   bus,
                                                   this);
    QDBusReply<quint32> reply1 = interface->call("Vendor");
    if(reply1.isValid()) {
        GfxVendor newVendor = vendorFromCode(reply1.value());
        if (vendor != newVendor) {
            vendor = newVendor;
            emit gfxStateChanged();
        }
    }
    QDBusReply<quint32> reply2 = interface->call("Power");
    if(reply2.isValid()) {
        auto newPower = powerFromCode(reply2.value());
        if(power != newPower) {
            power = newPower;
            emit gfxStateChanged();
        }
    }
}

K_PLUGIN_CLASS_WITH_JSON(SuperGFXCtl, "metadata.json")

#include "supergfxctl.moc"
