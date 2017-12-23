#ifndef REQUESTOR_H
#define REQUESTOR_H

#include <QObject>
#include <QNetworkAccessManager>

#include "o0globals.h"
#include "o2requestor.h"
#include "o2uber.h"

#include "uber-endpoints.h"

class UberRequestor : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(O2Uber *authenticator_ READ getAuthenticator WRITE setAuthenticator)
    void setAuthenticator(O2Uber *Authenticator) ;
    O2Uber *getAuthenticator() const;

    explicit UberRequestor(QObject *parent = 0);

    void makeNetworkCall(QString endpoint, QNetworkAccessManager::Operation operation, const QByteArray &data);

    void success(QNetworkReply *reply);
    void failure(QNetworkReply::NetworkError error);

    O2Uber *authenticator_;
};

#endif // REQUESTOR
