#include "uber-product-requestor.h"

UberProductRequestor::UberProductRequestor(QObject *parent) : UberRequestor(parent){

}

void UberProductRequestor::fetchProductFromNetwork(QString lat, QString lng){
    QString requestUrl =  QString(UBER_PRODUCTS_ENDPOINT).arg(lat).arg(lng);

    makeNetworkCall(requestUrl.toLatin1().data(),
                    QNetworkAccessManager::Operation::GetOperation);
}

void UberProductRequestor::deserialize(QByteArray data){
    QString stringReply = (QString) data;
    QJsonDocument jsonResponse =
            QJsonDocument::fromJson(stringReply.toUtf8());

    QJsonObject jsonObject = jsonResponse.object();
    QJsonArray products = jsonObject["products"].toArray();

    qDebug() << stringReply;

    QList<Product> productObjects;
    for(int i = 0; i < products.size(); i++){
        QJsonObject product = products[i].toObject();
        QString productId = product["product_id"].toString();
        QString image = product["image"].toString();
        QString productGroup = product["product_group"].toString();
        productObjects.append(Product(productId, image, productGroup));
    }

    emit productsChanged(productObjects);
}

void UberProductRequestor::onError(QString errorString){
    qDebug() << errorString;
}


