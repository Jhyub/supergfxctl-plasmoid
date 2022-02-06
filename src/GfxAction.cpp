#include <KLocalizedString>
#include <DaemonController.h>
#include "GfxAction.h"

GfxAction::operator GfxAction::Id() const {
    return id;
}

bool GfxAction::operator==(GfxAction &other) const {
    return id == other.id;
}

QString GfxAction::name() const {
    switch (id) {
        case LOGOUT:
            return i18n("Logout");
        case REBOOT:
            return i18n("Reboot");
        case INTEGRATED:
            return i18n("Integrated");
        default:
            return i18n("None");
    }
}

GfxAction &GfxAction::pending() {
    return GfxAction::from(static_cast<GfxAction::Id>(DaemonController::from().pendingAction()));
}