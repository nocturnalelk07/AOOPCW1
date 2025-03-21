// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "category.h"

// DONE Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};
Category::Category(std::string ident) {
    identifier = ident;
}

// DONE Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const {
    return items.size();
}

// DONE Write a function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
std::string Category::getIdent() const {
    return identifier;
}

// DONE Write a function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(std::string ident) {
    identifier = ident;
}

// DONE Write a function, newItem, that takes four parameters, an Item
// identifier (string), description (string), amount (double), and date (Date)
// and returns the Item object as a reference.  If an object with the same
// identifier already exists, then the existing object should be overwritten by
// the new Item. Throw a std::runtime_error if the Item object cannot be
// inserted into the container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
Item Category::newItem(std::string ident, std::string description, double amount, Date date) {
    auto item = Item(ident, description, amount, date);
    for (int i = 0; i < (int) items.size(); i++) {
        if (items[i].getIdent() == ident) {
            items[i] = item;

            return items[i];
        }
    }
    throw std::runtime_error(runtimeError);
}

// DONE Write a function, addItem, that takes one parameter, an Item object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - description should be overwritten by the item being added
//  - amount should be overwritten by the item being added
//  - date overwritten by the item being added
//  - false should be returned.
//
// Example:
//  Category cObj{"categoryIdent"};
//  Item iObj{"itemIdent"};
//  cObj.addItem(iObj);
bool Category::addItem(Item& item) {
    for (int i = 0; i < (int) items.size(); i++) {
        if (item.getIdent() == items[i].getIdent()) {
            //add the tags etc then return false
            for (int j = 0; j < (int) item.numTags(); j++) {
                items[i].addTag(item.getTag(j));
            }
            items[i].setDescription(item.getDescription());
            items[i].setAmount(item.getAmount());
            items[i].setDate(item.getDate());
            return false;
        }
    }
    //insert the object and return true
    items.push_back(item);
    return true;
}

// DONE Write a function, getItem, that takes one parameter, an Item identifier
// (a string) and returns the Item as a reference. If no Item exists, throw an
// appropriate exception.
//
// Hint: See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  auto iObj = cObj.getItem("newItemName");
Item Category::getItem(const std::string identifier) const {
    for (int i = 0; i < (int) items.size(); i++) {
        if (identifier == items[i].getIdent()) {
            return items[i];
        }
    }
    throw std::out_of_range(runtimeError);
}

// DONE Write a function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0
double Category::getSum() {
    double sum = 0;
    for (int i = 0; i < (int) items.size(); i++) {
        sum += items[i].getAmount();
    }
    std::cout << sum;
    return sum;
}

// DONE Write a function, deleteItem, that takes one parameter, an Item
// identifier (a string), deletes the item with that identifier from the
// container, and returns true if the Item was deleted. If no Item exists, throw
// an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");
bool Category::deleteItem(std::string identifier) {
    for (int i = 0; i < (int) items.size(); i++) {
        if (items[i].getIdent() == identifier) {
            items.erase(items.begin() + i);
            return true;
        }
    }
    throw std::out_of_range(runtimeError);
}

// DONE Write an == operator overload for the Category class, such that two
// Category objects are equal only if they have the same identifier and same
// Items.
//
// Example:
//  Category cObj1{"categoryIdent1"};
//  cObj.newItem("newItemName");
//  Category cObj2{"categoryIdent2"};
//  if(cObj1 == cObj2) {
//    ...
//  }
bool operator== (const Category &lhs, const Category &rhs) {
    if ((lhs.identifier == rhs.identifier) && (lhs.items == rhs.items)) {
        return true;
    }
    return false;
}

// DONE Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
std::string Category::str() {
    json j;
    to_json(j);
    
    return j;
}

//converts to json
void Category::to_json(json& j) {
    j = json{{"items", itemString()}};
}

//formats items vector as json
std::string Category::itemString() {
    std::stringstream ss;
    ss << "{";
    for (int i = 0; i < (int) items.size(); i++) {
        ss << items[i].str();
        if (i == (int) items.size()-1)
        {
            ss << "}";
        } else {
            ss << ",";
        }
        
    }
    return ss.str();
}
