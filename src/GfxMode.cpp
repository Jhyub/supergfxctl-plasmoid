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
            GfxMode::INTEGRATED,
            GfxMode::COMPUTE,
            GfxMode::VFIO,
            GfxMode::ASUS_MUX_DISCRETE,
            GfxMode::EGPU
    };
}

QString GfxMode::name() const {
    switch (id) {
        case HYBRID:
            return i18n("Hybrid");
        case INTEGRATED:
            return i18n("Integrated");
        case COMPUTE:
            return i18n("Compute");
        case VFIO:
            return i18n("vfio");
        case EGPU:
            return i18n("eGPU");
        case ASUS_MUX_DISCRETE:
            return i18n("Discrete (ASUS MUX)");
        default:
            return i18n("Unknown");
    }
}

QString GfxMode::iconName(GfxPower &power) const {
    bool isActive = power == GfxPower::from(GfxPower::ACTIVE);
    switch (id) {
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
        case ASUS_MUX_DISCRETE:
            if (isActive) return {"supergfxctl-plasmoid-gpu-asusmuxdiscrete-active"};
            else return {"supergfxctl-plasmoid-gpu-asusmuxdiscrete"};
        default:
            return {};
    }
}