#pragma once

#include <QObject>
#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

class KDSService : public QObject {
  Q_OBJECT

  public:
    explicit KDSService(QObject *parent = nullptr);

  private:
    HttpClient m_client;
    Websocket m_socket;
};
