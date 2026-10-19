#include "KdsConfig.hpp"
#include <QSettings>
#include <QString>

QString KdsConfig::firstEndpoint;
QString KdsConfig::websocketEndpoint;
QString KdsConfig::kdsAccessToken;

// 設定ファイルから色々読み込み
void KdsConfig::load(const bool isDev) {
  QString mainKey = "Server";
  if (isDev) {
    mainKey = "Dev";
  }

  const QSettings settings("./resources/setting.ini", QSettings::IniFormat);

  firstEndpoint = settings.value(mainKey + "/FirstEndpoint").toString();
  websocketEndpoint = settings.value(mainKey + "/WebsocketEndpoint").toString();
  kdsAccessToken = settings.value("Server/KdsAccessToken").toString();
}
