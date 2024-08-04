#pragma once

#include <QObject>

class NfoEditorQtBridge : public QObject {
  Q_OBJECT
public:
  explicit NfoEditorQtBridge(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE int reken_tijden_uit() { return 1; }
};