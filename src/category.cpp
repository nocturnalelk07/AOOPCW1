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
Category::Category(const std::string &ident) : items() {
    std::cout << "calling category constructor\n";
    identifier = ident;
}

// DONE Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();
unsigned int Category::size() const {
    std::cout << "calling category size\n";
    std::cout << "category item count: " << items.size() << "\n";
    return items.size();
}

// DONE Write a function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();
std::string Category::getIdent() const {
    std::cout << "calling category get identifier\n";
    return identifier;
}

// DONE Write a function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");
void Category::setIdent(const std::string &ident) {
    std::cout << "calling category set identifier\n";
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
Item Category::newItem(const std::string &ident, const std::string &description, const double &amount, const Date &date) {
    std::cout << "calling category new item\n";
    //makes item from params
    const Item item = Item(ident, description, amount, date);

    //if the item is already in the category replace it
    for (int i = 0; i < (int) items.size(); i++) {
        if (items.at(i).getIdent() == ident) {
            items.at(i) = Item(ident, description, amount, date);
            std::cout << "item replaced \n";
            size();
            return items[i];
        }
    }
    try {
        //size correctly increases by 1 as new item is added
        size();
        std::cout << "adding new item \n";
        items.push_back(item);
        std::cout << "new item added, size is now:\n";
        size();
        //next time size is called, it is 0 again
        return item;

    } catch(...) {
    throw std::runtime_error(categoryRuntimeError);
    }
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
bool Category::addItem(const Item &item) {
    std::cout << "calling category add item\n";
    for (int i = 0; i < (int) items.size(); i++) {
        if (item.getIdent() == items.at(i).getIdent()) {
            //add the tags etc then return false
            for (int j = 0; j < (int) item.numTags(); j++) {
                items[i].addTag(item.getTag(j));
            }
            items[i].setDescription(item.getDescription());
            items[i].setAmount(item.getAmount());
            items[i].setDate(item.getDate());
            size();
            return false;
        }
    }
    //insert the object and return true
    items.push_back(item);
    size();
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
Item Category::getItem(const std::string &identifier) const {
    std::cout << "calling category get item\n";
    for (int i = 0; i < (int) items.size(); i++) {
        if (identifier == items[i].getIdent()) {
            size();
            return items[i];
        }
    }
    throw std::out_of_range(categoryOOR);
}

// DONE Write a function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0
double Category::getSum() const {
    std::cout << "calling category get sum\n";
    double sum = 0;
    for (int i = 0; i < (int) items.size(); i++) {
        sum += items[i].getAmount();
    }
    std::cout << "the total sum is: " << sum << "\n";
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
bool Category::deleteItem(const std::string &identifier) {
    std::cout << "calling category delete item\n";
    for (int i = 0; i < (int) items.size(); i++) {
        if (items[i].getIdent() == identifier) {
            items.erase(items.begin() + i);
            return true;
        }
    }
    throw std::out_of_range(categoryOOR);
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
    std::cout << "calling category ==\n";
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
    std::cout << "calling category str\n";
    std::stringstream ss;
    json j;
    to_json(j, *this);
    ss << j;
    std::cout << "returning category str\n";
    return ss.str();
}

//converts to json
void Category::to_json(json& j, Category& c) {
    j = json{{identifierStr, c.identifier}, {itemsStr, c.getItemString()}};
}

//converts the items vector into a string for the to_json
std::string Category::getItemString() {
    std::stringstream ss;
    for (int i = 0; i < (int) items.size(); i++) {
        std::string it = items.at(i).str();
        ss << it;
        if (i == (int) items.size()-1) {
            ss << "}";
        } else {
            ss << ",";
        }
    }
    return ss.str();
}

void Category::from_json(const json& j, Category& c) {
    j.at(identifierStr).get_to(identifier);
    //j.at(itemsStr).get_to(items);
}

std::vector<Item> Category::getItems() const {
    std::cout << "calling category get items\n";
    return items;
}
