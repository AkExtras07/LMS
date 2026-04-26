#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "Book.h"
#include <vector>

class Library;

class Librarian : public User {
private:
    std::string employeeId;

public:
    Librarian(std::string n, std::string id, std::string empId);
    virtual void displayMenu();
    virtual std::string serialize() const;
    
    // Inside class Librarian
void removeBook(Library& lib, std::string isbn);
    
    void addBook(std::vector<Book*>& books, std::string t, std::string a, std::string i);
    
    
};

#endif
