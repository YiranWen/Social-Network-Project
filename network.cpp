#include "network.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <iterator>
#include <stack>


Network::Network(){}
Network::~Network(){
    for(auto user: users){
        delete user;
    }
}

User* Network::getUser(int ID){
    for(auto user:users){
        if(user->getId()==ID){
            return user;
        }
    }
    return nullptr;
}

void Network::addUser (User* user){
    users.push_back(user);
}

int Network::addConnection (std::string name1, std::string name2){
   for(auto user1: users){
    if(user1->getName()==name1){
        for(auto user2:users){
            if(user2->getName()==name2){
                user1->addFriend(user2->getId());
                user2->addFriend(user1->getId());
                return 0;
            }
        }
    }
   }
   return -1;
}

int Network::deleteConnection (std::string name1, std::string name2){
    for(auto user1: users){
    if(user1->getName()==name1){
        for(auto user2:users){
            if(user2->getName()==name2){
                user1->deleteFriend(user2->getId());
                user2->deleteFriend(user1->getId());
                return 0;
            }
        }
    }
   }
   return -1;
}

int Network::getId (std::string userName){
    for(auto user: users){    
        if(userName == user->getName()){
            return user->getId();
        }
    }
    return -1;
}
int Network::numUsers(){
    return users.size();
}
int Network::readUsers(char* filename){
    std::ifstream input(filename);
    if(input.fail()){
        std::cout<<"Failed\n";
        return -1;
	}

    int ID, birthyear, zipcode;
    std::string username, friends, line, sum;
    std::getline(input, sum);

    // Read user information from the file line by line
    while(getline(input,line)){
        int ID = std::stoi(line);
        getline(input,line);
        std::stringstream N(line);
        std::string last, first, name;
        N>>first;
        N>>last;
        name = first+" "+last;
        getline(input,line);
        int birthyear = std::stoi(line);
        getline(input,line);
        int zipcode = std::stoi(line);
        getline(input,line);
        std::istringstream ss(line);
        std::set<int>FriendsID;
        int friendID;
        while(ss>>friendID){
            FriendsID.insert(friendID);
        }
        User* user = new User(ID,name,birthyear,zipcode,FriendsID);
        this->addUser(user);
    }
    input.close();
    return 0;

}
int Network::writeUsers(char* filename) {
    std::ofstream output;
    output.open(filename);
    if (output.fail()) {
        return -1;
    }

    output << users.size() << std::endl;
    
    // Iterate over the users and write their information to the file
    for (auto i = users.begin(); i != users.end(); i++) {
        std::string a = "";

        // Iterate over the friends of the current user and concatenate them into a string
        for (auto j = (*i)->getFriends().begin(); j != (*i)->getFriends().end(); j++) {
            a += std::to_string(*j) + " ";
        }

        // Write user details to the file in a formatted way
        output << std::to_string((*i)->getId()) << "\n\t" << (*i)->getName() << "\n\t"
               << std::to_string((*i)->getYear()) << "\n\t" << std::to_string((*i)->getZip())
               << "\n\t" << a << std::endl;
    }

    output.close();
    return 0;
}


void Network::printUsers() const {
    for (const auto& user : users) {
        std::cout << user->getId() << " " << user->getName() << " " << user->getZip() << std::endl;
    }
}

//helper function
User* Network::findUserByName(std::string  name){
    for (User* user : users) {
        if (user->getName() == name) {
            return user;
        }
    }
    return nullptr;
}

//helper function
User* Network::findUserByID(int ID){
    for (User* user : users) {
        if (user->getId() == ID) {
            return user;
        }
    }
    return nullptr;
}

std::vector<int> Network::shortestPath(int from, int to){
    std::vector<int>UserID;
    std::queue<int>q;
    std::vector<int>prev(numUsers(),-1);
    std::vector<bool>visted(numUsers(),0);
    visted[from]=true;
    q.push(from); 
    while(q.size()>0){
        int cur = q.front();
        q.pop();
    User* curUser = findUserByID(cur);
    for(auto Friend:curUser->getFriends()){
        if(!visted[Friend]){
            q.push(Friend);
            prev[Friend]=cur;
            visted[Friend]=true;
        }
    }
    }
    int cur = to;
    while(cur!=-1){
        UserID.push_back(cur);
        cur=prev[cur];
    }
    reverse(UserID.begin(),UserID.end());
    return UserID;
}

