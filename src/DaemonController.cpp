#include "DaemonController.h"
#include <QTimer>
#include <QDBusPendingCallWatcher>
#include <QDBusReply>

DaemonController::DaemonController() {
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DaemonController::fetchDaemonVersion);
    connect(timer, &QTimer::timeout, this, &DaemonController::fetchMode);
    connect(timer, &QTimer::timeout, this, &DaemonController::fetchPower);
    connect(this, &DaemonController::daemonFailingChanged, this, &DaemonController::fetchSupported);
    connect(this, &DaemonController::daemonOutdatedChanged, this, &DaemonController::fetchSupported);
    timer->setInterval(1000);
    this->fetchDaemonVersion();
    this->fetchMode();
    this->fetchPower();
    this->fetchSupported();
    timer->start();
}

void DaemonController::fetch(const QString &method, const std::function<void(QDBusPendingCallWatcher *)> &lambda) {
    auto pendingCall = interface->asyncCall(method);
    auto *watcher = new QDBusPendingCallWatcher(pendingCall);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, lambda);
}

bool DaemonController::isDaemonOutdated() const {
    return m_isDaemonOutdated;
}

bool DaemonController::isDaemonFailing() const {
    return m_isDaemonFailing;
}

void DaemonController::fetchDaemonVersion() {
    fetch("Version", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<QString> reply = *watcher;
        if (reply.isValid()) {
            auto actualVersion = QVersionNumber::fromString(reply.value());
            auto expectedVersion = QVersionNumber::fromString(REQUIRED_UPSTREAM_VERSION);
            bool isOutdated = QVersionNumber::compare(actualVersion, expectedVersion) < 0;
            if (m_isDaemonOutdated != isOutdated) {
                m_isDaemonOutdated = isOutdated;
                emit daemonOutdatedChanged();
            }
            if (m_isDaemonFailing) {
                m_isDaemonFailing = false;
                emit daemonFailingChanged();
            }
        } else {
            if (!m_isDaemonFailing) {
                m_isDaemonFailing = true;
                emit daemonFailingChanged();
            }
        }
        watcher->deleteLater();
    });
}

quint32 DaemonController::mode() const {
    return m_mode;
}

void DaemonController::fetchMode() {
    fetch("Mode", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<quint32> reply = *watcher;
        if (reply.isValid()) {
            auto mode = reply.value();
            if (m_mode != mode) {
                m_mode = mode;
                emit modeChanged();
            }
        }
        watcher->deleteLater();
    });
}

quint32 DaemonController::power() const {
    return m_power;
}

void DaemonController::fetchPower() {
    fetch("Power", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<quint32> reply = *watcher;
        if (reply.isValid()) {
            auto power = reply.value();
            if (m_power != power) {
                m_power = power;
                emit powerChanged();
            }
        }
        watcher->deleteLater();
    });
}

QList<quint32> DaemonController::supported() const {
    return m_supported;
}

void DaemonController::fetchSupported() {
    fetch("Supported", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<QList<quint32>> reply = *watcher;
        if (reply.isValid()) {
            auto list = reply.value();
            if (m_supported != list) {
                m_supported = list;
                emit supportedChanged();
            }
        }
        watcher->deleteLater();
    });
}

void DaemonController::setMode(quint32 mode) {
    auto pendingCall = interface->asyncCall("SetMode", mode);
    auto *watcher = new QDBusPendingCallWatcher(pendingCall);
    connect(watcher, &QDBusPendingCallWatcher::finished, this, [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<quint32> reply = *watcher;
        if (reply.isValid()) {
            auto action = reply.value();
            if (m_action != action) {
                m_action = action;
            }
            m_errorMsg = "";
        } else {
            m_errorMsg = reply.error().message();
            m_action = 3; // GfxAction::NONE
        }
        emit actionChanged();
    });
}

quint32 DaemonController::action() const {
    return m_action;
}

quint32 DaemonController::pendingAction() const {
    return m_pendingAction;
}

quint32 DaemonController::pendingMode() const {
    return m_pendingMode;
}

void DaemonController::fetchPending() {
    fetch("PendingAction", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<quint32> reply = *watcher;
        if (reply.isValid()) {
            auto pendingAction = reply.value();
            if (m_pendingAction != pendingAction) {
                m_power = pendingAction;
                emit pendingChanged();
            }
        }
        watcher->deleteLater();
    });
    fetch("PendingMode", [this](QDBusPendingCallWatcher *watcher) {
        QDBusPendingReply<quint32> reply = *watcher;
        if (reply.isValid()) {
            auto pendingMode = reply.value();
            if (m_pendingMode != pendingMode) {
                m_pendingMode = pendingMode;
                emit pendingChanged();
            }
        }
        watcher->deleteLater();
    });
}

QString DaemonController::errorMsg() const {
    return m_errorMsg;
}