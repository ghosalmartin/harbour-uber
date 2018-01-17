#ifndef GOOGLEGEOCODINGSEARCHMODEL_H
#define GOOGLEGEOCODINGSEARCHMODEL_H

#include <QAbstractListModel>
#include <QHash>
#include <QDebug>

#include "src/objects/geocoding-object.h"
#include "src/network/google-geocoding-requestor.h"

class GoogleGeocodingSearchModel : public QAbstractListModel
{

    Q_OBJECT
    Q_PROPERTY(bool ready MEMBER m_ready NOTIFY readyChanged)
    Q_PROPERTY(GoogleGeocodingRequestor *requestor READ getRequestor WRITE setRequestor NOTIFY requestorChanged)

public:
    explicit GoogleGeocodingSearchModel();

    enum Roles {
        addressRole = Qt::UserRole + 1,
        latRole = Qt::UserRole + 2,
        lngRole = Qt::UserRole + 3
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return m_data.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const {
        return m_roles;
    }

    void appendRow(GeocodingObject geocodingObject);

    void setRequestor(GoogleGeocodingRequestor *requestor);

    GoogleGeocodingRequestor* getRequestor(){
        return m_requestor;
    }

    Q_INVOKABLE void searchForAddress(QString address);

signals:
    void readyChanged();
    void requestorChanged();

public slots:
    void populateModel(QList<GeocodingObject> geocodingObjects);

private:
    QList<GeocodingObject> m_data;
    QHash<int, QByteArray> m_roles;
    GoogleGeocodingRequestor *m_requestor;
    bool m_ready;
};

#endif // GOOGLEGEOCODINGSEARCHMODEL_H
