#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "clipboardmanager.h"
#include "clipboardmodel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    ClipboardManager manager;
    ClipboardModel model;

    QObject::connect(&manager,
        &ClipboardManager::newClipboardText,
        &model,
        &ClipboardModel::addClipboardItem);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("clipboardModel", &model);

    engine.load(QUrl(QStringLiteral("qrc:/qt/qml/clipboard_gui/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}