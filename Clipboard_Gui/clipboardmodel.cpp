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

Q_INVOKABLE void ClipboardModel::selectItem(int index)
{
    if (index < 0 || index >= items.size())
        return;

    const QString item = items.at(index);
    emit clipboardItemSelected(item);
}

void ClipboardModel::addClipboardItem(QString text)
{
    beginInsertRows(QModelIndex(), 0, 0);
    items.prepend(text);
    endInsertRows();
}

void ClipboardModel::loadFromHistory(QStringList history)
{
    beginResetModel();
    items = history;
    endResetModel();
}