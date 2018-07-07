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
#include "GUIUpdater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public GUIUpdater
{
    Q_OBJECT

public:
    explicit MainWindow(std::string serverIP, int port, QWidget *parent = 0);
     ~MainWindow();

public slots:
    void updateClientListView(const std::vector<std::string>& clientList);
    void updateMessageBrowser(std::vector<std::string> messageList);

private slots:
    void updateClientListttt();
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
