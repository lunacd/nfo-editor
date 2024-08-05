#include <NfoEditorQtBridge.hpp>

#include <NfoEditorUtils.hpp>

namespace NfoEditor {
void QtBridge::registerCompletionSource(const QString &completionSource) {
  m_autocomplete.registerCompletionSource(completionSource.toStdString());
}

QList<QString> QtBridge::autocomplete(const QString &completionSource,
                                      const QString &prefix) {
  // Convert prefix to lowercase before matching
  const auto lowerPrefix = toLower(prefix.toStdString());

  // Query backend for completion
  const auto completer =
      m_autocomplete.getCompleter(completionSource.toStdString());
  const auto matches = completer.complete(lowerPrefix);
  QList<QString> qResult;
  for (const auto &match : matches) {
    qResult.append(QString::fromStdString(match));
  }
  return qResult;
}

void QtBridge::addCompletionCandidate(const QString &completionSource,
                                      const QString &candidate) {
  auto completer = m_autocomplete.getCompleter(completionSource.toStdString());
  completer.addCandidate(candidate.toStdString());
}

void QtBridge::exportCompletionData() { m_autocomplete.exportCompletionData(); }
} // namespace NfoEditor