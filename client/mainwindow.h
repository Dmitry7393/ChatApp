#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string>
#include <QThread>
#include <QInputDialog>
#include "NetworkHandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string serverIP, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    ip::tcp::endpoint m_Endpoint;
    boost::shared_ptr<ServerConnection> m_ServerConnection;
    NetworkHandler m_NetworkHandler;
};

#endif // MAINWINDOW_H
