#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool available;
    bool isValid;

public:
    Book(std::string t, std::string a, std::string i, bool avail = true);

    std::string getTitle() const { return title; }
    std::string getAuthor() const { return author; }
    std::string getISBN() const { return isbn; }
    bool getAvailability() const { return available; }
    bool getIsValid() const { return isValid; }

    bool setTitle(const std::string& t);
    bool setAuthor(const std::string& a);
    void setStatus(bool status);

    void displayBookDetails() const;
    std::string serialize() const;
    static Book deserialize(const std::string& data);
};

#endif
