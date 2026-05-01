#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <mysql.h>

#include "User.h"
#include "Student.h"
#include "Librarian.h"
#include "Database.h"

using namespace std;

void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void showWelcome() {
    cout << "========================================\n";
    cout << "    LIBRARY MANAGEMENT SYSTEM (v1.0)    \n";
    cout << "========================================\n";
}

int main() {
    Database db;
    db.connect();

    bool running = true;

    while (running) {
        clearScreen();
        showWelcome();

        cout << "1. Login\n";
        cout << "2. Exit\n";
        cout << "Choice: ";

        int startChoice;
        cin >> startChoice;

        if (startChoice == 2) break;

        string name, userId;
        clearBuffer();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter User ID: ";
        cin >> userId;

        // 🔍 LOGIN QUERY
        string query = "SELECT role FROM users WHERE name = '" + name +
                       "' AND user_id = '" + userId + "'";

        MYSQL_RES* res = db.query(query);

        User* currentUser = nullptr;

        if (res) {
            MYSQL_ROW row = mysql_fetch_row(res);

            if (row) {
                string role = row[0];

                if (role == "librarian") {
                    currentUser = new Librarian(name, userId, "EMP");
                } else {
                    currentUser = new Student(name, userId);
                }
            }

            mysql_free_result(res);
        }

        if (!currentUser) {
            cout << "Invalid login!\n";
            cin.ignore();
            cin.get();
            continue;
        }

        bool loggedIn = true;

        while (loggedIn) {
            clearScreen();
            cout << "Logged in as: " << currentUser->getName() << "\n";
            currentUser->displayMenu();

            int choice;
            cout << "Choice: ";
            cin >> choice;

            Librarian* lib = dynamic_cast<Librarian*>(currentUser);
            Student* stu = dynamic_cast<Student*>(currentUser);

            // ================= LIBRARIAN =================
            if (lib) {
                switch (choice) {
                    case 1: {
                        string t, a, i;
                        clearBuffer();
                        cout << "Title: "; getline(cin, t);
                        cout << "Author: "; getline(cin, a);
                        cout << "ISBN: "; getline(cin, i);

                        string q = "INSERT INTO books (title, author, isbn, available) VALUES ('"
                                   + t + "', '" + a + "', '" + i + "', 1)";
                        db.execute(q);

                        cout << "Book added.\n";
                        break;
                    }

                    case 2: {
                        MYSQL_RES* res = db.query("SELECT name, user_id, role FROM users");

                        if (res) {
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(res))) {
                                cout << row[0] << " | " << row[1] << " | " << row[2] << endl;
                            }
                            mysql_free_result(res);
                        }
                        break;
                    }

                    case 4: {
                        string isbn;
                        cout << "Enter ISBN: ";
                        cin >> isbn;

                        string q = "DELETE FROM books WHERE isbn = '" + isbn + "'";
                        db.execute(q);

                        cout << "Book removed.\n";
                        break;
                    }

                    case 5: {
                        string n, id, role;
                        clearBuffer();

                        cout << "Name: "; getline(cin, n);
                        cout << "ID: "; getline(cin, id);
                        cout << "Role: "; getline(cin, role);

                        string q = "INSERT INTO users (name, user_id, role) VALUES ('"
                                   + n + "', '" + id + "', '" + role + "')";
                        db.execute(q);

                        cout << "Member added.\n";
                        break;
                    }

                    case 6: {
                        MYSQL_RES* res = db.query("SELECT user_id, isbn, issue_date, return_date FROM issued_books");

                        if (res) {
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(res))) {
                                cout << row[0] << " | " << row[1] << " | "
                                     << row[2] << " | " << row[3] << endl;
                            }
                            mysql_free_result(res);
                        }
                        break;
                    }

                    case 7:
                        loggedIn = false;
                        break;
                }
            }

            // ================= STUDENT =================
            else if (stu) {
                switch (choice) {
                    case 1: {
                        string q;
                        clearBuffer();
                        cout << "Search: ";
                        getline(cin, q);

                        string query = "SELECT title, author, isbn, available FROM books WHERE title LIKE '%" + q + "%'";
                        MYSQL_RES* res = db.query(query);

                        if (res) {
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(res))) {
                                cout << row[0] << " | " << row[1] << " | " << row[2]
                                     << " | " << (atoi(row[3]) ? "Available" : "Issued") << endl;
                            }
                            mysql_free_result(res);
                        }
                        break;
                    }

                    case 2: {
                        string isbn;
                        cout << "ISBN: ";
                        cin >> isbn;

                        string q = "SELECT available FROM books WHERE isbn = '" + isbn + "'";
                        MYSQL_RES* res = db.query(q);

                        if (res) {
                            MYSQL_ROW row = mysql_fetch_row(res);

                            if (row && atoi(row[0]) == 1) {
                                db.execute("INSERT INTO issued_books (user_id, isbn) VALUES ('" + userId + "', '" + isbn + "')");
                                db.execute("UPDATE books SET available = 0 WHERE isbn = '" + isbn + "'");

                                cout << "Book issued.\n";
                            } else {
                                cout << "Not available.\n";
                            }

                            mysql_free_result(res);
                        }
                        break;
                    }

                    case 3: {
                        string isbn;
                        cout << "ISBN: ";
                        cin >> isbn;

                        db.execute("UPDATE issued_books SET return_date = NOW() WHERE isbn = '" + isbn + "' AND return_date IS NULL");
                        db.execute("UPDATE books SET available = 1 WHERE isbn = '" + isbn + "'");

                        cout << "Book returned.\n";
                        break;
                    }

                    case 4: {
                        MYSQL_RES* res = db.query("SELECT title, author, isbn FROM books");

                        if (res) {
                            MYSQL_ROW row;
                            while ((row = mysql_fetch_row(res))) {
                                cout << row[0] << " | " << row[1] << " | " << row[2] << endl;
                            }
                            mysql_free_result(res);
                        }
                        break;
                    }

                    case 5:
                        loggedIn = false;
                        break;
                }
            }

            if (loggedIn) {
                cout << "\nPress Enter...";
                clearBuffer();
                cin.get();
            }
        }

        delete currentUser;
    }

    cout << "Goodbye!\n";
    return 0;
}