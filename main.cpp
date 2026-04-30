#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>

#include "Library.h"
#include "Book.h"
#include "User.h"
#include "Student.h"
#include "Librarian.h"

using namespace std;

// Cleans the input buffer to prevent getline() from skipping
void clearBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void showWelcome() {
    cout << "========================================\n";
    cout << "    LIBRARY MANAGEMENT SYSTEM (v1.0)    \n";
    cout << "========================================\n";
}

int main() {
    // Initializing the library system
    Library myLibrary;
    
    // Seed data: Only adds if the library is currently empty
    if (myLibrary.findUser("Admin", "L001") == nullptr) {
        myLibrary.addMember(new Librarian("Admin", "L001", "EMP101"));
        myLibrary.addMember(new Student("John Doe", "S001"));
        myLibrary.addBook(new Book("The C++ Programming Language", "Bjarne Stroustrup", "12345"));
        myLibrary.addBook(new Book("Clean Code", "Robert C. Martin", "67890"));
    }

    bool running = true;
    while (running) {
        clearScreen();
        showWelcome();
        
        cout << "1. Login\n";
        cout << "2. Exit Program\n";
        cout << "Choice: ";
        
        int startupChoice;
        if (!(cin >> startupChoice)) {
            clearBuffer();
            continue;
        }

        if (startupChoice == 2) {
            running = false;
            break; 
        }
        
        string loginName, loginId;
        cout << "\n--- Login ---\n";
        cout << "Enter Name: ";
        clearBuffer(); 
        getline(cin, loginName);

        cout << "Enter User ID: ";
        cin >> loginId;

        User* currentUser = myLibrary.findUser(loginName, loginId);

        if (currentUser == nullptr) {
            cout << "Invalid Name or ID combination. Press Enter to try again...";
            clearBuffer();
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
            if (!(cin >> choice)) {
                clearBuffer();
                continue;
            }

            try {
                Librarian* libPtr = dynamic_cast<Librarian*>(currentUser);
                Student* stuPtr = dynamic_cast<Student*>(currentUser);

                if (libPtr != nullptr) { // Librarian Menu Logic
                    switch (choice) {
                        case 1: {
                            string t, a, i;
                            clearBuffer();
                            cout << "Enter Title: ";  getline(cin, t);
                            cout << "Enter Author: "; getline(cin, a);
                            cout << "Enter ISBN: ";   getline(cin, i);
                            
                            libPtr->addBook(myLibrary.getBooks(), t, a, i);
                            cout << "\nBook added to system successfully.\n";
                            break;
                        }
                        case 2:
                            myLibrary.viewAllMembers();
                            break;
                        case 3:
                            myLibrary.saveToFile();
                            cout << "Data saved to local storage files.\n";
                            break;
                        case 4: {
                            string isbn;
                            cout << "Enter ISBN of the book to remove: ";
                            cin >> isbn;
                            libPtr->removeBook(myLibrary, isbn);
                            break;
                        }
                        case 5:
                            libPtr->manageMember(myLibrary);
                            break;
                        case 6:
                            myLibrary.viewIssuedBooksReport();
                            break;
                        case 7:
                            loggedIn = false;
                            break;
                        default:
                            cout << "Invalid choice.\n";
                    }
                } 
                else if (stuPtr != nullptr) { // Student Menu Logic
                    switch (choice) {
                        case 1: {
                            string q;
                            clearBuffer();
                            cout << "Enter Book Name/Search Query: "; getline(cin, q);
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
                clearBuffer();
                cin.get();
            }
        }
    }

    // Final save on exit
    myLibrary.saveToFile();
    cout << "Finalizing records... Goodbye!\n";
    return 0;
}