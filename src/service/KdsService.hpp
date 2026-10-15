#pragma once

#include <cstddef>
#include <vector>

#include <qqml.h>
#include <QObject>

#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"
#include "src/share/OrderStruct.hpp"

class KdsService : public QObject {
  Q_OBJECT
  QML_ELEMENT

  public:
    explicit KdsService(QObject *parent = nullptr, HttpClient *client = nullptr, Websocket *socket = nullptr);

    Order json2Struct();
    void awaitOrders();

  private:
    HttpClient *m_client;
    Websocket *m_socket;
};
