#pragma once

#include "src/service/network/KdsConfig.hpp"
#include <QObject>
#include <QNetworkAccessManager>


/**
* @brief 起動時にサーバーに接続するためのクライアントクラス
* 
* 本番時は 'https://sobile.nfolio.one/kds' にGETする。
* そこで全てのオーダーを一挙取得。あとはWebSocketで随時更新。
*/
class HttpClient : public QObject {
  Q_OBJECT

  public:
    explicit HttpClient(QObject *parent = nullptr);
    /**
    * @brief サーバーに接続
    */
    void connect2Server();
    /**
    * @brief リロード
    * 
    * 使うかなと思って定義したが、
    * よくよく考えればもう一回connect2Server()を実行すればいいだけなので恐らく不要。
    * 一応念の為定義したまま。ただ今の所非推奨。てか使えん。
    */
    void reload();

  private:
    const QUrl KDS_ENDPOINT_URL = QUrl(KdsConfig::firstEndpoint);
    QNetworkRequest m_request;
    QNetworkAccessManager m_manager;
};