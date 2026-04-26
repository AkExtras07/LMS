#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>

class Book; 
class User;

class Library {
private:
    std::vector<Book*> books;
    std::vector<User*> members;

public:
    Library();
    ~Library();

    void addBook(Book* b);
    void removeBookByISBN(std::string isbn);
    void addMember(User* u);
    void searchBook(std::string query);
    void viewAllBooks();
    void viewAllMembers();
    void removeMember(std::string userId);
    void toggleMemberStatus(std::string userId);
    
    User* findUser(const std::string& userId);
    std::vector<Book*>& getBooks();

    void saveToFile();
    void loadFromFile();
    void printBookHeader();
};

#endif
