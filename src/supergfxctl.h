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

class SuperGFXCtl : public Plasma::Applet
{
    Q_OBJECT
    Q_PROPERTY(QString vendorName READ gfxVendorName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString powerName READ gfxPowerName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString iconName READ gfxIconName NOTIFY gfxStateChanged)

public:
    SuperGFXCtl( QObject *parent, const QVariantList &args );
    ~SuperGFXCtl();
    QString gfxVendorName();
    QString gfxPowerName();
    QString gfxIconName();

signals:
    void gfxStateChanged();

private:
    void gfxGet();
    GfxVendor vendor;
    GfxPower power;
    GfxAction lastAction;
};

#endif
