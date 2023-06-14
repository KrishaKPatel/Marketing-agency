// 
// New For Phase 2
//

#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <unordered_map>
using namespace std;
#include<string>

void main_menu(); //main menu

// 
// New For Phase 2
//structure for customer
//
struct Customer {
    string name;
    string email;
    string phone;
    string type;
};

// 
// New For Phase 2
// customertable class
//
class CustomerTable {

public:
    void get_information(); //get the customer information
    void add_customer(Customer customer); //add the customer into hashtable
    void remove_customer(string email); //remove the customer from hashtable
    void display_customers_by_type(string type); //display the customer data by its type
    void display_customers_by_name(string type); //display the customer data by its name
    void load_from_file(string filename); //load the customer data from file to hashtable
    void save_to_file(string filename); //save the customer data from hashtable to file

private:
    std::unordered_map<string, Customer> table; //hashtable by using unordered-map
};
void customer_menu();
#endif

