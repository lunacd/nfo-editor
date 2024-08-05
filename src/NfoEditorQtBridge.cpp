#include <NfoEditorQtBridge.hpp>

#include <NfoEditorUtils.hpp>

namespace NfoEditor {
void QtBridge::registerCompletionSource(const QString &completionSource) {
  m_autocomplete.registerCompletionSource(completionSource.toStdString());
}

QList<QString> QtBridge::autocomplete(const QString &completionSource,
                                      const QString &prefix) {
  const auto completer =
      m_autocomplete.getCompleter(completionSource.toStdString());
  const auto lowerPrefix = toLower(prefix.toStdString());
  const auto matches = completer.complete(lowerPrefix);
  QList<QString> qResult;
  for (const auto &match : matches) {
    qResult.append(QString::fromStdString(match));
  }
  return qResult;
}
} // namespace NfoEditor