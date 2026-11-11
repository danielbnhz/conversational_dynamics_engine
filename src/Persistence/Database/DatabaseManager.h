
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QString>

class DatabaseManager
{
public:
    DatabaseManager();
    ~DatabaseManager();

    bool open();
    void close();

    bool isOpen() const;
    QString lastError() const;

private:
    QSqlDatabase database;
    QString errorMessage;
};

#endif // DATABASEMANAGER_H
