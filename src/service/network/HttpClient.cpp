#include "HttpClient.hpp"
#include "network/KdsConfig.hpp"
#include <QObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

HttpClient::HttpClient(QObject *parent) :
  QObject(parent),
  m_request(KDS_ENDPOINT_URL),
  m_manager(this)
{
  m_request.setRawHeader(
    "Authorization", 
    "Bearer " + KdsConfig::kdsAccessToken.toUtf8()
  );
}

void HttpClient::connect2Server() {
  QNetworkReply *reply = m_manager.get(m_request);
  connect(
    reply,
    &QNetworkReply::finished,
    this,
    [this, reply]() -> void
    {
      if (reply->error())
      { // 失敗
        reply->deleteLater();
        emit error(
          QString("Failed request: Code[%1]\nBody[%2]")
          .arg(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt())
          .arg(reply->readAll())
        );
      } else {
        const QJsonDocument json = QJsonDocument::fromJson(
          reply->readAll()
        );
        // json変換失敗
        if (json.isNull()) {
          emit error("Failed convert from text body to json.");
        }

        // json変数に加工済みレスポンスぶち込んだよ、のシグナル・要は成功
        emit jsonUsable(json);
      }

      // replyオブジェクト削除
      reply->deleteLater();
    }
  );
}

void HttpClient::reload() { // 多分いらん

}
