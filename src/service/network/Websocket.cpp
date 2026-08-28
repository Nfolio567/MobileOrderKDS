#include "Websocket.hpp"
#include <QObject>
#include <QWebSocket>

Websocket::Websocket(QObject *parent) :
  QObject(parent)
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
    [this]() -> void {
      emit Websocket::textMessage();
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
  m_websocket.open(KDS_WEBSOCKET_ENDPOINT);
}
