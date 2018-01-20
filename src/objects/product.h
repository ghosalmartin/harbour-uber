#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QObject>

class Product : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString productId MEMBER m_productId)
    Q_PROPERTY(QString image MEMBER m_image)
    Q_PROPERTY(QString productGroup MEMBER m_productGroup)

public:
    explicit Product(QObject *parent = 0);
    Product(QString productId,
            QString image,
            QString productGroup);

private:
    QString m_productId;
    QString m_image;
    QString m_productGroup;
};

#endif // PRODUCT_H
