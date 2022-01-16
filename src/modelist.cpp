//
// Created by jhyub on 12/12/21.
//

#include "modelist.h"

#include<QAbstractListModel>
#include<algorithm>

ModeList::ModeList(QObject *parent) : QAbstractListModel(parent) {

}

int ModeList::rowCount(const QModelIndex &p) const {
    return mData.size();
}

QVariant ModeList::data(const QModelIndex &index, int role) const {
    switch (role) {
        case NameRole:
            return mData[index.row()]->property("name");
        case IconNameRole:
            return mData[index.row()]->property("iconName");
        case RequirementRole:
            return mData[index.row()]->property("requirement");
        case SectionRole:
            return mData[index.row()]->property("section");
        case GfxModeRole:
            return mData[index.row()]->property("gfxMode");
        default:
            break;
    }
    return {};
}

QHash<int, QByteArray> ModeList::roleNames() const {
    static QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconNameRole] = "iconName";
    roles[RequirementRole] = "requirement";
    roles[SectionRole] = "section";
    roles[GfxModeRole] = "gfxMode";
    return roles;
}

void ModeList::append(QObject *o) {
    mData.append(o);
}

void ModeList::orderSections() {
    struct Sort {
        bool operator()(const QObject *a, const QObject *b) {
            return a->property("section").toInt() < b->property("section").toInt();
        }
    };
    std::sort(mData.begin(), mData.end(), Sort());
}
