#include "google-geocoding-requestor.h"

GoogleGeocodingRequestor::GoogleGeocodingRequestor(QObject *parent) : QObject(parent)
{

}

void GoogleGeocodingRequestor::searchForAddress(QString address){
    QNetworkAccessManager* manager =
            new QNetworkAccessManager(this);

    QString endpointUrl = QString(GOOGLE_GEOCODING_ENDPOINT).arg(address).replace(" ", "+");

    qDebug() << endpointUrl;

    QUrl url = QUrl(endpointUrl);
    QNetworkRequest request(url);

    manager->get(request);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
    eventLoop.exec();
}

void GoogleGeocodingRequestor::finished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        qDebug() << reply->readAll();
        delete reply;
        eventLoop.exit(0);
    }
    else {
        qDebug() << reply->errorString();
        delete reply;
        eventLoop.exit(0);
    }
}
