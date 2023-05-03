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
        case SWITCH_TO_INTEGRATED:
            return i18n("Switch to Integrated");
        case ASUS_EGPU_DISABLE:
            return i18n("Switch to Integrated or Hybrid");
        default:
            return i18n("Nothing");
    }
}

GfxAction &GfxAction::pending() {
    return GfxAction::from(static_cast<GfxAction::Id>(DaemonController::from().pendingAction()));
}