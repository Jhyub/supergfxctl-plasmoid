//
// Created by jhyub on 12/12/21.
//

#include "vendorlist.h"

#include<QAbstractListModel>
#include<algorithm>

VendorList::VendorList(QObject *parent) : QAbstractListModel(parent) {

}

int VendorList::rowCount(const QModelIndex &p) const {
    return mData.size();
}

QVariant VendorList::data(const QModelIndex &index, int role) const {
    switch (role) {
        case NameRole:
            return mData[index.row()]->property("name");
        case IconNameRole:
            return mData[index.row()]->property("iconName");
        case RequirementRole:
            return mData[index.row()]->property("requirement");
        case SectionRole:
            return mData[index.row()]->property("section");
        case IndexRole:
            return mData[index.row()]->property("index");
        default:
            break;
    }
    return {};
}

QHash<int, QByteArray> VendorList::roleNames() const {
    static QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[IconNameRole] = "iconName";
    roles[RequirementRole] = "requirement";
    roles[SectionRole] = "section";
    roles[IndexRole] = "index";
    return roles;
}

void VendorList::append(QObject *o) {
    mData.append(o);
}

void VendorList::orderSections() {
    struct Sort {
        bool operator()(const QObject *a, const QObject *b) {
            return a->property("section").toInt() < b->property("section").toInt();
        }
    };
    std::sort(mData.begin(), mData.end(), Sort());
}
