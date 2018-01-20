#ifndef PROFILE_H
#define PROFILE_H

#include <QString>
#include <QObject>

class Profile: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString picture MEMBER m_picture)
    Q_PROPERTY(QString firstName MEMBER m_firstName)
    Q_PROPERTY(QString lastName MEMBER m_lastName)
    Q_PROPERTY(QString uuid MEMBER m_uuid)
    Q_PROPERTY(QString riderId MEMBER m_riderId)
    Q_PROPERTY(QString email MEMBER m_email)
    Q_PROPERTY(QString mobileVerified MEMBER m_mobileVerified)
    Q_PROPERTY(QString promoCode MEMBER m_promoCode)

public:
    explicit Profile (QObject *parent = 0);
    Profile(QString picture,
            QString firstName,
            QString lastName,
            QString uuid,
            QString riderId,
            QString email,
            QString mobileVerified,
            QString promoCode);

private:
    QString m_picture;
    QString m_firstName;
    QString m_lastName;
    QString m_uuid;
    QString m_riderId;
    QString m_email;
    QString m_mobileVerified;
    QString m_promoCode;
};

#endif // PROFILE_H
