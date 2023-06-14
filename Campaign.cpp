#include <iostream>
#include <fstream>
#include <string>
#include<sstream>
#include "Client.h" //client header file
#include "Campaign.h" //header file
using namespace std;

//get the campaign details from the user 
void CampaignManager::getCampaignDetailsFromUser(string sname) {
    CampaignManager man;
    Campaign campaign;
    int ch, ch1;
    cout << "Enter campaign name: ";
    cin>>campaign.name;
    cout << "Enter campaign due date(mm-dd-yyyy): ";
    cin>>campaign.due;
    cout << "Enter campaign budget: $ ";
    cin >> campaign.budget;

    cout << "Choose the target audience "<<endl;
    cout << "1. Demographic(based on age, gender, income, education level, occupation)" << endl;
    cout << "2. Psychographic(based on attitudes, values, interests, and lifestyle)" << endl;
    cout << "3. Geographic location(based on location such as country, region or city)" << endl;
    cout << "4. Consumer behavior(based on purchasing habits, buying cycle, and decision-making process)" << endl;
    cin >> ch;
    switch(ch) {
    case 1:
        campaign.audience = "Demographic";
        break;
    case 2:
        campaign.audience = "Psychographic";
        break;
    case 3:
        campaign.audience = "Geographic location";
        break;
    case 4:
        campaign.audience = "Consumer behavior";
        break;
    default:
        cout << "please choose valid option." << endl;
        break;
    }
    cout << "Choose the channel " << endl;
    cout << "1. Social Media" << endl;
    cout << "2. Email marketing" << endl;
    cout << "3. Traditional Advertising" << endl;
    cin >> ch1;
    switch (ch1) {
    case 1:
        campaign.channel = "Social Media";
        break;
    case 2:
        campaign.channel = "Email marketing";
        break;
    case 3:
        campaign.channel = "Traditional Advertising";
        break;
    default:
        cout << "please choose valid option." << endl;
        break;
    }
    man.writeToFile(campaign , "campaign.txt", sname); //save data into file
    cout << campaign.name << " is successfully added!" << endl;
}

//check the client is existing or not
bool CampaignManager::isClientStored(string name) {
    ifstream inFile("clients.txt");
    string line;
    while (getline(inFile, line)) {
        size_t pos = line.find(",");
        string storedName = line.substr(0, pos);
        line.erase(0, pos + 1);
        if (name == storedName) {
            inFile.close();
            return true;
        }
    }
    inFile.close();
    return false;
}

//save the data into the file
void CampaignManager::writeToFile(Campaign campaign, string filename, string sname) {
    ofstream outfile(filename,ios::out|ios::app);
    if (!outfile.is_open()) {
        cerr << "Error: could not open file " << filename << endl;
        return;
    }
    else {
            outfile << sname<<","<<campaign.name << "," << campaign.due << "," << campaign.budget <<","<< campaign.audience<<","<< campaign.channel << endl;
        
    }
    outfile.close();
}

//load the data from file to array
int CampaignManager::loadCampFromFile(string filename, string name) {
    string n, camp, d, b, a, ch;
    Campaign campaign;

    ifstream infile(filename);
    if (!infile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return 0;
    }
    if (infile.peek() == ifstream::traits_type::eof())
    {
        cout << "No data found." << endl;
    }
    else 
    {
        string line;
        while (getline(infile, line)) {
            string cname, campname, due, budget, audience, channel;
            stringstream ss(line);
            // Read the name, email, and phone from the line
            getline(ss, cname, ',');
            getline(ss, campname, ',');
            getline(ss, due, ',');
            getline(ss, budget, ',');
            getline(ss, audience, ',');
            getline(ss, channel, ',');
            campaign.client_name = cname;
            campaign.name = campname;
            campaign.due = due;
            campaign.budget = budget;
            campaign.audience = audience;
            campaign.channel = channel;

                CampaignManager::campaigns[CampaignManager::numCampaigns] = campaign;
                CampaignManager::numCampaigns++;
            
        }
    }

    infile.close();
   
   return numCampaigns;
}

//display the data
void CampaignManager::display(string cname) {
    for (int i = 0; i < numCampaigns; i++) {
        if (CampaignManager::campaigns[i].client_name == cname) {
            cout << "Client Name: " << CampaignManager::campaigns[i].client_name << endl;
            cout << "Campaign Name: " << CampaignManager::campaigns[i].name << endl;
            cout << "Due Date: " << CampaignManager::campaigns[i].due << endl;
            cout << "Budget: $ " << CampaignManager::campaigns[i].budget << endl;
            cout << "Target Audience: " << CampaignManager::campaigns[i].audience << endl;
            cout << "Channel: " << CampaignManager::campaigns[i].channel << endl;
            cout << "\n";
        }
    }
}


//update the campaign data by its name
void CampaignManager::update(string name) {
    Campaign campaign;
    int foundIndex = -1;
    int i = 0;
    bool found = false;
    
    while (i < numCampaigns) {
        if (CampaignManager::campaigns[i].name == name) {
            foundIndex = i;
            deletecamp(campaigns, name);
            system("cls");
            cout << "Enter new budget:";
            cin >> CampaignManager::campaigns[foundIndex].budget;
            campaign = CampaignManager::campaigns[foundIndex];
            writeToFile(campaign, "campaign.txt", campaign.client_name);
            found = true;
        }
        
        i++;
    }
    if (!found) {
        cout << "campaign name is not matched." << endl;
    }
    cout << "campaign detail is updated!" << endl;
}

