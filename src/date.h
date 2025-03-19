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
    Date(std::string date);
    Date(int inputYear, int inputMonth, int inputDay);
    std::string str();
    void setDate(int year, int month, int day);
    int getYear();
    int getMonth();
    int getDay();


    friend bool operator== (const Date &lhs, const Date &rhs);
    friend bool operator< (const Date &lhs, const Date &rhs);

private:
    int year;
    int month;
    int day;
    int currentYear;
    int currentDay;
    int currentMonth;
    const int minimumDate = 1;
    const int yearAdjust = 1900;
    const std::string yearError = "please make sure the year is valid";
    const std::string monthError = "please make sure the month is valid";
    const std::string dayError = "please make sure the month is valid";
    const std::string inputError = "please input a valid date";

    bool validDay(int day, int month, int year);
    bool validYear(int inputYear);
    bool validMonth(int inputYear, int inputMonth);
};

#endif // DATE_H
