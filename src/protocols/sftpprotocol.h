#ifndef SFTPPROTOCOL_H
#define SFTPPROTOCOL_H

#include <QtCore>
#include "./base.h"

class SftpUploader : public Uploader
{
    QCurl _curl;
    QString _outputUrl;

public:
    SftpUploader(const QVariantMap settings);
    void upload(QIODevice *stream, UploadJob &job) override;
};

class SftpProtocol: public Protocol
{
    QList<ProtocolSettingInfo> _settingInfos;

public:
    SftpProtocol();

    // Protocol interface
    const QString getName();
    const QString getTitle();
    const QList<ProtocolSettingInfo> &getSettingInfos();
    Uploader *createUploader(const QVariantMap &settings);
};

#endif // SFTPPROTOCOL_H
