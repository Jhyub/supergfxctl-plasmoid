#ifndef PLASMA_SUPERGFXCTL_GFXMODECANDIDATE_H
#define PLASMA_SUPERGFXCTL_GFXMODECANDIDATE_H

#include<QAbstractListModel>
#include<QDBusConnection>
#include "GfxMode.h"
#include "GfxAction.h"

class GfxModeCandidate : public QObject {
Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("Is provided by backend")
    Q_PROPERTY(Section section READ section CONSTANT)
    Q_PROPERTY(QString reason READ reason CONSTANT)
    Q_PROPERTY(QString name READ displayName CONSTANT)
    Q_PROPERTY(QString icon READ displayIconName CONSTANT)
    Q_PROPERTY(QString buttonText READ buttonText CONSTANT)
    Q_PROPERTY(QString buttonIcon READ buttonIconName CONSTANT)

public:
    enum Section {
        ACTIVE,
        AVAILABLE,
        UNAVAILABLE,
        UNSUPPORTED,
    };

    Q_ENUM(Section)

    GfxModeCandidate(GfxMode &current, GfxMode &target) : current(current), target(target) {};

    Section section() const;

    QString reason() const;

    QString displayName() const;

    QString displayIconName() const;

    QString buttonText() const;

    QString buttonIconName() const;

    void realize() const;

private:
    GfxMode &current;
    GfxMode &target;
};

class GfxModeCandidateList : public QAbstractListModel {
Q_OBJECT
public:
    enum ModelRoles {
        SECTION = Qt::UserRole + 1,
        REASON,
        NAME,
        ICON,
        BUTTON_ICON,
        BUTTON_TEXT,
    };

    int rowCount(const QModelIndex &p) const;

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    void append(QObject *o);

    void freeAll();

    void realize(int index);

    static GfxModeCandidateList *from();

private:

    explicit GfxModeCandidateList(QObject *parent = nullptr) : QAbstractListModel(parent) {}

    void sortItems();

    QList<GfxModeCandidate *> m_data;
};

#endif //PLASMA_SUPERGFXCTL_GFXMODECANDIDATE_H
