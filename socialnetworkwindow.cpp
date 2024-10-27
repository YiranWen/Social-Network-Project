#include "socialnetworkwindow.h"
#include "ui_socialnetworkwindow.h"
#include "PostDialog.h"
#include <string>
#include <QVector>
#include <vector>
#include <iostream>

SocialNetworkWindow::SocialNetworkWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SocialNetworkWindow)
{

    ui->setupUi(this);
    connect(ui->LogInPushButton, &QPushButton::clicked, this, &SocialNetworkWindow::LogInButtonClicked);
    connect(ui->ListFriendsTable,&QTableWidget::cellClicked,this,&SocialNetworkWindow::FriendTableCellCliked);
    connect(ui->BackToOwnerButton,&QPushButton::clicked,this,&SocialNetworkWindow::BackToLoggedInUserPage);
    connect(ui->SuggestFriendTable,&QTableWidget::cellClicked,this,&SocialNetworkWindow::SuggFriendableCellCliked);
    connect(ui->AddFriendButton,&QPushButton::clicked,this,&SocialNetworkWindow::AddFriendButtonClicked);
    connect(ui->PostlistWidget,&QListWidget::itemClicked,this,&SocialNetworkWindow::PostListClicked);
    connect(ui->MoodAngry,&QPushButton::clicked,this,&SocialNetworkWindow::MoodAngry);
    connect(ui->MoodHappy,&QPushButton::clicked,this,&SocialNetworkWindow::MoodHappy);
    connect(ui->MoodBored,&QPushButton::clicked,this,&SocialNetworkWindow::MoodBored);
    connect(ui->MoodGoofy,&QPushButton::clicked,this,&SocialNetworkWindow::MoodGoofy);
    connect(ui->MoodSad,&QPushButton::clicked,this,&SocialNetworkWindow::MoodSad);
    connect(ui->MoodExcited,&QPushButton::clicked,this,&SocialNetworkWindow::MoodExcited);
    connect(ui->MoodTired,&QPushButton::clicked,this,&SocialNetworkWindow::MoodTired);


    network.readUsers("users.txt");
    network.readPosts("UsersPosts.txt");
    network.ReadComments("PostComments.txt");
    Display();

}



void SocialNetworkWindow::Display(){
    ui->ListFriendsTable->hide();
    ui->Profilepglabel->hide();
    ui->ListOfFriendLabel->hide();
    ui->BackToOwnerButton->hide();
    ui->SuggestFriendTable->hide();
    ui->FriendSuggLabel->hide();
    ui->AddFriendButton->hide();
    ui->SuccessAddLabel->hide();
    ui->PostlistWidget->hide();
    ui->ForWardPostlistWidget->hide();


    ui->numIncomPostLabel->hide();
    ui->NumForwPostLabel->hide();
    ui->NumOwnerPostlabel->hide();
    ui->MainPostLabel->hide();
    ui->MainPostLabel->setText("🔥 Post 🔥");
    ui->MyCollectionLabel->setText("🤩 My Post Collection 🤩");
    ui->MyCollectionLabel->hide();
    ui->CollectionlistWidget->hide();
    ui->SuccessAddLabel->setText("Successfully Added! 🥳");
    ui->FriendSuggLabel->setText("🥳 Friend Suggestions: 🥳 ");
    ui->Profilepglabel->setText("My Profile 😎");
    ui->ListOfFriendLabel->setText("👯 List of friends 👯");
    ui->AllForPostLabel->setText("🩷 Forwarded Posts 🩷");
    ui->AllForPostLabel->hide();

    ui->MPrompt->setText("Select Your Mood Today 👀👉 ");
    ui->MPrompt->hide();

    ui->MoodHappy->hide();
    ui->MoodAngry->hide();
    ui->MoodBored->hide();
    ui->MoodGoofy->hide();
    ui->MoodSad->hide();
    ui->MoodExcited->hide();
    ui->MoodTired->hide();

    ui->TodayMood->hide();

}

void SocialNetworkWindow::LogInButtonClicked(){
    std::string UserName = ui->LogInInputText->toPlainText().toStdString();
    if(network.findUserByName(UserName)==nullptr){
        ui->LogInLabel->setText("No matched user found, please enter again");
    }else{
        LoggedInUser = network.findUserByName(UserName);
        CurDisplayedUser = network.findUserByName(UserName);
        ui->LogInLabel->hide();
        ui->LogInInputText->hide();
        ui->LogInPushButton->hide();
        ProfilePage();
    }

}

