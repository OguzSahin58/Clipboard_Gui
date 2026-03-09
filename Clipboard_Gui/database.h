#pragma once

#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <sqlite3.h>

class Database
{
public:
    Database();
    ~Database();

    bool open(const QString& path);
    void createTable();

    void insertText(const QString& text);

private:
    sqlite3* db;
};

#endif