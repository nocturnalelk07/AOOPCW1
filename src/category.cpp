// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: <STUDENT NUMBER>
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "category.h"

// TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Category c{"categoryIdent"};

// TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Items in the Category contains.
//
// Example:
//  Category c{"categoryIdent"};
//  auto size = c.size();

// TODO Write a function, getIdent, that returns the identifier for the Category.
//
// Example:
//  Category cObj{"categoryIdent"};
//  auto ident = cObj.getIdent();

// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Category identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.setIdent("categoryIdent2");

// TODO Write a function, newItem, that takes four parameters, an Item
// identifier (string), description (string), amount (double), and date (Date)
// and returns the Item object as a reference.  If an object with the same
// identifier already exists, then the existing object should be overwritten by
// the new Item. Throw a std::runtime_error if the Item object cannot be
// inserted into the container for whatever reason.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");

// TODO Write a function, addItem, that takes one parameter, an Item object, and
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

// TODO Write a function, getItem, that takes one parameter, an Item identifier
// (a string) and returns the Item as a reference. If no Item exists, throw an
// appropriate exception.
//
// Hint: See the test scripts for the exception expected.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  auto iObj = cObj.getItem("newItemName");

// TODO Write a function, getSum, that returns the sum of all Item amounts in
// the category. If no Item exists return 0.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  auto sum = cObj.getSum() // 3.0

// TODO Write a function, deleteItem, that takes one parameter, an Item
// identifier (a string), deletes the item with that identifier from the
// container, and returns true if the Item was deleted. If no Item exists, throw
// an appropriate exception.
//
// Example:
//  Category cObj{"categoryIdent"};
//  cObj.newItem("newItemName");
//  bool result = cObj.deleteItem("newItemName");

// TODO Write an == operator overload for the Category class, such that two
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

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Category.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Category cObj{"categoryIdent"};
//  std::string s = cObj.str();
