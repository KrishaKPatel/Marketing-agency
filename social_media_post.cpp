#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "social_media_post.h" //header file
using namespace std;

string SocialMediaPost::getPostText() {
    return postText;
}

string SocialMediaPost::getPlatform() {
    return platform;
}

string SocialMediaPost::getStatus() {
    return status;
}

// setters
void SocialMediaPost::setStatus(string status) {
    this->status = status;
}

// read the social media posts from a file and push them onto a stack
void SocialMedia::readPosts(stack<SocialMediaPost>& postStack, const string& filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Error opening file: " << filename << endl;
    }
    string line;
    while (getline(infile, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        string postText = line.substr(0, pos1 - 1);
        string platform = line.substr(pos1 + 2, pos2 - pos1 - 2);
        string status = line.substr(pos2 + 2);
        SocialMediaPost post(postText, platform);
        post.setStatus(status);
        postStack.push(post);
    }
    infile.close();
}

// save the social media posts from a stack to a file
void SocialMedia::writePosts(stack<SocialMediaPost>& postStack, const string& filename) {
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }
    stack<SocialMediaPost> tempStack;
    while (!postStack.empty()) {
        SocialMediaPost post = postStack.top();
        tempStack.push(post);
        postStack.pop();
    }
    while (!tempStack.empty()) {
        SocialMediaPost post = tempStack.top();
        outfile << post.getPostText() << " | " << post.getPlatform() << " | " << post.getStatus() << endl;
        postStack.push(post);
        tempStack.pop();
    }
    outfile.close();
}

// publish the top social media post
void SocialMedia::publishTopPost(stack<SocialMediaPost>& postStack) {
    if (postStack.empty()) {
        cout << "No posts to publish." << endl;
        return;
    }
    SocialMediaPost post = postStack.top();
    postStack.pop();
    post.setStatus("Published");
    cout << "Publishing post: " << post.getPostText() << endl;
    
}

// social media menu
void social_menu() {
    system("cls");
    int ch;
    stack<SocialMediaPost> postStack; //define stack
    stack<SocialMediaPost> tempStack;
    SocialMedia sm;
    string name;
    string plat;
    bool found = false;
    char choice;
    cout << "Social Media Management" << endl;
    cout << "----------------------------"<<endl;
    cout << "1. Add the post" << endl;
    cout << "2. Publish the post" << endl;
    cout << "3. Back to main menu" << endl << endl;
    cout << "Select one option: ";
    cin >> ch;
    switch (ch) {
    case 1:
        system("cls");
        sm.readPosts(postStack, "social.txt");
        cout << "Enter Post :";
        getline(cin>>ws, name,'!');
        cout << "Enter the platform name :";
        cin >> plat;
        ;
       
        tempStack = postStack;  // check if post with same name already exists
        while (!tempStack.empty()) {
            if (tempStack.top().getPostText() == name) {
                found = true;
                break;
            }
            tempStack.pop();
        }
        if (found) {
            cout << "Post with same name already exists." << endl;
        }
        else {
            
            postStack.push(SocialMediaPost(name, plat)); // add the new post to the stack and save to file
            sm.writePosts(postStack, "social.txt");
            cout << "New Post successfully added!" << endl;
        }
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            social_menu(); //back to social menu
            break;
        case 'N':
            break;
        }
        break;
    case 2:
        system("cls");
        sm.readPosts(postStack, "social.txt"); 
        sm.publishTopPost(postStack); //publish the top post of the stack
        sm.writePosts(postStack, "social.txt");
        cout << "Back to menu(Y/N)";
        cin >> choice;
        switch (choice) {
        case 'Y':
            social_menu(); //back to social menu
            break;
        case 'N':
            break;
        }
        break;
    case 3:
        main_menu(); //main menu
        break;
    default:
        cout << "please select valid option..";
        break;
    }
}
  
