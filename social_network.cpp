#include <iostream>
#include "user.h"
#include "network.h"
#include "post.h"
#include <sstream>


using namespace std;

int main(int argc, char *argv[]){
    Network socialnetwork;
    socialnetwork.readUsers(argv[1]);
    socialnetwork.readPosts(argv[2]);
    int option;
        // Display menu
        cout<< "\nMenu Options:" << endl;
        cout<< "1. Add a user" << endl;
        cout<< "2. Add friend connection" << endl;
        cout<< "3. Delete friend connection" << endl;
        cout << "4. Print users" << endl;
        cout<< "5. Print friends" << endl;
        cout<< "6. Write to file" << endl;
        cout<< "7. Find shortest path between two users, and enter the users' names" << endl;
        cout<<"8. User at a given Distance"<<endl;
        cout<<"9. Get Friend Suggestions"<<endl;
        cout<<"10. Get groups"<<endl;
        cout<<"11. Get posts"<<endl;
        cout<<"12. Exit Program"<<endl;



        cout << "Choose an option (1-11) from the menu: ";
        cin >> option;
        cin.ignore();
        while (option>0&&option<12) {
            if(option == 1){
                string firstname, lastname,name;
                int birthYear, zipCode;
                cout << "Enter user's name, birthYear, and zipCode in one line : ";
                cin >> firstname >>lastname >>birthYear >> zipCode;
                set<int>friends;
                name = firstname + " "+lastname;
                int ID = socialnetwork.numUsers();
                socialnetwork.addUser(new User(ID, name, birthYear, zipCode, friends));
            }
             if(option == 2){
                string name1, name2, firstname1, firstname2, lastname1,lastname2;
                cout << "Enter the two user's name: ";
                cin>>firstname1>>lastname1>>firstname2>>lastname2;
                name1 = firstname1 +" "+ lastname1;
                name2 = firstname2 +" " + lastname2;
                if(socialnetwork.addConnection(name1,name2)==0){
                    cout<<"Successfully added friend connection!"<<endl;
                }else{
                    cout<<"Error: user not found"<<endl;
                }
            }
             if(option == 3){
                string name1, name2;
                cout << "Enter the two user's name: ";
                cin>>name1;
                cin>>name2;
                if(socialnetwork.deleteConnection(name1,name2)==0){
                    cout<<"Successfully deleted friend connection!"<<endl;
                }else{
                    cout<<"Error: user not found"<<endl;
                }
            }
             if(option == 4){
                socialnetwork.printUsers();
            }
             if(option == 5){
                string first,lastname,name;
                cout<<"Enter the user's name"<<endl;
                cin>>first>>lastname;
                name = first+" "+lastname;
                if(socialnetwork.findUserByName(name)==nullptr){
                    cout<<"Error: user not found"<<endl;
                    break;
                }else{
                    cout<<"Friends of "<<name<<":"<<endl;
                    User* user = socialnetwork.findUserByName(name);
                    for(const int friendsID:user->getFriends()){
                        User* frienduser = socialnetwork.findUserByID(friendsID);
                        cout << frienduser->getId() << " " << frienduser->getName() << std::endl;
                    }
                }
            }
             if(option == 6){
                string filename = "";
                char* fileName = new char[filename.length()+1];
                getline(cin,filename);
                for(int i = 0; i<filename.length();i++){
                    fileName[i]=filename[i];
                }
                cout<<"Enter file name"<<endl;
                socialnetwork.writeUsers(fileName);
                filename = "";
                delete[] fileName;
            }
            if(option == 7){
                string first1, last1, first2, last2, name1, name2;
                cout<<"Enter the users's name"<<endl;
                cin>>first1>>last1>>first2>>last2;
                name1 = first1+" "+last1;
                name2 = first2+" "+last2;
                if(name1==name2){
                    cout<<"Distance: 0"<<endl;
                    cout<<name1;
                    break;
               }else{
                int from = socialnetwork.findUserByName(name1)->getId();
                int to = socialnetwork.findUserByName(name2)->getId();
                cout<<from<<to;
                vector <int> shortestpath = socialnetwork.shortestPath(from,to);
                cout<<"Distance: "<<shortestpath.size()-1;
                for(auto userID:shortestpath){
                    cout<<socialnetwork.findUserByID(userID)->getName()<<"->";
                }
             }
            
            }
             if(option == 8){
                int UserFrom, UserTo, dis;
                string first, last, name;
                cout<<"Enter the user and distance"<<endl;
                cin>>first>>last>>dis;
                name = first+" "+last;
                UserFrom = socialnetwork.findUserByName(name)->getId();
                UserTo = 0;
                vector <int> path = socialnetwork.distanceUser(UserFrom,UserTo,dis);
                for(auto userID:path){
                    cout<<socialnetwork.findUserByID(userID)->getName()<<"->";
             }
             }
             if(option == 9){
                string first, last, name;
                int score = 0;
                cout<<"Enter the name of the user"<<endl;
                cin>>first>>last;
                name=first+" "+last;
                vector<int>sugfriend=socialnetwork.suggestFriends(socialnetwork.findUserByName(name)->getId(), score);
                if(sugfriend.empty()){
                    cout<<"None"<<endl;
                }else{
                 for(auto i:sugfriend){
                    cout<<socialnetwork.findUserByID(i)->getName()<<"Score: "<<score<<endl;
                }
             }
             }
            if(option == 10){
                vector<vector<int>>group=socialnetwork.groups();
                int n = 1;
                for(auto i:group){
                    cout<<"Set "<<n++<<"=>";
                    for(auto j:i){
                        cout<<socialnetwork.findUserByID(j)->getName()<<",";
                    }
                    cout<<endl;
                }
            }  
            if(option ==11){
                cout<<"Enter the user's name and number of posts your want to see"<<endl;
                int a;
                string first, last, name;
                cin>>first>>last>>a;
                name=first+" "+last;
                int ownerID = socialnetwork.findUserByName(name)->getId();
                cout<<socialnetwork.getPostsString(ownerID,a,false);
            }
        cout<< "\nMenu Options:" << endl;
        cout<< "1. Add a user" << endl;
        cout<< "2. Add friend connection" << endl;
        cout<< "3. Delete friend connection" << endl;
        cout << "4. Print users" << endl;
        cout<< "5. Print friends" << endl;
        cout<< "6. Write to file" << endl;
        cout<< "7. Find shortest path between two users, and enter the users' names" << endl;
        cout<<"8. User at a given Distance"<<endl;
        cout<<"9. Exit Program"<<endl;
        cout<<"10. Get groups"<<endl;
        cout<<"11. Get posts"<<endl;
        cout<<"12. Exit Program"<<endl;

        cout << "Choose an option (1-7) from the menu: ";
        cin >> option;
        cin.ignore();
        
        }
    return 0;   
}


