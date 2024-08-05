#include <NfoEditorQtBridge.hpp>

namespace NfoEditor {
QList<QString> QtBridge::autocomplete(const QString &prefix) {
  auto matches = m_autocomplete.complete(prefix.toStdString());
  QList<QString> qResult;
  for (const auto &match : matches) {
    qResult.append(QString::fromStdString(match));
  }
  return qResult;
}
} // namespace NfoEditor