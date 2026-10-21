#include <vector>

#include "../share/OrderStruct.hpp"
#include "OrderListModel.hpp"

#include <QJsonArray>
#include <QJsonObject>

#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

OrderListModel::OrderListModel(QObject *parent, const HttpClient *client, const Websocket *socket) :
  QAbstractListModel(parent) {
  connect(
    client,
    &HttpClient::jsonUsable,
    this,
    [this](const QJsonDocument &json) -> void {
      qDebug() << "Http";
      qDebug() << json;
      std::vector<Order> orders = json2Orders(json.object());
      for (const Order order : orders) {
        qDebug() << order.id;
      }

      set(orders);
    }
  );

  connect(
    socket,
    &Websocket::textMessage,
    this,
    [this](const QJsonDocument &message) -> void {
      qDebug() << message;
      std::vector<Order> orders = json2Orders(message.object());
      for (const Order order : orders) {
        qDebug() << order.id;
      }

      for (int i=0;i<orders.size();i++) {
        // デフォルトでfalseにしてるので存在はしてる
        // 提供済みってことはもう用済みなので削除
        if (orders[i].isProvided) {
          qDebug() << "remove";
          remove(orders[i].id);
        } else if (update(orders[i].id, orders[i])) {
          // updateで存在してなかったら即「1」が返されるので判定、成功したらそのままupdateして「0」が返ってパスされる
          append(orders[i]);
        }
      }
    }
  );

  // when receive error
  connect(
    client,
    &HttpClient::error,
    this,
    [this](const QString &message) -> void {
      emit error(
        QString("HttpClient error: %1")
        .arg(message)
      );
    }
  );

  connect(
    socket,
    &Websocket::error,
    this,
    [this](const QString &message) -> void {
      emit error(
        QString("WebSocket error: %1")
        .arg(message)
      );
    }
  );
}

auto OrderListModel::json2Orders(const QJsonObject &ordersObject) -> std::vector<Order> {
  // 最終的に返すやつ
  std::vector<Order> orders;

  for (const auto orderArrayRef : ordersObject["orders"].toArray()) {
    const auto orderObject = orderArrayRef.toObject();

    // OrderItemsループ
    QList<Item> items;
    for (const auto &orderItemJsonObject : orderObject["items"].toArray()) {
      QJsonObject orderItemObject = orderItemJsonObject.toObject();

      // optionsループ
      QList<QString> options;
      for (const auto &optionJsonObject : orderItemObject["options"].toArray()) {
        // option格納
        options.emplace_back(optionJsonObject.toString());
      }

      // item格納
      items.emplace_back(
        std::move(
          Item(
            orderItemObject["product"].toString(),
            options,
            orderItemObject["quantity"].toInt()
      )));
    }

    qDebug() << QString("loop: %1").arg(orderObject["id"].toString());
    // order格納
    orders.emplace_back(
      std::move(
        Order(
          orderObject["id"].toString(),
          orderObject["isCooking"].toBool(),
          orderObject["isCooked"].toBool(),
          orderObject["isProvided"].toBool(),
          items
    )));
  }

  return orders;
}

void OrderListModel::set(std::vector<Order> &orders) {
  // 追加ループ
  for (int i=0;i<orders.size();i++) {
    append(orders[i]);
  }
}

void OrderListModel::append(Order &order) {
  // 今から追加するやつのindex
  const int addingIndex = static_cast<int>(m_orderIDs.size());

  beginInsertRows(QModelIndex(), addingIndex, addingIndex);

  // mapのindex記録
  order.index = addingIndex;

  // 登録
  m_orderIDs.emplace_back(order.id);
  m_orders.emplace(order.id, order);

  endInsertRows();
}

int OrderListModel::update(const QString &orderID, Order &order) {
  try {
    // updateするやつのindex
    const int changedIndex = m_orders.at(orderID).index;
    // update
    m_orders.at(orderID) = std::move(order);
    emit dataChanged(
      index(changedIndex),
      index(changedIndex)
    );
    return 0;
  } catch (std::out_of_range e) {
    return 1;
  }
}

int OrderListModel::remove(const QString &orderID) {
  try {
    // ここでatがパスしなかったらcatchされる。
    const int removedIndex = m_orders.at(orderID).index;

    // 削除開始
    beginRemoveRows(QModelIndex(), removedIndex, removedIndex);
    m_orderIDs.erase(m_orderIDs.begin() + removedIndex);
    m_orders.erase(orderID);
    endRemoveRows();

    return 0;
  } catch (std::out_of_range e) {
    return 1;
  }
}

bool OrderListModel::contains(const QString &orderID) {
  const auto iterator = m_orders.find(orderID);

  // 存在するか
  return iterator != m_orders.end();
}
