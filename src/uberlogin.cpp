#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QMetaEnum>
#include <QDebug>

#include "uberlogin.h"
#include "o0globals.h"
#include "o0settingsstore.h"

UberLogin::UberLogin(QObject *parent) : QObject(parent)
{
    O0SettingsStore *store = new O0SettingsStore(O2_ENCRYPTION_KEY);
    store->setGroupKey("uber");
    authenticator_->setStore(store);
}

O2Uber *UberLogin::authenticator() const {
    return authenticator_;
}

void UberLogin::setAuthenticator(O2Uber *v) {
    authenticator_ = v;
}
