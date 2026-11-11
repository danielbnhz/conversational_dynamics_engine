
#include "DatabaseManager.h"

#include <QDir>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager()
{
    database = QSqlDatabase::addDatabase("QSQLITE");

    database.setDatabaseName(
        "data/databases/cde_research.sqlite"
    );
}

DatabaseManager::~DatabaseManager()
{
    close();
}

bool DatabaseManager::open()
{
    QDir directory;

    if (!directory.mkpath("data/databases")) {
        errorMessage = "Could not create database directory.";
        return false;
    }

    if (database.isOpen()) {
        return true;
    }

    if (!database.open()) {
        errorMessage = database.lastError().text();
        return false;
    }

    errorMessage.clear();

    qDebug() << "CDE database connected:"
             << database.databaseName();

    return true;
}

void DatabaseManager::close()
{
    if (database.isOpen()) {
        database.close();
    }
}

bool DatabaseManager::isOpen() const
{
    return database.isOpen();
}

QString DatabaseManager::lastError() const
{
    return errorMessage;
}
