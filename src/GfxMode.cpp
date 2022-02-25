#include "GfxMode.h"
#include "DaemonController.h"
#include <KLocalizedString>
#include <QDBusConnection>

GfxMode::operator GfxMode::Id() const {
    return id;
}

bool GfxMode::operator==(GfxMode &other) const {
    return id == other.id;
}

GfxMode &GfxMode::current() {
    return GfxMode::from(static_cast<GfxMode::Id>(DaemonController::from().mode()));
}

GfxMode &GfxMode::pending() {
    return GfxMode::from(static_cast<GfxMode::Id>(DaemonController::from().pendingMode()));
}

QVector<GfxMode::Id> GfxMode::supported() {
    auto original = DaemonController::from().supported();

    QVector<GfxMode::Id> ret{};

    for (auto i: original) {
        ret.push_back(static_cast<GfxMode::Id>(i));
    }

    return ret;
}

QVector<GfxMode::Id> GfxMode::all() {
    return {
            GfxMode::HYBRID,
            GfxMode::DEDICATED,
            GfxMode::INTEGRATED,
            GfxMode::COMPUTE,
            GfxMode::VFIO,
            GfxMode::EGPU
    };
}

QString GfxMode::name() const {
    switch (id) {
        case HYBRID:
            return i18n("Hybrid");
        case DEDICATED:
            return i18n("Dedicated");
        case INTEGRATED:
            return i18n("Integrated");
        case COMPUTE:
            return i18n("Compute");
        case VFIO:
            return i18n("vfio");
        case EGPU:
            return i18n("eGPU");
        default:
            return i18n("Unknown");
    }
}

QString GfxMode::iconName(GfxPower &power) const {
    bool isActive = power == GfxPower::from(GfxPower::ACTIVE);
    switch (id) {
        case DEDICATED:
            return {"supergfxctl-plasmoid-gpu-dedicated"};
        case INTEGRATED:
            if (isActive) return {"supergfxctl-plasmoid-gpu-integrated-active"};
            else return {"supergfxctl-plasmoid-gpu-integrated"};
        case COMPUTE:
            if (isActive) return {"supergfxctl-plasmoid-gpu-compute-active"};
            else return {"supergfxctl-plasmoid-gpu-compute"};
        case VFIO:
            if (isActive) return {"supergfxctl-plasmoid-gpu-vfio-active"};
            else return {"supergfxctl-plasmoid-gpu-vfio"};
        case EGPU:
            if (isActive) return {"supergfxctl-plasmoid-gpu-egpu-active"};
            else return {"supergfxctl-plasmoid-gpu-egpu"};
        case HYBRID:
            if (isActive) return {"supergfxctl-plasmoid-gpu-hybrid-active"};
            else return {"supergfxctl-plasmoid-gpu-hybrid"};
        default:
            return {};
    }
}