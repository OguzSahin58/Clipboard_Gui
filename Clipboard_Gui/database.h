#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <sqlite3.h>

class Database : public QObject
{
    Q_OBJECT   // ⚠ REQUIRED for signals/slots

public:
    explicit Database(QObject* parent = nullptr);

    bool open(const QString& path);
    void createTable();

    void insertText(const QString& text);
	void loadHistory();
	

signals:
    void historyLoaded(QStringList items);

private:
    sqlite3* db;
};

#endif