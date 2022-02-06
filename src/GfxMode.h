#ifndef PLASMA_SUPERGFXCTL_GFXMODE_H
#define PLASMA_SUPERGFXCTL_GFXMODE_H

#include <QString>
#include <QObject>
#include <QtQml/qqmlengine.h>
#include "GfxAction.h"
#include "GfxPower.h"

class GfxMode : public QObject {
Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Is provided by backend")
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    enum Id {
        HYBRID, DEDICATED, INTEGRATED, COMPUTE, VFIO, EGPU, NONE,
    };

    ~GfxMode() override = default;

    static GfxMode &from(Id id) {
        static GfxMode hybrid(HYBRID);
        static GfxMode dedicated(DEDICATED);
        static GfxMode integrated(INTEGRATED);
        static GfxMode compute(COMPUTE);
        static GfxMode vfio(VFIO);
        static GfxMode egpu(EGPU);
        static GfxMode none(NONE);
        switch (id) {
            case HYBRID:
                return hybrid;
            case DEDICATED:
                return dedicated;
            case INTEGRATED:
                return integrated;
            case COMPUTE:
                return compute;
            case VFIO:
                return vfio;
            case EGPU:
                return egpu;
            default:
                return none;
        }
    }

    explicit operator GfxMode::Id() const;

    bool operator==(GfxMode &other) const;

    static GfxMode &current();

    static GfxMode &pending();

    static QVector<Id> supported();

    static QVector<Id> all();

    QString name() const;

    QString iconName(GfxPower &power) const;

private:
    explicit GfxMode(Id id) : id(id) {}

    Id id;
};

#endif //PLASMA_SUPERGFXCTL_GFXMODE_H
