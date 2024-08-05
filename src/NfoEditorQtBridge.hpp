#pragma once

#include <QObject>

#include <NfoEditorAutocomplete.hpp>

namespace NfoEditor {
class QtBridge : public QObject {
  Q_OBJECT
public:
  explicit QtBridge(QObject *parent = nullptr) : QObject(parent) {}
  Q_INVOKABLE void registerCompletionSource(const QString &completionSource);
  Q_INVOKABLE QList<QString> autocomplete(const QString &completionSource,
                                          const QString &prefix);

private:
  Autocomplete m_autocomplete;
};
} // namespace NfoEditor