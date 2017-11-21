/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>

#include "uberlogin.h"

class Helper : public QObject {
    Q_OBJECT

public:
    Helper() : QObject(), o2Uber(this), waitForMsg_(false), msg_(QString()) {}

public slots:
    void processArgs() {

        connect(&o2Uber, SIGNAL(linkingFailed()), this, SLOT(onLinkingFailed()));
        connect(&o2Uber, SIGNAL(linkingSucceeded()), this, SLOT(onLinkingSucceeded()));
        o2Uber.doOAuth(O2::GrantFlowAuthorizationCode);
    }

    void onLinkingFailed() {
        qDebug() << "Linking failed!";
        qApp->exit(1);
    }

    void onLinkingSucceeded() {
        qDebug() << "Linking succeeded!";
        if (waitForMsg_) {
            //postStatusUpdate(msg_);
        } else {
            qApp->quit();
        }
    }

private:
    O2Uber o2Uber;
    bool waitForMsg_;
    QString msg_;
};

int main(int argc, char *argv[])
{


    QGuiApplication *app = SailfishApp::application(argc, argv);
    qDebug() << "Created Application";

    app->setOrganizationName("harbour-uber");
    app->setApplicationName("harbour-uber");

    QQuickView *view = SailfishApp::createView();
    qDebug() << "Created view";

    QString qml = QString("qml/%1.qml").arg("harbour-uber");

    view->setSource(SailfishApp::pathTo(qml));
    qDebug() << "Set source";
    view->show();
    qDebug() << "Showed view";

    Helper helper;

    return app->exec();

}

#include "harbour-uber.moc"
