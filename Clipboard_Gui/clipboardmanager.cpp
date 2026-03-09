#include "clipboardmanager.h"
#include <QDebug>

ClipboardManager::ClipboardManager(QObject* parent)
    : QObject(parent)
{
    clipboard = QGuiApplication::clipboard();

    connect(clipboard, &QClipboard::dataChanged,
        this, &ClipboardManager::onClipboardChanged);
}

void ClipboardManager::onClipboardChanged()
{
    QString text = clipboard->text();

    if (!text.isEmpty())
    {
        qDebug() << "Clipboard:" << text;
        emit newClipboardText(text);
    }
}