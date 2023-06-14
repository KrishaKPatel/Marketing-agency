// 
// New For Phase 2
//
#ifndef GRAPH_H
#define GRAPH_H

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

vector<string> getCampaignNames(string filename); //get the campaign names
void main_menu(); //main menu

// 
// New For Phase 2
// structure of edge
//
struct Edge {
    string customerName;
    int rating;
};

// 
// New For Phase 2
// rating-graph class
class Rating_graph {

public:
    unordered_map<string, vector<Edge>> adjList;
    void loadfromfile(string filename); //load the data from file
    void addRatingToFile(string filename, string cname); //add the rating from graph to file
    void addEdge(const string& campaignName, const string& customerName, int rating); //add the edge
    void addCampaign(const string& campaignName); //add campaign
    void addCustomerRating(const string& campaignName, const string& customerName, int rating); //add the customer rating for campaign
    float getAverageRating(const string& campaignName); //get the average rating
};

void rating_menu(); //rating menu

#endif // GRAPH_H

