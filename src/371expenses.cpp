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
#include <iostream>
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
    std::string inputCat;
    switch (a) {
      case Action::CREATE:
        throw std::runtime_error("create not implemented");
        break;
      case Action::JSON:
        //std::cout << "taking the json action\n";
        //decide which getJson method to use then call it
        //if there is no category argument an exception is caught and ignored (the string will remain empty)
        inputCat = "";
        try {
          inputCat = args[categoryStr].as<std::string>();
        } catch(...) {

        }

        //if there is a category in the command either call json with category or with category and item
        if (!inputCat.empty()) {
          std::string inputIt;
          try {
            inputIt = args[itemStr].as<std::string>();
          } catch (...) {

          }

          //if there is an item in the command call get with category and item
          if (!inputIt.empty()) {
            std::cout << getJSON(etObj, inputCat, inputIt);
          } else {
            std::cout << getJSON(etObj, inputCat);
          } 
        } else {
          std::cout << getJSON(etObj);
          }
        break;
      case Action::UPDATE:
        throw std::runtime_error("update not implemented");
        break;
      case Action::DELETE:
        throw std::runtime_error("delete not implemented");
        break;
      case Action::SUM:
        throw std::runtime_error("sum not implemented");
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

      "Date",
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
  //std::cout << "outputting etobj " << etObj.str() << std::endl;
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
  //std::cout << "outputting cat obj " << cObj.str() << std::endl;
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
  //std::cout << "outputting item obj " << iObj.str() << std::endl;
  return iObj.str();
}
