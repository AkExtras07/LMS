#include "Student.h"
#include "Book.h"      // FIX 1: Must include Book.h to call getISBN, setStatus, etc.
#include <iostream>
#include <sstream>

using namespace std;

// Constructor
Student::Student(string n, string id) : User(n, id), booksIssuedCount(0) {}

// Menu display
void Student::displayMenu() {
    cout << "\n===== STUDENT MENU =====\n"
         << "1. Search Book\n2. Issue Book\n3. Return Book\n"
         << "4. View All Books\n5. Logout\n"
         << "========================\n";
}

// Getters and Setters
int Student::getBooksIssuedCount() const { return booksIssuedCount; }
void Student::setBooksIssuedCount(int count) { booksIssuedCount = count; }

// Data persistence
string Student::serialize() const {
    stringstream ss;
    ss << booksIssuedCount;
    // Note: Ensure name and userId are accessible from User class
    return "STUDENT|" + getName() + "|" + getUserId() + "|" + ss.str();
}

// Issue Book Logic
void Student::issueBook(const string& isbn, vector<Book*>& books) {
    // 1. Check issue limit
    if (booksIssuedCount >= 3) {
        cout << "Error: Issue limit reached (Max 3 books).\n";
        return;
    }

    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getISBN() == isbn) {
            // 2. Check if already issued
            if (!books[i]->getAvailability()) {
                cout << "Error: Book is already issued.\n";
                return;
            }
            
            // 3. Mark as issued and save student name
            books[i]->setStatus(false);
            books[i]->setHolder(this->getName()); 
            
            booksIssuedCount++;
            cout << "Successfully Issued: " << books[i]->getTitle() << "\n";
            return;
        }
    }
    
    // 4. Fallback
    cout << "Error: Book with ISBN " << isbn << " not found.\n";
}

// Return Book Logic
void Student::returnBook(const string& isbn, vector<Book*>& books) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getISBN() == isbn) {
            if (!books[i]->getAvailability()) {
                // Check if THIS student is the one who actually has it
                if (books[i]->getHolder() == this->getName()) {
                    books[i]->setStatus(true);
                    books[i]->setHolder("None");
                    
                    if (booksIssuedCount > 0) booksIssuedCount--;
                    cout << "Returned: " << books[i]->getTitle() << "\n";
                    return;
                } else {
                    cout << "Error: This book was issued to " << books[i]->getHolder() << ", not you.\n";
                    return;
                }
            }
        }
    }
    cout << "Error: Invalid ISBN or book was not issued.\n";
}

Student::~Student() {}