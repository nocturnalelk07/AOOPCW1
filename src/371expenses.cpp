// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------

#include "371expenses.h"
#include "lib_cxxopts.hpp"
#include "item.h"
#include <iostream>
#include <string.h>
#include <cstring>

// TODO Complete this function. You have been provided some skeleton code which
//  retrieves the database file name from cxxopts.
//  1. Load the database file by calling load() on a ExpenseTracker object
//  2. Parse the 'action' argument to decide what action should be taken
//     (json, create, sum, delete, update).  'json' and 'sum' are the easiest to implement and
//     'update' is the hardest. The details of how these arguments work is in
//     the coursework specification.
//  3. Save the updated ExpenseTracker object to the JSON file if there have been
//     changes (calling save() on the ExpenseTracker object).
//
// Some commented out code has been provided. Using some of this will be
// demonstrated in the coursework video on Canvas. Remember, this coursework is
// meant to be challenging and testing your understanding of programming in C++.
// Part of the challenge is figuring things out on your own. That is a major
// part of software development.
//
// Example:
//  int main(int argc, char *argv[]) { return App::run(argc, argv); }
int App::run(int argc, char *argv[]) {
  auto options = App::cxxoptsSetup();

    auto args = options.parse(argc, argv);

    // Print the help usage if requested
    if (args.count("help")) {
      std::cout << options.help() << '\n';
      return 0;
    }

    // Open the database and construct the ExpenseTracker
    const std::string db = args["db"].as<std::string>();

    ExpenseTracker etObj{};
    // Only uncomment this once you have implemented the load function!
    etObj.load(db);

    // try parsing arguments and exit if there is an exception
    const Action a = parseActionArgument(args);
    
    switch (a) {
      case Action::CREATE:
        //creates a new category in the expense tracker with an ident equal to the argument, or do nothing if category already exists. output nothing and exit 0
        createNewCategory(args, etObj);
        etObj.save(db);
        break;
      case Action::JSON:
        //decide which getJson method to use then call it
        chooseGetJson(args, etObj);
        break;
      case Action::UPDATE:
        throw std::runtime_error("update not implemented");
        break;
      case Action::DELETE:
        //delete a category if it exists
        deleteCategory(args, etObj);
        etObj.save(db);
        break;
      case Action::SUM:
        //sum a category, takes no other values
        sumCategory(args, etObj);
        break;
      default:
        throw std::runtime_error("unknown action");
    }

    return 0;
}

// Create a cxxopts instance. You do not need to modify this function.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
cxxopts::Options App::cxxoptsSetup() {
  cxxopts::Options cxxopts("371expenses", "Student ID: " + STUDENT_NUMBER + "\n");

  cxxopts.add_options()(
      "db", "Filename of the 371expenses database",
      cxxopts::value<std::string>()->default_value("database.json"))(

      "action",
      "Action to take, can be: 'create', 'json', 'update', 'delete', 'sum'.",
      cxxopts::value<std::string>())(

      "category",
      "Apply action (create, json, update, delete, sum) to a category. If you "
      "want to add a category, set the action argument to 'create' and the "
      "category argument to your chosen category identifier.",
      cxxopts::value<std::string>())(

      "description",
      "Apply action (create, update) to an expense description. If you want to "
      "add an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "amount",
      "Apply action (create, update) to an expense amount. If you want to add "
      "an expense item, set the action argument to 'create', the category "
      "argument to your chosen category identifier and the description "
      "argument to the expense description and the amount argument to the "
      "expense amount, and the id argument to the unique expense id.",
      cxxopts::value<std::string>())(

      "item",
      "Apply action (create, update, json, delete) to an expense item "
      "identified by its id. If you want to update an expense item, set the "
      "action argument to 'update', the id argument to the expense identifier, "
      "the description argument to the updated expense description, and the "
      "amount argument to the updated expense amount.",
      cxxopts::value<std::string>())(

      "date",
      "When creating or updating an expense item, set the Date flag to change "
      "the expense item's Date to the one specified as an argument (e.g. "
      "'2024-11-23'). If the Date argument is ommitted set the expense Date "
      "to today's Date when creating an expense item, and leave the Date "
      "unchanged if omitted when updating an expense item.",
      cxxopts::value<std::string>())(

      "tag",
      "Apply action (create or delete) to a tag.  If you want to add a tag, "
      "set the action argument to 'create', the category argument to your "
      "chosen category identifier, the item argument to your chosen item "
      "identifier, and the tag argument to a single tag 'tag' or comma "
      "seperated list of tags: 'tag1,tag2'). The action update/sum/json are "
      "unsupported here.",
      cxxopts::value<std::string>())(

      "h,help", "Print usage.");

  return cxxopts;
}

