#include "post.h"
#include "comment.h"
#include <iostream>

std::string Post::toString(){
    std::string a = message_;
    return a;
}


int Post::getMessageId(){
    return messageId_;
}

int Post::getOwnerId(){
    return ownerId_;
}
std::string Post::getMessage(){
    return message_;
}
int Post::getLikes(){
    return likes_;
}

std::string Post::getAuthor(){
    return "";
}

 bool Post:: getIsPublic(){
    return true;
 }
 std::vector<Comment*> Post:: getComments(){
     return Comments;
 }

 void Post::addComment(Comment* c){
     Comments.push_back(c);
 }
 std::string Post::getCommentsString(){
     std::string s = "";
     for(auto c:Comments){
         s +=c->Comment::toString();
     }
     return s;
 }

 void Post::AddPeopleForwarded(std::string name){
     peopleForwarded.push_back(name);
     numForwarded++;
 }

 void Post::AddPostToCollection(std::string name){
     peopleAddToCollection.push_back(name);
     numCollected++;
 }

 std::string Post::ListOfPeopleReacted(){
     std::string comm ="People who commented:\n";
     std::string forw = "People who forwarded:\n";
     std::string coll = "People who added to collection:\n";
     for(auto i: Comments){
         comm += i->getCommenter()->getName() + "\n";
     }
     for(auto j: peopleForwarded){
         forw += j + "\n";
     }
     for(auto k:peopleAddToCollection){
         coll += k;
     }
     std::string s = comm+forw+coll;
     return s;
 }
 void Post::AddLikes(){
     likes_++;
 }

 std::string IncomingPost::toString(){
        std::string pri;
        if(isPublic_){
            pri = "";
        }else{
            pri = " (private) ";
        }
        std::string a = author_+" wrote"+pri+":"+Post::toString();
        return a;
    }
std::string IncomingPost::getAuthor(){
        return author_;
    }
bool IncomingPost::getIsPublic(){
        return isPublic_;
}