void SocialNetworkWindow::ProfilePage(){
    ui->SuccessAddLabel->hide();
    ui->PostlistWidget->clear();

    //on login user's profile page
    if(LoggedInUser->getId() == CurDisplayedUser->getId()){
        ui->AddFriendButton->hide();
        int i = LoggedInUser->getPosts().size();
        ui->NumOwnerPostlabel->setText(QString::fromStdString(std::to_string((i))));
        //show post list
        int row = 0;
        int Incom = 0;
        int Owner = 0;
        for (int i = LoggedInUser->getPosts().size()-1; i>=0; i--){
            if(LoggedInUser->getPosts()[i]->getIsOwner()){
                Owner++;
            }else{
                Incom++;
            }
            QListWidgetItem *newItem = new QListWidgetItem;
            QString post = QString::fromStdString(LoggedInUser->getPosts()[i]->toString());
            newItem->setText(post);
            ui->PostlistWidget->insertItem(row++, post);
            std::cout<<LoggedInUser->getPosts()[i]->toString()<<std::endl;
        }
        ui->PostlistWidget->show();
        QString in = QString::fromStdString(std::to_string(Incom))+" Incoming Posts";
        QString own = QString::fromStdString(std::to_string(Owner)) + " Owner Posts";

        ui->numIncomPostLabel->setText(in);
        ui->NumOwnerPostlabel->setText(own);
        ui->numIncomPostLabel->show();
        ui->NumOwnerPostlabel->show();

        ui->FriendSuggLabel->show();

        ui->Profilepglabel->setText("🐰 My Profile Page 🐰");


        //show list of friend suggestions
        row = 0;
        int score = 0;
        std::vector<int>sugg = network.suggestFriends(CurDisplayedUser->getId(), score);
        ui->SuggestFriendTable->setRowCount(sugg.size());
        ui->SuggestFriendTable->setColumnCount(3);
        for(int i = 0;i<sugg.size();i++){
            QString UserName = QString::fromStdString(network.findUserByID(sugg[i])->getName());
            QTableWidgetItem *Friend = new QTableWidgetItem(UserName);
            QTableWidgetItem *add = new QTableWidgetItem("Add as a friend");
            QTableWidgetItem *addID = new QTableWidgetItem(QString::number((network.findUserByID(sugg[i])->getId())));
            ui->SuggestFriendTable->setItem(row,2,add);
            ui->SuggestFriendTable->setItem(row,0,Friend);
            ui->SuggestFriendTable->setItem(row,1,addID);
            row++;
        }
        ui->SuggestFriendTable->show();


        //show collection
        ui->MyCollectionLabel->show();
        row = 0;
        for(int i =0; i<LoggedInUser->GetCollection().size();i++){
            QString CollPost = QString::fromStdString(LoggedInUser->GetCollection()[i]->getMessage());
            ui->CollectionlistWidget->insertItem(row++, CollPost);
        }
        ui->CollectionlistWidget->show();
        int numForw = LoggedInUser->getPosts().size()-ui->PostlistWidget->count();
        QString numf = QString::fromStdString(std::to_string(numForw))+" Forwarded Posts";
        ui->NumForwPostLabel->setText(numf);
        ui->NumForwPostLabel->show();

        if(!isMoodSelected){
            ui->MPrompt->show();
            ui->MoodHappy->show();
            ui->MoodAngry->show();
            ui->MoodBored->show();
            ui->MoodGoofy->show();
            ui->MoodSad->show();
            ui->MoodExcited->show();
            ui->MoodTired->show();
        }else{
            ui->TodayMood->show();
        }

    //on other user's profile page
    }else{
        ui->AddFriendButton->show();
        ui->SuggestFriendTable->hide();
        ui->FriendSuggLabel->hide();
        ui->BackToOwnerButton->show();
        std::string ProfileUserName = "🐰 "+ CurDisplayedUser->getName()+"'s Profile 🐰";
        ui->Profilepglabel->setText(QString::fromStdString(ProfileUserName));
        int row = 0;
        int Incom = 0;
        int Owner = 0;
        for (int i = CurDisplayedUser->getPosts().size()-1; i>=0; i--){
            if(CurDisplayedUser->getPosts().size()!=0){
                if(CurDisplayedUser->getPosts()[i]->getIsOwner()){
                    Owner++;
                }else{
                    Incom++;
                }
                }
            if(CurDisplayedUser->getPosts()[i]->getIsPublic()){
                QString post = QString::fromStdString(CurDisplayedUser->getPosts()[i]->toString());
                QListWidgetItem *newItem = new QListWidgetItem;
                newItem->setText(post);
                ui->PostlistWidget->insertItem(row++, newItem);
            }
            }
        QString in = QString::fromStdString(std::to_string(Incom))+" Incoming Posts";
        QString own = QString::fromStdString(std::to_string(Owner)) + " Owner Posts";
        ui->numIncomPostLabel->setText(in);
        ui->NumOwnerPostlabel->setText(own);
        ui->numIncomPostLabel->show();
        ui->NumOwnerPostlabel->show();
        ui->TodayMood->hide();

    }
    ui->Profilepglabel->show();
    ui->ListOfFriendLabel->show();
    ui->ListFriendsTable->setRowCount(CurDisplayedUser->getFriends().size());
    ui->ListFriendsTable->setColumnCount(2);
    int row = 0;

    //show friendlist
    QSet <int> FriendList (CurDisplayedUser->getFriends().begin(),CurDisplayedUser->getFriends().end());
    for(auto i:FriendList){
        QString FriendName = QString::fromStdString(network.findUserByID(i)->getName());
        QTableWidgetItem *Friend = new QTableWidgetItem(FriendName);
        QTableWidgetItem *addID = new QTableWidgetItem(QString::number(i));
        ui->ListFriendsTable->setItem(row,0,Friend);
        ui->ListFriendsTable->setItem(row,1,addID);
        row++;
    }
    ui->ListFriendsTable->show();

    //show ForwardedPosts
    for (int i = 0;i<CurDisplayedUser->GetForPost().size();i++){
        QListWidgetItem *newItem = new QListWidgetItem;
        QString post = QString::fromStdString(CurDisplayedUser->GetForPost()[i]->toString());
        newItem->setText(post);
        ui->ForWardPostlistWidget->insertItem(row++, post);
    }
    ui->ForWardPostlistWidget->show();
    QString c = QString::fromStdString(std::to_string(CurDisplayedUser->GetForPost().size())) + " Forwarded Posts";
    ui->NumForwPostLabel->setText(c);

    ui->MainPostLabel->show();
    ui->AllForPostLabel->show();

}


 void SocialNetworkWindow::SuggFriendableCellCliked(int row, int column){
     QTableWidgetItem *newFriend = ui->SuggestFriendTable->item(row,column-2);
     std::string userName = newFriend->text().toStdString();
     network.addConnection(userName,LoggedInUser->getName());
     ProfilePage();
     ui->SuccessAddLabel->show();
     network.writeUsers("users.txt");

 }

