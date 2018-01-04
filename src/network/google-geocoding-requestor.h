#ifndef GOOGLEGEOCODINGREQUESTOR_H
#define GOOGLEGEOCODINGREQUESTOR_H

#define GOOGLE_GEOCODING_ENDPOINT "https://maps.googleapis.com/maps/api/geocode/json?address=%1&key=AIzaSyD2cziNqnDU8kNX4lzrumelzC8abq_L7qY"

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QNetworkReply>

class GoogleGeocodingRequestor : public QObject
{
    Q_OBJECT
public:
    explicit GoogleGeocodingRequestor(QObject *parent = 0);

    Q_INVOKABLE void searchForAddress(QString address);

signals:

public slots:
    void finished(QNetworkReply *reply);

private:
    QEventLoop eventLoop;

};

#endif // GOOGLEGEOCODINGREQUESTOR_H
