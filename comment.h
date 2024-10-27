#ifndef COMMENT_H
#define COMMENT_H
#include "user.h"
#include <string>


class Comment{
public:
    Comment();
    Comment(std::string Content, User* Commenter):content(Content),commenter(Commenter){}
    std::string getContent();
    User* getCommenter();
    std::string toString();
private:
    std::string content = "";
    User* commenter;
};

#endif // COMMENT_H
