#include "GfxModeCandidate.h"
#include "GfxPower.h"
#include "GfxMode.h"
#include "DaemonController.h"
#include <algorithm>
#include <KLocalizedString>

GfxModeCandidate::Section GfxModeCandidate::section() const {
    if (current == target) {
        return Section::ACTIVE;
    }
    if (!GfxMode::supported().contains((GfxMode::Id) target)) {
        return Section::UNSUPPORTED;
    }
    QList<GfxMode::Id> a = {GfxMode::DEDICATED, GfxMode::HYBRID, GfxMode::EGPU};
    QList<GfxMode::Id> b = {GfxMode::COMPUTE, GfxMode::VFIO};
    if (a.contains((GfxMode::Id) current) && b.contains((GfxMode::Id) target)) {
        return Section::UNAVAILABLE;
    }
    return Section::AVAILABLE;
}

QString GfxModeCandidate::reason() const {
    // Assumption: UNAVAILABLE is for integrated-only candidates only
    if (section() == Section::UNAVAILABLE)
        return i18n("Switch to %1 is required", GfxMode::from(GfxMode::INTEGRATED).name());
    if (section() == Section::UNSUPPORTED && target == GfxMode::from(GfxMode::VFIO)) {
        return i18n("Disabled in configuration");
    }
    return {""};
}

QString GfxModeCandidate::displayName() const {
    return target.name();
}

QString GfxModeCandidate::displayIconName() const {
    return target.iconName(GfxPower::from(GfxPower::ACTIVE));
}

QString GfxModeCandidate::buttonText() const {
    switch (section()) {
        case Section::ACTIVE:
            return i18n("Active");
        case Section::AVAILABLE:
            return i18n("Available");
        case Section::UNAVAILABLE:
            return i18n("Unavailable");
        case Section::UNSUPPORTED:
            return i18n("Unsupported");
        default:
            return i18n("Unknown");
    }
}

QString GfxModeCandidate::buttonIconName() const {
    switch (section()) {
        case Section::ACTIVE:
            return GfxMode::from(GfxMode::DEDICATED).iconName(GfxPower::from(GfxPower::ACTIVE));
        case Section::AVAILABLE:
            return GfxMode::from(GfxMode::INTEGRATED).iconName(GfxPower::from(GfxPower::ACTIVE));
        default:
            return GfxMode::from(GfxMode::INTEGRATED).iconName(GfxPower::from(GfxPower::OFF));
    }
}

void GfxModeCandidate::realize() const {
    DaemonController::from().setMode(static_cast<quint32>((GfxMode::Id) target));
}

int GfxModeCandidateList::rowCount(const QModelIndex &p) const {
    return m_data.size();
}

QVariant GfxModeCandidateList::data(const QModelIndex &index, int role) const {
    switch (role) {
        case SECTION:
            return m_data[index.row()]->section();
        case REASON:
            return m_data[index.row()]->reason();
        case NAME:
            return m_data[index.row()]->displayName();
        case ICON:
            return m_data[index.row()]->displayIconName();
        case BUTTON_ICON:
            return m_data[index.row()]->buttonIconName();
        case BUTTON_TEXT:
            return m_data[index.row()]->buttonText();
    }
    return {};
}

QHash<int, QByteArray> GfxModeCandidateList::roleNames() const {
    static QHash<int, QByteArray> roles;
    roles[SECTION] = "section";
    roles[REASON] = "reason";
    roles[NAME] = "name";
    roles[ICON] = "icon";
    roles[BUTTON_TEXT] = "buttonText";
    roles[BUTTON_ICON] = "buttonIcon";
    return roles;
}

void GfxModeCandidateList::append(QObject *o) {
    m_data.append((GfxModeCandidate *) o);
}

void GfxModeCandidateList::freeAll() {
    qDeleteAll(m_data);
}

void GfxModeCandidateList::realize(int index) {
    m_data[index]->realize();
}

GfxModeCandidateList *GfxModeCandidateList::from() {
    auto list = new GfxModeCandidateList();
    for (auto i: GfxMode::all()) {
        auto candidate = new GfxModeCandidate(GfxMode::current(), GfxMode::from(i));
        list->append(candidate);
    }
    list->sortItems();
    return list;
}

void GfxModeCandidateList::sortItems() {
    struct Sort {
        bool operator()(const GfxModeCandidate *a, const GfxModeCandidate *b) {
            return a->section() < b->section();
        }
    };
    std::sort(m_data.begin(), m_data.end(), Sort());
}
