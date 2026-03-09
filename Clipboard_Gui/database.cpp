#include "database.h"

#include <sqlite3.h>
#include <QDebug>
#include <qfile.h>

Database::Database(QObject* parent)
    : QObject(parent), db(nullptr)
{
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

void Database::loadHistory()
{
    QList<QString> history;
    const char* sql = "SELECT content FROM clipboard_history ORDER BY created_at DESC;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char* text = sqlite3_column_text(stmt, 0);
        history.append(QString::fromUtf8(reinterpret_cast<const char*>(text)));
    }
    sqlite3_finalize(stmt);
	emit historyLoaded(history);
}