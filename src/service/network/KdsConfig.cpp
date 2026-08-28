#include "KdsConfig.hpp"
#include <QSettings>
#include <QString>

QString KdsConfig::firstEndpoint;
QString KdsConfig::websocketEndpoint;
QString KdsConfig::kdsAccessToken;

void KdsConfig::load() {
  QSettings settings("./resources/setting.ini", QSettings::IniFormat);

  firstEndpoint = settings.value("Server/FirstEndpoint").toString();
  websocketEndpoint = settings.value("Server/WebsocketEndpoint").toString();
  kdsAccessToken = settings.value("Server/KdsAccessToken").toString();
}
