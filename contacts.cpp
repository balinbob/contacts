#include "classdef.h"
#include "manager.h"

int main() {
    Contact myContact("Bob Allred", "910-895-8888", "balinbob@gmail.com", BirthDate(1961, 01, 18));
    Manager myManager;
    myContact.print();
    

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Enter data\n";
        std::cout << "2. Search by name\n";
        std::cout << "3. Print\n";
        std::cout << "4, Load from file\n";
        std::cout << "5. Save to file\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        int choice = 0;
        std::cin >> choice;
        std::cin.ignore(10000, '\n'); // Clear leftover newline

        switch (choice) {
            case 1:
                myManager.addContact();
                break;
            case 2:
                // myContact.searchByName();
                break;
            case 3:
                myManager.printContacts();
                // myContact.printSorted();
                break;
            case 4:
                myManager.loadAllContacts("mycontacts.txt");
                break;
            case 5:
                myManager.saveNewContacts("mycontacts.txt");
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