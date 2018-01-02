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
    if(this->m_profile != profile){
        this->m_profile = profile;
        emit profileChanged(profile);
    }
}

Profile* UberProfileRequestor::getProfile(){
    return this->m_profile;
}

void UberProfileRequestor::deserialize(QByteArray data) {
    QString stringReply = (QString) data;
    QJsonDocument jsonResponse =
            QJsonDocument::fromJson(stringReply.toUtf8());

    //    QJsonObject jsonObject = jsonResponse.object();

    Profile *profile = new Profile("pic",
                                   "firstname",
                                   "lastname",
                                   "uuid",
                                   "riderid",
                                   "email",
                                   "mobileverified",
                                   "promocode");
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
