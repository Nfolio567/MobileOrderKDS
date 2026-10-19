#include "service/KdsService.hpp"
#include "service/network/HttpClient.hpp"
#include "service/network/Websocket.hpp"
#include "service/network/KdsConfig.hpp"
#include "model/OrderListModel.hpp"

#include <QGuiApplication>
#include <QtQml>
#include <QString>

#include "model/OrderListCookFilter.hpp"
#include "model/OrderListProvidingFilter.hpp"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QString string = "";

  bool isDev = false;

  // 開発モードか否か
  if (argc > 1) {
    const int MODE_RESULT = strcmp(argv[1], "-D");
    isDev = (MODE_RESULT == 0);
  }

  // クラス初期化ゾーン
  KdsConfig::load(isDev);
  auto *client = new HttpClient();
  auto *socket = new Websocket();
  auto *orderListModel = new OrderListModel(&app, client, socket);
  KdsService kdsService(
    &app,
    client,
    socket
  );

  auto *beforeCooking = new OrderListCookFilter(&app);
  auto *beforeProviding = new OrderListProvidingFilter(&app);

  beforeCooking->setSourceModel(orderListModel);
  beforeProviding->setSourceModel(orderListModel);

  // QMLエンジン初期化ゾーン
  QQmlApplicationEngine engine;
  qmlRegisterSingletonInstance<OrderListCookFilter>(
    "Kds",
    1, 0,
    "OrderListCookModel",
    beforeCooking
    );
  qmlRegisterSingletonInstance<OrderListProvidingFilter>(
    "Kds",
    1, 0,
    "OrderListProvidingModel",
    beforeProviding
  );

  engine.loadFromModule("QMLModules", "App");

  // Httpリクエストおくって、WS初期化まで
  kdsService.awaitOrders();

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
