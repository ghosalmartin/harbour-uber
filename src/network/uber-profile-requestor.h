#ifndef UBERPROFILEREQUESTOR_H
#define UBERPROFILEREQUESTOR_H

#include <QObject>
#include <QDebug>

#include "uber-endpoints.h"
#include "uber-requestor.h"

class UberProfileRequestor : public UberRequestor
{
    Q_OBJECT
public:
    explicit UberProfileRequestor(QObject *parent = 0);

    Q_INVOKABLE void getProfile();

signals:

public slots:
};

#endif // UBERPROFILEREQUESTOR_H
