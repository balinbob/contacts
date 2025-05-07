#include "classdef.h"
#include "manager.h"
#include <regex>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <optional>
#include <algorithm>

bool Manager::addContact() {
    std::string name = "";
    std::string phone = "";
    std::string email = "";
    std::string birthdate = "";
    
    std::cout << "Enter a contact, or press Enter to exit.\n";
    std::cout << "Name           : ";
    std::getline(std::cin, name);

    name = this->trim(name);
    if (name == "") return false; // Exit if name is empty
   
    do {
        std::cout << "Phone Number (123-456-7890): ";
        std::getline(std::cin, phone);
    } while (!Manager::isValidPhone(phone));
    std::cout << "Email Address  : ";
    std::getline(std::cin, email);
    do {
        std::cout << "Birthdate (YYYY-MM-DD): ";
        std::getline(std::cin, birthdate);
    } while (!Manager::isValidDate(birthdate));
    
    
    std::optional<BirthDate> newBirthDate = BirthDate::fromString(birthdate);
    
    if (newBirthDate.has_value()) {
        Contact newContact(name, phone, email, newBirthDate.value());
        this->allContacts.push_back(newContact); // Add to allContacts
        this->saveNewContact("mycontacts.txt", newContact);
    } else {
        std::cerr << "Invalid birthdate, Contact not added\n";
        return false;
    }
    return true;
}

void Manager::enterContacts() {
    int howMany = 0;
    while (this->addContact()) {
        howMany++;
    }
    std::cout << "You entered " << howMany << " contacts\n";
}

void Manager::searchContacts() {
    std::string query;
    bool found = false;
    std::cout << "Search name: ";
    std::getline(std::cin, query);

    std::cout << "Searching for contacts...\n";
    for (Contact& contact : this->allContacts) {
        if (this->fuzzyMatch(query, contact.getName())) {
            std::cout << "Found contact:\n";
            std::cout << "ID: " << std::setw(3) << std::setfill('0') << contact.getId() << "\n";   
            contact.print();
            found = true;
        }
    }
    if (!found) {
        std::cout << "Contact not found\n";
    }
}

std::vector<Contact>::iterator Manager::searchContactById(int id) {
    if (id == 0) {
        while (true) {
            std::cout << "Search ID: ";
            std::cin >> id;

            if (std::cin.fail()) {
                std::cin.clear(); // Clear failbit
                std::cin.ignore(10000, '\n'); // Discard invalid input
                std::cout << "Invalid input! Please enter a number.\n";
                continue;
            }
            std::cin.ignore(10000, '\n');
            break;
        }
    }

    for (auto it = this->allContacts.begin(); it != this->allContacts.end(); ++it) {
        if (it->getId() == id) {
            it->print();
            return it;
        }
    }
    std::cout << "ID not found..\n";
    return this->allContacts.end();
}

void Manager::deleteContactById() {
    char response;
    std::vector<Contact>::iterator it = searchContactById();
    if (it == this->allContacts.end()) { return; }
    std::cout << "Really delete contact? (y/n) ";
    std::cin >> response;
    if (response != 'y' && response != 'Y') {
        std::cout << "cancelled..\n";
        return;
    }
    this->allContacts.erase(it);
    saveAllContacts("mycontacts.txt");
    std::cout << "Contact deleted\n";
}

void Manager::saveAllContacts(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing\n";
        return;
    }
    for (const Contact& contact : this->allContacts) {
        outfile << contact.getName() << "\n";
        outfile << contact.getPhone() << "\n";
        outfile << contact.getEmail() << "\n";
        outfile << contact.getBirthDate().toString() << "\n";
        outfile << "--------------------------\n";
    }
    outfile.close();
    std::cout << "All contacts written to file\n";
}


void Manager::saveNewContact(const std::string& filename, const Contact& newContact) {
    std::ofstream outfile(filename, std::ios::app); // Open in append mode
    if (!outfile.is_open()) {
        std::cerr << "Failed to open " << filename << " for writing\n";
        return;
    }
    outfile << newContact.getName() << "\n";
    outfile << newContact.getPhone() << "\n";
    outfile << newContact.getEmail() << "\n";
    outfile << newContact.getBirthDate().toString() << "\n";
    outfile << "--------------------------\n";
    outfile.close();
    std::cout << "Contact saved to " << filename <<  " successfully!\n";
}

void Manager::loadAllContacts(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cout << "Failed to open " << filename << " for reading.\n";
        return;
    } else { 
        std::cout << "Loading contacts from " << filename << "\n";
        std::string name = "";
        std::string phone = "";
        std::string email = "";
        std::string birthdate = "";
        std::string delimiter = "";
        this->allContacts.clear(); // Clear existing contacts before loading
        while (std::getline(infile, name) && std::getline(infile, phone) && std::getline(infile, email) && std::getline(infile, birthdate)) {
            Contact contact(name, phone, email, BirthDate::fromString(birthdate).value());
            std::getline(infile, delimiter);
            this->allContacts.push_back(contact);
        }
        infile.close();
        std::cout << "Contacts loaded successfully: " << this->allContacts.size() << "\n";
    }
}

void Manager::printContacts() const {
    for (const Contact& contact : this->allContacts) {
        contact.print();
    }
}

bool Manager::isValidPhone(const std::string& phone) {
    std::regex pattern("^[0-9]{3}-[0-9]{3}-[0-9]{4}$");
    return std::regex_match(phone, pattern); 
}    
bool Manager::isValidDate(const std::string& date) {
    std::regex pattern("^[0-9]{4}-[0-9]{2}-[0-9]{2}$");
    return std::regex_match(date, pattern);
}
std::string Manager::trim(std::string str) {
    str.erase(0, str.find_first_not_of(" \t\r\n")); // remove leading spaces
    str.erase(str.find_last_not_of(" \t\r\n") + 1); // remove trailing spaces
    return str;
}
std::string Manager::toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
        [](unsigned char c) {return std::tolower(c);});
    return str;
}
bool Manager::fuzzyMatch(const std::string& query, const std::string& target) {
    std::string cleanedQuery = Manager::toLower(Manager::trim(query));
    std::string cleanedTarget = Manager::toLower(Manager::trim(target));
    return cleanedTarget.find(cleanedQuery) != std::string::npos;
}