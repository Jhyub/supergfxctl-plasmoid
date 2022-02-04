#ifndef PLASMA_SUPERGFXCTL_GFXACTION_H
#define PLASMA_SUPERGFXCTL_GFXACTION_H

#include <QObject>
#include <QtQml/qqmlengine.h>

class GfxAction : public QObject {
Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Is provided by backend")
    Q_PROPERTY(QString name READ name CONSTANT)
public:
    enum Id {
        LOGOUT, REBOOT, INTEGRATED, NONE,
    };

    Q_ENUM(Id)

    ~GfxAction() override = default;

    static GfxAction &from(Id id) {
        static GfxAction logout(GfxAction::LOGOUT);
        static GfxAction reboot(GfxAction::REBOOT);
        static GfxAction integrated(GfxAction::INTEGRATED);
        static GfxAction none(GfxAction::NONE);
        switch (id) {
            case LOGOUT:
                return logout;
            case REBOOT:
                return reboot;
            case INTEGRATED:
                return integrated;
            default:
                return none;
        }
    }

    QString name() const;

    static GfxAction &current();

private:
    explicit GfxAction(Id id) : id(id) {}

    Id id;
};

#endif //PLASMA_SUPERGFXCTL_GFXACTION_H
