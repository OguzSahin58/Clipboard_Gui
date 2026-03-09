#pragma once
#ifndef CLIPBOARDMODEL_H
#define CLIPBOARDMODEL_H

#include <QAbstractListModel>
#include <QStringList>

class ClipboardModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        TextRole = Qt::UserRole + 1
    };

    ClipboardModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void addClipboardItem(QString text);

private:
    QStringList items;
};

#endif