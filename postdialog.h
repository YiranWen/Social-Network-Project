#ifndef POSTDIALOG_H
#define POSTDIALOG_H
#include "ui_postdialog.h"
#include "network.h"
#include "post.h"
#include "user.h"
#include "comment.h"
#include <QString>
#include <QDialog>



namespace Ui {
class SocialNetworkPost;
}

class SocialNetworkPost : public QDialog
{
    Q_OBJECT

public:
    explicit SocialNetworkPost(QWidget *parent = nullptr);
    void CommentButtonClicked();

    void LikeButtonClicked();

    void ForwardButtonCicked();
    void AddColButtonClicked();
    void SetPostText(QString text);
    void SetUp(User* loginU,User* CurdisU,Post* p);
    void EnterCommentButtonClicked();

    void setUpPost(Post* post);
    void SetCommentTable(Post* post);

    ~SocialNetworkPost();

// signals:
//     void commentAdded(Post* post, Comment* comment);

private:
    Ui::SocialNetworkPost *ui;
    Network network;
    User* LoggedInUser;
    User* CurDisplayedUser;
    Post* post;
};

#endif // POSTDIALOG_H
