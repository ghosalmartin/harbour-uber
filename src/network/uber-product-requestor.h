#ifndef UBERPRODUCTREQUESTOR_H
#define UBERPRODUCTREQUESTOR_H

#include <QObject>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "uber-endpoints.h"
#include "uber-requestor.h"

#include "src/objects/product.h"

class UberProductRequestor : public UberRequestor
{
    Q_OBJECT

public:
    UberProductRequestor(QObject *parent = 0);

    void deserialize(QByteArray data);
    void onError(QString errorString);

    void fetchProductFromNetwork(QString lat, QString lng);

signals:
    void productsChanged(QList<Product> products);

};

#endif // UBERPRODUCTREQUESTOR_H
