#include "KdsConfig.hpp"
#include <QSettings>

void KdsConfig::load() {
  QSettings settings("./resources/setting.ini", QSettings::IniFormat);

  firstEndpoint = settings.value("Server/FirstEndpoint").toString();
  websocketEndpoint = settings.value("Server/WebsocketEndpoint").toString();
  kdsAccessToken = settings.value("Server/KdsAccessToken").toString();
}
