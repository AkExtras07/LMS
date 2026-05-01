#include "Student.h"
#include "Database.h"
#include <iostream>
#include <mysql.h>

using namespace std;

Student::Student(string n, string id) : User(n, id) {}

void Student::displayMenu() {
    cout << "\n===== STUDENT MENU =====\n"
         << "1. Search Book\n2. Issue Book\n3. Return Book\n"
         << "4. View All Books\n5. Logout\n"
         << "========================\n";
}

string Student::serialize() const {
    return "STUDENT|" + getName() + "|" + getUserId();
}

void Student::issueBook(Database& db, const string& isbn) {
    string query = "SELECT available FROM books WHERE isbn = '" + isbn + "'";
    MYSQL_RES* res = db.query(query);

    if (!res) return;

    MYSQL_ROW row = mysql_fetch_row(res);

    if (row && row[0] && atoi(row[0]) == 1) {

        string insertQuery = "INSERT INTO issued_books (user_id, isbn) VALUES ('"
                             + getUserId() + "', '" + isbn + "')";
        db.execute(insertQuery);

        string updateQuery = "UPDATE books SET available = 0 WHERE isbn = '" + isbn + "'";
        db.execute(updateQuery);

        cout << "Book issued successfully.\n";
    } else {
        cout << "Book not available.\n";
    }

    mysql_free_result(res);
}

void Student::returnBook(Database& db, const string& isbn) {
    string query = "SELECT * FROM issued_books WHERE isbn = '" + isbn +
                   "' AND user_id = '" + getUserId() +
                   "' AND return_date IS NULL";

    MYSQL_RES* res = db.query(query);

    if (!res) return;

    MYSQL_ROW row = mysql_fetch_row(res);

    if (row) {

        string updateIssued = "UPDATE issued_books SET return_date = NOW() WHERE isbn = '"
                              + isbn + "' AND user_id = '" + getUserId() +
                              "' AND return_date IS NULL";
        db.execute(updateIssued);

        string updateBook = "UPDATE books SET available = 1 WHERE isbn = '" + isbn + "'";
        db.execute(updateBook);

        cout << "Book returned successfully.\n";
    } else {
        cout << "Error: You did not issue this book.\n";
    }

    mysql_free_result(res);
}

Student::~Student() {}