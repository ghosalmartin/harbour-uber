#include "uber-profile-requestor.h"

UberProfileRequestor::UberProfileRequestor(QObject *parent)
    : UberRequestor(parent)
{
    connect(this, SIGNAL(profileChanged(Profile*)),
            this, SLOT(setProfile(Profile*)));
}

void UberProfileRequestor::fetchProfileFromNetwork(){
    makeNetworkCall(
                UBER_ME_ENDPOINT,
                QNetworkAccessManager::Operation::GetOperation,
                QByteArray());
}

void UberProfileRequestor::setProfile(Profile *profile){
    if(this->profile != profile){
        this->profile = profile;
        emit profileChanged(profile);
    }
}

Profile* UberProfileRequestor::getProfile(){
    return this->profile;
}

void UberProfileRequestor::deserialize(QByteArray data) {
    QString stringReply = (QString) data;
    QJsonDocument jsonResponse =
            QJsonDocument::fromJson(stringReply.toUtf8());

//    QJsonObject jsonObject = jsonResponse.object();

    Profile *profile = new Profile();
    profile->m_email = "test@test.com";
    profile->m_firstName = "martin";;
    profile->m_lastName = "ghosal";
    profile->m_mobileVerified = "true";
    profile->m_picture = "picture";
    profile->m_promoCode = "promo_code";
    profile->m_riderId = "rider_id";
    profile->m_uuid = "uuid";

    setProfile(profile);
//    Profile profile;
//    profile.email = jsonObject["email"].toString();
//    profile.firstName = jsonObject["first_name"].toString();
//    profile.lastName = jsonObject["last_name"].toString();
//    profile.mobileVerified = jsonObject["mobile_verified"].toString();
//    profile.picture = jsonObject["picture"].toString();
//    profile.promoCode = jsonObject["promo_code"].toString();
//    profile.riderId = jsonObject["rider_id"].toString();
//    profile.uuid = jsonObject["uuid"].toString();
}

void UberProfileRequestor::onError(QString errorString){
    qDebug() << errorString;
}
