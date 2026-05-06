#include "Database.h"
#include <iostream>

using namespace std;

Database::Database() {
    conn = nullptr;
}

Database::~Database() {
    if (conn) {
        mysql_close(conn);
    }
}

bool Database::connect() {
	 conn = mysql_init(NULL);
	 
    if (!mysql_real_connect(conn, "127.0.0.1", "root", "admin1234", "lms_db", 3306, NULL, 0)) {
        cout << "Connection failed: " << mysql_error(conn) << endl;
        return false;
    }

    cout << "Connected to database!\n";
    return true;
}

void Database::execute(const string& query) {
    if (!conn) {
        connect();
    }

    if (mysql_query(conn, query.c_str())) {
        cout << "Execute Error: " << mysql_error(conn) << endl;
    }
}

MYSQL_RES* Database::query(const string& query) {
    if (!conn) {
        cout << "Reconnecting...\n";
        connect();
    }

    if (mysql_query(conn, query.c_str())) {
        cout << "Query Error: " << mysql_error(conn) << endl;
        return nullptr;
    }

    return mysql_store_result(conn);
}