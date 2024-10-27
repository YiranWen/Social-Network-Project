#ifndef POST_H
#define POST_H
#include <iostream>
#include <vector>
#include <string>

class Comment;
class Post{
private:
    int messageId_ = 0;
    int ownerId_ = 0;
    std::string message_ = "";
    int likes_ = 0;
    std::vector<Comment*>Comments;
    int numForwarded = 0;
    std::vector<std::string> peopleForwarded;
    int numCollected = 0;
    std::vector<std::string> peopleAddToCollection;
public:
    //constructors
    Post(){}
    Post(int messageId, int ownerId, std::string message, int likes): messageId_(messageId), ownerId_(ownerId), message_(message), likes_(likes) {}
    
    //pre:none
    //post: return a string containing message and like numbers of the the corresponding user
    virtual std::string toString();

    //pre:none
    //none: return messageId
    int getMessageId();

    //pre:none
    //none: return owner ID
    int getOwnerId();

    //pre:none
    //none: return message
    std::string getMessage();

    //pre:none
    //none: return likes number
    int getLikes();

    //pre:none
    //none: return empty string
    virtual std::string getAuthor();

    //pre:none
    //none: return true by default
    virtual bool getIsPublic();

    std::vector<Comment*> getComments();

    void addComment(Comment* c);

    std::string getCommentsString();

    void AddPeopleForwarded(std::string name);

    void AddPostToCollection(std::string name);

    std::vector <std::string> GetpeopleForwarded(){
        return peopleForwarded;
    }
    std::vector<std::string> GetpeopleAddToCollection(){
        return peopleAddToCollection;
    }


    std::string ListOfPeopleReacted();


    void AddLikes();

    virtual bool getIsOwner(){
        return true;
    }
    int getNumForwarded(){
        return numForwarded;
    }
    int getNumCollected(){
        return numCollected;
    }
};

class IncomingPost:public Post{
    private:
        std::string author_;
        bool isPublic_;
    public:
    //constructors
    IncomingPost(){}
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author)
    : Post(messageId,ownerId,message,likes), isPublic_(isPublic),author_(author){}
    
    ////pre:none
    //post: returning the content containing the author name, post content, and privacy status
    std::string toString();

    //pre:none
    //none: return author name
    std::string getAuthor();

    //pre:none
    //none: return true if is public, false if is private
    bool getIsPublic();

    bool getIsOwner(){
        return false;
    }

};

#endif
