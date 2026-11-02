#pragma once
#include <qsortfilterproxymodel.h>
#include <QObject>

#include "OrderListModel.hpp"

class OrderListProvidingFilter : public QSortFilterProxyModel {
  Q_OBJECT

public:
  using QSortFilterProxyModel::QSortFilterProxyModel;

  /**
   * 注文番号を取得
   * @param idx index
   * @return orderID
   */
  Q_INVOKABLE QString getID(int idx) const;

protected:
  auto filterAcceptsRow(int source_row, const QModelIndex &source_parent) const -> bool override {
    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    const bool isCooked = sourceModel()->data(index, OrderListModel::IS_COOKED_ROLE).toBool();
    const bool isProvided = sourceModel()->data(index, OrderListModel::IS_PROVIDED_ROLE).toBool();

    return isCooked && !isProvided;
  }
};
