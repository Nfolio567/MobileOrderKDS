#include "Websocket.hpp"
#include "KdsConfig.hpp"
#include <QObject>
#include <QWebSocket>

Websocket::Websocket(QObject *parent) :
  QObject(parent),
  m_request(KDS_WEBSOCKET_ENDPOINT)
{
  connect( // On Connected
    &m_websocket,
    &QWebSocket::connected,
    this,
    [this]() -> void {
      emit Websocket::connected();
    }
  );

  connect(
    &m_websocket,
    &QWebSocket::textMessageReceived,
    this,
    [this](const QString &message) -> void {
      emit Websocket::textMessage(message);
    }
  );

  connect(
    &m_websocket,
    &QWebSocket::disconnected,
    this,
    [this]() -> void {
      emit Websocket::disconnected();
    }
  );
}

void Websocket::connectSocket() {
  m_request.setRawHeader(
    "Authorization",
    "Bearer " + KdsConfig::kdsAccessToken.toUtf8()
  );
  m_websocket.open(m_request);
}
