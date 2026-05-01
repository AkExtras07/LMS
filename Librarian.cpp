#include "Librarian.h"
#include "./Database.h"
#include <iostream>

using namespace std;

Librarian::Librarian(string n, string id, string empId)
    : User(n, id), employeeId(empId) {}

void Librarian::displayMenu() {
    cout << "\n===== LIBRARIAN MENU =====\n"
         << "1. Add Book\n2. View All Members\n3. System Info\n"
         << "4. Remove Book\n5. Manage Members\n6. Issued Books Detail\n7. Logout\n"
         << "==========================\n";
}

string Librarian::serialize() const {
    return "LIBRARIAN|" + getName() + "|" + getUserId() + "|" + employeeId;
}

void Librarian::addBook(Database& db, string t, string a, string i) {
    	string query = "INSERT INTO books (title, author, isbn, available) VALUES ('" + t + "', '" + a + "', '" + i + "', 1)";
        db.execute(query);

    cout << "Book added successfully.\n";
}

void Librarian::removeBook(Database& db, string isbn) {
    string query = "DELETE FROM books WHERE isbn = '" + isbn + "'"; db.execute(query);

    cout << "Book removed successfully.\n";
}

void Librarian::manageMember(Database& db) {
    int choice;
    cout << "\n--- Member Management ---\n";
    cout << "1. Add Member\n2. Remove Member\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        string name, id, role;
        cin.ignore(1000, '\n');
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter User ID: ";
        getline(cin, id);
        cout << "Enter Role (student/librarian): ";
        getline(cin, role);

        string query = "INSERT INTO users (name, user_id, role) VALUES ('" 
               + name + "', '" + id + "', '" + role + "')";
db.execute(query);

        cout << "Member added successfully.\n";
    }
    else if (choice == 2) {
        string id;
        cout << "Enter User ID to remove: ";
        cin >> id;

        string query = "DELETE FROM users WHERE user_id = '" + id + "'";
db.execute(query);

        cout << "Member removed successfully.\n";
    }
    else {
        cout << "Invalid choice.\n";
    }
}