// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// The root object that holds all data for 371expenses. This
// class contains Categories, which in turn hold Expense Items,
// which have a description, amount, and date
// -----------------------------------------------------

#ifndef EXPENSETRACKER_H
#define EXPENSETRACKER_H

#include "category.h"
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <utility>

static const std::string etRuntimeError = "et runtime error";
static const std::string etOOR = "et out of range error";

class ExpenseTracker {
public:
    ExpenseTracker();
    unsigned int size() const;
    Category newCategory(const std::string &categoryIdent);
    bool addCategory(Category &category);
    Category& getCategory(const std::string &categoryIdent);
    bool deleteCategory(std::string &categoryIdent);
    double getSum() const;
    void load(std::string &DbFileName) const;
    void save(std::string &filePath) const;
    std::string str() const;
    json to_json() const;
    std::string categoryString() const;

    friend bool operator==(const ExpenseTracker &lhs, const ExpenseTracker &rhs);

private:
    std::vector<Category> categories;

};

#endif // EXPENSETRACKER_H
