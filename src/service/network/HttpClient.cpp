#include "HttpClient.hpp"
#include "network/KdsConfig.hpp"
#include <QObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

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
      {
        reply->deleteLater();
        return;
      }

      QJsonDocument json = QJsonDocument::fromJson(
        reply->readAll()
      );
      
      // json変数に加工済みレスポンスぶち込んだよ、のシグナル
      emit jsonUsable(json);      
      reply->deleteLater();
    }
  );
}

void HttpClient::reload() { // 多分いらん

}
