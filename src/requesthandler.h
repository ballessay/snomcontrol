#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QQueue>

struct SSettings;


class CRequestHandler : public QObject
{
    Q_OBJECT

public:
    CRequestHandler(const SSettings& settings, QObject* pParent = nullptr);

    void Dial(const QString& sNumber);
    void HangUp();

signals:
    void Message(QString sMessage);
    void Error(QString sError);

private slots:
    void Encrypted(QNetworkReply* reply);
    void Finished(QNetworkReply* reply);
    void NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
    void AuthenticationRequired(QNetworkReply*, QAuthenticator* authenticator);
#ifndef QT_NO_SSL
    void SslErrors(QNetworkReply*, const QList<QSslError>& errors);
#endif

private:
    void Request(const QUrl& url, const QString& sMessage);

private:
    QNetworkAccessManager m_nam;
    const SSettings& m_settings;
    QQueue<std::pair<QNetworkRequest, QString>> m_requests;
};

#endif // REQUESTHANDLER_H
