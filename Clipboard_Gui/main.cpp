#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "clipboardmanager.h"
#include "clipboardmodel.h"

#include "database.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    Database db; 
    db.open("database.db");
    db.createTable();


    ClipboardManager manager;
    ClipboardModel model;

    QObject::connect(&db,
        &Database::historyLoaded,
        &model,
        &ClipboardModel::loadFromHistory);

    QObject::connect(&manager,
        &ClipboardManager::newClipboardText,
        &model,
        &ClipboardModel::addClipboardItem);

    QObject::connect(&manager,
        &ClipboardManager::newClipboardText,
        [&](QString text)
        {
            db.insertText(text);
        });
    QObject::connect(&model,
        &ClipboardModel::clipboardItemSelected,
        &manager,
        &ClipboardManager::setClipboardText);

    QObject::connect(&model,
        &ClipboardModel::deleteAllRequested,
        &db,
		&Database::deleteAllHistory);

    db.loadHistory();

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("clipboardModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/clipboard_gui/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}