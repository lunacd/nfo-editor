#include <QApplication>
#include <QQmlApplicationEngine>

auto main(int argc, char **argv) -> int {
  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.load(QUrl(QStringLiteral("qrc:/NfoEditor.qml")));

  return QApplication::exec();
}