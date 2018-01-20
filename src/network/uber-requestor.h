#ifndef REQUESTOR_H
#define REQUESTOR_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QEventLoop>

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

    void makeNetworkCall(char *endpoint, QNetworkAccessManager::Operation operation, const QByteArray &data = QByteArray());

    virtual void deserialize(QByteArray data) = 0;
    virtual void onError(QString errorString) = 0;

protected:
    O2Uber *authenticator_;

public slots:
    void finished(QNetworkReply *reply);

private:
    QEventLoop eventLoop;
};

#endif // REQUESTOR
