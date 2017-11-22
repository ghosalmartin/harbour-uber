#ifndef UBERLOGIN_H
#define UBERLOGIN_H

#include <QObject>

#include "o2uber.h"

class UberLogin : public QObject
{
    Q_OBJECT

public:
    explicit UberLogin(QObject *parent = 0);

signals:
    void extraTokensReady(const QVariantMap &extraTokens);
    void linkingFailed();
    void linkingSucceeded();

public slots:
    void doOAuth(O2::GrantFlow grantFlowType);
    void validateToken();

private slots:
    void onLinkedChanged();
    void onLinkingSucceeded();
    void onOpenBrowser(const QUrl &url);
    void onCloseBrowser();
    void onFinished();

private:
    O2Uber *o2Uber_;
};

#endif // UBERLOGIN_H
