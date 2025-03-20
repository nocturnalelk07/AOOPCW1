// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Date class that contains the following member variables
// - year
// - month
// - day
// -----------------------------------------------------

#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
public:
    Date();
    Date(const std::string date);
    Date(const unsigned int inputYear, const unsigned int inputMonth, const unsigned int inputDay);
    std::string str() const;
    void setDate(const unsigned int year, const unsigned int month, const unsigned int day);
    unsigned int getYear() const;
    unsigned int getMonth() const;
    unsigned int getDay() const;


    friend bool operator== (const Date &lhs, const Date &rhs);
    friend bool operator< (const Date &lhs, const Date &rhs);

private:
    unsigned int year;
    unsigned int month;
    unsigned int day;
    unsigned int currentYear;
    unsigned int currentDay;
    unsigned int currentMonth;
    const unsigned int minimumDate = 1;
    const unsigned int yearAdjust = 1900;
    const unsigned int maximumMonth = 12;
    const std::string yearError = "please make sure the year is valid";
    const std::string monthError = "please make sure the month is valid";
    const std::string dayError = "please make sure the month is valid";
    const std::string inputError = "please input a valid date";

    bool validDay(const unsigned int day, const unsigned int month, const unsigned int year);
    bool validYear(const unsigned int inputYear);
    bool validMonth( const unsigned int inputYear, const unsigned int inputMonth);
    void updateCurrentDate();
};

#endif // DATE_H