void SocialNetworkWindow::FriendTableCellCliked(int row, int column){
    QTableWidgetItem *user = ui->ListFriendsTable->item(row,column);
    std::string userName = user->text().toStdString();
    CurDisplayedUser = network.findUserByName(userName);
    ProfilePage();
}

void SocialNetworkWindow::BackToLoggedInUserPage(){
    CurDisplayedUser = LoggedInUser;
    ProfilePage();
}

void SocialNetworkWindow::AddFriendButtonClicked(){
    network.addConnection(CurDisplayedUser->getName(),LoggedInUser->getName());
    ui->SuccessAddLabel->show();
    network.writeUsers("users.txt");
}

void SocialNetworkWindow::PostListClicked(QListWidgetItem* item){
    post = network.FindPostHelper(item->text().toStdString());
    SocialNetworkPost dialog(this);
    dialog.SetUp(LoggedInUser,CurDisplayedUser,post);
    dialog.SetPostText(item->text());
    dialog.setUpPost(post);
    dialog.SetCommentTable(post);
    dialog.exec();

}

    void SocialNetworkWindow:: MoodHappy(){
        ui->TodayMood->setText("Happy 😃");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow:: MoodAngry(){
        ui->TodayMood->setText("Bored 🥱");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow::MoodBored(){
        ui->TodayMood->setText("Angry 😡");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow::MoodGoofy(){
        ui->TodayMood->setText("Goofy 😜");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow::MoodSad(){
        ui->TodayMood->setText("Sad😢");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow::MoodExcited(){
        ui->TodayMood->setText("Excited 🥳");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;

    }
    void SocialNetworkWindow::MoodTired(){
        ui->TodayMood->setText("Tired 😩");
        ui->TodayMood->show();
        ui->MPrompt->hide();
        ui->MoodHappy->hide();
        ui->MoodAngry->hide();
        ui->MoodBored->hide();
        ui->MoodGoofy->hide();
        ui->MoodSad->hide();
        ui->MoodExcited->hide();
        ui->MoodTired->hide();
        isMoodSelected = true;
    }
SocialNetworkWindow::~SocialNetworkWindow()
{
    network.WriteComments("PostComments.txt");
    delete ui;
}
