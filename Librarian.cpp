#include "Librarian.h"
#include "Library.h"
#include <iostream>

using namespace std;

Librarian::Librarian(string n, string id, string empId) 
    : User(n, id), employeeId(empId) {}

void Librarian::displayMenu() {
    cout << "\n===== LIBRARIAN MENU =====\n"
         << "1. Add Book\n2. View All Members\n3. Save Data\n"
         << "4. Remove Book\n5. Logout\n" // Added option 4
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
