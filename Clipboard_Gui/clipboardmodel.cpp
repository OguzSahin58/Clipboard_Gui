#include "clipboardmodel.h"

ClipboardModel::ClipboardModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

int ClipboardModel::rowCount(const QModelIndex&) const
{
    return items.size();
}

QVariant ClipboardModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == TextRole)
        return items.at(index.row());

    return QVariant();
}

QHash<int, QByteArray> ClipboardModel::roleNames() const
{
    return {
        {TextRole, "text"}
    };
}

void ClipboardModel::addClipboardItem(QString text)
{
    beginInsertRows(QModelIndex(), 0, 0);
    items.prepend(text);
    endInsertRows();
}