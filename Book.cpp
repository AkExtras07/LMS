#include "Book.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

Book::Book(string t, string a, string i, bool avail, string holder) {
    if (t.empty() || a.empty() || i.empty()) {
        isValid = false;
        title = "Unknown";
        author = "Unknown";
        isbn = "0000";
        currentHolder = "None" ;
    } else {
        title = t;
        author = a;
        isbn = i;
        isValid = true;
        currentHolder = holder;
    }
    available = avail;
}

void Book::setStatus(bool status) { 
    available = status; 
}

void Book::displayBookDetails() const{
    cout << left << setw(30) << title.substr(0, 29)
         << setw(25) << author.substr(0, 24)
         << setw(15) << isbn
		 << (available ? "Available" : "Issued") << "\n";
}

bool Book::setTitle(const string& t) {
    if (t.empty()) return false; 
    title = t;
    return true;
}

bool Book::setAuthor(const string& a) {
    if (a.empty()) return false;
    author = a;
    return true;
}

string Book::serialize() const {
    return title + "|" + author + "|" + isbn + "|" + (available ? "1" : "0") + "|" + currentHolder;
}

Book Book::deserialize(const string& data) {
    stringstream ss(data);
    string t, a, i, availStr, holder;
    getline(ss, t, '|');
    getline(ss, a, '|');
    getline(ss, i, '|');
    getline(ss, availStr, '|');
    getline(ss, holder, '|');
    
    if (holder.empty()) holder = "None"; 
	bool isAvail = (availStr == "1");   
	
    return Book(t, a, i, isAvail, holder);
}
