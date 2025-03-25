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

static const std::string categoryRuntimeError = "category error at runtime";
static const std::string categoryOOR = "category out of range error";
static const std::string itemsStr = "items";

class Category {
public:
    Category(const std::string &ident);
    unsigned int size() const;
    std::string getIdent() const;
    void setIdent(const std::string &ident);
    Item newItem(const std::string &itemIdent, const std::string &desc, const double &amount, const Date &date);
    bool addItem(const Item &item);
    Item getItem(const std::string &ident) const;
    std::vector<Item> getItems() const;
    double getSum() const;
    bool deleteItem(const std::string &ident);
    std::string str();
    void to_json(json& j, Category& c);
    void from_json(const json& j, Category& c);

    friend bool operator== (const Category &lhs, const Category &rhs);

private:
    std::vector<Item> items;
    std::string identifier;
    
    std::string itemString() const;
};


#endif // CATEGORY_H
