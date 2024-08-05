#include <NfoEditorQtBridge.hpp>

namespace NfoEditor {
void QtBridge::registerCompletionSource(const QString &completionSource) {
  m_autocomplete.registerCompletionSource(completionSource.toStdString());
}

QList<QString> QtBridge::autocomplete(const QString &completionSource,
                                      const QString &prefix) {
  const auto completer =
      m_autocomplete.getCompleter(completionSource.toStdString());
  const auto matches = completer.complete(prefix.toStdString());
  QList<QString> qResult;
  for (const auto &match : matches) {
    qResult.append(QString::fromStdString(match));
  }
  return qResult;
}
} // namespace NfoEditor