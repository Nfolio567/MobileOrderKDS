#pragma once

#include <QSettings>
#include <QString>

class KdsConfig {  
  public:
    static QString firstEndpoint;
    static QString websocketEndpoint;
    static QString kdsAccessToken;

    static void load();
};
