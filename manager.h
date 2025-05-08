#ifndef MANAGER_H
#define MANAGER_H


#include "classdef.h"
#include <vector>
#include <string>


class Manager{
private:
    //std::vector<Contact> contacts;
    //std::vector<Contact> newContact;
    //std::vector<Contact> tempContacts;
    //std::vector<Contact> storedContacts;
    std::vector<Contact> allContacts;


public:
    // Manager();

    bool addContact();
    void enterContacts();
    void searchContacts();
    std::vector<Contact>::iterator searchContactById(int id = 0);
    void deleteContactById();
    void printContacts() const;
    void saveNewContact(const std::string& filename, const Contact& newContact);
    void saveAllContacts(const std::string& filename);
    void loadAllContacts(const std::string& filename);
    static bool isValidPhone(const std::string& phone);
    static bool isValidDate(const std::string& date);
    static std::string trim(std::string str);
    static std::string toLower(std::string str);
    bool fuzzyMatch(const std::string& query, const std::string& target);
    void printSortedList() const;
};


#endif