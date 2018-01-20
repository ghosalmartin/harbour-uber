#include "src/objects/profile.h"

Profile::Profile(
        QString picture,
        QString firstName,
        QString lastName,
        QString uuid,
        QString riderId,
        QString email,
        QString mobileVerified,
        QString promoCode)
{

    this->m_picture = picture;
    this->m_firstName = firstName;
    this->m_lastName = lastName;
    this->m_uuid = uuid;
    this->m_riderId = riderId;
    this->m_email = email;
    this->m_mobileVerified = mobileVerified;
    this->m_promoCode = promoCode;
}
