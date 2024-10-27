#include "user.h"
#include "post.h"
#include <iostream>
#include <set>


int User::getId() { 
    return id;
}

 std::string User::getName() {
    return name;
}

int User::getYear(){
    return birthyr;
}

int User::getZip(){
    return zipcode;
}

std::set<int>& User::getFriends(){
    return Friend;
}

void User::addFriend(int friendID){
    if(Friend.find(friendID)!=Friend.end()){
        return;
    }
    Friend.insert(friendID);
}

void User::deleteFriend(int friendID){
    if(Friend.find(friendID)!=Friend.end()){
    Friend.erase(friendID);
    }
    return;
}


void User::addPost(Post* post){
    messages_.push_back(post);
}

std::vector<Post*> User::getPosts(){
    return messages_;
}

std::string User::getPostsString(int howMany,bool showOnlyPublic){
    std::string output = "";
    if(howMany<messages_.size()){
        if(showOnlyPublic){
            for(auto i = messages_.end()-1;i>=messages_.end()-howMany;i--){
                if((*i)->getIsPublic()){
                    output+="\n"+(*i)->toString()+"\n";
                }
            }
        }else{
            for(auto i = messages_.end()-1;i>=messages_.end()-howMany;i--){     
                    output+="\n"+(*i)->toString()+"\n";
            }
        }
    }else{
        if(showOnlyPublic){
            for(auto i = messages_.end()-1;i>=messages_.begin();i--){
                if((*i)->getIsPublic()){
                    output+="\n"+(*i)->toString()+"\n";
                }
            }
        }else{
            for(auto i = messages_.end()-1;i>=messages_.begin();i--){     
                    output+="\n"+(*i)->toString()+"\n";
            }
        }
    }
    return output;
}

void User::AddCollection(Post *post){
    Collection.push_back(post);
}

std::vector<Post*> User::GetCollection(){
    return Collection;
}

std::string User::getCollectionString(){
    std::string s = "";
    for(auto c:Collection){
        s +=c->toString();
    }
    return s;
}






