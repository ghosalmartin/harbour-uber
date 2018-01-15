#include "google-geocoding-requestor.h"

GoogleGeocodingRequestor::GoogleGeocodingRequestor(QObject *parent) : QObject(parent)
{}

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

void GoogleGeocodingRequestor::processData(QByteArray data){
    QString stringReply = (QString) data;
    QJsonDocument jsonResponse =
            QJsonDocument::fromJson(stringReply.toUtf8());

    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray resultsObject = jsonObject[JSON_RESULTS_KEY].toArray();

    QList<GeocodingObject> geocodingObjects;

    for(int i = 0; i < resultsObject.size(); i++){
        QString formattedAddress = resultsObject[i].toObject()[JSON_FORMATTED_ADDRESS_KEY].toString();
        QJsonObject location = resultsObject[i].toObject()["geometry"].toObject()["location"].toObject();
        QString lat = location["lat"].toString();
        QString lng = location["lng"].toString();
        geocodingObjects.append(GeocodingObject(formattedAddress, QGeoCoordinate(lat.toDouble(), lng.toDouble())));
    }

    emit dataProcessed(geocodingObjects);
}
