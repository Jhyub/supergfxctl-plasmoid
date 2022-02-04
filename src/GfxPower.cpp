#include "GfxPower.h"
#include "DaemonController.h"
#include <KLocalizedString>

GfxPower::operator GfxPower::Id() const {
    return id;
}

bool GfxPower::operator==(GfxPower &other) const {
    return id == other.id;
}

GfxPower &GfxPower::current() {
    return GfxPower::from(static_cast<Id>(DaemonController::from().power()));
}

QString GfxPower::name() const {
    switch (id) {
        case ACTIVE:
            return i18n("Active");
        case SUSPENDED:
            return i18n("Suspended");
        case OFF:
            return i18n("Off");
        case UNKNOWN:
            return i18n("Unknown");
        default:
            return i18n("Unknown");
    }
}

QString GfxPower::iconName() const {
    switch (id) {
        case ACTIVE:
            return {"supergfxctl-plasmoid-dgpu-active"};
        case SUSPENDED:
            return {"supergfxctl-plasmoid-dgpu-suspended"};
        case OFF:
            return {"supergfxctl-plasmoid-dgpu-off"};
        default:
            return {""};
    }
}