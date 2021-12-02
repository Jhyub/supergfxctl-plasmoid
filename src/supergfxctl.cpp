/*
    SPDX-FileCopyrightText: 2021 Janghyub Seo <jhyub06@gmail.com>
    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#include "supergfxctl.h"
#include <KLocalizedString>

supergfxctl::supergfxctl(QObject *parent, const QVariantList &args)
    : Plasma::Applet(parent, args),
      m_nativeText(i18n("Text coming from C++ plugin"))
{
}

supergfxctl::~supergfxctl()
{
}

QString supergfxctl::nativeText() const
{
    return m_nativeText;
}

K_PLUGIN_CLASS_WITH_JSON(supergfxctl, "metadata.json")

#include "supergfxctl.moc"
