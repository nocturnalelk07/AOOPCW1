// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// A Category contains one or more Expense Items, each with
// their own identifier ('ident').
// -----------------------------------------------------

#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
#include <sstream>

#include "item.h"
#include "date.h"

static const std::string runtimeError = "category error at runtime";

class Category {
public:
    Category(std::string ident);
    unsigned int size();
    std::string getIdent();
    void setIdent(std::string ident);
    Item newItem(std::string itemIdent, std::string desc, double amount, Date date);
    bool addItem(Item& item);
    Item getItem(std::string ident);
    double getSum();
    bool deleteItem(std::string ident);
    std::string str();

    friend bool operator== (const Category &lhs, const Category &rhs);

private:
    std::vector<Item> items;
    std::string identifier;

    void to_json(json& j);
    std::string itemString();
};


#endif // CATEGORY_H
