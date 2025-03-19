// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "date.h"
#include <ctime>
#include <string>
#include <iostream>
#include <sstream>


// TESTING write a default constructor that sets the member variables to today's
// date. 
// Example:
//  Date d = Date();
//default constructor for date
date::date() {
    //get todays date as a timestamp then turn it into a dateTime struct and get the values
    time_t timestamp = time(&timestamp);
    //gm time may result in some confusion outside this timezone but will make inputs more standardised than localtime worldwide
    struct tm currentTime = *gmtime(&timestamp);

    currentDay = currentTime.tm_mday;
    day = currentDay;
    //months are represented as time since january (0-11) so adding one (1-12) is more human readable.
    currentMonth = currentTime.tm_mon + 1;
    month = currentMonth;
    //years are represented as time since 1900 so adding 1900 years gives the current year.
    currentYear = currentTime.tm_year + yearAdjust;
    year = currentYear;
}

// TESTING write a constructor that takes a three integer argument and sets the
// appropriate member variables (year, month, day). If the date is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");

date::date(int inputYear, int inputMonth, int inputDay) {
    
    time_t timestamp = time(&timestamp);
    struct tm currentTime = *gmtime(&timestamp);

    currentDay = currentTime.tm_mday;
    currentMonth = currentTime.tm_mon + 1;
    currentYear = currentTime.tm_year + yearAdjust;

    //verify and set the year month and day
    if (validYear(inputYear)) {
        year = inputYear;
    } else {
        throw std::invalid_argument(yearError);
    }
    if (validMonth(inputYear, inputMonth)) {
        month = inputMonth;
    } else {
        throw std::invalid_argument(monthError);
    }
    if (validDay(inputDay, inputMonth, inputYear)) {
        day = inputDay;
    } else {
        throw std::invalid_argument(dayError);
    }
}

// TESTING write a constructor that takes a string argument in "YYYY-MM-DD" format
// and sets the appropriate member variables (year, month, day). If dateString
// is not valid throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");
date::date(std::string date) {

    time_t timestamp = time(&timestamp);
    struct tm currentTime = *gmtime(&timestamp);

    currentDay = currentTime.tm_mday;
    currentMonth = currentTime.tm_mon + 1;
    currentYear = currentTime.tm_year + yearAdjust;

    year = NULL;
    month = NULL;
    day = NULL;
    std::stringstream stringStream(date);
    char delimiter = '-';
    std::string tempS;
    int tempI;

    while(getline(stringStream, tempS, delimiter)) {
        tempI = stoi(tempS);
        //the year has to be more than or equal to the minimum year (1900) and no more than the current year
        if (year == NULL && (validYear(tempI))) {
            year = tempI;
        //the minimum date is 1 as defined in the header file, this is relevant for months and days
        } else if (month == NULL && validMonth(year, tempI)) {
            month = tempI;
        } else if (day == NULL && validDay(tempI, month, year)) {
            day = tempI;
        } else {
            throw std::invalid_argument(inputError);
        }
    }
}

//a set of methods that hold the logic for whether or not a day month or year is a valid input for the system so that it isnt repeated
bool date::validDay(int day, int month, int year) {
    //calculate how many days in the given month
    int maxDays;
    bool valid = true;
    //works out how many days the month has
    switch (month) {
        case 2:
        {
            //for a given year to be a leap year, it must be divisible by 4 but not 100, or it must be divisible by 400.
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ) {
                maxDays = 29;
            } else {
                maxDays = 28;
            }
        }
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        {
            maxDays = 31;
        }
        default:
        maxDays = 30;
    }
    if (!(day <= maxDays)) {
        valid = false;
    }

    if (month == currentMonth && day > currentDay) {
        valid == false;
    }
    return valid;
}

bool date::validYear(int inputYear) {
    bool valid = false;
    if(inputYear >= yearAdjust && inputYear <= currentYear) {
        valid = true;
    }
    return valid;
}

bool date::validMonth(int inputYear, int inputMonth) {
    bool valid = false;
    if (inputMonth >= minimumDate && (inputMonth <= currentMonth || inputYear < currentYear)) {
        valid = true;
    }
    return valid;
}

// TESTING Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  
// Example:
//  Date d = Date(2024,12,25);
//  std::cout << d.str() << std::endl;
std::string date::str() {
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    return(ss.str());
}

// TODO create a function setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters.
// Example:
//  Date d = Date();
//  d.setDate(2024, 12, 25);
void date::setDate(int inputYear, int inputMonth, int inputDay) {
    if (!validYear(year)) {
        throw std::invalid_argument(yearError);
    } else if (!validMonth(year, month)) {
        throw std::invalid_argument(monthError);
    } else if (!validDay(day, month, year)) {
        throw std::invalid_argument(dayError);
    } else {
        year = inputYear;
        month = inputMonth;
        day = inputDay;
    }
}

// TESTING Write a function, getYear, that takes no parameters and returns year
// member variable
// Example:
//  Date d = Date();
//  auto year = d.getYear();
int date::getYear() {
    return year;
}

// TESTING Write a function, getMonth, that takes no parameters and returns month
// member variable
// Example:
//  Date d = Date();
//  auto month = d.getMonth();
int date::getMonth() {
    return month;
}

// TESTING Write a function, getDay, that takes no parameters and returns day
// member variable
// Example:
//  Date d = Date();
//  auto day = d.getDay();
int date::getDay() {
    return day;
}

// TESTING Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date(2024, 12, 25);
//  if (d1 == d2) {
//    ...
//  }
bool operator== (const date &lhs, const date &rhs) {
    bool isEqual = false;
    if((lhs.year == rhs.year) && (lhs.month == rhs.month) && (lhs.day == rhs.day)) {
        isEqual = true;
    }
    return isEqual;
}

// TESTING Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. 
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date();
//  Date d2 = Date(2024, 12, 31);
//   if (d1 < d2) {
//     ...
//   }
bool operator< (const date &lhs, const date &rhs) {
    bool isLessThan = false;

    if(lhs.year == rhs.year) {

        //if the years are equal we need to check the months
        if (lhs.month == rhs.month) {

            //if the months are equal we need to check the days
            if(lhs.day >= rhs.day) {
                //do nothing because date is equal or more than
            }

        //if the months aren't equal, check if lhs is less    
        } else if (lhs.month < rhs.month) {
            isLessThan = true;
        } // else do nothing

    //if the years aren't equal check if lhs is less    
    } else if (lhs.year < rhs.year) {
        isLessThan = true;
    } // else do nothing

    return isLessThan;
}
