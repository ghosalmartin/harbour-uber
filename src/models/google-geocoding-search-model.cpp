#include "google-geocoding-search-model.h"

GoogleGeocodingSearchModel::GoogleGeocodingSearchModel(): QAbstractListModel(), m_requestor(0), m_ready(false){
    m_roles[addressRole] = "address";
    m_roles[latRole] = "lat";
    m_roles[lngRole] = "lng";
}

QVariant GoogleGeocodingSearchModel::data(const QModelIndex &index, int role) const {

    int row = index.row();
    if (row < 0 || row > m_data.size()) return QVariant();
    GeocodingObject geocodingObject = m_data.at(row);

    switch(role)
    {
    case addressRole: return geocodingObject.m_address;
    case latRole: return geocodingObject.m_location.latitude();
    case lngRole: return geocodingObject.m_location.longitude();
    default: return QVariant();
    }
}

void GoogleGeocodingSearchModel::appendRow(GeocodingObject geocodingObject) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(geocodingObject);
    endInsertRows();
}

void GoogleGeocodingSearchModel::populateModel(QList<GeocodingObject> geocodingObjects) {
    beginResetModel();
    m_data.clear();
    m_data = geocodingObjects;
    endResetModel();
    m_ready = true;
    emit readyChanged();
}

void GoogleGeocodingSearchModel::setRequestor(GoogleGeocodingRequestor *requestor) {
    if (m_requestor != requestor) {
        if (m_requestor) {
            disconnect(m_requestor, SIGNAL(dataProcessed(QList<GeocodingObject>)), this, SLOT(populateModel(QList<GeocodingObject>)));
        }
        m_requestor = requestor;
        if (m_requestor) {
            connect(m_requestor, SIGNAL(dataProcessed(QList<GeocodingObject>)), this, SLOT(populateModel(QList<GeocodingObject>)));
        }
        emit requestorChanged();
    }
}

void GoogleGeocodingSearchModel::searchForAddress(QString address) {
    m_requestor->searchForAddress(address);
}
