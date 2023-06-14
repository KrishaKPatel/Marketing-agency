#ifndef SOCIAL_MEDIA_POST_H
#define SOCIAL_MEDIA_POST_H

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

void main_menu(); //main menu

//define SocialMediaPost class
class SocialMediaPost {
private:
    string postText;
    string platform;
    string status;

public:
    // constructor
    SocialMediaPost(string postText, string platform) {
        this->postText = postText;
        this->platform = platform;
        this->status = "Pending"; // default status
    }

    // getters
    string getPostText();
    string getPlatform();
    string getStatus();

    // setters
    void setStatus(string status);
};

//class SocialMedia class
class SocialMedia {

    stack<SocialMediaPost> postStack; //define stack

public:

    void readPosts(stack<SocialMediaPost>& postStack, const string& filename); //read the post from file into stack
    void writePosts(stack<SocialMediaPost>& postStack, const string& filename); //write the post into file
    void publishTopPost(stack<SocialMediaPost>& postStack); //publish the post
    
};

void social_menu(); //social media menu

#endif // SOCIAL_MEDIA_POST_H

