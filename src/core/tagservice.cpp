#include "tagservice.h"


Tag convertResultToTag(QSqlQuery result) {
    Tag tag;
    auto rec = result.record();
    tag.id = result.value(rec.indexOf("id")).toUInt();
    tag.name = result.value(rec.indexOf("name")).toString();
    tag.createAt = result.value(rec.indexOf("createdAt")).toDateTime();
    tag.lastUsedTimestamp = result.value(rec.indexOf("lastUsedTimestamp")).toUInt();
    return tag;
}

TagService::TagService(SqlStore &store)
    : _store(store)
{

}

TagService::~TagService()
{

}

QList<Tag> TagService::getAll()
{
    QList<Tag> tags;
    auto result = _store.exec("SELECT * FROM tags ORDER BY lastUsedTimestamp DESC");
    while (result.next()) {
        tags.append(convertResultToTag(result));
    }
    return tags;
}

uint TagService::append(const QString &name)
{
    QDateTime now = QDateTime::currentDateTime();

    auto query = _store.prepare("INSERT INTO tags (name, createdAt, lastUsedTimestamp) VALUES (:name, :createdAt, :lastUsedTimestamp)");
    query.bindValue(":name", name);
    query.bindValue(":createdAt", now.toString(Qt::ISODate));
    query.bindValue(":lastUsedTimestamp", now.toTime_t());

    if (!query.exec())
        qDebug() << "add tag failed: " << query.lastError().text();

    return query.lastInsertId().toUInt();
}

void TagService::update(uint id, const QString &name)
{
    auto query = _store.prepare("UPDATE tags SET name=:name WHERE id=:id");
    query.bindValue(":name", name);
    query.bindValue(":id", id);
    query.exec();
}

void TagService::remove(uint id)
{
    auto query = _store.prepare("DELETE FROM tags WHERE id=:id");
    query.bindValue(":id", id);
    query.exec();
}

uint TagService::findOrAppend(const QString &name)
{
    qDebug() << "find or append " << name;
    auto query = _store.prepare("SELECT id FROM tags WHERE name=:name");
    query.bindValue(":name", name);

    auto result = _store.exec();
    if (result.next()) {
        qDebug() << "tag found: " << result.value(0);
        return result.value(0).toUInt();
    }
    return append(name);
}
