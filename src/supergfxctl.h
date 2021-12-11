/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef SUPERGFXCTL_H
#define SUPERGFXCTL_H


#include <Plasma/Applet>

enum class GfxVendor {
    NVIDIA,
    INTEGRATED,
    COMPUTE,
    VFIO,
    EGPU,
    HYBRID,
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

class SuperGfxCtl : public Plasma::Applet
{
    Q_OBJECT
    Q_PROPERTY(QString vendorName READ vendorName NOTIFY stateChanged)
    Q_PROPERTY(QString powerName READ powerName NOTIFY stateChanged)
    Q_PROPERTY(QString iconName READ iconName NOTIFY stateChanged)
    Q_PROPERTY(QString actionName READ actionName NOTIFY actionChanged)
    Q_PROPERTY(bool isSelectEnabled READ isSelectEnabled NOTIFY actionChanged)


public:
    SuperGfxCtl(QObject *parent, const QVariantList &args );
    ~SuperGfxCtl();
    QString vendorName();
    QString powerName();
    QString iconName();
    QString actionName();
    Q_INVOKABLE void revertVendor();
    bool isSelectEnabled();

signals:
    void stateChanged();
    void actionChanged();

private:
    GfxVendor vendor;
    GfxPower power;
    GfxAction action = GfxAction::NONE;
    void setVendor(GfxVendor vendor);
    void getState();
};

#endif
