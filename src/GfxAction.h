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
        LOGOUT, INTEGRATED, ASUS_GPU_MUX_DISABLE, NONE,
    };

    Q_ENUM(Id)

    ~GfxAction() override = default;

    static GfxAction &from(Id id) {
        static GfxAction logout(GfxAction::LOGOUT);
        static GfxAction integrated(GfxAction::INTEGRATED);
        static GfxAction asusGpuMuxDisable(GfxAction::ASUS_GPU_MUX_DISABLE);
        static GfxAction none(GfxAction::NONE);
        switch (id) {
            case LOGOUT:
                return logout;
            case INTEGRATED:
                return integrated;
            case ASUS_GPU_MUX_DISABLE:
                return asusGpuMuxDisable;
            default:
                return none;
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
