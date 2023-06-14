// 
// New For Phase 2
//
#include "Rating.h" //header file
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

// 
// New For Phase 2
// get the campaign name
//
vector< string> getCampaignNames(string filename) {
    vector< string> campaignNames;
    ifstream file(filename);
    if (file) {
        string line;
        while (getline(file, line)) {
            string cname, campname, due, budget, audience, channel;
            stringstream ss(line);
            // Read the name, email, and phone from the line
            getline(ss, cname, ',');
            getline(ss, campname, ',');
            getline(ss, due, ',');
            getline(ss, budget, ',');
            getline(ss, audience, ',');
            getline(ss, channel, ',');
            campaignNames.push_back(campname);
        }
    }
    else {
        cerr << "Error: Unable to open file '" << filename << "'." << endl;
    }
    return campaignNames;
}

// 
// New For Phase 2
// load the data from file 
//
void Rating_graph::loadfromfile(string filename) {
    ifstream file(filename);
    if (file) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string campaignName, customerName, ratingStr;
            getline(iss, campaignName, ',');
            getline(iss, customerName, ',');
            getline(iss, ratingStr, ',');

            int rating = stoi(ratingStr);

            addCustomerRating(campaignName, customerName, rating); //add the customer rating
        }
    }
}

// 
// New For Phase 2
//add a rating from the user and store it in the file
//
void Rating_graph::addRatingToFile(string filename, string cname) {
    ofstream file(filename, ios::app); // Open the file in append mode
    if (file) {
        string customerName;
        float rating;

        cout << "Enter Customer Name: ";
        cin >> customerName;

        cout << "Enter Rating(0-5): ";
        cin >> rating;
        cin.ignore(); // Ignore the newline character

        file << cname << "," << customerName << "," << setprecision(3) << rating << endl;

        cout << "Rating added successfully!" << endl;
    }
    else {
        cout << "Error opening the file." << endl;
    }
}

// 
// New For Phase 2
// add the edge
//
void Rating_graph::addEdge(const string& campaignName, const string& customerName, int rating) {
    adjList[campaignName].push_back(Edge{ customerName, rating });
}

// 
// New For Phase 2
// add the campaign
//
void Rating_graph::addCampaign(const string& campaignName) {
    adjList[campaignName];
}

// 
// New For Phase 2
// add customer rating 
//
void Rating_graph::addCustomerRating(const string& campaignName, const string& customerName, int rating) {
    addCampaign(campaignName); //add campaign
    addEdge(campaignName, customerName, rating); //add edge
}

// 
// New For Phase 2
//get the average of the rating of the campaign
//
float Rating_graph::getAverageRating(const string& campaignName) {
    float sum = 0.0;
    int count = 0;
    float ans;
    for (auto& edge : adjList[campaignName]) {
        sum += edge.rating;
        count++;
    }
    ans = sum / count;
    return count > 0 ? ans : 0.0;
}

// 
// New For Phase 2
// rating menu
//
void rating_menu() {
    system("cls");
    Rating_graph graph;
    int ch;
    string campaignName;
    char ch1;
    vector< string> campaignNames = getCampaignNames("campaign.txt");

     cout << "Campaign Names:" <<  endl;
    for (size_t i = 0; i < campaignNames.size(); ++i) {
         cout << i + 1 << ". " << campaignNames[i] <<  endl;
    }

     cout << "Choose a campaign number: ";
    int campaignNumber;
     cin >> campaignNumber;
    system("cls");
    cout << "1. Add the rating" << endl;
    cout << "2. Calculate the average rating" << endl;
    cout << "3. Display the average rating of all campaigns" << endl;
    cout << "4. Back to main menu" << endl;
    cout << "Select any one option:";
    cin >> ch;
    switch (ch) {
    case 1:
        system("cls");
        if (campaignNumber >= 1 && campaignNumber <= campaignNames.size()) {
            string campaignName = campaignNames[campaignNumber - 1];
            graph.addRatingToFile("campaign_ratings.csv", campaignName); //add the rating to file
        }
        else {
             cerr << "Error: Invalid campaign number." <<  endl;
        }
        cout << "Back to the menu(Y/N): "; 
        cin >> ch1;
        switch (ch1) {
        case 'Y':
            rating_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
        break;
    case 2:
        system("cls");
        graph.loadfromfile("campaign_ratings.csv"); //load the data from the file
        if (campaignNumber >= 1 && campaignNumber <= campaignNames.size()) {
            string campaignName = campaignNames[campaignNumber - 1];
            cout << "Average rating of " << campaignName << " is : " << setprecision(3) << graph.getAverageRating(campaignName) <<endl; //get the average of the rating
        }
        cout << "Back to the menu(Y/N): ";
        cin >> ch1;
        switch (ch1) {
        case 'Y':
            rating_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
        break;
    case 3:
        system("cls");
        graph.loadfromfile("campaign_ratings.csv"); //load the data from the file
        cout << "Campaign Name\tAverage Rating\n";
        for (auto& campaign : graph.adjList) {
            cout << campaign.first << "\t\t" << setprecision(3) << graph.getAverageRating(campaign.first) << endl;
        }
        cout << "Back to the menu(Y/N): ";
        cin >> ch1;
        switch (ch1) {
        case 'Y':
            rating_menu(); //back to customer menu
            break;
        case 'N':
            break;
        }
    case 4:
        main_menu(); //main menu
        break;
    default:
        cout << "Please select valid option.";
        break;
    }

}