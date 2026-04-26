#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    std::string name;
    std::string userId;
    bool isActive;

public:
    User(std::string n, std::string id); 
    virtual ~User();
    
    bool getStatus() const { return isActive; } // Add this
    void setStatus(bool status) { isActive = status; }

    std::string getName() const;
    std::string getUserId() const;

    virtual void displayMenu() = 0; 
    virtual std::string serialize() const = 0; 
};

#endif
