#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "Book.h"
#include "Database.h"   // 🔥 force full definition
#include <string>
#include <vector>

class Library;
class Database;

class Librarian : public User {
private:
    std::string employeeId;

public:
    Librarian(std::string n, std::string id, std::string empId);
    virtual void displayMenu();
    virtual std::string serialize() const;
    
    // Inside class Librarian
//void removeBook(Library& lib, std::string isbn);

//void addBook(std::vector<Book*>& books, std::string t, std::string a, std::string i);
    
//void manageMember(Library& lib);    
    void addBook(Database& db, std::string t, std::string a, std::string i);
void removeBook(Database& db, std::string isbn);
void manageMember(Database& db);
    
};

#endif