// DONE Rewrite this function so that it works. This function should
//  case-insensitively check the action argument retrieved from cxxopts and
//  convert this to a value from the ACTION enum. If an invalid value is given
//  in a string, throw an std::invalid_argument exception.
//
// Example:
//  auto options = App::cxxoptsSetup();
//  auto args = options.parse(argc, argv);
//  App::Action action = parseActionArgument(args);
App::Action App::parseActionArgument(cxxopts::ParseResult &args) {

  std::string input = args["action"].as<std::string>();

  //uppers the input to be case insensitive
  std::transform(input.begin(), input.end(), input.begin(), ::toupper);

  if (input == jsonStr) {
    return Action::JSON;
  } else if (input == sumStr) {
    return Action::SUM;
  }else if (input == createStr) {
    return Action::CREATE;
  }else if (input == deleteStr) {
    return Action::DELETE;
  }else if (input == updateStr) {
    return Action::UPDATE;
  }else {
    throw std::invalid_argument("action");
  }
}

// DONE Write a function, getJSON, that returns a std::string containing the
// JSON representation of a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function).
//
// Example:
//  ExpenseTracker etObj{};
//  std::cout << getJSON(etObj);
std::string App::getJSON(ExpenseTracker &etObj) {
  // Only uncomment this once you have implemented the functions used!
  return etObj.str();
}

// DONE Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific Category in a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function and
// make any other adjustments).
//
// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::cout << getJSON(etObj, c);
std::string App::getJSON(ExpenseTracker &etObj, const std::string &c) {
  // Only uncomment this once you have implemented the functions used!
  auto cObj = etObj.getCategory(c);
  return cObj.str();
}

// DONE Write a function, getJSON, that returns a std::string containing the
//  JSON representation of a specific ExpenseItem in a ExpenseTracker object.
//
// This function has been implemented for you, but you may wish to adjust it.
// You will have to uncomment the code, which has been left commented to ensure
// the coursework framework compiles (i.e., it calls functions that you must
// implement, once you have implemented them you may uncomment this function and
// make any other adjustments).
//
// Example:
//  ExpenseTracker etObj{};
//  std::string c = "category argument value";
//  std::string id = "expense id argument value";
//  std::cout << getJSON(etObj, c, id);
std::string App::getJSON(ExpenseTracker &etObj, 
                         const std::string &c,
                         const std::string &id) {
  // Only uncomment this once you have implemented the functions used!
  auto iObj = etObj.getCategory(c).getItem(id);
  return iObj.str();
}

//chooses the correct form of getJson to call and output
void App::chooseGetJson(const cxxopts::ParseResult &args, ExpenseTracker &etObj) {
  std::string inputCat;
  std::string inputIt;
  //if there is no category argument an exception is caught and ignored (the string will remain empty)
  try {
    inputCat = args[categoryStr].as<std::string>();
  } catch(...) {
  }



  //if there is a category in the command either call json with category or with category and item
  if (!inputCat.empty()) {
    try {
      inputIt = args[itemStr].as<std::string>();
    } catch (...) {
    }
    //if there is an item in the command call get with category and item
    if (!inputIt.empty()) {
      std::cout << getJSON(etObj, inputCat, inputIt);
    } else if (!inputCat.empty()) {
      std::cout << getJSON(etObj, inputCat);
    } 
  } else {
    std::cout << getJSON(etObj);
    }


    //if an item is provided there must be a category, or throw an exception
    if (!inputIt.empty()) {
      if (!inputCat.empty()) {
        //get a json item
      } else {
        throw std::out_of_range(jsonMissingCategoryError);
      }
    }
}

