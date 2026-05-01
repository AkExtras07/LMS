#ifndef LIBRARY_H
#define LIBRARY_H

#include "database.h"

class Library {
public:
    Library();
    ~Library();

    void viewAllMembers(Database& db);
    void viewIssuedBooksReport(Database& db);
};

#endif