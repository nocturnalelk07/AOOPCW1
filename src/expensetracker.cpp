// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2024/25)
// Department of Computer Science, Swansea University
//
// Author: 2121292
//
// Canvas: https://canvas.swansea.ac.uk/courses/52781
// -----------------------------------------------------
#include "expensetracker.h"


// DONE Write a ExpenseTracker constructor that takes no parameters and constructs an
//  an ExpenseTracker object
//
// Example:
//  ExpenseTracker etObj{};
ExpenseTracker::ExpenseTracker() {
    std::cout << "et constructor---- \n";
}

// DONE Write a function, size, that takes no parameters and returns an unsigned
//  int of the number of categories the ExpenseTracker contains.
//
// Example:
//  ExpenseTracker etObj{};
//  auto size = etObj.size();
unsigned int ExpenseTracker::size() const{
    std::cout << "calling et Size \n";
    return categories.size();
}

// DONE Write a function, newCategory, that takes one parameter, a category
//  identifier, and returns the Category object as a reference. If an object
//  with the same identifier already exists, then the existing object should be
//  returned. Throw a std::runtime_error if the Category object cannot be
//  inserted into the container.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
Category ExpenseTracker::newCategory(const std::string &ident) {
    std::cout << "calling et new category\n";
    //return the category if it already exists
    for (int i = 0; i < (int) categories.size(); i++){
        if (categories[i].getIdent() == ident) {
            return categories[i];
        }
    }
    try {
        Category category = Category(ident); 
        categories.push_back(category);
        return category;
    } catch(...) {
    throw std::runtime_error(etRuntimeError);
    }
}

// DONE Write a function, addCategory, that takes one parameter, a Category
//  object, and returns true if the object was successfully inserted. If an
//  object with the same identifier already exists, then the contents should be
//  merged (see also Category::addItem) and then returns false. Throw a
//  std::runtime_error if the Category object cannot be inserted into the
//  container for whatever reason.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj{"categoryIdent"};
//  etObj.addCategory(cObj);
bool ExpenseTracker::addCategory(const Category &category) {
    std::cout << "calling et add category\n";
    for (int i = 0; i < (int) categories.size(); i++) {
        if (categories[i].getIdent() == category.getIdent()) {
            for (int j = 0; j < (int) category.size(); j++)
            {
                //adds the item from the given category to the existing one
                
                std::vector<Item> newItems = category.getItems();
                std::cout << "adding " << newItems[j].str() << "to category\n";
                categories[i].addItem(newItems[j]);
            }
            //override any other values here
            return false;
        }
    }
    //if we get here category doesnt exist and we can add it
    try {
    categories.push_back(category);
    } catch(...) {
        throw std::runtime_error(etRuntimeError);
    }
    return true;
}

// DONE Write a function, getCategory, that takes one parameter, a Category
//  identifier and returns the Category with that identifier. If no Category
//  exists, throw an appropriate exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  auto cObj = etObj.getCategory("categoryIdent");
Category& ExpenseTracker::getCategory(const std::string &ident) {
    std::cout << "calling et get category\n";
    //loop through the categories in the expense tracker looking for the right one
    for (int i = 0; i < (int) categories.size(); i++) {
        categories[i].size();
        if (categories[i].getIdent() == ident) {
            std::cout << "leaving get category with: " << categories[i].getIdent() << "\n";
            categories[i].size();
            return categories[i];
        }
    }
    std::cout << "throwing get category: \n";
    throw std::out_of_range(etOOR);
}

// DONE Write a function, deleteCategory, that takes one parameter, a Category
//  identifier, and deletes that catagory from the container, and returns true
//  if the Category was deleted. If no Category exists, throw an appropriate
//  exception.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.newCategory("categoryIdent");
//  etObj.deleteCategory("categoryIdent");
bool ExpenseTracker::deleteCategory(const std::string &ident) {
    std::cout << "calling et delete category\n";
    for (int i = 0; i < (int) categories.size(); i++) {
        if (categories[i].getIdent() == ident) {
            categories.erase(categories.begin() + i);
            return true;
        }
    }
    throw std::out_of_range(etOOR);
}

// DONE Write a function, getSum, that returns the sum of all Category expense
// sums. This consists of the sum of all individual item amounts across all categories.
// If no categories or no items exists return 0.
//
// Example:
//  ExpenseTracker etObj{};
//  Category cObj = etObj.newCategory("categoryIdent");
//  Category cObj2 = etObj.newCategory("categoryIdent2");
//  cObj.newItem("newItemName", "Description", "1.0", Date(2024,12,25));
//  cObj.newItem("newItemName2", "Description", "2.0", Date(2024,12,25));
//  cObj2.newItem("newItemName3", "Description", "3.0", Date(2024,12,25));
//  cObj2.newItem("newItemName4", "Description", "4.0", Date(2024,12,25));
//  auto sum = ejObj.getSum() // 10.0
double ExpenseTracker::getSum() const {
    std::cout << "calling et get sum\n";
    double sum = 0;
    for (int i = 0; i < (int) categories.size(); i++) {
        sum += categories[i].getSum();
    }
    return sum;
}

