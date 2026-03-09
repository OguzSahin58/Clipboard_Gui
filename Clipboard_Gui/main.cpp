#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "clipboardmanager.h"
#include "clipboardmodel.h"

#include "database.h"

int main(int argc, char* argv[])
{

    Database db; 
    db.open("database.db");
    db.createTable();

    QGuiApplication app(argc, argv);

    ClipboardManager manager;
    ClipboardModel model;

	// mode.loadFromDatabase(db.loadHistory());

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

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("clipboardModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/clipboard_gui/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}