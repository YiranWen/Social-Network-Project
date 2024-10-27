#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include "post.h"
#include "comment.h"
#include <iostream>
#include <vector>

class Network{
private:
std::vector<User *> users;

/*
pre: 'from' and 'to' are valid vertex IDs within the graph. 
post: Returns the length of the shortest path from 'from' to 'to' in terms of the number of edges. If no path exists, returns -1.
*/
int shortestPathLength(int from, int to);

/*
pre: none
post: Returns the number of common elements between sets 'a' and 'b'.
*/
int NumCommonElements(std::set<int> a, std::set<int>b);

/*
pre:'source' is valid vertex IDs within the graph.
post:return the connecting component of the giving source vertex
*/
std::vector<int> DFS(int source, std::vector<bool>& visited);


public:
//constructor 
Network();

//destructor
~Network();

/*
pre:none
post: takes in an ID and returns a pointser to the corresponding User
    If no user is found, return nullptr
*/
User* getUser(int ID);

/*
pre: user is a valid pointer to a User object
post: add a new User to the Network database
*/
void addUser (User* user);

/*
Pre: Users with names name1 and name2 exist in the Network.
Post: Friendship connection is added between users with names name1 and name2. Returns 0 on success, -1 if either user is not found.
*/
int addConnection (std::string name1, std::string name2);

/*
Pre: Users with names name1 and name2 exist in the Network.
Post: Friendship connection is deleted between users with names name1 and name2. Returns 0 on success, -1 if either user is not found.
*/
int deleteConnection (std::string name1, std::string name2);

/*
pre: user with the specified userName exists in the Network.
post: Returns the ID of the user with the specified name, or -1 if not found.*/
int getId (std::string userName);

/*
pre: None.
post: Returns the number of users in the Network.
*/
int numUsers();

/*
pre: The input file specified by filename is correctly formatted.
post: Users and their connections are read from the file and added to the Network. Returns 0 on success, -1 on failure.
*/
int readUsers(char* filename);

/*
pre: The output file specified by filename can be written.
post: Users and their connections are written to the file. Returns 0 on success, -1 on failure.
*/
int writeUsers (char* filename);

/*
pre: None.
post: Prints the ID, name, and zip code of each user in the Network.
*/
void printUsers() const;

/*
pre: None.
post: Returns a pointer to the User with the specified name, or nullptr if not found.
*/
User* findUserByName(std::string name);

/*
pre: None.
post: Returns a pointer to the User with the specified ID, or nullptr if not found.*/
User* findUserByID(int ID);

/*
pre:'from' and 'to' are valid vertex IDs within the graph.
post:Returns a vector representing the shortest path from 'from' to 'to' in terms of vertex IDs. If no path exists, the vector is empty.
*/
std::vector<int> shortestPath(int from, int to);

/*
pre: 'from' is a valid vertex ID within the graph. 
post: Returns a vector representing the path from 'from' to the vertex at a distance of 'distance'. If no such path exists, the vector is empty. 
*/
std::vector<int> distanceUser(int from, int& to, int distance);

/*
pre: 'who' is a valid vertex ID within the graph. 
post: Returns a vector of potential friends for the specified user ('who') and updates 'score' with the highest score among potential friends.
*/
std::vector<int>suggestFriends(int who, int& score);

/*
pre:none
post:return every connecting component in the social network graph
*/
std::vector<std::vector<int>>groups();

//pre: ownerId corresponds to a valid user
//post: add the post of the given ownerId to the corresponding user's messages_ vector. 
//      If it is an incoming post, add as an incoming object, otherwise add as a post object

void addPost(int ownerId, std::string messgae, int likes, bool isIncoming, std::string authorNmae, bool isPublic);

//pre: ownerId corresponds to a valid user
//post: Returns a formatted string containing posts based on specified parameters.
std::string getPostsString(int ownerId, int howMany, bool showOnlyPublic);


//pre: The input file specified by filename is correctly formatted.
//post: Posts and related information are read from the file and added to the Network. Returns 0 on success, -1 on failure.
int readPosts(char* fname);

//pre: The input file specified by filename is correctly formatted.
//post: Posts and related information are read from the file and added to the Network. Returns 0 on success, -1 on failure.
int writePosts(char* fname);

Post* FindPostHelper(std::string s);

Post* FindPostByID(int id);


int ReadComments(char* filename);

int WriteComments(char* filename);
};

#endif
