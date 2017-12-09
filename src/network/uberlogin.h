#ifndef UBERLOGIN_H
#define UBERLOGIN_H

#include <QObject>

#include "o2uber.h"

class UberLogin : public QObject
{
    Q_OBJECT


public:
    /// OAuth authenticator
    Q_PROPERTY(O2Uber *authenticator_ READ authenticator WRITE setAuthenticator)
    O2Uber *authenticator() const;
    void setAuthenticator(O2Uber *v) ;

    Q_INVOKABLE void getProfile();
    Q_INVOKABLE void setupStore();

    explicit UberLogin(QObject *parent = 0);

public slots:
    void success(int id, QNetworkReply::NetworkError error, QByteArray data);
    void failure(QNetworkReply::NetworkError);

private:
    O2Uber *authenticator_;
};

#endif // UBERLOGIN_H
