#pragma once

#include <QString>
#include <QStringList>

struct Item {
  QString product;
  QStringList options;
  int quantity;

  Item(
    const QString &product,
    const QStringList &options,
    const int quantity
  ) :
    product(product),
    options(options),
    quantity(quantity)
    {}
};

struct Order {
  QString id;
  bool isCooking;
  bool isCooked;
  bool isProvided;
  QList<Item> items;
  int index = 0;

  Order(
    const QString &id,
    const bool isCooking,
    const bool isCooked,
    const bool isProvided,
    const QList<Item> &items
  ):
    id(id),
    isCooking(isCooking),
    isCooked(isCooked),
    isProvided(isProvided),
    items(items)
    {}
};
