//
// Created by jhyub on 12/12/21.
//

#ifndef PLASMA_SUPERGFXCTL_VENDORLIST_H
#define PLASMA_SUPERGFXCTL_VENDORLIST_H

#include<QAbstractListModel>

class VendorList : public QAbstractListModel {
Q_OBJECT

public:
    enum ModelRoles {
        NameRole = Qt::UserRole + 1,
        IconNameRole,
        RequirementRole, // 0 -> none, 1 -> vfio config, 2  -> integrated, based on current state
        SectionRole, // 0 -> active, 1 -> available, 2 -> unavailable
        GfxIndexRole, // index of enum, 0 -> nvidia, 1 -> integrated, ...
    };

    explicit VendorList(QObject *parent = nullptr);

    int rowCount(const QModelIndex &p) const;

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    void append(QObject *o);

    void orderSections();

private:
    QList<QObject *> mData;
};

#endif //PLASMA_SUPERGFXCTL_VENDORLIST_H
