#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDesktopServices>
#include <QMetaEnum>
#include <QDebug>

#include "uberlogin.h"
#include "o0globals.h"
#include "o0settingsstore.h"

const char UBER_CLIENT_ID[] = "z2hUEP5mar6x466S6JoVqjOFLQA5yei3";
const char UBER_CLIENT_SECRET[] = "bX4Zy0RzGxPAklazjPLgyouiktUHM1sKQ36q6eZ_";

const char UBER_LOGIN_URL[] = "https://login.uber.com/oauth/v2/authorize";
const char UBER_ME_URL[] = "https://api.uber.com/v1.2/me";

const int localPort = 8888;

#define QENUM_NAME(o,e,v) (o::staticMetaObject.enumerator(o::staticMetaObject.indexOfEnumerator(#e)).valueToKey((v)))
#define GRANTFLOW_STR(v) QString(QENUM_NAME(O2, GrantFlow, v))

UberLogin::UberLogin(QObject *parent) : QObject(parent)
{
    o2Uber_ = new O2Uber(this);

    o2Uber_->setClientId(UBER_CLIENT_ID);
    o2Uber_->setClientSecret(UBER_CLIENT_SECRET);
    o2Uber_->setLocalPort(localPort);
    o2Uber_->setRequestUrl(UBER_LOGIN_URL);

    O0SettingsStore *store = new O0SettingsStore(O2_ENCRYPTION_KEY);
    store->setGroupKey("uber");
    o2Uber_->setStore(store);

    connect(o2Uber_, SIGNAL(linkedChanged()), this, SLOT(onLinkedChanged()));
    connect(o2Uber_, SIGNAL(linkingFailed()), this, SIGNAL(linkingFailed()));
    connect(o2Uber_, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
    connect(o2Uber_, SIGNAL(openBrowser(QUrl)), this, SLOT(onOpenBrowser(QUrl)));
    connect(o2Uber_, SIGNAL(closeBrowser()), this, SLOT(onCloseBrowser()));
}

void UberLogin::doOAuth(O2::GrantFlow grantFlowType) {
    qDebug() << "Starting OAuth 2 with grant flow type" << GRANTFLOW_STR(grantFlowType) << "...";
    o2Uber_->setGrantFlow(grantFlowType);
    o2Uber_->unlink();
    o2Uber_->link();
}

void UberLogin::validateToken() {
    if (!o2Uber_->linked()) {
        qWarning() << "ERROR: Application is not linked!";
        emit linkingFailed();
        return;
    }

    QString accessToken = o2Uber_->token();
    QString debugUrlStr = QString(UBER_ME_URL).arg(accessToken);
    QNetworkRequest request = QNetworkRequest(QUrl(debugUrlStr));
    QNetworkAccessManager *mgr = new QNetworkAccessManager(this);
    QNetworkReply *reply = mgr->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(onFinished()));
    qDebug() << "Validating user token. Please wait...";
}

void UberLogin::onOpenBrowser(const QUrl &url) {
    qDebug() << "Attempting to open browser!";

}

void UberLogin::onCloseBrowser() {
}

void UberLogin::onLinkedChanged() {
    qDebug() << "Link changed!";
}

void UberLogin::onLinkingSucceeded() {
    O2Uber *o1t = qobject_cast<O2Uber *>(sender());
    if (!o1t->linked()) {
        return;
    }
    QVariantMap extraTokens = o1t->extraTokens();
    if (!extraTokens.isEmpty()) {
        emit extraTokensReady(extraTokens);
        qDebug() << "Extra tokens in response:";
        foreach (QString key, extraTokens.keys()) {
            qDebug() << "\t" << key << ":" << (extraTokens.value(key).toString().left(3) + "...");
        }
    }
    emit linkingSucceeded();
}

void UberLogin::onFinished() {
    QNetworkReply *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply) {
        qWarning() << "NULL reply!";
        emit linkingFailed();
        return;
    }

    reply->deleteLater();
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Reply error:" << reply->error();
        qWarning() << "Reason:" << reply->errorString();
        emit linkingFailed();
        return;
    }

    QByteArray replyData = reply->readAll();
    bool valid = !replyData.contains("error");
    if (valid) {
        qDebug() << "Token is valid";
        emit linkingSucceeded();
    } else {
        qDebug() << "Token is invalid";
        emit linkingFailed();
    }
}

