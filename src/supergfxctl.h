/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef SUPERGFXCTL_H
#define SUPERGFXCTL_H


#include <Plasma/Applet>
#include <QDBusInterface>
#include <QTimer>
#include <vendorlist.h>

enum class GfxVendor {
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
    Q_PROPERTY(QString vendorName READ vendorName NOTIFY stateChanged)
    Q_PROPERTY(QString powerName READ powerName NOTIFY stateChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY stateChanged)
    Q_PROPERTY(QString actionName READ actionName NOTIFY actionChanged)
    // expect that a supergfxd reload after config edit will reload plasmoid
    Q_PROPERTY(VendorList *vendorList READ vendorList NOTIFY stateChanged)
    Q_PROPERTY(int loadingGfxIdx READ loadingGfxIdx NOTIFY loadingChanged)
    Q_PROPERTY(bool isSelectEnabled READ isSelectEnabled NOTIFY actionChanged)
    Q_PROPERTY(int timeout READ timeout NOTIFY timeoutChanged)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY loadingChanged) // errors happen on switch attempts


public:
    SuperGfxCtl(QObject *parent, const QVariantList &args);

    ~SuperGfxCtl();

    QString vendorName();

    QString powerName();

    QString iconName();

    QString actionName();

    VendorList *vendorList();

    Q_INVOKABLE void revertVendor();

    Q_INVOKABLE void setVendor(int gfxIndex);

    int loadingGfxIdx();

    bool isSelectEnabled();

    int timeout();

    QString errorMessage();

signals:

    void stateChanged();

    void actionChanged();

    void loadingChanged();

    void timeoutChanged();

    void finishedSetVendorCall(QDBusPendingCallWatcher *);

    void finishedGetVendorCall(QDBusPendingCallWatcher *);

    void finishedGetPowerCall(QDBusPendingCallWatcher *);

private:
    GfxVendor vendor;
    GfxPower power;
    GfxAction action = GfxAction::NONE;

    quint32 vendorReply;

    int mLoadingGfxIdx = -1;

    bool isVfioEnabled;

    void setVendor(GfxVendor vendor);

    void getState();

    VendorList *currentList = nullptr, *oldList = nullptr;

    QString mErrorMessage;

    int mTimeout = 0;

    void reduceTimer();

    QTimer *timeoutTimer = new QTimer(this);

private slots:

    void finishSetVendorCall(QDBusPendingCallWatcher *);

    void finishGetVendorCall(QDBusPendingCallWatcher *);

    void finishGetPowerCall(QDBusPendingCallWatcher *);
};

#endif
