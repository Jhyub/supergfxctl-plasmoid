#include "SuperGfxCtl.h"
#include "DaemonController.h"
#include "GfxModeCandidate.h"
#include <QtQml/QQmlEngine>
#include <Solid/Device>
#include <Solid/DeviceNotifier>

SuperGfxCtl::SuperGfxCtl(QObject *parent, const KPluginMetaData &data, const QVariantList &args) : Plasma::Applet(parent, data, args) {
    auto &ctl = DaemonController::from();
    connect(&ctl, &DaemonController::daemonOutdatedChanged, this, &SuperGfxCtl::daemonOutdatedChanged);
    connect(&ctl, &DaemonController::daemonFailingChanged, this, &SuperGfxCtl::daemonFailingChanged);
    connect(&ctl, &DaemonController::modeChanged, this, &SuperGfxCtl::modeChanged);
    connect(&ctl, &DaemonController::modeChanged, this, &SuperGfxCtl::iconNameChanged);
    connect(&ctl, &DaemonController::powerChanged, this, &SuperGfxCtl::powerChanged);
    connect(&ctl, &DaemonController::powerChanged, this, &SuperGfxCtl::iconNameChanged);
    connect(&ctl, &DaemonController::modeChanged, this, &SuperGfxCtl::candidateChanged);
    connect(&ctl, &DaemonController::powerChanged, this, &SuperGfxCtl::candidateChanged);
    connect(&ctl, &DaemonController::supportedChanged, this, &SuperGfxCtl::candidateChanged);
    connect(&ctl, &DaemonController::pendingChanged, this, &SuperGfxCtl::pendingChanged);
    connect(&ctl, &DaemonController::errorMsgChanged, this, &SuperGfxCtl::errorMsgChanged);
    connect(&ctl, &DaemonController::setModeFinished, this, [this] { m_realizing = -1; emit realizingChanged(); });

    auto notifier = Solid::DeviceNotifier::instance();
    const auto devices = Solid::Device::listFromType(Solid::DeviceInterface::Battery, QString());
    for (const Solid::Device &device: devices) {
        auto batteryCandidate = device.as<Solid::Battery>();
        if (batteryCandidate->type() == Solid::Battery::PrimaryBattery) {
            battery = batteryCandidate;
            break;
        }
    }
    connect(battery, &Solid::Battery::chargeStateChanged, this, &SuperGfxCtl::chargingChanged);
}

bool SuperGfxCtl::isDaemonOutdated() const {
    return DaemonController::from().isDaemonOutdated();
}

bool SuperGfxCtl::isDaemonFailing() const {
    return DaemonController::from().isDaemonFailing();
}

GfxMode *SuperGfxCtl::mode() const {
    auto ret = &GfxMode::current();
    QQmlEngine::setObjectOwnership(ret, QQmlEngine::CppOwnership);
    return ret;
}

GfxPower *SuperGfxCtl::power() const {
    auto ret = &GfxPower::current();
    QQmlEngine::setObjectOwnership(ret, QQmlEngine::CppOwnership);
    return ret;
}

QString SuperGfxCtl::iconName() const {
    return GfxMode::current().iconName(GfxPower::current());
}

GfxModeCandidateList *SuperGfxCtl::candidates() {
    if (currentList != previousList && previousList != nullptr) {
        previousList->freeAll();
        delete previousList;
        previousList = currentList;
    }
    currentList = GfxModeCandidateList::from();
    if (previousList == nullptr) {
        previousList = currentList;
    }
    return currentList;
}

void SuperGfxCtl::realizeCandidate(int index) {
    m_realizing = index;
    emit realizingChanged();
    currentList->realize(index);
}

// Assumption: list is sorted, so [0] points to GfxModeCandidate(current, current)
void SuperGfxCtl::revert() {
    realizeCandidate(0);
}

GfxAction *SuperGfxCtl::pendingAction() const {
    auto ret = &GfxAction::pending();
    QQmlEngine::setObjectOwnership(ret, QQmlEngine::CppOwnership);
    return ret;
}

GfxMode *SuperGfxCtl::pendingMode() const {
    auto ret = &GfxMode::pending();
    QQmlEngine::setObjectOwnership(ret, QQmlEngine::CppOwnership);
    return ret;
}

bool SuperGfxCtl::isPending() const {
    return !(GfxAction::pending() == GfxAction::from(GfxAction::NOTHING));
}

QString SuperGfxCtl::errorMsg() const {
    return DaemonController::from().errorMsg();
}

int SuperGfxCtl::realizing() const {
    return m_realizing;
}

bool SuperGfxCtl::isCharging() const {
    if (battery == nullptr) return false;
    return battery->chargeState() != Solid::Battery::Discharging;
}

K_PLUGIN_CLASS(SuperGfxCtl)

#include "SuperGfxCtl.moc"
