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
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

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
    // open json
    QFile file("/etc/supergfxd.conf");
    file.open(QIODevice::ReadOnly);
    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    isVfioEnabled = json.value("gfx_vfio_enable").toBool();
    file.close();
    // run timer
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SuperGfxCtl::getState);
    timer->setInterval(1000);
    this->getState();
    timer->start();
}

SuperGfxCtl::~SuperGfxCtl() {
}

QString SuperGfxCtl::vendorName() {
    return vendorToName(vendor);
}

QString SuperGfxCtl::powerName() {
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

QString SuperGfxCtl::iconName() {
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

QString SuperGfxCtl::actionName() {
    if (action == GfxAction::REBOOT)
        return {"Reboot"};
    if (action == GfxAction::LOGOUT)
        return {"Logout"};
    return {""};
}

//TODO: this function includes a memory leak (possibly), but I have never learned c++ properly and can't handle it
VendorList *SuperGfxCtl::vendorList() {
    auto list = new VendorList();

    enum class Requirement {
        NONE,
        VFIO,
        INTEGRATED,
    };

    enum class Section {
        ACTIVE,
        AVAILABLE,
        UNAVAILABLE,
    };

    Requirement requirement;
    Section section;

    nvidia = new QObject();
    requirement = Requirement::NONE;
    if (vendor == GfxVendor::NVIDIA) section = Section::ACTIVE;
    else section = Section::AVAILABLE;
    nvidia->setProperty("name", "NVIDIA");
    nvidia->setProperty("iconName", "supergfxctl-plasmoid-gpu-nvidia");
    nvidia->setProperty("requirement", static_cast<int>(requirement));
    nvidia->setProperty("section", static_cast<int>(section));
    nvidia->setProperty("index", 0);
    list->append(nvidia);

    integrated = new QObject();
    requirement = Requirement::NONE;
    if (vendor == GfxVendor::INTEGRATED) section = Section::ACTIVE;
    else section = Section::AVAILABLE;
    integrated->setProperty("name", "Integrated");
    integrated->setProperty("iconName", "supergfxctl-plasmoid-gpu-integrated-active");
    integrated->setProperty("requirement", static_cast<int>(requirement));
    integrated->setProperty("section", static_cast<int>(section));
    integrated->setProperty("index", 1);
    list->append(integrated);

    compute = new QObject();
    switch (vendor) {
        case GfxVendor::COMPUTE:
            section = Section::ACTIVE;
            requirement = Requirement::NONE;
            break;
        case GfxVendor::INTEGRATED:
        case GfxVendor::VFIO:
            section = Section::AVAILABLE;
            requirement = Requirement::NONE;
            break;
        default:
            section = Section::UNAVAILABLE;
            requirement = Requirement::INTEGRATED;
    }
    compute->setProperty("name", "Compute");
    compute->setProperty("iconName", "supergfxctl-plasmoid-gpu-compute-active");
    compute->setProperty("requirement", static_cast<int>(requirement));
    compute->setProperty("section", static_cast<int>(section));
    compute->setProperty("index", 2);
    list->append(compute);

    vfio = new QObject();
    switch (vendor) {
        case GfxVendor::VFIO:
            section = Section::ACTIVE;
            requirement = Requirement::NONE;
            break;
        case GfxVendor::INTEGRATED:
        case GfxVendor::COMPUTE:
            if (isVfioEnabled) {
                section = Section::AVAILABLE;
                requirement = Requirement::NONE;
            } else {
                section = Section::UNAVAILABLE;
                requirement = Requirement::VFIO;
            }
            break;
        default:
            section = Section::UNAVAILABLE;
            if (isVfioEnabled) requirement = Requirement::INTEGRATED;
            else requirement = Requirement::VFIO;
    }
    vfio->setProperty("name", "vfio");
    vfio->setProperty("iconName", "supergfxctl-plasmoid-gpu-vfio-active");
    vfio->setProperty("requirement", static_cast<int>(requirement));
    vfio->setProperty("section", static_cast<int>(section));
    vfio->setProperty("index", 3);
    list->append(vfio);

    hybrid = new QObject();
    requirement = Requirement::NONE;
    if (vendor == GfxVendor::HYBRID) section = Section::ACTIVE;
    else section = Section::AVAILABLE;
    hybrid->setProperty("name", "Hybrid");
    hybrid->setProperty("iconName", "supergfxctl-plasmoid-gpu-hybrid-active");
    hybrid->setProperty("requirement", static_cast<int>(requirement));
    hybrid->setProperty("section", static_cast<int>(section));
    hybrid->setProperty("index", 5);
    list->append(hybrid);

    list->orderSections();

    return list;
}

void SuperGfxCtl::revertVendor() {
    setVendor(vendor);
}

void SuperGfxCtl::setVendor(int index) {
    setVendor(static_cast<GfxVendor>(index));
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
            emit actionChanged();
        }
    }
}

bool SuperGfxCtl::isSelectEnabled() {
    return action != GfxAction::REBOOT && action != GfxAction::LOGOUT;
}

void SuperGfxCtl::getState() {
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
            emit stateChanged();
        }
    }
    QDBusReply<quint32> reply2 = interface->call("Power");
    if (reply2.isValid()) {
        auto newPower = static_cast<GfxPower>(reply2.value());
        if (power != newPower) {
            power = newPower;
            emit stateChanged();
        }
    }
}

K_PLUGIN_CLASS_WITH_JSON(SuperGfxCtl, "metadata.json")

#include "supergfxctl.moc"
