#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <string>

class Database {
private:
    MYSQL* conn;

public:
    Database();
    ~Database();

    bool connect();

    void execute(const std::string& query);
    MYSQL_RES* query(const std::string& query);
};

#endif