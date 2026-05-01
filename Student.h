#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Book.h"
#include <vector>
#include <string>

using namespace std;

class Database;

class Student : public User {
private:
    int booksIssuedCount;

public:
    Student(std::string n, std::string id);
    virtual ~Student();

    virtual void displayMenu();
    virtual std::string serialize() const;

void issueBook(Database& db, const string& isbn);
void returnBook(Database& db, const string& isbn);
   // void issueBook(const std::string& isbn, std::vector<Book*>& books);
   // void returnBook(const std::string& isbn, std::vector<Book*>& books);
    int getBooksIssuedCount() const;
    void setBooksIssuedCount(int count);
};

#endif
