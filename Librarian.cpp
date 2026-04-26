#include "Librarian.h"
#include "Library.h"
#include "student.h"
#include <iostream>

using namespace std;

Librarian::Librarian(string n, string id, string empId) 
    : User(n, id), employeeId(empId) {}

void Librarian::displayMenu() {
    cout << "\n===== LIBRARIAN MENU =====\n"
         << "1. Add Book\n2. View All Members\n3. Save Data\n"
         << "4. Remove Book\n5. Manage Members\n6. Logout\n" // Added option 4
         << "==========================\n";
}

string Librarian::serialize() const {
    return "LIBRARIAN|" + name + "|" + userId + "|" + employeeId;
}

void Librarian::addBook(vector<Book*>& books, string t, string a, string i) {
    books.push_back(new Book(t, a, i));
    cout << "Book added successfully.\n";
    
    
}

void Librarian::removeBook(Library& lib, string isbn) {
    lib.removeBookByISBN(isbn);
}


//void Librarian::manageMember(Library& lib) {
//    int choice;
//    cout << "1. Add Member\n2. Remove Member\n3. Toggle Status\nChoice: ";
//    cin >> choice;
    // Implementation calls lib.addMember, lib.removeMember, or lib.toggleMemberStatus
//}

void Librarian::manageMember(Library& lib) {
    int choice;
    cout << "\n--- Member Management ---\n";
    cout << "1. Add Member\n2. Remove Member\n3. Toggle Status (Active/Inactive)\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        // ADD MEMBER
        string n, id, type;
        cin.ignore(1000, '\n'); // Clear the buffer so getline works
        cout << "Enter Name: ";
        getline(cin, n);
        cout << "Enter User ID: ";
        getline(cin, id);
        cout << "Role (S for Student, L for Librarian): ";
        cin >> type;

        if (type == "S" || type == "s") {
            lib.addMember(new Student(n, id));
            cout << "Student account created.\n";
        } else if (type == "L" || type == "l") {
            string empId;
            cout << "Enter Employee ID: ";
            cin >> empId;
            lib.addMember(new Librarian(n, id, empId));
            cout << "Librarian account created.\n";
        } else {
            cout << "Invalid role.\n";
        }
    } 
    else if (choice == 2) {
        // REMOVE MEMBER
        string id;
        cout << "Enter User ID to remove: ";
        cin >> id;
        lib.removeMember(id); // Calls the function we added to Library.cpp
    } 
   // else if (choice == 3) {
   //     // TOGGLE STATUS
   //     string id;
   //     cout << "Enter User ID to toggle status: ";
   //     cin >> id;
   //     lib.toggleMemberStatus(id); // Calls the function we added to Library.cpp
   // } 
    else {
        cout << "Invalid choice.\n";
    }
}
