#include "geocoding-object.h"

GeocodingObject::GeocodingObject(QString address,
                                 QGeoCoordinate location)
{
    m_address = address;
    m_location = location;
}
