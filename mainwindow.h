#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>

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

private:
    Ui::MainWindow *ui;
    void getBookSlot(QNetworkReply *reply);
    void makeRequest();
    void login();

    QString webToken;

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
};
#endif // MAINWINDOW_H