// TODO Write a function, load, that takes one parameter, a std::string,
//  containing the filename for the database. Open the file, read the contents,
//  and populates the container for this ExpenseTracker. If the file does not open throw
//  an appropriate exception (either std::runtime_error or a derived class).
//
// A note on clashes:
//  If you encounter two categories with the same identifier, or two expense items with the same
//  identifier within the same category, you may choose whichever category/item is parsed
//  by the nlohmann json library. The json spec on duplicate keys is undefined, so
//  you can default to the behaviour of the nlohmann json library.
// JSON formatting:
//  The JSON file has the following format (see the sample database.json file
//  also provided with the coursework framework):
// {
//   "Studies": {
//     "1": {
//       "amount": 999.99,
//       "date": "2024-12-25",
//       "description": "Laptop",
//       "tags": [
//         "computer",
//         "programming",
//         "uni"
//       ]
//     },
//     ...
//   },
//   "Travel": {
//     "3": {
//       "amount": 164.0,
//       "date": "2024-12-30",
//       "description": "Bus Pass",
//       "tags": [
//         "bus",
//         "uni"
//       ]
//     }
//   },
//   ...
// }
//
// More help:
//  To help you with this function, I've selected the nlohmann::json
//  library that you must use for your coursework. Read up on how to use it
//  here: https://github.com/nlohmann/json. You may not use any other external
//  library other than the one I have provided. You may choose to process the
//  JSON yourself without the help of the library but I guarantee this will be
//  more work.
//
//  Understanding how to use external libraries is part of this coursework! You
//  will need to use this file to deserialize the JSON from string
//  to the JSON object provided by this library. Don't just look at the code
//  provided below, or in the README on the GitHub and despair. Google search,
//  look around, try code out in a separate file to all figure out how to use
//  this library.
//
//  Once you have deserialized the JSON string into an object, you will need to
//  loop through this object, constructing Category and Item objects according
//  to the JSON data in the file.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");
void ExpenseTracker::load(const std::string &file) {
    std::cout << "calling et load\n";

    
    try {
        //open the file with filePath
        std::ifstream in(file);
        //read the contents of the file parsed as json
        json data = json::parse(in);
        std::cout << data << std::endl;

        //populate the container for this expense tracker by looping through the json
        //this should add a category (and all the categories' data) each loop
        for (json::iterator it = data.begin(); it != data.end(); ++it) {

            //get the json for the current category to read
            json jCategory = it.value();

            //get the identifier
            std::string ident = it.key();

            //create the category
            Category category = Category(ident);

            //loop through the items in the category and add them
            for (json::iterator catIt = jCategory.begin(); catIt != jCategory.end(); ++catIt) {
                //items have an identifier, a description, an amount, a date and tags
                std::string identifier = catIt.key();
                std::string description = catIt.value().at(descriptionStr);
                double amount = catIt.value().at(amountStr);
                Date date = catIt.value().at(dateStr);
                std::vector<std::string> tags = catIt.value().at(tagsStr);

                //create an item from these variables
                Item newItem = Item(identifier, description, amount, date, tags);

                //add the item to the category
                category.addItem(newItem);
            } // leave item loop

            //add the category to the et
            addCategory(category);

        } //leave category loop
    
    } catch (...) {
            throw std::runtime_error(etRuntimeError);
        }
}

// TODO Write a function, save, that takes one parameter, the path of the file
//  to write the database to. The function should serialise the ExpenseTracker object
//  as JSON.
//
// Example:
//  ExpenseTracker etObj{};
//  etObj.load("database.json");
//  ...
//  etObj.save("database.json");
void ExpenseTracker::save(const std::string &filePath) {
    std::cout << "calling et save\n";
    
    //find the file from the filepath and open an output stream
    std::ofstream out(filePath);

    //serialise the object to json
    std::string string = str();
    out << string;
    out.close();
}

// DONE Write an == operator overload for the ExpenseTracker class, such that two
//  ExpenseTracker objects are equal only if they have the exact same data.
//
// Example:
//  ExpenseTracker etObj1{};
//  ExpenseTracker etObj2{};
//  if(etObj1 == etObj2) {
//    ...
//  }
bool operator== (const ExpenseTracker &lhs, const ExpenseTracker &rhs) {
    std::cout << "et == operator \n";
    bool isEqual = true;
    if (lhs.categories == rhs.categories) {
    } else {
        isEqual = false;
    }

    return isEqual;
}

// DONE Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the ExpenseTracker.
//
// Hint:
//  See the coursework specification for how this JSON should look.
//
// Example:
//  ExpenseTracker etObj{};
//  std::string s = etObj.str();
std::string ExpenseTracker::str() {
    std::cout << "calling et str\n";
    json j;
    to_json(j, *this);
    std::cout << "returning et str\n";
    return j.dump();
}

//converts to json
//TODO
void ExpenseTracker::to_json(json& j, ExpenseTracker& et) {
    j = json({et.categoryString()});
}

//formats categories vector into a json style string
std::string ExpenseTracker::categoryString() {
    std::stringstream ss;
    for(int i = 0; i < (int) categories.size(); i++) {
        ss << categories.at(i).str();
    }
    return ss.str();
}
