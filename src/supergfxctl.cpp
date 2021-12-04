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

GfxState stateFromCode(quint32 code) {
    switch(code) {
        case 0:
            return GfxState::NVIDIA;
        case 1:
            return GfxState::INTEGRATED;
        case 2:
            return GfxState::COMPUTE;
        case 3:
            return GfxState::VFIO;
        case 4:
            return GfxState::EGPU;
        case 5:
            return GfxState::HYBRID;
        default: //whatever
            return GfxState::NVIDIA;
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

QString SuperGFXCtl::gfxStateName() {
    switch(state) {
        case GfxState::NVIDIA:
            return {"NVIDIA"};
        case GfxState::INTEGRATED:
            return {"integrated"};
        case GfxState::COMPUTE:
            return {"compute"};
        case GfxState::VFIO:
            return {"vfio"};
        case GfxState::EGPU:
            return {"eGPU"};
        case GfxState::HYBRID:
            return {"hybrid"};
    }
    return {"NVIDIA"};
}

QString SuperGFXCtl::gfxStateIconName() {
    switch (state) {
        case GfxState::NVIDIA:
            return {"supergfxctl-plasmoid-gpu-nvidia"};
        case GfxState::INTEGRATED:
            if(power) return {"supergfxctl-plasmoid-gpu-integrated-active"};
            else return {"supergfxctl-plasmoid-gpu-integrated"};
        case GfxState::COMPUTE:
            if(power) return {"supergfxctl-plasmoid-gpu-compute-active"};
            else return {"supergfxctl-plasmoid-gpu-compute"};
        case GfxState::VFIO:
            if(power) return {"supergfxctl-plasmoid-gpu-vfio-active"};
            else return {"supergfxctl-plasmoid-gpu-vfio"};
        case GfxState::EGPU:
            if(power) return {"supergfxctl-plasmoid-gpu-egpu-active"};
            else return {"supergfxctl-plasmoid-gpu-egpu"};
        case GfxState::HYBRID:
            if(power) return {"supergfxctl-plasmoid-gpu-hybrid-active"};
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
        GfxState newState = stateFromCode(reply1.value());
        if (state != newState) {
            state = newState;
            emit gfxStateChanged();
        }
    }
    QDBusReply<quint32> reply2 = interface->call("Power");
    if(reply2.isValid()) {
        bool newPower = (bool) reply2.value();
        if(power != newPower) {
            power = newPower;
            emit gfxStateChanged();
        }
    }
}

K_PLUGIN_CLASS_WITH_JSON(SuperGFXCtl, "metadata.json")

#include "supergfxctl.moc"
