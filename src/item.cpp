// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "item.h"

// DONE Write a constructor that takes four parameters, a string identifier,
// a description, an amount, and a date and initialises the object and member data.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
Item::Item(const std::string& inputIdentifier, const std::string& inputDescription, const double& inputAmount, const Date& inputDate) {
    //std::cout << "in item constructor \n";
    identifier = inputIdentifier;
    description = inputDescription;
    amount = inputAmount;
    date = inputDate;
}

Item::Item(const std::string& inputIdentifier, const std::string& inputDescription, const double& inputAmount, const Date& inputDate,
     const std::vector<std::string>& inputTags) {
    //std::cout << "in item constructor \n";
    identifier = inputIdentifier;
    description = inputDescription;
    amount = inputAmount;
    date = inputDate;
    tags = inputTags;
}

// DONE Write a function, getIdent, that returns the identifier for the Item.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.getIdent();
std::string Item::getIdent() const {
    //std::cout << "calling item get ident\n";
    return identifier;
}

// DONE Write a function, getDescription, that returns the description for the Item.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.getDescription();
std::string Item::getDescription() const {
    //std::cout << "calling item get description\n";
    return description;
}

// DONE Write a function, setDescription, that takes one parameter, a string for a new
//  Item description, and updates the member variable. It returns nothing.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  auto ident = iObj.setDescription("New Item Description");
void Item::setDescription(const std::string &inputDescription) {
    //std::cout << "calling item set description\n";
    description = inputDescription;
}

// DONE Write a function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.addTag("tag");
bool Item::addTag(const std::string &inputTag) {
    //std::cout << "calling item add tag\n";

    for (int i = 0; i < (int) tags.size(); i++) {
        if (tags[i] == inputTag) {
            //find the tag so return
            return false;
        }
    }

    tags.push_back(inputTag);
    return true;
}

// DONE Write a function, deleteTag, that takes one parameter, a tag
// string, deletes it from the container, and returns true if the tag
// string was deleted. If no tag exists with that name, throw an appropriate
// exception.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.addTag("tag");
//  iObj.deleteTag("tag");
bool Item::deleteTag(const std::string &inputTag) {
    //std::cout << "calling item delete tag\n";

    for (int i = 0; i < (int) tags.size(); i++) {
        if (tags[i] == inputTag) {
            tags.erase(tags.begin() + i);
            return true;
        }
    }
    throw std::out_of_range(tagNotFoundError);
}

// DONE Write a function, numTags, that takes no parameters and returns an
// unsigned int of the number of tags in the Item contains.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.numTags(); // 0
unsigned int Item::numTags() const {
    //std::cout << "calling item num tags\n";
    return tags.size();
}

// DONE Write a function, containsTag, that takes one parameter, a tag string.
// If the tag exists, return true. Otherwise return false.
//
// Example:
//  Item iObj{"1", "Description", 1.99, Date(2024,12,25)};
//  iObj.addTag("tag");
//  iObj.containsTag("tag"); // true
bool Item::containsTag(const std::string &inputTag) const {
    //std::cout << "calling item contains tag\n";

    for (int i = 0; i < (int) tags.size(); i++) {
        if (tags[i] == inputTag) {
            return true;
        }
    }
    return false;
}

// DONE Write a function, getAmount, that returns the amount for the Item.
double Item::getAmount() const {
    //std::cout << "calling item get amount\n";
    return amount;
}

// DONE Write a function setAmount, that takes one parameter, a double for
// a new amount, and updates the member variable. It returns nothing.
void Item::setAmount(const float &inputAmount) {
    //std::cout << "calling item set amount\n";
    amount = inputAmount;
}

// DONE Write a function, getDate, that returns the date for the Item.
Date Item::getDate() const {
    //std::cout << "calling item get date\n";
    return date;
}

// DONE Write a function setDate, that takes one parameter, a date, and updates
// the member variable. It returns nothing.
void Item::setDate(const Date &inputDate) {
    //std::cout << "calling item set date\n";
    Date date = inputDate;
    date = date;
    //std::cout << date.str();
}

// DONE Write an == operator overload for the Item class, such that two
// Item objects are equal only if they have the same identifier, date,
// amount, description, and tags.
// Example:
//  Item iObj1{"Item Name"};
//  Item iObj2{"Item Name"};
//  if(iObj1 == iObj2) {
//   ...
//  }
bool operator== (const Item &lhs, const Item &rhs) {
    //std::cout << "calling item ==\n";
    bool isEqual = false;
    if((lhs.identifier == rhs.identifier)
         && (lhs.description == rhs.description)
         && (lhs.amount == rhs.amount)
         && (lhs.date == rhs.date)
         && (lhs.tags == rhs.tags)) {
            isEqual = true;
    }

    return isEqual;
}

// DONE Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Item.
// See the coursework specification for how this JSON should look.
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
std::string Item::str() {
    //std::cout << "calling item str\n";
    json j;
    to_json(j, *this);
    //std::cout << "returning item str: \n" << j.dump(2) << std::endl;
    
    return j.dump();
}

void Item::to_json(json& j, const Item& item) {
    //j[identifier][descriptionStr] = description;
    //j[identifier][descriptionStr][amountStr] = description;
    //this looks most correct so far
    //j[identifier] = { {descriptionStr, description}, {amountStr, amount} };

    //j[identifier] = { {amountStr, amount}, {dateStr, date.str()}, {descriptionStr, description}, {tagsStr, tags} };
    double jAmount = amount;
    jAmount = std::round(jAmount * 100) / 100;
    j = { {amountStr, jAmount}, {dateStr, date.str()}, {descriptionStr, description}, {tagsStr, tags} };
}

void Item::from_json(const json& j, Item& item) {
    j.at(identifierStr).get_to(item.identifier);
    j.at(descriptionStr).get_to(item.description);
    j.at(amountStr).get_to(item.amount);
    j.at(dateStr).get_to(date);
}

std::string Item::getTag(int index) const {
    //std::cout << "calling item get tag\n";
    return tags[index];
}
