#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QNetworkRequest"
#include "QNetworkAccessManager"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_Quit, SIGNAL(triggered()), this, SLOT(close()));

    // QString webToken = "HapPaB54t0zf4M1xbgVioe67+xQ1GolcCWWC8jbsOwbQNfWuC4YYG4zVQTYO4b+DoatQRD4VUxQ62n0gcc1frQ==";
    QString webToken = this->login();

    QString site_url="http://localhost:3000/book/1";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    //Onnistuneen loginin seurauksena saadaan arvo muuttujalle webToken, jonka
    //tietotyyppi on QByteArray ja sen eteen asetetaan merkkijono Bearer
    QByteArray myToken="Bearer "+webToken.toUtf8();
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::getBookSlot);
    reply = manager->get(request);
}

void MainWindow::login() {
    QString url="http://localhost:3000/login";
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json.insert("username", "test_user");
    json.insert("password", "test123");
    QByteArray jsonData = QJsonDocument(json).toJson();

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::getLogin);
    QNetworkReply *reply = networkManager->post(request, jsonData);
}


QString MainWindow::getLogin(QNetworkReply *reply) {
    QByteArray response_data=reply->readAll();

    return QString(response_data);
}


void MainWindow::getBookSlot(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString book;

    book=QString::number(json_obj["id_book"].toInt())+","+json_obj["name"].toString()+","+json_obj["author"].toString();

    // foreach (const QJsonValue &value, json_array) {
    //     QJsonObject json_obj = value.toObject();
    //     book+=QString::number(json_obj["id_book"].toInt())+","+json_obj["name"].toString()+","+json_obj["author"].toString()+"\r";
    // }

    ui->textEditResults->setText(book);

    reply->deleteLater();
    manager->deleteLater();
}


MainWindow::~MainWindow()
{
    delete ui;
}
