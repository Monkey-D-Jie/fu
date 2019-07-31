#ifndef LOCALSTORAGEPROTOCOL_H
#define LOCALSTORAGEPROTOCOL_H

#include <QtCore>
#include "./base.h"


class LocalStorageUploader : public Uploader
{
    QString _folder;
    QString _output;

public:
    LocalStorageUploader(const QVariantMap settings);
    ~LocalStorageUploader() override;
    QString upload(QDataStream *stream, const QString name, bool overwrite = false) override;
};

class LocalStorageProtocol : public Protocol
{
    QList<ProtocolSettingInfo> _settingInfos;

public:
    LocalStorageProtocol();
    const QString getName();
    const QString getTitle();
    const QList<ProtocolSettingInfo> &getSettingInfos();
    Uploader *createUploader(const QVariantMap &settings);
};

#endif // LOCALSTORAGEPROTOCOL_H
