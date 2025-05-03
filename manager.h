#ifndef MANAGER_H
#define MANAGER_H


#include "classdef.h"
#include <vector>
#include <string>


class Manager{
private:
    std::vector<Contact> contacts;
    std::vector<Contact> newContact;
    std::vector<Contact> storedContacts;
    std::vector<Contact> allContacts;


public:
    // Manager();

    void addContact();
//    void searchContacts(const Contact& query);
    void printContacts() const;
    //    std::tuple<int, int, int> parseBirthdate(const std::string& birthdate) const;
    void saveNewContact(const std::string& filename, const Contact& newContact);
    void loadAllContacts(const std::string& filename);
    bool isValidPhone(const std::string& phone);
    bool isValidDate(const std::string& date);
};


#endif