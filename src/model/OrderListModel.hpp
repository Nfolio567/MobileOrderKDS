#include <vector>

#include <QAbstractListModel>
#include <QObject>

#include "../share/OrderStruct.hpp"

class OrderListModel : public QAbstractListModel {
  Q_OBJECT

public:
  enum Roles {
    ORDER_ID_ROLE = Qt::UserRole + 1,
    IS_COOKING_ROLE,
    IS_COOKED_ROLE,
    IS_PROVIDED_ROLE
  };

  explicit OrderListModel(QObject *parent = nullptr);

  // 要素数
  int rowCount(const QModelIndex &parent) const override {
    // このリストモデルは階層構造を持たないので、子要素か否かで行数は0を返す
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

    // コピーはしません！！ポインタの管理もしません！！
    const Order &order = m_orders.at(m_orderIDs[index.row()]);

    // roleによって返すやつ変える。returnしてるので特にbreakはいらない。
    switch (role) {
      case ORDER_ID_ROLE: return order.id;
      case IS_COOKING_ROLE: return order.isCooking;
      case IS_COOKED_ROLE: return order.isCooked;
      case IS_PROVIDED_ROLE: return order.isProvided;
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
    };
  }

  // オーダー配列ぶちこみ
  void set(std::vector<Order> &orders);
  // 要素追加
  void append(Order &order);
  // 要素更新
  int update(const QString &orderID, const Order &order);
  // 要素削除
  int remove(const QString &orderID);

private:
  // orderIDをkeyにしてorderの中身格納
  std::map<QString, Order> m_orders;
  // orderIDの配列、data()で使用
  std::vector<QString> m_orderIDs;
};
