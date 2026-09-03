#pragma once

#include <cstddef>
#include <vector>

#include <qqml.h>
#include <QObject>

#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

class KdsService : public QObject {
  Q_OBJECT
  QML_ELEMENT

  public:
    explicit KdsService(QObject *parent = nullptr, HttpClient *client = nullptr, Websocket *websocket = nullptr);

    struct Products {
      int id;
      QString name;
      int price;
      int stockQuantity;
      QString description;
    };

    struct Options {
      int id;
      QString name;
      int price;
    };

    struct OptionsJunction {
      Options optionsID;
    };

    struct OrderItems {
      int id;
      QString orderID;
      Products products;
      std::vector<OptionsJunction> options;
      int quantity;
    };

    struct Orders {
      QString id;
      QString userID;
      bool isPos;
      QString fakeOrderID;
      bool isCooking;
      bool isCooked;
      bool isProvided;
      std::vector<OrderItems> items;
      bool paid;
    };

    Orders json2Struct();
    void awaitOrders();

  private:
    HttpClient *m_client;
    Websocket *m_socket;
};
