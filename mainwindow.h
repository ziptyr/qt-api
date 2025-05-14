#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void getCarAll();
    void getCarId();
    void postCar();
    void putCar();
    void deleteCar();

    void requestGet(QString site_url);
    void requestPost(QString site_url, QJsonObject jsonObj);
    void requestPut(QString site_url, QJsonObject jsonObj);
    void requestDelete(QString site_url);

    void outputReplyArray(QNetworkReply *reply);
    void outputReplyString(QNetworkReply *reply);

private:
    Ui::MainWindow *ui;

    QString webToken;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
};
#endif // MAINWINDOW_H
