#include "classdef.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <optional>

    BirthDate::BirthDate(int y, int m, int d) : year(y), month(m), day(d) {}
    BirthDate::BirthDate() : year(0), month(0), day(0) {}

    int BirthDate::getYear() const {return year;}
    int BirthDate::getMonth() const {return month;}
    int BirthDate::getDay() const {return day;}

    void BirthDate::setYear(int y) {year = y;}
    void BirthDate::setMonth(int m) {month = m;}
    void BirthDate::setDay(int d) {day = d;}

    std::string BirthDate::toString() const {
        std::ostringstream oss;
        oss << std::setw(4) << std::setfill('0') << year << "-"
            << std::setw(2) << std::setfill('0') << month << "-"
            << std::setw(2) << std::setfill('0') << day;
        return oss.str();
    }

    std::optional<BirthDate> BirthDate::fromString(const std::string& s) {
        std::stringstream ss(s);
        int year = 0;
        int month = 0;
        int day = 0;
        char delimiter;

        if (ss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-') {
            return BirthDate(year, month, day);
        } else {
            return BirthDate();
        }
    }

    int Contact::nextId = 1; // start IDs from 1
    Contact::Contact(const std::string& n, const std::string& p, const std::string& e, const BirthDate& b) :
        id(nextId++), name(n), phoneNumber(p), emailAddress(e), birthDate(b) {}
    Contact::Contact() : id(nextId++), name(""), phoneNumber(""), emailAddress(""), birthDate() {}

    int Contact::getId() const {
        return id;
    }
    
    std::string Contact::getName() const {return name;}
    std::string Contact::getPhone() const {return phoneNumber;}
    std::string Contact::getEmail() const {return emailAddress;}
    BirthDate Contact::getBirthDate() const {return birthDate;}
    
    void Contact::setName(const std::string& n) {name = n;}
    void Contact::setPhone(const std::string& p) {phoneNumber = p;}
    void Contact::setEmail(const std::string& e) {emailAddress = e;}
    void Contact::setBirthDate(const BirthDate& b) {birthDate = b;}

    void Contact::print() const {
        std::cout << "ID: " << std::setw(3) << std::setfill('0') << Contact::getId() << "\n";
        std::cout << name << "\n" << phoneNumber << "\n";
        std::cout << emailAddress << "\n" << birthDate.toString() << "\n";
        std::cout << "--------------------------\n";
    }
