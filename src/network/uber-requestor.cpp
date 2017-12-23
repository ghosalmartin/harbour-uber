#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

#include "uber-requestor.h"

UberRequestor::UberRequestor(QObject *parent) : QObject(parent){}

void UberRequestor::setAuthenticator(O2Uber *authenticator) {
    authenticator_ = authenticator;
}

O2Uber *UberRequestor::getAuthenticator() const {
    return authenticator_;
}

void UberRequestor::makeNetworkCall(QString endpointUrl, QNetworkAccessManager::Operation operation, const QByteArray &data){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    QUrl url = QUrl(endpointUrl);
    QString authorizationHeader = "Bearer " + authenticator_->token();
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);
    request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER, authorizationHeader.toUtf8());

    QNetworkReply *reply;

    switch (operation) {
    case QNetworkAccessManager::Operation::PutOperation:
        reply = manager->put(request, data);
        break;

    case QNetworkAccessManager::Operation::GetOperation:
        reply = manager->get(request);
        break;
    case QNetworkAccessManager::Operation::PostOperation:
        reply = manager->post(request, data);
        break;
    default:
        break;
    }

    connect(reply, SIGNAL(finished()), this, SLOT(success(reply)));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));

}


void UberRequestor::success(QNetworkReply *reply){
//    deserialize(data);
}

void UberRequestor::failure(QNetworkReply::NetworkError error){
    qDebug() << "UberLogin::Failure";
}
