#ifndef GEOCODINGOBJECT_H
#define GEOCODINGOBJECT_H

#include <QString>
#include <QGeoCoordinate>
class GeocodingObject
{
public:
    GeocodingObject(QString address,
                    QGeoCoordinate location);

    QString m_address;
    QGeoCoordinate m_location;
};

#endif // GEOCODINGOBJECT_H
