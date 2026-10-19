#pragma once

#include <vector>

#include <QAbstractListModel>
#include <QObject>

#include "../share/OrderStruct.hpp"
#include "network/HttpClient.hpp"
#include "network/Websocket.hpp"

class OrderListModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum Roles {
    ORDER_ID_ROLE = Qt::UserRole + 1,
    IS_COOKING_ROLE,
    IS_COOKED_ROLE,
    IS_PROVIDED_ROLE,
    ITEMS_ROLE
  };

  explicit OrderListModel(QObject *parent = nullptr, const HttpClient *client = nullptr, const Websocket *socket = nullptr);

  // 要素数
  int rowCount(const QModelIndex &parent) const override {
    // リストモデルは階層構造を持たないので、子要素だった場合は行数0を返す
    if (parent.isValid()) {
      return 0;
    }

    return m_orderIDs.size();
  }

  // indexからデータ取得
  QVariant data(const QModelIndex &index, const int role) const override {
    if (!index.isValid() || index.row() < 0 || index.row() >= m_orderIDs.size()) {
      return {};
    }

    const Order &order = m_orders.at(m_orderIDs[index.row()]);

    // roleによって返すやつ変える。returnしてるので特にbreakはいらない。
    switch (role) {
      case ORDER_ID_ROLE: return order.id;
      case IS_COOKING_ROLE: return order.isCooking;
      case IS_COOKED_ROLE: return order.isCooked;
      case IS_PROVIDED_ROLE: return order.isProvided;
      case ITEMS_ROLE: {
        QVariantList items;
        for (const Item &item : order.items) {
          items.append(QVariantMap{
            { "product", item.product },
            { "options", item.options}
          });
        }
        return items;
      }
      default: return {};
    }
  }

  // ロールの名前決め
  QHash<int, QByteArray> roleNames() const override {
    return {
      {ORDER_ID_ROLE, "orderID"},
      {IS_COOKING_ROLE, "isCooking"},
      {IS_COOKED_ROLE, "isCooked"},
      {IS_PROVIDED_ROLE, "isProvided"},
      {ITEMS_ROLE, "items"}
    };
  }

  /**
  * 注文たちを一気に追加
  * @param orders
  */
  void set(std::vector<Order> &orders);

  /**
  * 指定した注文を追加する
  * @param order
  */
  void append(Order &order);

  /**
  * 指定した注文を更新する
  * @param orderID お客さん側の短いID
  * @param order 更新内容
  * @return 指定した要素が存在しているか(1: 成功, 0: 存在しない)
  */
  int update(const QString &orderID, Order &order);

  /**
  * 指定した注文を削除する
  * @param orderID お客さん側の短いID
  * @return 削除する注文が存在しているか(0: 成功, 1: 存在しない)
  */
  int remove(const QString &orderID);

  /**
   * QJsonDocumentをOrderの配列に変換
   * @param ordersObject
   * @return Orderの配列
   */
  static std::vector<Order> json2Orders(const QJsonObject &ordersObject);

  bool contains(const QString &orderID);

signals:
  void error(const QString &message);

private:
  // orderIDをkeyにしてorderの中身格納
  std::map<QString, Order> m_orders;
  // orderIDの配列、data()で使用
  std::vector<QString> m_orderIDs;
};
