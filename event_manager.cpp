// 
// New For Phase 2
//
#include "event_manager.h" //header file
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;

EventManager::EventManager(const  string& file) : fileName(file) {} //constructor

// 
// New For Phase 2
// load the attendees data from file to set
void EventManager::loadAttendees() {
     ifstream inputFile(fileName);
    if (inputFile.is_open()) {
         string line;
        while ( getline(inputFile, line)) {
             string event;
             string name;
             string email;

             stringstream ss(line);
             getline(ss, event, '|');

             set< pair< string,  string>> eventAttendees;
            while ( getline(ss, name, ',')) {
                 getline(ss, email, ' ');
                eventAttendees.insert( make_pair(name, email)); 
            }

            events[event] = eventAttendees;
        }
        inputFile.close();
    }
}

// 
// New For Phase 2
// save the attendees from set to file
//
void EventManager::saveAttendees() {
     ofstream outputFile(fileName);
    if (outputFile.is_open()) {
        for (const auto& event : events) {
            outputFile << event.first << "|";
            for (const auto& attendee : event.second) {
                outputFile << attendee.first << "," << attendee.second << " ";
            }
            outputFile <<  endl;
        }
        cout << "Data saved successfully.."<<endl;
        outputFile.close();
    }
}

// 
// New For Phase 2
// add the events
//
void EventManager::addEvent(const  string& event) {
    events[event] =  set< pair< string,  string>>();
}

// 
// New For Phase 2
// add attendees to set
//
void EventManager::addAttendee(const  string& event, const  string& name, const  string& email) {
    auto it = events.find(event);
    if (it != events.end()) {
        it->second.insert( make_pair(name, email));
    }
}

// 
// New For Phase 2
// display the attendees
//
void EventManager::displayAttendees(const  string& event) {
    auto it = events.find(event);
    if (it != events.end()) {
        cout << "Attendees for Event: " << it->first << endl;
        for (const auto& attendee : it->second) {
            cout << "Name: " << attendee.first << ", Email: " << attendee.second << endl;
        }  
    }
    else {
         cout << "Event not found." <<  endl;
    }
}

// 
// New For Phase 2
// send emails for next event to all the attendees
//
void EventManager::sendEmailsForUpcomingEvent() {
    std::string upcomingEvent;
    string eventname;
    for (const auto& event : events) {
        if (event.second.empty()) {
            upcomingEvent = event.first;
            cout << upcomingEvent << endl;
        }
    }
    cout << "Enter event name for sending email: ";
    cin >> eventname;
    if (!upcomingEvent.empty()) {
        system("cls");
        std::cout << "Sending emails for the upcoming event: " << eventname << std::endl;
        for (const auto& event : events) {
            for (const auto& attendee : event.second) {
                std::cout << "Sending email to: " << attendee.second << std::endl;
                // Your email sending implementation goes here
            }
        }
    }
    else {
        std::cout << "No upcoming event found." << std::endl;
    }
}

// 
// New For Phase 2
// get the events
//
 set< string> EventManager::getEvents() const {
     set< string> eventSet;
    for (const auto& event : events) {
        eventSet.insert(event.first);
    }
    return eventSet;
}

// 
// New For Phase 2
// event menu
//
 void event_menu() {
     EventManager eventManager("attendees.txt");
     system("cls");
     // Load attendees from file
     set<string> events;
     string event, chosenEvent, name, email;
     int ch;
     char choice;
     cout << "Event Management "<<endl;
     cout << "--------------------------------------------"<<endl;
     cout << "1. Add the event\n";
     cout << "2. Add the attendees\n";
     cout << "3. Display the attendees of event\n";
     cout << "4. Send a email to attendees for next event\n";
     cout << "5. Back to main menu\n";
     cout << "Select any one option:";
     cin >> ch;
     switch (ch) {
     case 1:
         eventManager.loadAttendees(); //load the attendees from file 
         system("cls");
         cout << "Enter the event name: ";
         cin >> event;
         eventManager.addEvent(event); //add the evnet
         eventManager.saveAttendees(); //save the data to file
         cout << "Back to menu(Y/N)";
         cin >> choice;
         switch (choice) {
         case 'Y':
             event_menu(); //back to event menu
             break;
         case 'N':
             break;
         }
         break;
     case 2:
         //Get the list of events
         system("cls");
         eventManager.loadAttendees(); //load the attendees from file 
         events = eventManager.getEvents(); //get the event
         cout << "List of Events:" << endl;
         for (const auto& event : events) {
             cout << event << endl;
         }
         cout << "Enter the name of the event you want to choose: ";
         cin >> chosenEvent;

         system("cls");

         cout << "Enter the name:";
         cin >> name;
         cout << "Enter the email id:";
         cin >> email;

         eventManager.addAttendee(chosenEvent, name, email); //add the attendee
         eventManager.saveAttendees();
         cout << "Back to menu(Y/N)";
         cin >> choice;
         switch (choice) {
         case 'Y':
             event_menu(); //back to event menu
             break;
         case 'N':
             break;
         }
         break;
     case 3:
         //Get the list of events
         system("cls");
         eventManager.loadAttendees(); //load the attendees from file 
         events = eventManager.getEvents();
         cout << "List of Events:" << endl;
         for (const auto& event : events) {
             cout << event << endl;
         }
         cout << "Enter the name of the event you want to choose: ";
         cin >> chosenEvent;

         system("cls");
         // Display attendees for the chosen event
         eventManager.displayAttendees(chosenEvent); //dislpay the attendees for particular event
         cout << "Back to menu(Y/N)";
         cin >> choice;
         switch (choice) {
         case 'Y':
             event_menu(); //back to event menu
             break;
         case 'N':
             break;
         }
         break;
     case 4:
         system("cls");
         eventManager.loadAttendees(); //load the attendees from file 
         // Send emails for the upcoming event
         eventManager.sendEmailsForUpcomingEvent(); //send email to all the attendees for next upcoming event
         cout << "Back to menu(Y/N)";
         cin >> choice;
         switch (choice) {
         case 'Y':
             event_menu(); //back to event menu
             break;
         case 'N':
             break;
         }
         break;
     case 5:
         main_menu(); //main menu
         break;
     default:
         cout << "Please select valid option..";
         break;
     }
 }