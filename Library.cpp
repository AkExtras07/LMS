#include "Library.h"
#include <iostream>
#include <mysql.h>

using namespace std;

Library::Library() {}

Library::~Library() {}

void Library::viewAllMembers(Database& db) {
    MYSQL_RES* res = db.query("SELECT name, user_id, role FROM users");

    if (!res) return;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        cout << (row[0] ? row[0] : "NULL") << " | "
             << (row[1] ? row[1] : "NULL") << " | "
             << (row[2] ? row[2] : "NULL") << endl;
    }

    mysql_free_result(res);
}

void Library::viewIssuedBooksReport(Database& db) {
    MYSQL_RES* res = db.query("SELECT user_id, isbn, issue_date, return_date FROM issued_books");

    if (!res) return;

    MYSQL_ROW row;

    while ((row = mysql_fetch_row(res))) {
        cout << (row[0] ? row[0] : "NULL") << " | "
             << (row[1] ? row[1] : "NULL") << " | "
             << (row[2] ? row[2] : "NULL") << " | "
             << (row[3] ? row[3] : "NULL") << endl;
    }

    mysql_free_result(res);
}