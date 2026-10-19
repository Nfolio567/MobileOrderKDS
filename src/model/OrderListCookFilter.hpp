#pragma once
#include <qsortfilterproxymodel.h>

#include "OrderListModel.hpp"

class OrderListCookFilter : public QSortFilterProxyModel {
  Q_OBJECT

public:
  using QSortFilterProxyModel::QSortFilterProxyModel;

protected:
  auto filterAcceptsRow(int source_row, const QModelIndex &source_parent) const -> bool override {
    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    const bool isCooking = sourceModel()->data(index, OrderListModel::IS_COOKING_ROLE).toBool();
    const bool isCooked = sourceModel()->data(index, OrderListModel::IS_COOKED_ROLE).toBool();
    const bool isProvided = sourceModel()->data(index, OrderListModel::IS_PROVIDED_ROLE).toBool();

    return (isCooking && !isCooked && !isProvided) | (!isCooking && !isCooked && !isProvided);
  }
};
