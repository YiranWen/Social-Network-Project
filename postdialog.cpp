#include "PostDialog.h"
#include "ui_postdialog.h"

SocialNetworkPost::SocialNetworkPost(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SocialNetworkPost)
{
    ui->setupUi(this);
    connect(ui->CommentButton,&QPushButton::clicked,this,&SocialNetworkPost::CommentButtonClicked);
    connect(ui->AddColButton,&QPushButton::clicked,this,&SocialNetworkPost::AddColButtonClicked);
    connect(ui->LikeButton,&QPushButton::clicked,this,&SocialNetworkPost::LikeButtonClicked);
    connect(ui->ForwardButton,&QPushButton::clicked,this,&SocialNetworkPost::ForwardButtonCicked);
    connect(ui->EnterComButton,&QPushButton::clicked,this,&SocialNetworkPost::EnterCommentButtonClicked);

    ui->CommenEditor->hide();
    ui->EnterComButton->hide();
    ui->CommenPromptlable->hide();

    ui->ComtLabel->setText(" 💬 Comments 💬");
    ui->ForLabel->setText("💌 People Who Forwarded 💌");
    ui->AddColLabel->setText(" 🤩 People Who Added to Collection 🤩");
}

void SocialNetworkPost::SetCommentTable(Post* post){
    network.ReadComments("PostComments.txt");
    int row = 0;
    std::vector<Comment*>com = post->getComments();
    ui->CommentTable->setRowCount(com.size());
    ui->CommentTable->setColumnCount(2);
    for (Comment* i:com){
        QString UserName = QString::fromStdString(i->getCommenter()->getName());
        QString comments = QString::fromStdString(i->getContent());
        QTableWidgetItem *user = new QTableWidgetItem(UserName);
        QTableWidgetItem *Comments = new QTableWidgetItem(comments);
        ui->CommentTable->setItem(row,0,user);
        ui->CommentTable->setItem(row,1,Comments);
        row++;
    }
}

void SocialNetworkPost::setUpPost(Post* newPost) {
    post = newPost;
    if (post) {
        int likes = post->getLikes();
        QString c = "👍🏻 by " + QString::number(likes) + " people";
        ui->Numlike->setText(c);
    }

}

SocialNetworkPost::~SocialNetworkPost()
{
    network.WriteComments("PostComments.txt");
    delete ui;
}

void SocialNetworkPost::SetPostText(QString text){
    ui->DisplayPostLabel->setText(text);
}

void SocialNetworkPost::CommentButtonClicked(){

    ui->CommentButton->hide();
    ui->AddColButton->hide();
    ui->DisplayPostLabel->hide();
    ui->ForwardButton->hide();
    ui->ForwardlistWidget->hide();

    ui->LikeButton->hide();
    ui->CommentTable->hide();
    ui->pplAddCoLlistWidget->hide();

    ui->ComtLabel->hide();
    ui->ForLabel->hide();
    ui->AddColLabel->hide();

    ui->Numlike->hide();

    ui->CommenEditor->show();
    ui->EnterComButton->show();
    ui->CommenPromptlable->show();

}

void SocialNetworkPost::EnterCommentButtonClicked(){

    std::string content = ui->CommenEditor->toPlainText().toStdString();
    Comment *comment = new Comment(content,LoggedInUser);
    post->addComment(comment);

    network.ReadComments("PostComments.txt");
    int row = 0;
    std::vector<Comment*>com = post->getComments();
    ui->CommentTable->setRowCount(com.size());
    ui->CommentTable->setColumnCount(2);
    for (Comment* i:com){
        QString UserName = QString::fromStdString(i->getCommenter()->getName());
        QString comments = QString::fromStdString(i->getContent());
        QTableWidgetItem *user = new QTableWidgetItem(UserName);
        QTableWidgetItem *Comments = new QTableWidgetItem(comments);
        ui->CommentTable->setItem(row,0,user);
        ui->CommentTable->setItem(row,1,Comments);
        row++;
    }

    ui->CommenEditor->hide();
    ui->EnterComButton->hide();
    ui->CommenPromptlable->hide();

    ui->CommentButton->show();
    ui->AddColButton->show();
    ui->AddColLabel->show();
    ui->DisplayPostLabel->show();
    ui->ForwardButton->show();
    ui->ForwardlistWidget->show();
    ui->LikeButton->show();
    ui->CommentTable->show();
    ui->pplAddCoLlistWidget->show();
    ui->ComtLabel->show();
    ui->ForLabel->show();
    ui->AddColButton->show();
    network.WriteComments("PostComments.txt");
    ui->Numlike->show();

}

void SocialNetworkPost::LikeButtonClicked(){
    post->AddLikes();
    int likes = post->getLikes();
    QString c = "👍🏻 by "+ QString::fromStdString(std::to_string(likes))+" people";
    ui->Numlike->setText(c);
}

void SocialNetworkPost::ForwardButtonCicked(){
    LoggedInUser->AddForPost(post);
    post->AddPeopleForwarded(LoggedInUser->getName());
    int row = 0;
    for(int i = 0;i<post->GetpeopleForwarded().size();i++){
        QString forwUser = QString::fromStdString(post->GetpeopleForwarded()[i]);
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(forwUser);
        ui->ForwardlistWidget->insertItem(row++, newItem);
    }
}


void SocialNetworkPost::AddColButtonClicked(){
    post->AddPostToCollection(LoggedInUser->getName());
    LoggedInUser->AddCollection(post);
    int row = 0;
    for(int i = 0;i<post->GetpeopleAddToCollection().size();i++){
        QString AddColUser = QString::fromStdString(post->GetpeopleAddToCollection()[i]);
        QListWidgetItem *newItem = new QListWidgetItem;
        newItem->setText(AddColUser);
        ui->pplAddCoLlistWidget->insertItem(row++, newItem);
    }
}

void SocialNetworkPost::SetUp(User *loginU, User *CurdisU, Post *p){
    LoggedInUser = loginU;
    CurDisplayedUser = CurdisU;
    post = p;
    network.ReadComments("PostComments.txt");

}


