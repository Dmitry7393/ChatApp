#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdio.h>
#include <string>
#include <QThread>
#include <QInputDialog>
#include <QScopedPointer>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractItemView>

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
    void updateClientList();
    void sendMessage();
    void getNewMessages();
    void selectOtherClient(const QModelIndex& index);

private:
    void updateView();

private:
    Ui::MainWindow *ui;
    QScopedPointer<ClientServerInteraction> m_ClientServer;
    QStringListModel *model;
    QString m_selectedClientLogin;
};

#endif // MAINWINDOW_H
