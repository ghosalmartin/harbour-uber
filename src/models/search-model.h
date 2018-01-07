#ifndef SEARCHMODEL_H
#define SEARCHMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "src/objects/geocoding-object.h"
#include "src/network/google-geocoding-requestor.h"

class SearchModel : public QAbstractListModel
{

    Q_OBJECT
    Q_PROPERTY(bool ready MEMBER m_ready NOTIFY readyChanged)
    Q_PROPERTY(GoogleGeocodingRequestor *requestor MEMBER m_requestor NOTIFY requestorChanged)

public:
    explicit SearchModel();

    enum Roles {
        addressRole = Qt::UserRole + 1
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

#endif // SEARCHMODEL_H
