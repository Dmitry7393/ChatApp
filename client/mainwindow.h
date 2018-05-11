#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string>
#include <QThread>
#include <QInputDialog>
#include <QScopedPointer>

#include "ClientServerInteraction.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(std::string serverIP, int port, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void sendMessage();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QScopedPointer<ClientServerInteraction> m_ClientServer;
};

#endif // MAINWINDOW_H
