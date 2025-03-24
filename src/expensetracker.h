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
static const std::string categoriesStr = "categories";

class ExpenseTracker {
public:
    ExpenseTracker();
    unsigned int size() const;
    Category newCategory(const std::string &categoryIdent);
    bool addCategory(const Category &category);
    Category& getCategory(const std::string &categoryIdent);
    bool deleteCategory(const std::string &categoryIdent);
    double getSum() const;
    void load(const std::string &DbFileName);
    void save(const std::string &filePath);
    std::string str();
    std::string categoryString();
    void to_json(json& j, ExpenseTracker& et);

    friend bool operator==(const ExpenseTracker &lhs, const ExpenseTracker &rhs);

private:
    std::vector<Category> categories;
    

};

#endif // EXPENSETRACKER_H
