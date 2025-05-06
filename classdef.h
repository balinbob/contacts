#ifndef CLASSDEF_H
#define CLASSDEF_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <optional>

class BirthDate {
private:
    int year;
    int month;
    int day;
    
public:
    BirthDate(int y, int m, int d);
    BirthDate();
    
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    
    void setYear(int y);
    void setMonth(int m);
    void setDay(int d);
    
    std::string toString() const;
    static std::optional<BirthDate> fromString(const std::string& date);
};

class Contact {
private:
    static int nextId;
    const int id;
    std::string name;
    std::string phoneNumber;
    std::string emailAddress;
    BirthDate birthDate;
    
    
    public:
    Contact(const std::string& n, const std::string& p, const std::string& e, const BirthDate& b);
    Contact();
    
    int getId() const;

    std::string getName() const;
    std::string getPhone() const;
    std::string getEmail() const;
    BirthDate getBirthDate() const;

    void setName(const std::string& n);
    void setPhone(const std::string& p);
    void setEmail(const std::string& e);
    void setBirthDate(const BirthDate& b);

    
    void print() const;
};

#endif // CLASSDEF_H