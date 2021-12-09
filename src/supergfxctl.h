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

class SuperGfxCtl : public Plasma::Applet
{
    Q_OBJECT
    Q_PROPERTY(QString vendorName READ gfxVendorName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString powerName READ gfxPowerName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString iconName READ gfxIconName NOTIFY gfxStateChanged)
    Q_PROPERTY(QString wantedName READ wantedVendorName NOTIFY wantedChanged)
    Q_PROPERTY(bool isSelectEnabled READ isSelectEnabled NOTIFY wantedChanged)


public:
    SuperGfxCtl(QObject *parent, const QVariantList &args );
    ~SuperGfxCtl();
    QString gfxVendorName();
    QString gfxPowerName();
    QString gfxIconName();
    QString wantedVendorName();
    Q_INVOKABLE void revertWanted();
    bool isSelectEnabled();
    void gfxGet();

signals:
    void gfxStateChanged();
    void wantedChanged();

private:
    GfxVendor vendor;
    GfxPower power;
    GfxVendor wanted;
    void setVendor(GfxVendor vendor);
    bool isWantedInit = false;
};

#endif
