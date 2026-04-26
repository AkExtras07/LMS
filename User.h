#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;
    std::string userId;

public:
    User(std::string n, std::string id); 
    virtual ~User();

    std::string getName() const;
    std::string getUserId() const;

    virtual void displayMenu() = 0; 
    virtual std::string serialize() const = 0; 
};

#endif
