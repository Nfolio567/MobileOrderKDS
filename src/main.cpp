#include "service/KdsService.hpp"
#include "service/network/HttpClient.hpp"
#include "service/network/Websocket.hpp"
#include "service/network/KdsConfig.hpp"

#include <QNetworkAccessManager>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QtCore/QDebug>

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  // 開発モードか否か
  const int MODE_RESULT = strcmp(argv[1], "-D");
  bool isDev = (MODE_RESULT == 0);

  // サービスクラス初期化ゾーン
  KdsConfig::load(isDev);
  auto *client = new HttpClient();
  auto *socket = new Websocket();
  KdsService kdsService(
    &app,
    client,
    socket
  );

  // QMLエンジン初期化ゾーン
  QQmlApplicationEngine engine;
  qmlRegisterSingletonInstance<HttpClient>(
    "Kds",
    1, 0,
    "HttpClient",
    client
  );
  qmlRegisterSingletonInstance<Websocket>(
    "Kds",
    1, 0,
    "WebSocket",
    socket
  );
  engine.loadFromModule("KDS-QML", "App");

  // Httpリクエストおくって、WS初期化まで
  kdsService.awaitOrders();

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}