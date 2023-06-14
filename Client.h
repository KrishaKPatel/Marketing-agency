#ifndef CLIENT
#define CLIENT
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
using namespace std;

void main_menu(); //main menu

//define the client class
class Client {
public:
    string name, email, pno;
    Client* next;

    // Constructor
    Client(string n, string e, string a) {
        name = n;
        email = e;
        pno = a;
        next = nullptr;
    }
};

// Define the ClientList class
class ClientList {
public:
    Client* head;

    // Constructor
    ClientList() {
        head = nullptr;
    }

    // Destructor
    ~ClientList() {
        Client* current = head;
        while (current != nullptr) {
            Client* temp = current;
            current = current->next;
            delete temp;
        }
    }

    bool isClientStored(string name, string email, string age); //function of checking the client is exsited or not
    void saveToFile(string filename); //function of save the data into the file
    void addClient(string name, string email, string pno); //function of adding the client
    void printList(Client* current); //function of display the client detail
    void updateNode(string name); //function of update the detail of client
    void deleteClient(string name); //function of delete the client detail
};
void loadClientsFromFile(ClientList& list, string filename); //function of load the client data from file to linked list
void client_menu(); //client menu
#endif // !CLIENT

