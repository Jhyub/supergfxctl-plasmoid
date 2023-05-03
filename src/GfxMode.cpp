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
            GfxMode::NVIDIA_NO_MODESET,
            GfxMode::VFIO,
            GfxMode::ASUS_EGPU,
            GfxMode::ASUS_MUX_DGPU,
    };
}

QString GfxMode::name() const {
    switch (id) {
        case HYBRID:
            return i18n("Hybrid");
        case INTEGRATED:
            return i18n("Integrated");
        case NVIDIA_NO_MODESET:
            return i18n("NvidiaNoModeset");
        case VFIO:
            return i18n("vfio");
        case ASUS_EGPU:
            return i18n("eGPU (ASUS)");
        case ASUS_MUX_DGPU:
            return i18n("dGPU (ASUS MUX)");
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
        case VFIO:
            if (isActive) return {"supergfxctl-plasmoid-gpu-vfio-active"};
            else return {"supergfxctl-plasmoid-gpu-vfio"};
        case ASUS_EGPU:
            if (isActive) return {"supergfxctl-plasmoid-gpu-egpu-active"};
            else return {"supergfxctl-plasmoid-gpu-egpu"};
        case HYBRID:
            if (isActive) return {"supergfxctl-plasmoid-gpu-hybrid-active"};
            else return {"supergfxctl-plasmoid-gpu-hybrid"};
        case ASUS_MUX_DGPU:
        case NVIDIA_NO_MODESET:
            if (isActive) return {"supergfxctl-plasmoid-gpu-dedicated-active"};
            else return {"supergfxctl-plasmoid-gpu-dedicated"};
        default:
            return {};
    }
}