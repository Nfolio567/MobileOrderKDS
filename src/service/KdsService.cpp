#include "KdsService.hpp"
#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

#include <QObject>

KdsService::KdsService(QObject *parent, HttpClient *client, Websocket *socket):
  QObject(parent),
  m_client(client),
  m_socket(socket)
{
  m_client->setParent(this);
  m_socket->setParent(this);
}

void KdsService::awaitOrders() {
  connect( // 初期エンドポイントアクセスの処理がしっかり完了するまで待つ。
    m_client,
    &HttpClient::jsonUsable,
    this,
    [this]() -> void {
      m_socket->connectSocket();
    }
  );

  m_client->connect2Server();
}

KdsService::Orders json2Struct() {

}
