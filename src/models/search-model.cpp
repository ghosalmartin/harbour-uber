#include "search-model.h"

SearchModel::SearchModel(): QAbstractListModel(), m_requestor(0), m_ready(false)
{
    m_roles[addressRole] = "address";
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    if (row < 0 || row > m_data.size()) return QVariant();
    GeocodingObject geocodingObject = m_data.at(row);

    if(role == addressRole){
        return geocodingObject.m_address;
    } else {
        return QVariant();
    }
}

void SearchModel::appendRow(GeocodingObject geocodingObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(geocodingObject);
    endInsertRows();
}

void SearchModel::populateModel(QList<GeocodingObject> geocodingObjects)
{
    beginResetModel();
    m_data.clear();
    m_data = geocodingObjects;
    endResetModel();
    m_ready = true;
    emit readyChanged();
}

void SearchModel::setRequestor(GoogleGeocodingRequestor *requestor){
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
