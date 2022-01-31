#ifndef SUPERGFXCTL_H
#define SUPERGFXCTL_H

#include <Plasma/Applet>
#include <QDBusInterface>
#include <QTimer>
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
    Q_PROPERTY(GfxAction *expectedAction READ expectedAction NOTIFY expectionChanged)
    Q_PROPERTY(QString errorMsg READ errorMsg NOTIFY expectionChanged) // error happens on expecting

public:
    SuperGfxCtl(QObject *parent, const QVariantList &args);

    bool isDaemonOutdated() const;

    bool isDaemonFailing() const;

    GfxMode *mode() const;

    GfxPower *power() const;

    QString iconName() const;

    GfxModeCandidateList *candidates();

    Q_INVOKABLE void realizeCandidate(int index);

    Q_INVOKABLE void revert();

    GfxAction *expectedAction() const;

    QString errorMsg() const;

signals:

    void daemonOutdatedChanged();

    void daemonFailingChanged();

    void modeChanged();

    void powerChanged();

    void candidateChanged();

    void iconNameChanged();

    void expectionChanged();

private:

    GfxModeCandidateList *currentList = nullptr;

    GfxModeCandidateList *previousList = nullptr;

};

#endif
