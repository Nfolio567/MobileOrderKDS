#include "HttpClient.hpp"
#include <QObject>
#include <QJsonDocument>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

HttpClient::HttpClient(QObject *parent) :
  QObject(parent),
  m_request(KDS_ENDPOINT_URL),
  m_manager(this)
{}

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
      
      reply->deleteLater();
    }
  );
}

void HttpClient::reload() { // 多分いらん

}
