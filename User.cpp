#include "User.h"

User::User(std::string n, std::string id) : name(n), userId(id), isActive(true) {} // Updated}

std::string User::getName() const { return name; }
std::string User::getUserId() const { return userId; }

User::~User() {}
