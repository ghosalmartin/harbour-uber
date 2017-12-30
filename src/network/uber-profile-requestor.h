#ifndef UBERPROFILEREQUESTOR_H
#define UBERPROFILEREQUESTOR_H

#include <QObject>
#include <QDebug>
#include <QJsonDocument>

#include "uber-endpoints.h"
#include "uber-requestor.h"

#include "src/objects/profile.h"

class UberProfileRequestor : public UberRequestor
{
    Q_OBJECT
    Q_PROPERTY(Profile *profile_ READ getProfile WRITE setProfile NOTIFY profileChanged)

public:
    explicit UberProfileRequestor(QObject *parent = 0);

    void deserialize(QByteArray data);
    void onError(QString errorString);

    Q_INVOKABLE void fetchProfileFromNetwork();

    Profile* getProfile();

signals:
    void profileChanged(Profile *profile);

private:
    Profile *profile;

private slots:
    void setProfile(Profile *profile);

};

#endif // UBERPROFILEREQUESTOR_H
