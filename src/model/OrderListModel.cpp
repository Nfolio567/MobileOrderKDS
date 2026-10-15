#include <QObject>
#include <vector>

#include "../share/OrderStruct.hpp"
#include "OrderListModel.hpp"

OrderListModel::OrderListModel(QObject *parent) :
  QAbstractListModel(parent)
{}

/**
 * 注文たちを一気に追加
 * @param orders
 */
void OrderListModel::set(std::vector<Order> &orders) {
  // 追加ループ
  for (int i=0;i<orders.size();i++) {
    append(orders[i]);
  }
}

/**
 * 指定した注文を追加する
 * @param order
 */
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

/**
 * 指定した注文を更新する
 * @param orderID お客さん側の短いID
 * @param order 更新内容
 * @return 指定した要素が存在しているか(1: 成功, 0: 存在しない)
 */
int OrderListModel::update(const QString &orderID, const Order &order) {
  try {
    // updateするやつのindex
    const int changedIndex = m_orders.at(orderID).index;
    // update
    m_orders.at(orderID) = order;
    emit dataChanged(
      index(changedIndex),
      index(changedIndex)
    );
    return 0;
  } catch (std::out_of_range e) {
    return 1;
  }
}

/**
 * 指定した注文を削除する
 * @param orderID お客さん側の短いID
 * @return 削除する注文が存在しているか(0: 成功, 1: 存在しない)
 */
int OrderListModel::remove(const QString &orderID) {
  try {
    // ここでatがパスでき中たらcatchまでいくます。
    const int removedIndex = m_orders.at(orderID).index;

    // 削除開始
    beginRemoveRows(QModelIndex(), removedIndex, removedIndex);
    m_orderIDs.erase(m_orderIDs.begin() + removedIndex);
    m_orders.erase(orderID);
    endRemoveRows();
  } catch (std::out_of_range e) {
    return 1;
  }
}
