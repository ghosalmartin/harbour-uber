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

    QJsonObject jsonObject = jsonResponse.object();

    Profile *profile = new Profile(jsonObject["picture"].toString(),
                                   jsonObject["first_name"].toString(),
                                   jsonObject["last_name"].toString(),
                                   jsonObject["uuid"].toString(),
                                   jsonObject["rider_id"].toString(),
                                   jsonObject["email"].toString(),
                                   jsonObject["mobile_verified"].toString(),
                                   jsonObject["promo_code"].toString());
    setProfile(profile);
}

void UberProfileRequestor::onError(QString errorString){
    qDebug() << errorString;
}
