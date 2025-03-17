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

class date {
public:
    date();
    date(std::string date);
    date(int inputYear, int inputMonth, int inputDay);

private:
    int year;
    int month;
    int day;
    int currentYear;
    int currentDay;
    int currentMonth;
    const int minimumDate = 1;
    const int yearAdjust = 1900;

    bool validDay(int day, int month, int year);
};

#endif // DATE_H
