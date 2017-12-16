#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "requestor.h"
#include "o0globals.h"
#include "o0settingsstore.h"

#include "o2requestor.h"

#include "endpoints.h"

Requestor::Requestor(QObject *parent) : QObject(parent)
{
}

void Requestor::setAuthenticator(O2Uber *v) {
    authenticator_ = v;
}

void Requestor::makeNetworkCall(QString endpointUrl){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    O2Requestor *requestor = new O2Requestor(manager, authenticator_, this);
    QUrl url = QUrl(endpointUrl);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);

    requestor->get(request);
    connect(requestor, SIGNAL(finished(int, QNetworkReply::NetworkError, QByteArray)),
            this, SLOT(success(int, QNetworkReply::NetworkError, QByteArray)));
}

void Requestor::success(int id, QNetworkReply::NetworkError error, QByteArray data){

    qDebug() << "UberLogin::Success";
    qDebug() << data;

    //    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    //  QJsonArray jsonArray = jsonResponse.array();
}

void Requestor::failure(QNetworkReply::NetworkError error){
    qDebug() << "UberLogin::Failure";
}
