#include "Student.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

Student::Student(string n, string id) : User(n, id), booksIssuedCount(0) {}

void Student::displayMenu() {
    cout << "\n===== STUDENT MENU =====\n"
         << "1. Search Book\n2. Issue Book\n3. Return Book\n"
         << "4. View All Books\n5. Logout\n"
         << "========================\n";
}

int Student::getBooksIssuedCount() const { return booksIssuedCount; }
void Student::setBooksIssuedCount(int count) { booksIssuedCount = count; }

string Student::serialize() const {
    stringstream ss;
    ss << booksIssuedCount;
    return "STUDENT|" + name + "|" + userId + "|" + ss.str();
}

void Student::issueBook(const string& isbn, vector<Book*>& books) {
    if (booksIssuedCount >= 3)
        throw runtime_error("Issue limit reached.");

    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getISBN() == isbn) {
            if (!books[i]->getAvailability())
                throw runtime_error("Book is already issued.");
            
            books[i]->setStatus(false);
            booksIssuedCount++;
            cout << "Issued: " << books[i]->getTitle() << "\n";
            return;
        }
    }
    throw runtime_error("Book not found.");
}

void Student::returnBook(const string& isbn, vector<Book*>& books) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getISBN() == isbn) {
            if (books[i]->getAvailability())
                throw runtime_error("Book was not issued.");
            
            books[i]->setStatus(true);
            booksIssuedCount--;
            cout << "Returned: " << books[i]->getTitle() << "\n";
            return;
        }
    }
    throw runtime_error("Book not found.");
}

Student::~Student() {}
