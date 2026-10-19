#pragma once

#include "src/service/network/KdsConfig.hpp"
#include <QObject>
#include <QWebSocket>

class Websocket : public QObject {
  Q_OBJECT

  public:
    explicit Websocket(QObject *parent = nullptr);
    void connectSocket();

  signals:
    void connected();
    void textMessage(const QJsonDocument &message);
    void disconnected();
    void error(const QString &message);

  private:
    const QUrl KDS_WEBSOCKET_ENDPOINT = QUrl(KdsConfig::websocketEndpoint);
    QWebSocket m_websocket;
    QNetworkRequest m_request;  
};
