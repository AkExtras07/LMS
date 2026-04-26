#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // For system("cls") or system("clear")

#include "Library.h"
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Librarian.h"

using namespace std;

// Helper function to clear the console screen
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showWelcome() {
    cout << "========================================\n";
    cout << "   LIBRARY MANAGEMENT SYSTEM (v1.0)     \n";
    cout << "========================================\n";
}

int main() {
    Library myLibrary;
    
    // Seed some initial data if files are empty
    if (myLibrary.findUser("L001") == NULL) {
        myLibrary.addMember(new Librarian("Admin", "L001", "EMP101"));
        myLibrary.addMember(new Student("John Doe", "S001"));
        myLibrary.addBook(new Book("The C++ Programming Language", "Bjarne Stroustrup", "12345"));
        myLibrary.addBook(new Book("Clean Code", "Robert C. Martin", "67890"));
    }

    bool running = true;
    while (running) {
        clearScreen();
        showWelcome();
        
        string userId;
        cout << "Enter User ID to Login (or 'exit' to quit): ";
        cin >> userId;

        if (userId == "exit") {
            running = false;
            break;
        }

        User* currentUser = myLibrary.findUser(userId);

        if (currentUser == NULL) {
            cout << "User not found! Press Enter to try again...";
            cin.ignore();
            cin.get();
            continue;
        }

        bool loggedIn = true;
        while (loggedIn) {
            clearScreen();
            cout << "Logged in as: " << currentUser->getName() << "\n";
            currentUser->displayMenu();
            
            int choice;
            cout << "Enter choice: ";
            cin >> choice;

            try {
                // Determine if user is Librarian or Student to handle specific actions
                Librarian* libPtr = dynamic_cast<Librarian*>(currentUser);
                Student* stuPtr = dynamic_cast<Student*>(currentUser);

                if (libPtr != NULL) { // Librarian Logic
                    switch (choice) {
                        case 1: {
                            string t, a, i;
                            cout << "Enter Title: "; cin.ignore(); getline(cin, t);
                            cout << "Enter Author: "; getline(cin, a);
                            cout << "Enter ISBN: "; getline(cin, i);
                            libPtr->addBook(myLibrary.getBooks(), t, a, i);
                            break;
                        }
                        case 2:
                            myLibrary.viewAllMembers();
                            break;
                        case 3:
                            myLibrary.saveToFile();
                            cout << "Data saved successfully.\n";
                            break;
                        case 4: {
                            string isbn;
                            cout << "Enter ISBN of the book to remove: ";
                            cin >> isbn;
                            libPtr->removeBook(myLibrary, isbn);
                            break;
                               }
                        case 5: // Changed logout to case 5
                           loggedIn = false;
                           break;
                           default:
                           cout << "Invalid choice.\n";
                                  }
                             } 
                else if (stuPtr != NULL) { // Student Logic
                    switch (choice) {
                        case 1: {
                            string q;
                            cout << "Enter search query: "; cin.ignore(); getline(cin, q);
                            myLibrary.searchBook(q);
                            break;
                        }
                        case 2: {
                            string isbn;
                            cout << "Enter ISBN to issue: "; cin >> isbn;
                            stuPtr->issueBook(isbn, myLibrary.getBooks());
                            break;
                        }
                        case 3: {
                            string isbn;
                            cout << "Enter ISBN to return: "; cin >> isbn;
                            stuPtr->returnBook(isbn, myLibrary.getBooks());
                            break;
                        }
                        case 4:
                            myLibrary.viewAllBooks();
                            break;
                        case 5:
                            loggedIn = false;
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                }
            } catch (const exception& e) {
                cout << "ERROR: " << e.what() << "\n";
            }

            if (loggedIn) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
        }
    }

    cout << "Exiting system. Goodbye!\n";
    return 0;
}

