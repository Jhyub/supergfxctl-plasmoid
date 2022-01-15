/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef SUPERGFXCTL_H
#define SUPERGFXCTL_H


#include <Plasma/Applet>
#include <QDBusInterface>
#include <QTimer>
#include <modelist.h>

enum class GfxMode {
    HYBRID,
    DEDICATED,
    INTEGRATED,
    COMPUTE,
    VFIO,
    EGPU,
};

enum class GfxPower {
    ACTIVE,
    SUSPENDED,
    OFF,
    UNKNOWN,
};

enum class GfxAction {
    LOGOUT,
    REBOOT,
    INTEGRATED,
    NONE,
};

class SuperGfxCtl : public Plasma::Applet {
Q_OBJECT
    Q_PROPERTY(QString modeName READ modeName NOTIFY stateChanged)
    Q_PROPERTY(QString powerName READ powerName NOTIFY stateChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY stateChanged)
    Q_PROPERTY(QString actionName READ actionName NOTIFY actionChanged)
    Q_PROPERTY(ModeList *modeList READ modeList NOTIFY stateChanged)
    Q_PROPERTY(int loadingGfxIdx READ loadingGfxIdx NOTIFY loadingChanged)
    Q_PROPERTY(bool isSelectEnabled READ isSelectEnabled NOTIFY actionChanged)
    Q_PROPERTY(int timeout READ timeout NOTIFY timeoutChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY loadingChanged) // errors happen on switch attempts


public:
    SuperGfxCtl(QObject *parent, const QVariantList &args);

    ~SuperGfxCtl();

    QString modeName();

    QString powerName();

    QString iconName();

    QString actionName();

    ModeList *modeList();

    Q_INVOKABLE void revertMode();

    Q_INVOKABLE void setMode(int modeIndex);

    int loadingGfxIdx();

    bool isSelectEnabled();

    int timeout();

    QString errorMessage();

signals:

    void stateChanged();

    void actionChanged();

    void loadingChanged();

    void timeoutChanged();

    void finishedSetModeCall(QDBusPendingCallWatcher *);

    void finishedGetModeCall(QDBusPendingCallWatcher *);

    void finishedGetPowerCall(QDBusPendingCallWatcher *);

private:
    GfxMode mode;
    GfxPower power;
    GfxAction action = GfxAction::NONE;

    // Future mode
    int mLoadingModeIdx = -1;

    bool isVfioEnabled;

    void setMode(GfxMode mode);

    void getState();

    ModeList *currentList = nullptr, *oldList = nullptr;

    QString mErrorMessage;

    int mTimeout = 0;

    void reduceTimer();

    QTimer *timeoutTimer = new QTimer(this);

private slots:

    void finishSetModeCall(QDBusPendingCallWatcher *watcher);

    void finishGetModeCall(QDBusPendingCallWatcher *watcher);

    void finishGetPowerCall(QDBusPendingCallWatcher *);
};

#endif
