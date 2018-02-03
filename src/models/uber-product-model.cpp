#include "uber-product-model.h"

UberProductModel::UberProductModel(QObject *parent) : QAbstractListModel(parent), m_requestor(0), m_ready(false)
{
    m_roles[productIdRole] = "productId";
    m_roles[productGroupRole] = "productGroup";
    m_roles[imageRole] = "image";
}

QVariant UberProductModel::data(const QModelIndex &index, int role) const {

    int row = index.row();
    if (row < 0 || row > m_data.size()) return QVariant();
    Product product = m_data.at(row);

    switch(role)
    {
    case productIdRole: return product.m_productId;
    case productGroupRole: return product.m_productGroup;
    case imageRole: return product.m_image;
    default: return QVariant();
    }
}

void UberProductModel::appendRow(Product product) {
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_data.append(product);
    endInsertRows();
}

void UberProductModel::populateModel(QList<Product> products) {
    beginResetModel();
    m_data.clear();
    m_data = products;
    endResetModel();
    m_ready = true;
    emit readyChanged();
}

void UberProductModel::setRequestor(UberProductRequestor *requestor) {
    if (m_requestor != requestor) {
        if (m_requestor) {
            disconnect(m_requestor, SIGNAL(productsChanged(QList<Product>)), this, SLOT(populateModel(QList<Product>)));
        }
        m_requestor = requestor;
        if (m_requestor) {
            connect(m_requestor, SIGNAL(productsChanged(QList<Product>)), this, SLOT(populateModel(QList<Product>)));
        }
        emit requestorChanged();
    }
}

void UberProductModel::getProducts(QString lat, QString lng) {
    m_requestor->fetchProductFromNetwork(lat, lng);
}
