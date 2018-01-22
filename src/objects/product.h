#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>

class Product
{

public:
    Product(QString productId,
            QString image,
            QString productGroup);

    QString m_productId;
    QString m_image;
    QString m_productGroup;
};

#endif // PRODUCT_H