//creates a new category from input if not already exists
void App::createNewCategory(const cxxopts::ParseResult &args, ExpenseTracker &etObj) {
  bool categoryExists = false;
  std::string categoryIdent;
  std::string categoryItemId;
  double categoryItemAmount = 0;
  std::string categoryItemDesc;
  std::string categoryItemDate;
  std::string categoryItemTag;
  Date date;

  //get the category value, which there will always be or throw an error
  try {
    categoryIdent = args[categoryStr].as<std::string>();
  } catch (...) {

    throw std::out_of_range(createMissingArgError);
  }
  

  //if the category exists an exception will be thrown and the code will not execute
  try {
    etObj.getCategory(categoryIdent);
    categoryExists = true;
  } catch (...) {
    categoryExists = false;
  }

  //if the category doesnt exist then create it
  if (!categoryExists) {
    etObj.newCategory(categoryIdent);
  }

    std::cout << "category was created successfully";
    //get all the items' values that we need
    try {
    categoryItemId = args[itemStr].as<std::string>();
    } catch (...) {
    }

    try {
    categoryItemAmount = stoi(args[amountStr].as<std::string>());
    categoryItemAmount = round(categoryItemAmount * 100) / 100;
    } catch (...) {
      std::cout << "exception caught stoi";
    }

    try {
    categoryItemDesc = args[descriptionStr].as<std::string>();

    } catch (...) {
    }

    try {
    categoryItemDate = args[dateCapsStr].as<std::string>();
    if(categoryItemDate.empty()) {
      //if no date provided then use current date
      date = Date();
    } else {
      date = Date(categoryItemDate);
    }
    categoryItemTag = args[tagStr].as<std::string>();
    } catch (...) {
    }
  
    //call the method to create a new item and add it to the category
    if (!(categoryItemId.empty() || categoryItemDesc.empty() || categoryItemAmount == 0)) {
    etObj.getCategory(categoryIdent).addItem(createNewItem(categoryItemId, categoryItemDesc,
       categoryItemAmount, categoryItemDate, categoryItemTag));
    }
  
}

//creates a new item and adds it to the given category
Item App::createNewItem(const std::string &itemIdent, const std::string &itemDesc,
   const double &amount, const Date &date, const std::string &tags) {

    Item inputItem = Item(itemIdent, itemDesc, amount, date);

    if (!tags.empty()) {
      std::stringstream ss;
      char delimiter = ',';
      std::string tempS;
      ss << tags;
      //loop through and add the tags
      while (getline(ss, tempS, delimiter)) {
        inputItem.addTag(tempS);
      }
      }

      return inputItem;
}

//deletes a category, item or tag based on input
void App::deleteCategory(const cxxopts::ParseResult &args, ExpenseTracker &et) {
  std::string categoryIdent;
  std::string ItemIdent;
  std::string tagIdent;

  try {
    categoryIdent = args[categoryStr].as<std::string>();
  } catch (...) {
  }
  try {
    ItemIdent = args[itemStr].as<std::string>();
  } catch (...) {
  }
  try {
    tagIdent = args[tagStr].as<std::string>();
  } catch (...) {
  }

  if (!categoryIdent.empty()) {
    if (!ItemIdent.empty()) {
      if (!tagIdent.empty()) {
        et.getCategory(categoryIdent).getItem(ItemIdent).deleteTag(tagIdent);
      } else {
        et.getCategory(categoryIdent).deleteItem(ItemIdent);
      }
    } else {
      et.deleteCategory(categoryIdent);
    }
  }
  
}

void App::sumCategory(const cxxopts::ParseResult &args, ExpenseTracker &et) {
  std::string categoryIdent;
  double totalSum = 0;

  try {
    categoryIdent = args[categoryStr].as<std::string>();
  } catch (...) {
  }
  

  if (categoryIdent.empty()) {
    //get the sum of all categories
    totalSum = et.getSum();

  } else {
    //get the sum of a category
    totalSum = et.getCategory(categoryIdent).getSum();
  }
  
  //round the total and output it
  totalSum = round(totalSum * 100) / 100;
  std::cout << totalSum;
}
