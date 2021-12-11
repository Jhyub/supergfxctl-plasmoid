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
    Q_PROPERTY(QString vendorName READ gfxVendorName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString powerName READ gfxPowerName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString iconName READ gfxIconName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString actionName READ gfxActionName NOTIFY gfxActionChanged)
    Q_PROPERTY(bool isSelectEnabled READ isSelectEnabled NOTIFY gfxActionChanged)


public:
    SuperGfxCtl(QObject *parent, const QVariantList &args );
    ~SuperGfxCtl();
    QString gfxVendorName();
    QString gfxPowerName();
    QString gfxIconName();
    QString gfxActionName();
    Q_INVOKABLE void revertVendor();
    bool isSelectEnabled();

signals:
    void gfxStateChanged();
    void gfxActionChanged();

private:
    GfxVendor vendor;
    GfxPower power;
    GfxAction action = GfxAction::NONE;
    void setVendor(GfxVendor vendor);
    void gfxGet();
};

#endif
