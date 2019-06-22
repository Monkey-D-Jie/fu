#ifndef CLIP_H
#define CLIP_H

#include <QtCore>
#include <QPixmap>

struct Clip
{
    uint id;
    QVariant data;
    bool isImage;
    bool isFile;
    QByteArray rawPngThumb;
    QString name;
    QDateTime createdAt;
};

#endif // CLIP_H