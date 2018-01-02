#ifndef UBERPROFILEREQUESTOR_H
#define UBERPROFILEREQUESTOR_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

#include "uber-endpoints.h"
#include "uber-requestor.h"

#include "src/objects/profile.h"

class UberProfileRequestor : public UberRequestor
{
    Q_OBJECT
    Q_PROPERTY(Profile* profile READ getProfile WRITE setProfile NOTIFY profileChanged)

public:
    explicit UberProfileRequestor(QObject *parent = 0);

    void deserialize(QByteArray data);
    void onError(QString errorString);

    Q_INVOKABLE void fetchProfileFromNetwork();

    Profile* getProfile();

signals:
    void profileChanged(Profile *m_profile);

private:
    Profile *m_profile;

private slots:
    void setProfile(Profile *m_profile);

};

#endif // UBERPROFILEREQUESTOR_H
