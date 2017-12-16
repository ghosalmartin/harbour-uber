#ifndef UBERLOGIN_H
#define UBERLOGIN_H

#include <QObject>

#include "o2uber.h"

class Requestor : public QObject
{
    Q_OBJECT


public:
    /// OAuth authenticator
    Q_PROPERTY(O2Uber *authenticator_ WRITE setAuthenticator)
    void setAuthenticator(O2Uber *v) ;

    Q_INVOKABLE void makeNetworkCall(QString endpointUrl);

    explicit Requestor(QObject *parent = 0);

public slots:
    void success(int id, QNetworkReply::NetworkError error, QByteArray data);
    void failure(QNetworkReply::NetworkError);

private:
    O2Uber *authenticator_;
};

#endif // UBERLOGIN_H
