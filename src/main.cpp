#include "service/KdsService.hpp"
#include "service/network/HttpClient.hpp"
#include "service/network/Websocket.hpp"
#include "service/network/KdsConfig.hpp"
#include "model/OrderListModel.hpp"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QFontDatabase>
#include <QString>
#include <QDirIterator>

#include "model/OrderListCookFilter.hpp"
#include "model/OrderListProvidingFilter.hpp"

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

  QDirIterator it(":/", QDirIterator::Subdirectories);
  while (it.hasNext()) qDebug() << it.next();


  // フォントロード
  const QString atkinsonRoot = ":/qt/qml/QMLModules/fonts/Atkinson_Hyperlegible/AtkinsonHyperlegible-%1.ttf";
  const int atkinsonFontID =
    QFontDatabase::addApplicationFont(atkinsonRoot.arg("Regular"));
  QFontDatabase::addApplicationFont(atkinsonRoot.arg("Bold"));

  const QString zenKakuGothicNewRoot = ":/qt/qml/QMLModules/fonts/Zen_Kaku_Gothic_New/ZenKakuGothicNew-%1.ttf";
  const int zenKakuGothicNewFontID =
    QFontDatabase::addApplicationFont(zenKakuGothicNewRoot.arg("Regular"));
  QFontDatabase::addApplicationFont(zenKakuGothicNewRoot.arg("Medium"));
  QFontDatabase::addApplicationFont(zenKakuGothicNewRoot.arg("Bold"));

  // フォントのラベル取得
  const QStringList atkinson = QFontDatabase::applicationFontFamilies(atkinsonFontID);
  const QStringList zenKakuGothicNew = QFontDatabase::applicationFontFamilies(zenKakuGothicNewFontID);

  // ちゃんとうまく読み込めてたらセットする。ダメだったらワーニング出す
  if (!atkinson.isEmpty() && !zenKakuGothicNew.isEmpty()) {
    QFont font;
    font.setFamilies({
      atkinson.first(),
      zenKakuGothicNew.first(),
    });
    app.setFont(font);
  } else {
    qWarning() << "Failed load fonts";
  }


  // 開発モードか否か
  bool isDev = false;
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
