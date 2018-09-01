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

    void updateClientListView(const std::vector<std::string>& clientList);
    void updateMessageBrowser(const std::vector<std::string>& messageList);

    ~MainWindow();

private slots:
    void updateClientList();
    void sendMessage();
    void selectClient(const QModelIndex& index);

private:
    QScopedPointer<Ui::MainWindow> m_ui;
    QScopedPointer<ClientServerInteraction> m_ClientServer;
    QStringListModel *m_ListModel;
    QString m_selectedClientLogin;
};

#endif // MAINWINDOW_H
