#pragma once

#include <qqml.h>
#include <QObject>

#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

class KdsService : public QObject {
  Q_OBJECT
  QML_ELEMENT

  public:
    explicit KdsService(QObject *parent = nullptr);

  private:
    HttpClient m_client;
    Websocket m_socket;
};
