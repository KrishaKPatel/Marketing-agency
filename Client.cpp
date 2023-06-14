#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include "Client.h" //header file
using namespace std;

//check client is existed ot not
bool ClientList::isClientStored(string name, string email, string age) {
    ifstream inFile("clients.txt");
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        string storedName = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        string storedEmail = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(",");
        string storedPhone = line.substr(0, pos);
        if (name == storedName && email == storedEmail && age == storedPhone) {
            cout << "Client is already existing";
            inFile.close();
            return true;
        }
        else if (name == storedName) {
            cout << "This client name is already stored." << endl;
            inFile.close();
            return true;
        }
        else if (email == storedEmail) {
            cout << "This client email is already stored." << endl;
            inFile.close();
            return true;
        }
        else if (age == storedPhone) {
            cout << "This client Phone no is already stored." << endl;
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

// Save the list of clients to a file
void ClientList::saveToFile(string filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }
    Client* current = head;
    while (current != nullptr) {
        outfile << current->name << "," << current->email << "," << current->pno << endl;
        current = current->next;
    }
    outfile.close();
}

// Add a client to the list
void ClientList::addClient(string name, string email, string pno) {
    Client* newClient = new Client(name, email, pno);
    if (head == nullptr) {
        head = newClient;
    }
    else {
        Client* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newClient;
        cout << name << " is added to list." << endl;
    }
}



// Print the list of clients by recursion
void ClientList::printList(Client* current) {
    if (current == nullptr) {
        return;
    }
    cout << "Name: " << current->name << endl;
    cout << "Email: " << current->email << endl;
    cout << "Phone no: " << current->pno << endl;
    cout << endl;
    printList(current->next); //recursive call
    
}

//update the client details
void ClientList::updateNode(string name) {
    Client* current = head;
    while (current != NULL) {
        if (current->name == name) {
            cout << "Enter new email: ";
            cin >> current->email;
            cout << "Enter new phone no: ";
            cin >> current->pno;
            saveToFile("clients.txt");
            cout << name << " is successfully updated!" << endl;
            return;
        }
        current = current->next;

    }

    cout << "Client not found" << endl;
}

// delete a client from the list by name
void ClientList::deleteClient(string name) {
        
    if (head == NULL) {
        cout << name << " is not found." << endl;
        return;
    }

    if (head->name == name) {
        Client* temp = head;
        head = head->next;
        delete temp;
        cout << name << " is successfully deleted!" << endl;
    }
    else {
        Client* temp = head;
        while (temp->next != NULL) {
            if (temp->next->name == name) {
                Client* del = temp->next;
                temp->next = temp->next->next;
                delete del;
                break;
            }
            temp = temp->next;
        }
        cout << name << " is successfully deleted!" << endl;
    }
    saveToFile("clients.txt");
}

//load client detail from file to linked list
void loadClientsFromFile(ClientList& list, string filename) {
    string n, e, p;
    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }
     
     if(infile.peek() == ifstream::traits_type::eof()) 
     {  
        cout << "No data found." << endl;
     }

    else {
        string line;
        while (getline(infile, line)) {
            string name, email, ageString;
            stringstream ss(line);
            // Read the name, email, and phone from the line
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, ageString, '\n');
            n = name;
            e = email;
            p = ageString;
            list.addClient(n, e, p);
            system("cls");
        }
    }

    infile.close();
}

//client menu
void client_menu() 
{
    system("cls");
    ClientList clientList;
    string name, email, pno, update_name, delete_name;
    char choice;
    int ch;
    
    cout << "Client Management" << endl;
    cout << "----------------------------------" << endl;
    cout << "1. Add a client detail" << endl;
    cout << "2. Display a client detail" << endl;
    cout << "3. Update a client detail" << endl;
    cout << "4. Delete a client detail" << endl;
    cout << "5. Main menu" << endl;
    cout << endl;
    cout << "Select one option:";
    cin >> ch;
    switch (ch) {
    case 1:
        loadClientsFromFile(clientList, "clients.txt"); //load the data from file to linked list
        system("cls");
        cout << "Enter client name: ";
        cin >> name;
        cout << "Enter client email: ";
        cin >> email;
        cout << "Enter client phone no: ";
        cin >> pno;
        if (clientList.isClientStored(name, email, pno) == true) {
            cout << "Failed to store the data."<<endl;
        }
        else {
            clientList.addClient(name, email, pno); //adding the client detail
            clientList.saveToFile("clients.txt"); //save the data into file
        }
        
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu(); //back to client menu
            break;
        case 'N':
            break;
        }
        break;
    case 2:
        system("cls");
        loadClientsFromFile(clientList, "clients.txt"); //load the data from file to linked list
        clientList.printList(clientList.head); //display all the clients detail
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu(); //back to client menu
            break;
        case 'N':
            break;
        }
        break;
    case 3:
        system("cls");
        loadClientsFromFile(clientList, "clients.txt"); //load the data from file to linked list
        cout << "Enter the client name for updating:";
        cin >> update_name;
        clientList.updateNode(update_name); //update the client detail
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu(); //back to client menu
            break;
        case 'N':
            break;
        }
        break;
    case 4:
        system("cls");
        loadClientsFromFile(clientList, "clients.txt"); //load the data from file to linked list
        cout << "Enter the client name for delete:";
        cin >> delete_name;
        clientList.deleteClient(delete_name); //delete the client detail
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu(); //back to client menu
            break;
        case 'N':
            break;
        }
        break;
    case 5:
        main_menu(); //back to main menu
        break;
    default:
        cout << "Invalid option" << endl;
        break;
    }

}
