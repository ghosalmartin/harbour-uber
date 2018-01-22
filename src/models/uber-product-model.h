#ifndef UBERPRODUCTMODEL_H
#define UBERPRODUCTMODEL_H


#include <QAbstractListModel>
#include <QHash>
#include <QObject>

#include "src/objects/product.h"
#include "src/network/uber-product-requestor.h"

class UberProductModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool ready MEMBER m_ready NOTIFY readyChanged)
    Q_PROPERTY(UberProductRequestor *requestor READ getRequestor WRITE setRequestor NOTIFY requestorChanged)

public:
    explicit UberProductModel(QObject *parent = 0);

    enum Roles {
        productIdRole = Qt::UserRole + 1,
        productGroupRole = Qt::UserRole + 2,
        imageRole = Qt::UserRole + 3
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const {
        return m_data.size();
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const {
        return m_roles;
    }

    void appendRow(Product product);

    void setRequestor(UberProductRequestor *requestor);

    UberProductRequestor* getRequestor(){
        return m_requestor;
    }

    Q_INVOKABLE void getProducts(QString lat, QString lng);

signals:
    void readyChanged();
    void requestorChanged();

public slots:
    void populateModel(QList<Product> products);

private:
    QList<Product> m_data;
    QHash<int, QByteArray> m_roles;
    UberProductRequestor *m_requestor;
    bool m_ready;
};

#endif // UBERPRODUCTMODEL_H
