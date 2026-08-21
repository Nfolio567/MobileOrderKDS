#include <QObject>
#include <QNetworkAccessManager>

class HttpClient : public QObject {
  Q_OBJECT

  public:
    explicit HttpClient(QObject *parent = nullptr);
    void connect2Server();
    void reload();

  private:
    const QUrl KDS_ENDPOINT_URL = QUrl("https://sobile.nfolio.one/kds");
    QNetworkRequest m_request;
    QNetworkAccessManager m_manager;
};