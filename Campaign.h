#ifndef CAMPAIGN
#define CAMPAIGN
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
using namespace std;

void main_menu(); //main menu

const int MAX_CAMPAIGNS = 10; 

//define Campaign class
class Campaign {
public:
    string client_name;
    string name;
    string due;
    string budget;
    string audience;
    string channel;
};

//define CampaignManager class
class CampaignManager {
public:
    Campaign campaigns[MAX_CAMPAIGNS]; // array to store campaigns
    int numCampaigns; // number of campaigns in the array

    //constructor
    CampaignManager() {
        numCampaigns = 0;
    }

    void getCampaignDetailsFromUser(string name); //get the campaign detail from the user input
    bool isClientStored(string name); //checked that client is existed or not
    void writeToFile(Campaign campaign,string filename, string sname); //save the campaign data into file
    int loadCampFromFile(string filename, string cname); //load the campaign data from file to array
    void display(string cname); //display the campaigns data
    void update(string name); // update the campaign detail
    void deletecamp(Campaign campaigns[],string name); //delete the campaign by its name
    void totalrevenue(string name); //generate total revenue of the client
};

void campaign_menu(); //campaign main page
void cam_sub_menu(string cname); //campaign sub menu
void revenue(); //call totalrevenue function and display the revenue
#endif // !CAMPAIGN
