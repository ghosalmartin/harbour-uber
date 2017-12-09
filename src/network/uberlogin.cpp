#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QDebug>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include "uberlogin.h"
#include "o0globals.h"
#include "o0settingsstore.h"

#include "o2requestor.h"

UberLogin::UberLogin(QObject *parent) : QObject(parent)
{
    //    O0SettingsStore *store = new O0SettingsStore(O2_ENCRYPTION_KEY);
    //    store->setGroupKey("uber");
    //    authenticator_->setStore(store);
}

O2Uber *UberLogin::authenticator() const {
    return authenticator_;
}

void UberLogin::setupStore(){
    O0SettingsStore *store = new O0SettingsStore(O2_ENCRYPTION_KEY);
    store->setGroupKey("uber");
    authenticator_->setStore(store);
    qDebug() << "UberLogin::setupStore";

}

void UberLogin::setAuthenticator(O2Uber *v) {
    authenticator_ = v;
}

void UberLogin::getProfile(){
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    O2Requestor *requestor = new O2Requestor(manager, authenticator_, this);
    QUrl url = QUrl("https://api.uber.com/v1.2/profile");

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, O2_MIME_TYPE_XFORM);

    int reply = requestor->get(request);

    connect(requestor, SIGNAL(finished(int, QNetworkReply::NetworkError, QByteArray)), this, SLOT(success(int, QNetworkReply::NetworkError, QByteArray)));
}

void UberLogin::success(int id, QNetworkReply::NetworkError error, QByteArray data){

    qDebug() << "UberLogin::Success";
    qDebug() << data;

    //    QJsonDocument jsonResponse = QJsonDocument::fromJson(reply->readAll());
    //  QJsonArray jsonArray = jsonResponse.array();
}

void UberLogin::failure(QNetworkReply::NetworkError error){
    qDebug() << "UberLogin::Failure";

}
