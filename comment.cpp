#include "comment.h"

std::string Comment::getContent(){
    return content;
}
User* Comment:: getCommenter(){
    return commenter;
}
std::string Comment::toString(){
    std::string s = content + " commented by: " + commenter->getName();
    return s;
}
