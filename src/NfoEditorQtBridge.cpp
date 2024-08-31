#include <NfoEditorQtBridge.hpp>

#include <NfoEditorUtils.hpp>
#include <NfoEditorXml.hpp>

#include <algorithm>
#include <iterator>

#include <QUrl>

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
  const auto completer = m_autocomplete.getCompleter(completionSource.toStdString());
  completer.addCandidate(candidate.toStdString());
}

void QtBridge::exportCompletionData() const { m_autocomplete.exportCompletionData(); }

void QtBridge::saveToXml(const QUrl &filePath, const QString &title,
                         const QString &studio, const QList<QString> &actors,
                         const QList<QString> &tags) {
  static const auto qStringToStd = [](const auto &actor) {
    return actor.toStdString();
  };

  std::vector<std::string> stdActors;
  stdActors.reserve(actors.size());
  std::vector<std::string> stdTags;
  stdTags.reserve(tags.size());
  std::ranges::transform(actors, std::back_inserter(stdActors), qStringToStd);
  std::ranges::transform(tags, std::back_inserter(stdTags), qStringToStd);

  const NfoData data{title.toStdString(), studio.toStdString(), stdActors,
                     stdTags};
  data.saveToFile(filePath.path().toStdString());
}
} // namespace NfoEditor