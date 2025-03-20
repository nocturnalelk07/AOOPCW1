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
#include "date.h"

class Item {
public:
    Item(std::string identifier, std::string description, double amount, Date date);
    std::string getIdent();
    std::string getDescription();
    void setDescription(std::string description);
    bool addTag(std::string tag);
    bool deleteTag(std::string tag);
    unsigned int numTags();
    bool containsTag(std::string tag);
    double getAmount();
    void setAmount(float amount);
    Date getDate();
    void setDate(Date date);
    std::string str();

    friend bool operator== (const Item &lhs, const Item &rhs);

//(Private is default but helps for clarity to state it)
private:
    std::string identifier;
    std::string description;
    double amount;
    Date date;
    std::vector<std::string> tags;
    const std::string tagNotFoundError = "Error: tag was not found";

};
#endif // ITEM_H
