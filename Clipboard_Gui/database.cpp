#include "database.h"

#include <sqlite3.h>
#include <QDebug>
#include <qfile.h>

Database::Database()
{
    db = nullptr;
}

Database::~Database()
{
    if (db)
        sqlite3_close(db);
}

bool Database::open(const QString& path)
{
    if (sqlite3_open(path.toStdString().c_str(), &db))
    {
        qDebug() << "Database open failed";
        return false;
    }

    qDebug() << "Database opened";
    return true;
}

void Database::createTable()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS clipboard_history ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT,"
        "created_at DATETIME DEFAULT CURRENT_TIMESTAMP);";

    char* err = nullptr;

    if (sqlite3_exec(db, sql, nullptr, nullptr, &err) != SQLITE_OK)
    {
        qDebug() << "SQL error:" << err;
        sqlite3_free(err);
    }
}

void Database::insertText(const QString& text)
{
    QString sql = "INSERT INTO clipboard_history(content) VALUES(?);";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(db, sql.toStdString().c_str(), -1, &stmt, nullptr);

    sqlite3_bind_text(
        stmt,
        1,
        text.toStdString().c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
}