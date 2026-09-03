#include "KdsConfig.hpp"
#include <QSettings>
#include <QString>

QString KdsConfig::firstEndpoint;
QString KdsConfig::websocketEndpoint;
QString KdsConfig::kdsAccessToken;

void KdsConfig::load(bool isDev) {
  QString mainKey = "Server";
  if (isDev) {
    mainKey = "Dev";
  }

  QSettings settings("./resources/setting.ini", QSettings::IniFormat);

  firstEndpoint = settings.value(mainKey + "/FirstEndpoint").toString();
  websocketEndpoint = settings.value(mainKey + "/WebsocketEndpoint").toString();
  kdsAccessToken = settings.value("Server/KdsAccessToken").toString();
}
