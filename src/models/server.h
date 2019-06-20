#ifndef SERVER_H
#define SERVER_H

#include "protocol.h"
#include "outputformat.h"
#include <QtCore>

struct Server
{
    uint id;
    QString name;
    QString protocol;
    QVariantMap settings;
    bool uploadEnabled;
    uint outputFormatId;
    QDateTime createdAt;
    Uploader *uploader;
    OutputFormat outputFormater;
};

#endif // SERVER_H
