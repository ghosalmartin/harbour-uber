#include "google-geocoding-requestor.h"

GoogleGeocodingRequestor::GoogleGeocodingRequestor(QObject *parent) : QObject(parent)
{

}

void GoogleGeocodingRequestor::searchForAddress(QString address){
    QNetworkAccessManager* manager =
            new QNetworkAccessManager(this);

    QString endpointUrl = QString(GOOGLE_GEOCODING_ENDPOINT).arg(address).replace(" ", "+");

    QUrl url = QUrl(endpointUrl);
    QNetworkRequest request(url);

    manager->get(request);

    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(finished(QNetworkReply*)));
    eventLoop.exec();
}

void GoogleGeocodingRequestor::finished(QNetworkReply *reply){
    if (reply->error() == QNetworkReply::NoError) {
        processData(reply->readAll());
        delete reply;
        eventLoop.exit(0);
    }
    else {
        qDebug() << reply->errorString();
        delete reply;
        eventLoop.exit(0);
    }
}

void processData(QByteArray data){
    QString stringReply = (QString) data;
    QJsonDocument jsonResponse =
            QJsonDocument::fromJson(stringReply.toUtf8());

    QJsonObject jsonObject = jsonResponse.object();

    QList<GeocodingObject> geocodingObjects;

    QJsonObject resultsObject = jsonObject["results"].toArray();

    QJsonArray::iterator it;
    for (it = resultsObject.begin(); it != resultsObject.end(); it++) {
        QString key = it->first;
        QString value = it->second;
    }

}
