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

    explicit UberLogin(QObject *parent = 0);

private:
    O2Uber *authenticator_;
};

#endif // UBERLOGIN_H
