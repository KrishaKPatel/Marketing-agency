// 
// New For Phase 2
//
#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include <string>
#include <map>
#include <set>
using namespace std;

void main_menu(); //main menu

// 
// New For Phase 2
// eventmanager class
//
class EventManager {
public:
    EventManager(const  string& file);

    void loadAttendees(); //load the attendees from file to set
    void saveAttendees(); //save the attendees from set to file

    void addEvent(const  string& event); //add the event
    void addAttendee(const  string& event, const  string& name, const  string& email); //add attendees 
    void displayAttendees(const  string& event); //display the attendees
    void sendEmailsForUpcomingEvent(); //send email for next event to all attendees

     set< string> getEvents() const; //get the events

private:
     string fileName; //file name
     map< string,  set< pair< string,  string>>> events; //set for events
};
void event_menu();
#endif  // EVENT_MANAGER_H
