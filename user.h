#ifndef USER_H
#define USER_H
#include <iostream>
#include <set>
#include <vector>

class Post;
class Comment;

class User {
    private:
        int id;
        std::string name;
        int birthyr;
        int zipcode; 
        std::set<int>Friend;
        std::vector <Post*> messages_;
        std::vector<Post*> Collection;
        std::vector<Post*> ForWpost;

    public:
        //constructors
        User(){};
        User(int ID, std::string Name, int Birthyr, int Zipcode,  std::set<int> Friends):id(ID),name(Name), birthyr(Birthyr),zipcode(Zipcode),Friend(Friends){};
        ~User() {
            for (Post* post : messages_) {
            delete post;
            }
        }
        //accessor methods return the user’s name, their user ID, birth year, and zip code, and a reference to the set of friends
        
        // Pre: None
        // Post: Returns the ID of the user. 
        int getId() ;

        // Pre: None
        // Post: Returns the name of the user as a string.
        std::string getName() ; 

        // Pre: None
        // Post: Returns the birth year of the user.
        int getYear();

        // Pre: None
        // Post: Returns the zip code of the user.
        int getZip(); 

        // Pre: None
        // Post: Returns a reference to the set of friends.
        std::set<int>& getFriends();

        // Pre: friendID is not in the set of friends
        // Post: Adds the friend with the given ID to the set of friends.
        void addFriend(int friendID);
        
        // Pre: friendID is in the set of friends
        // Post: Removes the friend with the given ID from the set of friends.
        void deleteFriend(int friendID);

        //pre: the post object is properly initailized
        //post: add the post object to the vector messages_
        void addPost(Post* post);
        
        //pre:none
        //post: return the vector messages_ of the calling object
        std::vector<Post*> getPosts();

        //pre: User object is properly instantiated, and messages_ vector contains valid objects
        //post: return a a string consist of the concatenation of the most recent howMany posts. 
        //       If showOnlyPublic is true, only return the public posts, otherwise return both private and public posts
        std::string getPostsString(int howMany,bool showOnlyPublic);

        void AddCollection(Post* post);

        std::vector<Post*>GetCollection();

        std::vector<Post*>GetForPost(){
            return ForWpost;
        }

        void AddForPost(Post* post){
            ForWpost.push_back(post);
        }


        std::string getCollectionString();


};

#endif
