#include "widget.h"
#include "arrowwidget.h"

#include <QUrl>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    player=new QMediaPlayer(this);
    this->resize(400,600);
    manager=new QNetworkAccessManager(this);

    te=new QTextEdit(this);
    bt=new QPushButton(te);
    lw=new QListWidget(this);
    lw->setGeometry(0,0,400,500);
    te->setGeometry(0,500,400,100);
    bt->setGeometry(350,70,48,28);
    bt->setText("send");

    connect(bt,SIGNAL(clicked(bool)),this,SLOT(net_request()));
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(net_reply(QNetworkReply*)));
}

void Widget::net_request()
{
    QJsonValue buf(te->toPlainText());
    //封装jason包;
    QJsonObject text;
    text.insert("text",buf);

    QJsonObject image;
    image.insert("url","");

    QJsonObject location;
    location.insert("city","成都");
    location.insert("province","四川");
    location.insert("street","科华北路");

    QJsonObject selfInfo;
    selfInfo.insert("location",location);

    QJsonObject userInfo;
    userInfo.insert("apiKey","eab500505ce24317b49b6c1fe4a2c3e2");
    userInfo.insert("userId","6e4c5b7095e4c93b");

    QJsonObject perception;
    perception.insert("inputText",text);
    perception.insert("inputImage",image);
    perception.insert("selfInfo",selfInfo);



    QJsonObject json;
    json.insert("perception",perception);
    json.insert("userInfo",userInfo);


    //转换为bytearray;
    QByteArray data=(QJsonDocument(json).toJson(QJsonDocument::Indented));//用缩进形式;

    //将封装好的请求发出;
    QNetworkRequest request;
    request.setUrl(QUrl("http://openapi.tuling123.com/openapi/api/v2"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    manager->post(request,data);

    te->clear();
}

void Widget::net_reply(QNetworkReply* reply)
{
    QByteArray data;
    data=reply->readAll();

    qDebug()<<QString(data);

    QJsonDocument doc =  QJsonDocument::fromJson(data);
    QJsonObject obj =  doc.object();

    QString text;
    if(obj.contains("results"))
    {
        QJsonArray results=obj.take("results").toArray();

        QJsonObject array=results.at(0).toObject();

        QJsonObject value=array.take("values").toObject();
        text=value.take("text").toString();
        qDebug()<<text;

       lw->addItem(text);
      //  te->setText(text);
    }
#if 1
    QByteArray url="http://tsn.baidu.com/text2audio?";
        url.append(QString("&lan=zh&cuid=00-50-56-C0-00-08&ctp=1&tok=24.e5bc619116e3ac7ba9813e281448ae48.2592000.1568974865.282335-17059448&pit=15&per=5"));
        url.append("&tex=");
        url.append(QUrl::toPercentEncoding(text));
        qDebug()<<url;

        player->setMedia(QUrl::fromLocalFile(url));
        player->play();
#endif       
}

Widget::~Widget()
{

}
