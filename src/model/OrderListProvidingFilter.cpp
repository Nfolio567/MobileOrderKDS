#include "OrderListProvidingFilter.hpp"

QString OrderListProvidingFilter::getID(int idx) const {
  return data(index(idx, 0), OrderListModel::ORDER_ID_ROLE).toString();
}
