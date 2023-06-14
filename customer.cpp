// 
// New For Phase 2
//
#include "customer.h" //header file 
#include<string>
#include <sstream >
#include <fstream>
#include<iostream>
using namespace std;

// 
// New For Phase 2
// Get the customer information
//
void  CustomerTable::get_information() {
    int ch;
    Customer customer;
    cout << "Enter the customer name: ";
    cin >> customer.name;
    cout << "Enter the email id: ";
    cin >> customer.email;
    cout << "Enter the phone no: ";
    cin >> customer.phone;
    cout << "Select the type of customer " << endl;
    cout << "1. Demographic(based on age, gender, income, education level, occupation)" << endl;
    cout << "2. Psychographic(based on attitudes, values, interests, and lifestyle)" << endl;
    cout << "3. Geographic location(based on location such as country, region or city)" << endl;
    cout << "4. Consumer behavior(based on purchasing habits, buying cycle, and decision-making process)" << endl;
    cin >> ch;
    switch (ch) {
    case 1:
        customer.type = "Demographic";
        break;
    case 2:
        customer.type = "Psychographic";
        break;
    case 3:
        customer.type = "Geographic location";
        break;
    case 4:
        customer.type = "Consumer behavior";
        break;
    default:
        cout << "please choose valid option." << endl;
        break;
    }
    add_customer(customer);
    save_to_file("customer.csv");
}

// 
// New For Phase 2
// add the customer into hashtable
//
void CustomerTable::add_customer(Customer customer) {
    table[customer.email] = customer;
}

// 
// New For Phase 2
// remove customer detail
//
void CustomerTable::remove_customer(string name) {
    vector<pair<int, string>> matching_customers;
    int index = 0;
    int i = 0;
    for (const auto& pair : table) {
        Customer customer = pair.second;
        if (customer.name == name) {
            matching_customers.push_back({ index, customer.email });
        }
        index++;
    }
    if (matching_customers.empty()) {
        cout << "\nNo customer found with name " << name << endl;
        return;
    }
    else if (matching_customers.size() == 1) {
        string email = matching_customers[0].second;
        table.erase(email);
        save_to_file("customer.csv");
        cout << "\nCustomer with email " << email << " removed successfully." << endl << endl;
    }
    else {
        cout << "\nMultiple customers found with name " << name << ":" << endl;
        cout << "\nList the customers email id(reference for removing)" << endl;
        for (const auto& pair : matching_customers) {
            cout << i << ". " << pair.second << endl;
            i++;
        }
        cout << "Enter the index of the customer to remove: ";
        int remove_index;
        cin >> remove_index;
        if (remove_index >= 0 && remove_index < matching_customers.size()) {
            string email = matching_customers[remove_index].second;
            table.erase(email);
            save_to_file("customer.csv");
            cout << "Customer with email " << email << " removed successfully." << endl <<endl;
        }
        else {
            cout << "Invalid index." << endl;
        }
    }
}

// 
// New For Phase 2
// load the data from file into hashtable
//
void CustomerTable::load_from_file(string filename) {
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    string line;
    while (getline(input_file, line)) {
        Customer customer;
        stringstream ss(line);
        getline(ss, customer.name, ',');
        getline(ss, customer.email, ',');
        getline(ss, customer.phone, ',');
        getline(ss, customer.type, '\n');
        add_customer(customer);
    }
}

// 
// New For Phase 2
// save the data into file from hashtable
//
void CustomerTable::save_to_file(string filename) {
    ofstream output_file(filename);
    if (!output_file.is_open()) {
        throw runtime_error("Failed to open file: " + filename);
    }

    for (auto it = table.begin(); it != table.end(); ++it) {
        const Customer& customer = it->second;
        output_file << customer.name << ',' << customer.email << ',' << customer.phone << ',' << customer.type << '\n';
    }

}

// 
// New For Phase 2
// display customer data by its type
//
void CustomerTable::display_customers_by_type(string type) {
    int count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        const Customer& customer = it->second;
        if (customer.type == type) {
            count += 1;
            cout << "Name: " << customer.name << endl;
            cout << "Email: " << customer.email << endl;
            cout << "Phone: " << customer.phone << endl;
            cout << "Type: " << customer.type << endl;
            cout << endl;
        }
    }
    if (count == 0) {
        cout << "No data found." << endl;
    }
}

// 
// New For Phase 2
// display customer detail by its name
//
void CustomerTable::display_customers_by_name(string name) {
    int count = 0;
    for (auto it = table.begin(); it != table.end(); ++it) {
        const Customer& customer = it->second;
        if (customer.name == name) {
            count += 1;
            cout << "Name: " << customer.name << endl;
            cout << "Email: " << customer.email << endl;
            cout << "Phone: " << customer.phone << endl;
            cout << "Type: " << customer.type << endl;
            cout << endl;
        }
    }
    if (count == 0) {
        cout << "No data found." << endl;
    }
}

// 
// New For Phase 2
// customer menu
//
void customer_menu() {
    system("cls");
    CustomerTable customer_table;
    customer_table.load_from_file("customer.csv");
    int ch, ch1, ch2;
    string name, type;
    string name1;
    char choice;
    cout << "Customer Management System" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "1. Add the customer" << endl;
    cout << "2. Remove the customer" << endl;
    cout << "3. Display the customers" << endl;
    cout << "4. Back to the main menu" << endl;
    cout << "Select any one option:";
    cin >> ch;
    switch (ch) {
    case 1:
        system("cls");
        customer_table.get_information(); //get the information
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            customer_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
        break;
    case 2:
        system("cls");
        cout << "Enter the customer name for removing: ";
        cin >> name;
        customer_table.remove_customer(name); //remove the customer detail
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            customer_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
        break;
    case 3:
        system("cls");
        cout << "Display the customers details" << endl;
        cout << "-------------------------------------" << endl;
        cout << "1. According to name" << endl;
        cout << "2. According to type" << endl;
        cout << "Select any one option: ";
        cin >> ch1;
        switch (ch1) {
        case 1:
            cout << "\nEnter the customer name: ";
            cin >> name1;
            customer_table.display_customers_by_name(name1); //display customer by its name
            break;

        case 2:
            cout << "\nSelect the type of customer " << endl;
            cout << "1. Demographic(based on age, gender, income, education level, occupation)" << endl;
            cout << "2. Psychographic(based on attitudes, values, interests, and lifestyle)" << endl;
            cout << "3. Geographic location(based on location such as country, region or city)" << endl;
            cout << "4. Consumer behavior(based on purchasing habits, buying cycle, and decision-making process)" << endl;
            cin >> ch;
            switch (ch) {
            case 1:
                type = "Demographic";
                break;
            case 2:
                type = "Psychographic";
                break;
            case 3:
                type = "Geographic location";
                break;
            case 4:
                type = "Consumer behavior";
                break;
            }
            customer_table.display_customers_by_type(type); //display the customer detail by its type
            break;
        }
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            customer_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
        break;
    case 4:
        main_menu(); //back to main menu
    }
}

