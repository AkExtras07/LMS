#include "Library.h"
#include "Book.h"
#include "Student.h"
#include "Librarian.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>
#include <cstdlib> // For atoi

using namespace std;

Library::Library() { loadFromFile(); }

Library::~Library() {
    for (size_t i = 0; i < books.size(); ++i) delete books[i];
    for (size_t i = 0; i < members.size(); ++i) delete members[i];
}

void Library::addBook(Book* b) {
    if (!b) return;
    books.push_back(b);
}

void Library::addMember(User* u) {
    members.push_back(u);
}

void Library::printBookHeader() {
    cout << "\n" << string(80, '-') << "\n"
         << left << setw(30) << "Title" << setw(25) << "Author" 
         << setw(15) << "ISBN" << "Status\n"
         << string(80, '-') << "\n";
}

void Library::searchBook(string query) {
    transform(query.begin(), query.end(), query.begin(), ::tolower);
    bool found = false;
    printBookHeader();
    
    for (size_t i = 0; i < books.size(); ++i) {
        Book* b = books[i];
        string t = b->getTitle();
        string a = b->getAuthor();
        string isbn = b->getISBN();
        
        transform(t.begin(), t.end(), t.begin(), ::tolower);
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        transform(isbn.begin(), isbn.end(), isbn.begin(), ::tolower);
        
        if (t.find(query) != string::npos ||
            a.find(query) != string::npos ||
            isbn.find(query) != string::npos) {
            b->displayBookDetails();
            found = true;
        }
    }
    
    if (!found)
        cout << "No books found matching \"" << query << "\".\n";
    cout << string(80, '-') << "\n";
}

void Library::viewAllBooks() {
    if (books.empty()) { cout << "Empty.\n"; return; }
    printBookHeader();
    for (size_t i = 0; i < books.size(); ++i) books[i]->displayBookDetails();
}

void Library::viewAllMembers() {
    printBookHeader(); // Reusing line formatting
    for (size_t i = 0; i < members.size(); ++i) {
        cout << members[i]->getName() << " [" << members[i]->getUserId() << "]\n";
    }
}

// In Library.cpp - Replace the old function body with this:
User* Library::findUser(string name, string id) {
    for (size_t i = 0; i < members.size(); ++i) {
        // Now checks both Name and ID
        if (members[i]->getName() == name && members[i]->getUserId() == id) {
            return members[i];
        }
    }
    return NULL; 
}



vector<Book*>& Library::getBooks() { return books; }

void Library::saveToFile() {
    ofstream bfile("books.dat");
    for (size_t i = 0; i < books.size(); ++i) bfile << books[i]->serialize() << "\n";
    bfile.close();

    ofstream mfile("members.dat");
    for (size_t i = 0; i < members.size(); ++i) mfile << members[i]->serialize() << "\n";
    mfile.close();
}

void Library::loadFromFile() {
    ifstream bfile("books.dat");
    string line;
    while (getline(bfile, line)) {
        if (!line.empty()) books.push_back(new Book(Book::deserialize(line)));
    }
    bfile.close();

    ifstream mfile("members.dat");
    while (getline(mfile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string role, name, id, extra;
        getline(ss, role, '|'); getline(ss, name, '|');
        getline(ss, id, '|'); getline(ss, extra, '|');
        
        if (role == "STUDENT") {
            Student* s = new Student(name, id);
            s->setBooksIssuedCount(atoi(extra.c_str()));
            members.push_back(s);
        } else if (role == "LIBRARIAN") {
            members.push_back(new Librarian(name, id, extra));
        }
    }
    
    mfile.close();
}

void Library::removeBookByISBN(string isbn) {
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i]->getISBN() == isbn) {
            delete books[i]; // Correctly free memory for the pointer
            books.erase(books.begin() + i); // Remove from the vector list
            cout << "Book removed successfully.\n";
            return;
        }
    }
    cout << "Error: Book with ISBN " << isbn << " not found.\n";
  } 
  
void Library::removeMember(string userId) {
    for (size_t i = 0; i < members.size(); ++i) {
        if (members[i]->getUserId() == userId) {
            delete members[i]; 
            members.erase(members.begin() + i);
            cout << "Member removed.\n";
            return;
        }
    }
    cout << "Member not found.\n";
}



void Library::viewIssuedBooksReport() {
    cout << "\n" << string(75, '=') << "\n";
    cout << left << setw(30) << "BOOK TITLE" << setw(20) << "ISBN" << "BORROWER NAME\n";
    cout << string(75, '-') << "\n";

    bool found = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (!books[i]->getAvailability()) { // If Issued
            cout << left << setw(30) << books[i]->getTitle().substr(0, 29)
                 << setw(20) << books[i]->getISBN()
                 << books[i]->getHolder() << "\n";
            found = true;
        }
    }
    if (!found) cout << "No books are currently issued.\n";
}

//void Library::toggleMemberStatus(string userId) {
 //   User* u = findUser(userId);
 //   if (u) {
 //       u->setStatus(!u->getStatus());
 //       cout << "Status updated to: " << (u->getStatus() ? "Active" : "Inactive") << "\n";
  //  } else {
 //       cout << "Member not found.\n";
//    }
//}  
	