#pragma once
#ifndef CLIPBOARDMANAGER_H
#define CLIPBOARDMANAGER_H

#include <QObject>
#include <QClipboard>
#include <QGuiApplication>

class ClipboardManager : public QObject
{
    Q_OBJECT

public:
    explicit ClipboardManager(QObject* parent = nullptr);

signals:
    void newClipboardText(QString text);

private slots:
    void onClipboardChanged();

public slots:
    void setClipboardText(QString text);

private:
    QClipboard* clipboard;
};

#endif