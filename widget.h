#ifndef WIDGET_H
#define WIDGET_H
#include <QPushButton>
#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QMediaPlayer>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
private slots:
    void net_request();
    void net_reply(QNetworkReply*);
private:
    QNetworkAccessManager *manager;
    QPushButton *bt;
    QListWidget *lw;
    QTextEdit *te;
    QMediaPlayer *player;
};

#endif // WIDGET_H
