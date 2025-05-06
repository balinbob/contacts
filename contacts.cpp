#include "classdef.h"
#include "manager.h"

int main() {
    Contact myContact("Bob Allred", "910-895-8888", "balinbob@gmail.com", BirthDate(1961, 01, 18));
    Manager myManager;
    myContact.print();
    
    myManager.loadAllContacts("mycontacts.txt");

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Enter data\n";
        std::cout << "2. Search by name\n";
        std::cout << "3. Print all\n";
        std::cout << "4. Delete Contact by ID\n";
        std::cout << "5. Load from file\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        
        if (std::cin.fail()) {
            std::cin.clear(); // Clear failbit
            std::cin.ignore(10000, '\n'); // Discard invalid input
            std::cout << "Invalid input! Please enter a number.\n";
            continue; // Skip to next loop iteration
        }
        
        
        std::cin.ignore(10000, '\n'); // Clear leftover newline

        switch (choice) {
            case 1:
                myManager.enterContacts();
                break;
            case 2:
                myManager.searchContacts();
                break;
            case 3:
                myManager.printContacts();
                // myContact.printSorted();
                break;
            case 4:
                myManager.searchContactById();
                break;
            case 5:
                myManager.loadAllContacts("mycontacts.txt");
                break;
            case 6:
                std::cout << "Goodbye!\n";
                return 0;
                break;
            default:
                std::cout << "Invalid choice\n";
                break;
        }
    }
}