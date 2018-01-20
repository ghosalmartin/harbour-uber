#ifndef GOOGLEGEOCODINGREQUESTOR_H
#define GOOGLEGEOCODINGREQUESTOR_H

#define GOOGLE_GEOCODING_ENDPOINT "https://maps.googleapis.com/maps/api/geocode/json?address=%1&key=AIzaSyD2cziNqnDU8kNX4lzrumelzC8abq_L7qY"

#define JSON_RESULTS_KEY "results"
#define JSON_FORMATTED_ADDRESS_KEY "formatted_address"
#define JSON_GEOMETRY_KEY = "geometry"
#define JSON_LOCATION_KEY = "location"

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>

#include "src/objects/geocoding-object.h"

class GoogleGeocodingRequestor : public QObject
{
    Q_OBJECT
public:
    explicit GoogleGeocodingRequestor(QObject *parent = 0);

    void searchForAddress(QString address);

signals:
    void dataProcessed(QList<GeocodingObject> geocodingObjects);

public slots:
    void finished(QNetworkReply *reply);

private:
    QEventLoop eventLoop;
    void processData(QByteArray data);

};

#endif // GOOGLEGEOCODINGREQUESTOR_H
