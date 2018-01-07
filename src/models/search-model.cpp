#include "search-model.h"

SearchModel::SearchModel(): QAbstractItemModel(), m_requestor(0), m_ready(false)
{
    m_roles[addressRole] = "address";
}

QVariant SearchModel::data(const QModelIndex &index, int role) const
{

    int row = index.row();
    if (row < 0 || row > data_.size()) return QVariant();
    GeocodingObject geocodingObject = data_.at(row);

    if(role == addressRole){
        geocodingObject.m_address;
    } else {
        return QVariant();
    }
}

void SearchModel::appendRow(GeocodingObject geocodingObject)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    data_.append(geocodingObject);
    endInsertRows();
}

void SearchModel::populateModel(QList<GeocodingObject> geocodingObjects)
{

    beginResetModel();
    m_data.clear();
    m_data = geocodingObjects;
    endResetModel();
    setReady(true);
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
