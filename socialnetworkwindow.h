#ifndef SOCIALNETWORKWINDOW_H
#define SOCIALNETWORKWINDOW_H
#include "network.h"
#include "post.h"
#include "user.h"
#include "PostDialog.h"
#include "comment.h"
#include <QMainWindow>
#include <QListWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class SocialNetworkWindow;
}
QT_END_NAMESPACE

class SocialNetworkWindow : public QMainWindow
{
    Q_OBJECT

public:
    SocialNetworkWindow(QWidget *parent = nullptr);
    ~SocialNetworkWindow();

    //pre:None
    //Post: If a user with the entered username is found, the logged-in and displayed users are set, and certain UI elements are hidden.
    //      The ProfilePage() function is then called.
    void LogInButtonClicked();

    //Pre: The logged-in and displayed users are set.
    //Post: The UI is updated based on whether the displayed user is the logged-in user or not.
    //      Friend suggestions, friend list, recent posts, and appropriate labels are displayed or hidden accordingly.
    void ProfilePage();

    //Pre: A cell in the friend list table is clicked.
    //Post: The displayed user is set to the selected friend, and the profile page is updated.
    void FriendTableCellCliked(int row, int column);

    //Pre: None
    //Post: The displayed user is set back to the logged-in user, and the profile page is updated.
    void BackToLoggedInUserPage();

    //Pre: A cell in the friend suggestion table is clicked.
    //Post: The selected friend is added to the user's connections, and the profile page is updated.
    //      The success label is displayed, and user data is written to the "users.txt" file.
    void SuggFriendableCellCliked (int row, int column);

    //Pre: None
    //Post: The displayed user is added to the logged-in user's connections.
    //      The success label is displayed, and user data is written to the "users.txt" file.
    void AddFriendButtonClicked();

    //Pre: None
    //Post: The specified UI elements are hidden, and the success label text is set to "Successfully Added!"
    void Display();

    void PostListClicked(QListWidgetItem* item);

    void MoodHappy();
    void MoodAngry();
    void MoodBored();
    void MoodGoofy();
    void MoodSad();
    void MoodExcited();
    void MoodTired();





private:
    Network network;
    User* LoggedInUser;
    User* CurDisplayedUser;
    Ui::SocialNetworkWindow *ui;
    Post* post;
    bool isMoodSelected = false;
};
#endif // SOCIALNETWORKWINDOW_H