//delete the campaign detail by name
void CampaignManager::deletecamp(Campaign campaigns[], string name) {
    Campaign campaign;
    bool found = false;
    for (int i = 0; i < numCampaigns; i++) {
        if (CampaignManager::campaigns[i].name == name) {
            found = true;
            for (int j = i; j < numCampaigns - 1; j++) {
                CampaignManager::campaigns[j] = CampaignManager::campaigns[j + 1];
            }
            numCampaigns--;
            break;
        }
    }
    if (found) {

        ofstream outfile("campaign.txt",ios::out|ios::trunc);
      
        for (int i = 0; i < numCampaigns; i++) {
            campaign = CampaignManager::campaigns[i];
            writeToFile(campaign, "campaign.txt", campaign.client_name);
            
        }
        outfile.close();
        
    }
    else {
        cout << "Campaign not found." << endl;
    }
    cout << "campaign is deleted!" << endl;
}

//campaign menu
void campaign_menu() {
    system("cls");
    string name;
    char choice;

    cout << "Enter Client Name: ";
    cin >> name;
    CampaignManager man;
    
    if (man.isClientStored(name)) {
        
        cam_sub_menu(name);
    }
    else {
        cout << "Client is not found." << endl;
        cout << "Go to client menu(Y|N): ";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu();
            break;
        case 'N':
            break;
        default:
            cout << "please choose valid option..";
            break;
        }
    }

}

//campaign sub menu
void cam_sub_menu(string cname) {
    system("cls");
    int ch1,res;
    char choice;
    string campname,delname;
    CampaignManager man1;
    Campaign campaigns[MAX_CAMPAIGNS]; 
    cout << "Campaign Management" << endl;
    cout << "-------------------------------------------------" << endl;
    cout << "1. Add the campaign detail" << endl;
    cout << "2. Display campaign for particular client" << endl;
    cout << "3. Update the campaign detail" << endl;
    cout << "4. Delete the campaign detail" << endl;
    cout << "5. Back to main menu" << endl << endl;
    cout << "Select one option: ";
    cin >> ch1;
    switch (ch1) {
    case 1:
        system("cls");
        res = man1.loadCampFromFile("campaign.txt", cname);
        if (res <= 10) { //preventing for overflow error
            man1.getCampaignDetailsFromUser(cname);
        }
        else {
           cout << "Sorry, you couldn't add the campaign for this client.\n";
        }
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            campaign_menu(); //back to campaign menu
            break;
        case 'N':
            break;
        }
        break;
    case 2:
        system("cls");
        res = man1.loadCampFromFile("campaign.txt", cname);
        man1.display(cname);
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            campaign_menu(); //back to campaign menu
            break;
        case 'N':
            break;
        }
        break;
    case 3:
        system("cls");
        cout << "Enter the campaign name for updating:";
        cin >> campname;
        res = man1.loadCampFromFile("campaign.txt", cname);
        man1.update(campname);
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            campaign_menu(); //back to campaign menu
            break;
        case 'N':
            break;
        }
        break;
    case 4:
        system("cls");
        cout << "Enter the campaign name for deleting:";
        cin >> delname;
        res = man1.loadCampFromFile("campaign.txt", cname);
        man1.deletecamp(campaigns ,delname);
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            campaign_menu(); //back to campaign menu
            break;
        case 'N':
            break;
        }
        break;
    case 5:
        main_menu(); //back to main menu
        break;
    default:
        cout << "please choice valid option.";
        break;
    }
}

//generating the total revenue of the client
void CampaignManager::totalrevenue(string name) {
    long double rev = 0;
    CampaignManager man;
    string num;
    for (int i = 0; i < numCampaigns ; i++)
    {
        if (CampaignManager::campaigns[i].client_name == name) {
            rev += stoi(CampaignManager::campaigns[i].budget);
            num = to_string(rev);
        }
        else {
            rev = 0;
            num = to_string(rev);
        }
    }
    cout << "Client Name: " << name << endl;
    cout << "Total Revenue Of The " << name << " is: $" << num << endl;
}

//call totalrevenue function and display the revenue of the client
void revenue() {
    system("cls");
    CampaignManager man;
    string name;
    int res;
    char choice,ch;
    cout << "Total Revenue Of The Client" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter the client name:";
    cin >> name;
    if (man.isClientStored(name)) {
        res = man.loadCampFromFile("campaign.txt", name);
        man.totalrevenue(name);
    }
    else {
        cout << "Client is not found." << endl;
        cout << "Go to client menu(Y|N): ";
        cin >> choice;
        switch (choice) {
        case 'Y':
            client_menu(); //back to client menu
            break;
        case 'N':
            break;
        default:
            cout << "please choose valid option..";
            break;
        }
    }
    cout << "Back to main menu(Y|N): "; 
    cin >> ch;
    switch (ch) {
    case 'Y':
        main_menu(); //back to main menu
        break;
    case 'N':
        break;
    default:
        cout << "Please select the valid option.." << endl;
        break;
    }
}
