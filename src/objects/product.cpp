#include "product.h"

Product::Product(
        QString productId,
        QString image,
        QString productGroup)
{
    this->m_productId = productId;
    this->m_image = image;
    this->m_productGroup = productGroup;
}
