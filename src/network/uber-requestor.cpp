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

void UberRequestor::makeNetworkCall(
        char *endpointUrl,
        QNetworkAccessManager::Operation operation,
        const QByteArray &data){

    QNetworkAccessManager* manager =
            new QNetworkAccessManager(this);

    QUrl url = QUrl(endpointUrl);
    QString authorizationHeader =
            "Bearer " + authenticator_->token();
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      O2_MIME_TYPE_XFORM);
    request.setRawHeader(O2_HTTP_AUTHORIZATION_HEADER,
                         authorizationHeader.toUtf8());

    switch (operation) {
    case QNetworkAccessManager::Operation::PutOperation:
        manager->put(request, data);
        break;

    case QNetworkAccessManager::Operation::GetOperation:
        manager->get(request);
        break;
    case QNetworkAccessManager::Operation::PostOperation:
        manager->post(request, data);
        break;
    default:
        break;
    }

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
    eventLoop.exec();
}


void UberRequestor::finished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        deserialize(reply->readAll());
        delete reply;
        eventLoop.exit(0);
    }
    else {
        onError(reply->errorString());
        delete reply;
        eventLoop.exit(0);
    }
}
