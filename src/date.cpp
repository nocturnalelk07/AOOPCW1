// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "date.h"

// DONE write a default constructor that sets the member variables to today's
// date. 
// Example:
//  Date d = Date();
//default constructor for date
Date::Date() {
    updateCurrentDate();
    day = currentDay;
    month = currentMonth;
    year = currentYear;
}

// DONE write a constructor that takes a three integer argument and sets the
// appropriate member variables (year, month, day). If the date is not valid
// throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");

Date::Date(const unsigned int inputYear, const unsigned int inputMonth, const unsigned int inputDay) {
    
    updateCurrentDate();

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

// DONE write a constructor that takes a string argument in "YYYY-MM-DD" format
// and sets the appropriate member variables (year, month, day). If dateString
// is not valid throw an appropriate exception.
// Example:
//  Date d = Date("2024-12-25");
Date::Date(const std::string date) {

    updateCurrentDate();

    unsigned int tempYear;
    unsigned int tempMonth;
    unsigned int tempDay;

    std::stringstream stringStream(date);
    char delimiter = '-';
    std::string tempS;
    
    getline(stringStream, tempS, delimiter);
    tempYear = stoi(tempS);
    if (validYear(tempYear)) {
        year = tempYear;
    } else {
        throw std::invalid_argument(yearError);
    }
    getline(stringStream, tempS, delimiter);
    tempMonth = stoi(tempS);
    if (validMonth(tempYear, tempMonth)) {
        month = tempMonth;
    } else {
        throw std::invalid_argument(monthError);
    }
    getline(stringStream, tempS, delimiter);
    tempDay = stoi(tempS);
    if (validDay(tempDay, tempMonth, tempYear)) {
        day = tempDay;
    } else {
        throw std::invalid_argument(dayError);
    }
}

//a set of methods that hold the logic for whether or not a day month or year is a valid input for the system so that it isnt repeated
bool Date::validDay(const unsigned int day, const unsigned int month, const unsigned int year) {
    updateCurrentDate();

    //calculate how many days in the given month
    unsigned int maxDays;
    bool valid = true;
    //works out how many days the month has
    switch (month) {
        case 2:
        {
            //for a given year to be a leap year, it must be divisible by 4 but not 100, or it must be divisible by 400.
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0 ) {
                maxDays = 29;
                break;
            } else {
                maxDays = 28;
                break;
            }
        }
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        {
            maxDays = 31;
            break;
        }
        default:
        maxDays = 30;
        break;
    }
    if (!(day <= maxDays)) {
        valid = false;
    }

    if (month == currentMonth && day > currentDay) {
        valid = false;
    }
    return valid;
}

bool Date::validYear(const unsigned int inputYear) {
    updateCurrentDate();
    bool valid = false;
    if(inputYear >= yearAdjust && inputYear <= currentYear) {
        valid = true;
    }
    return valid;
}

bool Date::validMonth(const unsigned int inputYear, const unsigned int inputMonth) {
    updateCurrentDate();
    bool valid = false;
    if ((inputMonth >= minimumDate) && (inputMonth <= maximumMonth) && (inputMonth <= currentMonth || inputYear < currentYear)) {
        valid = true;
    }
    return valid;
}

void Date::updateCurrentDate() {
    //get todays date as a timestamp then turn it into a dateTime struct and get the values
    time_t timestamp = time(&timestamp);

    //gm time may result in some confusion outside this timezone but will make inputs more standardised than localtime worldwide
    struct tm currentTime = *gmtime(&timestamp);


    currentDay = currentTime.tm_mday;

    //months are represented as time since january (0-11) so adding one (1-12) is more human readable.
    currentMonth = currentTime.tm_mon + 1;

    //years are represented as time since 1900 so adding 1900 years gives the current year.
    currentYear = currentTime.tm_year + yearAdjust;
}

// DONE Write a function, str, that takes no parameters and returns a
// std::string representation of the Date object in YYYY-MM-DD format.  
// Example:
//  Date d = Date(2024,12,25);
//  std::cout << d.str() << std::endl;
std::string Date::str() const {
    std::stringstream ss;
    ss << year << "-" << month << "-" << day;
    return(ss.str());
}

// DONE create a function setDate, that takes three parameters: year, month,
// day and sets the appropriate member variables to those parameters.
// Example:
//  Date d = Date();
//  d.setDate(2024, 12, 25);
void Date::setDate(const unsigned int inputYear, const unsigned int inputMonth, const unsigned int inputDay) {
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

// DONE Write a function, getYear, that takes no parameters and returns year
// member variable
// Example:
//  Date d = Date();
//  auto year = d.getYear();
unsigned int Date::getYear() const {
    return year;
}

// DONE Write a function, getMonth, that takes no parameters and returns month
// member variable
// Example:
//  Date d = Date();
//  auto month = d.getMonth();
unsigned int Date::getMonth() const {
    return month;
}

// DONE Write a function, getDay, that takes no parameters and returns day
// member variable
// Example:
//  Date d = Date();
//  auto day = d.getDay();
unsigned int Date::getDay() const {
    return day;
}

// DONE Write an == operator overload for the Date class, such that two
// Date objects are equal only if they have the same member variables.
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date(2024, 12, 25);
//  if (d1 == d2) {
//    ...
//  }
bool operator== (const Date &lhs, const Date &rhs) {
    bool isEqual = false;
    if((lhs.year == rhs.year) && (lhs.month == rhs.month) && (lhs.day == rhs.day)) {
        isEqual = true;
    }
    return isEqual;
}

// DONE Write an < operator overload for the Date class, that returns true if
// the first Date object is chronologically before the second date object.
// Otherwise return false. 
// Example:
//  Date d1 = Date(2024, 12, 25);
//  Date d2 = Date();
//  Date d2 = Date(2024, 12, 31);
//   if (d1 < d2) {
//     ...
//   }
bool operator< (const Date &lhs, const Date &rhs) {
    bool isLessThan = false;
    if(lhs.year == rhs.year) {

        //if the years are equal we need to check the months
        if (lhs.month == rhs.month) {

            //if the months are equal we need to check the days
            if(lhs.day >= rhs.day) {
                //do nothing because date is equal or more than
            } else {
                //if not equal or more than then day is less
                isLessThan = true;
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
