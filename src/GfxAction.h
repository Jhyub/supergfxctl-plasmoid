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
        LOGOUT, REBOOT, SWITCH_TO_INTEGRATED, ASUS_EGPU_DISABLE, NOTHING,
    };

    Q_ENUM(Id)

    ~GfxAction() override = default;

    static GfxAction &from(Id id) {
        static GfxAction logout(GfxAction::LOGOUT);
        static GfxAction reboot(GfxAction::REBOOT);
        static GfxAction switchToIntegrated(GfxAction::SWITCH_TO_INTEGRATED);
        static GfxAction asusEgpuDisable(GfxAction::ASUS_EGPU_DISABLE);
        static GfxAction nothing(GfxAction::NOTHING);
        switch (id) {
            case LOGOUT:
                return logout;
            case REBOOT:
                return reboot;
            case SWITCH_TO_INTEGRATED:
                return switchToIntegrated;
            case ASUS_EGPU_DISABLE:
                return asusEgpuDisable;
            default:
                return nothing;
        }
    }

    explicit operator GfxAction::Id() const;

    bool operator==(GfxAction &other) const;

    QString name() const;

    static GfxAction &pending();

private:
    explicit GfxAction(Id id) : id(id) {}

    Id id;
};

#endif //PLASMA_SUPERGFXCTL_GFXACTION_H
