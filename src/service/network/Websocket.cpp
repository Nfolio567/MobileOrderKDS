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
    [this]() {
      emit Websocket::connected();
    }
  );

  connect(
    &m_websocket,
    &QWebSocket::textMessageReceived,
    this,
    [this]() {
      emit Websocket::textMessage();
    }
  );

  connect(
    &m_websocket,
    &QWebSocket::disconnected,
    this,
    [this]() {
      emit Websocket::disconnected();
    }
  );
}

void Websocket::connectSocket() {
  m_websocket.open(KDS_WEBSOCKET_ENDPOINT);
}
