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
        case ASUS_DISABLED:
            return i18n("Disabled");
        case ASUS_MUX_DISCRETE:
            return i18n("Active (ASUS MUX)");
        case OFF:
            return i18n("Off");
        default:
            return i18n("Unknown");
    }
}

QString GfxPower::iconName() const {
    switch (id) {
        case ACTIVE:
        case ASUS_MUX_DISCRETE:
            return {"supergfxctl-plasmoid-dgpu-active"};
        case SUSPENDED:
            return {"supergfxctl-plasmoid-dgpu-suspended"};
        default:
            return {"supergfxctl-plasmoid-dgpu-off"};
    }
}