std::vector<int> Network::distanceUser(int from, int& to, int distance){
    std::vector<int>UserID;
    auto it = std::find(users.begin(),users.end(),findUserByID(from));
    if(it==users.end()){
        to = -1;
        return UserID;
    }
    std::queue<int>q;
    std::vector<bool>visited (numUsers(),0);
    std::vector<int>prev(numUsers(),-1);
    std::vector<int>dis (numUsers(),-1);

    dis[from]=0;
    visited[from]=true;
    q.push(from);

    while(q.size()>0){
        int cur = q.front();
        q.pop();
        for(auto Friend:findUserByID(cur)->getFriends()){
            if(!visited[Friend]){
                prev[Friend]=cur;
                dis[Friend] = dis[cur]+1;
                visited[Friend]=true;
                q.push(Friend);
            }
        }
    }
    int cur = 0;
    for(auto i:dis){
        if(dis[i]==distance){
            cur = i;
        }
    }
    to = cur;
    while(cur!=-1){
            UserID.push_back(cur);
            cur=prev[cur];
        }
    reverse(UserID.begin(),UserID.end());
    return UserID;

}
//helper function of suggestFriends
int Network::shortestPathLength(int from, int to){
    std::queue<int>q;
    std::vector<bool>visited (numUsers(),0);
    std::vector<int>dis(numUsers(),-1);
    dis[from]=0;
    visited[from]=true;
    q.push(from);
    while(q.size()>0){
        int cur = q.front();
        q.pop();
        for(auto Friend:findUserByID(cur)->getFriends()){
            if(!visited[Friend]){
                dis[Friend]=dis[cur]+1;
                visited[Friend]=true;
                q.push(Friend);
            }
        }
    }    
    return dis[to];
}

//helper function of suggestFriends
int Network::NumCommonElements(std::set<int>a, std::set<int>b){
    std::set<int>v;
    std::set_intersection(std::begin(a),std::end(a),std::begin(b),std::end(b),std::inserter(v, v.begin())); //make set v to contain the common elements in a and b
    return v.size();
}

std::vector<int> Network::suggestFriends(int who, int& score){
    std::vector<int>output;
    std::vector<int>Friendscore(numUsers(),0);
    for(auto it:users){
        int cur = it->getId();
        //Only update the score for potential friends with distance 2 from the specified user who
        if(shortestPathLength(cur,who)==2){
            Friendscore[cur]=NumCommonElements(findUserByID(who)->getFriends(),findUserByID(cur)->getFriends());
        }
    }
    auto highestscore = *max_element(Friendscore.begin(),Friendscore.end());// get the highest score
    score = highestscore;
    //record the potential friends with the highest score to the output vector
    for(int i = 0;i<Friendscore.size();++i){
        if(Friendscore[i]==highestscore && highestscore!=0){
            output.push_back(i);
        }
    }
    return output;
}

//helper function DFS of groups()
std::vector<int> Network::DFS(int source, std::vector<bool>& visited){
    std::stack<int>s;
    std::vector<int>output;
    visited[source]=true;
    s.push(source);
    output.push_back(source);
    while(s.size()!=0){
        int cur = s.top();
        s.pop();
        for(int i:findUserByID(source)->getFriends()){
            if(!visited[i]){
                visited[i]=true;
                s.push(i);
                output.push_back(i);
            }
        }
    }
    return output;
}

std::vector<std::vector<int>>Network::groups(){
    std::vector<bool>visited(numUsers(),0);
    std::vector<std::vector<int>>output;
    for(auto i :users){
        if(!visited[i->getId()]){
            output.push_back(DFS(i->getId(),visited));
        }
    }
    return output;
}

