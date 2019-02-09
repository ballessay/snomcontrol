#include "requesthandler.h"
#include "settings.h"
#include <QNetworkReply>



CRequestHandler::CRequestHandler(const SSettings& settings, QObject* pParent) :
    QObject (pParent),
    m_nam(this),
    m_settings(settings)
{
    connect(&m_nam, &QNetworkAccessManager::finished,
            this, &CRequestHandler::Finished);
}


void CRequestHandler::Dial(const QString& sNumber)
{
    const QString sRequest("http://" + m_settings.sUsername + ":" +
                           m_settings.sPassword + "@" + m_settings.sPhoneUrl +
                           "/command.htm?number=" + sNumber + "&outgoing_uri=" +
                           m_settings.sSipAccount);

    Request(QUrl(sRequest), tr("Call started"));
}


void CRequestHandler::HangUp()
{
    const QString sRequest("http://" + m_settings.sPhoneUrl +
                      "/command.htm?key=CANCEL");

    Request(QUrl(sRequest), tr("Cancel transmitted"));
}


void CRequestHandler::Encrypted(QNetworkReply* reply)
{
    emit Message("Encrypted: " + reply->url().toString());

    reply->deleteLater();
}


void CRequestHandler::Finished(QNetworkReply* reply)
{
    if (reply->error())
    {
        emit Error("Finished with error: " + QString::number(reply->error()));
    }
    else
    {
        const auto data = m_requests.takeFirst();
        if (data.first == reply->request())
        {
            emit Message(data.second);
        }
        else
        {
            emit Message("Request finished");
        }
    }

    reply->deleteLater();
}


void CRequestHandler::NetworkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    emit Message("NetworkAccessibleChanged: " + QString::number(accessible));
}


void CRequestHandler::AuthenticationRequired(QNetworkReply*, QAuthenticator*)
{
    emit Message("AuthenticationRequired");
}


#ifndef QT_NO_SSL
void CRequestHandler::SslErrors(QNetworkReply*, const QList<QSslError>& errors)
{
    for (const auto& error : errors)
    {
        emit Error("SslErrors: " + error.errorString());
    }
}
#endif


void CRequestHandler::Request(const QUrl& url, const QString& sMessage)
{
    QNetworkRequest request(url);

    m_requests.append(std::make_pair(request, sMessage));

    m_nam.get(request);
}
