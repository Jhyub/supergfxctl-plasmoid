#ifndef SUPERGFXCTL_H
#define SUPERGFXCTL_H

#include <Plasma/Applet>
#include <QDBusInterface>
#include <QTimer>
#include <Solid/Battery>
#include "GfxAction.h"
#include "GfxMode.h"
#include "GfxPower.h"
#include "GfxModeCandidate.h"

class SuperGfxCtl : public Plasma::Applet {
Q_OBJECT
    Q_PROPERTY(bool isDaemonOutdated READ isDaemonOutdated NOTIFY daemonOutdatedChanged)
    Q_PROPERTY(bool isDaemonFailing READ isDaemonFailing NOTIFY daemonFailingChanged)
    Q_PROPERTY(GfxMode *mode READ mode NOTIFY modeChanged)
    Q_PROPERTY(GfxPower *power READ power NOTIFY powerChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY iconNameChanged)
    Q_PROPERTY(GfxModeCandidateList *candidates READ candidates NOTIFY candidateChanged)
    Q_PROPERTY(GfxAction *pendingAction READ pendingAction NOTIFY pendingChanged)
    Q_PROPERTY(GfxMode *pendingMode READ pendingMode NOTIFY pendingChanged)
    Q_PROPERTY(bool isPending READ isPending NOTIFY pendingChanged)
    Q_PROPERTY(int realizing READ realizing NOTIFY realizingChanged)
    Q_PROPERTY(QString errorMsg READ errorMsg NOTIFY errorMsgChanged)
    Q_PROPERTY(bool isCharging READ isCharging NOTIFY chargingChanged)

public:
    SuperGfxCtl(QObject *parent, const KPluginMetaData &data, const QVariantList &args);

    bool isDaemonOutdated() const;

    bool isDaemonFailing() const;

    GfxMode *mode() const;

    GfxPower *power() const;

    QString iconName() const;

    GfxModeCandidateList *candidates();

    Q_INVOKABLE void realizeCandidate(int index);

    Q_INVOKABLE void revert();

    GfxAction *pendingAction() const;

    GfxMode *pendingMode() const;

    bool isPending() const;

    QString errorMsg() const;

    int realizing() const;

    bool isCharging() const;

signals:

    void daemonOutdatedChanged();

    void daemonFailingChanged();

    void modeChanged();

    void powerChanged();

    void candidateChanged();

    void iconNameChanged();

    void realizingChanged();

    void pendingChanged();

    void errorMsgChanged();

    void chargingChanged();

private:

    GfxModeCandidateList *currentList = nullptr;

    GfxModeCandidateList *previousList = nullptr;

    int m_realizing = -1;

    const Solid::Battery *battery = nullptr;

};

#endif
