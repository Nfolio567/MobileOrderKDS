#include "service/network/KdsConfig.hpp"

#include <QNetworkAccessManager>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[]) {
  KdsConfig::load();

  QGuiApplication app(argc, argv);

  QQmlApplicationEngine engine;
  engine.loadFromModule("KDS-QML", "App");

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}