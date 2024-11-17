#ifndef PLASMA_SUPERGFXCTL_DAEMONCONTROLLER_H
#define PLASMA_SUPERGFXCTL_DAEMONCONTROLLER_H

#include <QObject>
#include <QDBusConnection>
#include <QDBusInterface>
#include <QVersionNumber>

class DaemonController : public QObject {
Q_OBJECT
public:
    ~DaemonController() override = default;

    static DaemonController &from() {
        static DaemonController instance;
        return instance;
    }

    bool isDaemonOutdated() const;

    bool isDaemonFailing() const;

    quint32 mode() const;

    quint32 power() const;

    QList<quint32> supported() const;

    void setMode(quint32 mode);

    quint32 pendingAction() const;

    quint32 pendingMode() const;

    QString errorMsg() const;

signals:

    void daemonOutdatedChanged();

    void daemonFailingChanged();

    void modeChanged();

    void powerChanged();

    void supportedChanged();

    void setModeFinished();

    void pendingChanged();

    void errorMsgChanged();

private:

    DaemonController();

    QDBusConnection bus = QDBusConnection::systemBus();
    QDBusInterface *interface = new QDBusInterface("org.supergfxctl.Daemon",
                                                   "/org/supergfxctl/Gfx",
                                                   "org.supergfxctl.Daemon",
                                                   bus,
                                                   this);

    void fetch(const QString &method, const std::function<void(QDBusPendingCallWatcher *)> &lambda);

    bool m_isDaemonOutdated = false;

    bool m_isDaemonFailing = false;

    void fetchDaemonVersion();

    quint32 m_mode = 0;

    void fetchMode();

    quint32 m_power = 5; // Set default to GfxPower::UNKNOWN

    void fetchPower();

    QList<quint32> m_supported;

    void fetchSupported();

    QString m_errorMsg;

    void fetchPending();

    quint32 m_pendingAction = 3; // Assumption: GfxAction::NONE

    quint32 m_pendingMode = 6; // Assumption: GfxMode::NONE
};

#endif //PLASMA_SUPERGFXCTL_DAEMONCONTROLLER_H