void Network::addPost(int ownerId, std::string message, int likes, bool isIncoming, std::string authorName, bool isPublic){
    std::vector<Post*>AllPosts;
    for(auto user:users){
        for(auto post:user->getPosts()){
            AllPosts.push_back(post);
        }
    }
    int messageId = AllPosts.size();
    if(isIncoming){
        Post* post = new IncomingPost(messageId, ownerId, message, likes, isPublic, authorName);
        findUserByID(ownerId)->User::addPost(post);
    }else{
        Post* post = new Post(messageId, ownerId, message, likes);
        findUserByID(ownerId)->User::addPost(post);
    }
}

std::string Network::getPostsString(int ownerId, int howMany, bool showOnlyPublic){
    return findUserByID(ownerId)->User::getPostsString(howMany,showOnlyPublic);
}
   

int Network::readPosts(char* fname){
    std::ifstream input(fname);
    if(input.fail()){
        return -1;
	}

    std::string line, sumPosts;
    std::getline(input, sumPosts);

    while(getline(input,line)){
        int messageId = std::stoi(line);
        getline(input,line);
        std::string messageText = line;
        getline(input,line);
        int ownerId = std::stoi(line);
        getline(input,line);
        int likes = std::stoi(line);

        getline(input,line);
        if(line.empty()){
            getline(input,line);
            addPost(ownerId, messageText,likes,false,"", true);
        }else{
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::string ispublic = line;
            getline(input,line); 
            line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
            std::string authorName = line;
            bool isPublic;
            if(ispublic == ""||ispublic == "public"){
                isPublic = true;
            }else{
                isPublic = false;
            }
            addPost(ownerId, messageText,likes,true,authorName,isPublic);
         }
        }
    input.close();
    return 0;
}



int Network::writePosts(char* fname){
    std::ofstream output;
    output.open(fname);
    if (output.fail()) {
        return -1;
    }
    std::vector<Post*>AllPosts;
    for(auto user:users){
        for(auto post:user->getPosts()){
            AllPosts.push_back(post);
        }
    }

  
   std::sort(AllPosts.begin(), AllPosts.end(), []( Post* pa,  Post* pb) {
    return pb->getMessageId() > pa->getMessageId();
});
    output<<AllPosts.size()<<std::endl;
    for(auto i:AllPosts){
        output<<std::to_string(i->getMessageId())<<"\n\t"<<i->getMessage()<<"\n\t"<<std::to_string(i->getOwnerId())<<
        "\n\t"<<std::to_string(i->getLikes())<<"\n\t";
        if(i->getAuthor()!=""){
            if(i->getIsPublic()){
                output<<"public"<<"\n\t";
            }else{
                output<<"private"<<"\n\t";
            }
            output<<i->getAuthor()<<"\n";

        }else{
            output<<std::endl;
            output<<std::endl;
        }
    }
    output.close();
   return 0;
}


Post* Network::FindPostHelper(std::string s){
    for(User* i: users){
        for(Post* j:i->getPosts()){
            if(s.find(":")!=-1){
                std::string a = s.substr(s.find(":")+1);
                if(a==j->getMessage()){
                    return j;
                }
            }else{
                if(s==j->getMessage()){
                    return j;
                }
            }
        }
    }

}

int Network::ReadComments(char* filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        return -1;
    }

    std::string line;

    while (std::getline(file, line)) {
        Post* post = FindPostByID(std::stoi(line));
        getline(file,line);
        std::string Commenter = line;
        User* user = findUserByName(Commenter);
        getline(file,line);
        std::string content = line;
        post->addComment(new Comment(content,user));
    }


    file.close();
    return 0;
}



int Network::WriteComments(char* filename){
    std::ofstream file(filename);
    if (!file.is_open()) {
        return -1;
    }
    std::vector<Post*>AllPosts;
    for(auto user:users){
        for(auto post:user->getPosts()){
            AllPosts.push_back(post);
        }
    }
    for (auto post : AllPosts) {
        for (const auto comment : post->getComments()) {
            file << std::to_string(post->getMessageId()) <<"\n\t"<<comment->getCommenter()->getName() << "\n\t"<<
            comment->getContent() <<"\n";
        }
    }
    file.close();
    return 0;
}

Post* Network::FindPostByID(int id){
    for(User* i: users){
        for(Post* j:i->getPosts()){
            if(j->getMessageId() == id){
                return j;
            }
        }
    }

}
