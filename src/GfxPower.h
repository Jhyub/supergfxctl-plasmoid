#ifndef PLASMA_SUPERGFXCTL_GFXPOWER_H
#define PLASMA_SUPERGFXCTL_GFXPOWER_H

#include <QObject>
#include <QtQml/qqmlengine.h>

class GfxPower : public QObject {
Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Is provided by backend")
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString iconName READ iconName CONSTANT)
public:
    enum Id {
        ACTIVE, SUSPENDED, OFF, ASUS_DISABLED, ASUS_MUX_DISCRETE, UNKNOWN,
    };

    ~GfxPower() override = default;

    static GfxPower &from(Id id) {
        static GfxPower active(ACTIVE);
        static GfxPower suspended(SUSPENDED);
        static GfxPower off(OFF);
        static GfxPower asusDisabled(ASUS_DISABLED);
        static GfxPower asusMuxDiscrete(ASUS_MUX_DISCRETE);
        static GfxPower unknown(UNKNOWN);
        switch (id) {
            case ACTIVE:
                return active;
            case SUSPENDED:
                return suspended;
            case OFF:
                return off;
            case ASUS_DISABLED:
                return asusDisabled;
            case ASUS_MUX_DISCRETE:
                return asusMuxDiscrete;
            case UNKNOWN:
                return unknown;
            default:
                return unknown;
        }
    }

    explicit operator GfxPower::Id() const;

    bool operator==(GfxPower &other) const;

    static GfxPower &current();

    QString name() const;

    QString iconName() const;

private:
    explicit GfxPower(Id id) : id(id) {}

    static QMap<Id, GfxPower *> map;

    Id id;
};

#endif //PLASMA_SUPERGFXCTL_GFXPOWER_H
