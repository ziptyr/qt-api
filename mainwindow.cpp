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

    connect(ui->pushButton_show_carAll, &QPushButton::clicked, this, &MainWindow::getCarAll);
    connect(ui->pushButton_show_carId, &QPushButton::clicked, this, &MainWindow::getCarId);
    connect(ui->pushButton_create, &QPushButton::clicked, this, &MainWindow::postCar);
    connect(ui->pushButton_edit, &QPushButton::clicked, this, &MainWindow::putCar);
    connect(ui->pushButton_delete, &QPushButton::clicked, this, &MainWindow::deleteCar);
}

void MainWindow::getCarAll()
{
    ui->textEditResults->setText("");

    QString site_url="http://localhost:3000/car";
    requestGet(site_url);
}

void MainWindow::deleteCar()
{
    ui->textEditResults->setText("");

    QString site_url="http://localhost:3000/car/" + ui->spinBox_delete_carId->text();
    requestDelete(site_url);
}

void MainWindow::getCarId()
{
    ui->textEditResults->setText("");

    QString site_url="http://localhost:3000/car/" + ui->spinBox_show_carId->text();
    requestGet(site_url);
}

void MainWindow::postCar()
{
    QJsonObject jsonObj;
    jsonObj.insert("branch", ui->lineEdit_create_create_branch->text());
    jsonObj.insert("model", ui->lineEdit_create_create_model->text());

    QString site_url="http://localhost:3000/car/";
    requestPost(site_url, jsonObj);
}

void MainWindow::putCar()
{
    QJsonObject jsonObj;
    jsonObj.insert("branch", ui->lineEdit_edit_branch->text());
    jsonObj.insert("model", ui->lineEdit_edit_model->text());

    QString site_url="http://localhost:3000/car/" + ui->spinBox_edit_carId->text();
    requestPut(site_url, jsonObj);
}

void MainWindow::requestDelete(QString site_url)
{
    QNetworkRequest request(site_url);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::outputReplyString);
    reply = manager->deleteResource(request);
}

void MainWindow::requestGet(QString site_url)
{
    QNetworkRequest request(site_url);

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::outputReplyArray);
    reply = manager->get(request);
}

void MainWindow::requestPut(QString site_url, QJsonObject jsonObj)
{
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::outputReplyString);
    reply = manager->put(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::requestPost(QString site_url, QJsonObject jsonObj)
{
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::outputReplyString);
    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::outputReplyArray(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString output_string;

    QJsonArray json_array = json_doc.array();

    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        output_string+=QString::number(json_obj["id_car"].toInt())+","+json_obj["branch"].toString()+","+json_obj["model"].toString()+"\r";
    }

    ui->textEditResults->setText(output_string);

    reply->deleteLater();
    manager->deleteLater();
}

void MainWindow::outputReplyString(QNetworkReply *reply)
{
    QByteArray response_data=reply->readAll();

    ui->textEditResults->setText(response_data);

    reply->deleteLater();
    manager->deleteLater();
}



MainWindow::~MainWindow()
{
    delete ui;
}
