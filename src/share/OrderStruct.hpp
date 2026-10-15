#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <vector>

struct Items {
  QString product;
  std::vector<QString> options;
};

struct Order {
  QString id;
  bool isCooking;
  bool isCooked;
  bool isProvided;
  Items items;
  int index = 0;

  Order(
    const QString &id,
    const bool isCooking,
    const bool isCooked,
    const bool isProvided,
    const Items &items
  ):
    id(id),
    isCooking(isCooking),
    isCooked(isCooked),
    isProvided(isProvided),
    items(items)
    {}
};

/**
  * @brief Ordersに変換
  */
inline std::vector<Order> ordersFronJson(const QByteArray &json) {
  std::vector<Order> orders;

  QJsonDocument qJson = QJsonDocument::fromJson(json);
  QJsonArray jsonArray = qJson.array();

  for (const QJsonValue i : jsonArray) {
    QJsonObject object = i.toObject();
    
  }
}
