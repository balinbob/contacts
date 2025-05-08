#include "classdef.h"
#include "manager.h"


void printMenu() {
    std::cout << "Menu:\n";
    std::cout << "1. Enter contacts\n";
    std::cout << "2. Search by name\n";
    std::cout << "3. Print all contacts\n";
    std::cout << "4. Delete contact by id\n";
    std::cout << "5. Load from file\n";
    std::cout << "6. Exit\n";
    std::cout << "Enter your choice: ";
    return;
}
int getIntInput() {
    int input = 0;
    std::string inp = "";
    while (input == 0) {
        printMenu();
        std::getline(std::cin, inp);
        if (inp.empty()) { continue; }
    
        try {
            input = std::stoi(inp);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Not a number: " << e.what() << "\n";
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Number out of range: " << e.what() << "\n";
            continue;
        }

    }
    return input;
}



int main() {
    Manager myManager;
    myManager.loadAllContacts("mycontacts.txt");

    while (true) {
        
        int choice = getIntInput();

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
                myManager.deleteContactById();
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
