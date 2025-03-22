// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
// An Item class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). An Item also has a description (e.g. 'Costa
// Coffee'), a double amount (e.g. 2.55), and date associated with it. 
// -----------------------------------------------------

#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <sstream>

#include "date.h"
#include "lib_json.hpp"

using json = nlohmann::json;

static const std::string tagNotFoundError = "Error: tag was not found";
class Item {
public:
    Item(std::string identifier, std::string description, double amount, Date date);
    std::string getIdent() const;
    std::string getDescription() const;
    void setDescription(const std::string description);
    bool addTag(const std::string tag);
    bool deleteTag( std::string tag);
    unsigned int numTags() const;
    bool containsTag(const std::string tag) const;
    double getAmount() const;
    void setAmount(const float amount);
    Date getDate() const;
    void setDate(const Date date);
    std::string str() const;
    
    std::string getTag(int index);

    friend bool operator== (const Item &lhs, const Item &rhs);

//(Private is default but helps for clarity to state it)
private:
    std::string identifier;
    std::string description;
    double amount;
    Date date;
    std::vector<std::string> tags;
    
    json to_json() const;
    std::string tagString() const;
};
#endif // ITEM_H
