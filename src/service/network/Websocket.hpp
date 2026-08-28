#pragma once

#include "src/service/network/KdsConfig.hpp"
#include <QObject>
#include <QUrl>
#include <QWebSocket>

class Websocket : public QObject {
  Q_OBJECT

  public:
    explicit Websocket(QObject *parent = nullptr);
    void connectSocket();

  signals:
    void connected();
    void textMessage();
    void disconnected();

  private:
    const QUrl KDS_WEBSOCKET_ENDPOINT = QUrl(KdsConfig::websocketEndpoint);
    QWebSocket m_websocket;
};
