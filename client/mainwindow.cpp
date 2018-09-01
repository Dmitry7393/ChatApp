#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string serverIP, int port, QWidget *parent) :
    QMainWindow(parent),
    m_ui(new Ui::MainWindow),
    m_ClientServer(new ClientServerInteraction(serverIP, port))
{
    m_ui->setupUi(this);

    m_ClientServer->setGUIUpdater((GUIUpdater*) this);
    m_ListModel = new QStringListModel(this);

    connect(m_ui->m_getClientListButton, SIGNAL(clicked()), this, SLOT(updateClientList()));
    connect(m_ui->m_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(m_ui->m_clientListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectClient(const QModelIndex&)));

    QString username = QInputDialog::getText(this, tr("Enter login"),
                                            tr("Your login:"), QLineEdit::Normal,
                                            "", NULL);

    m_ClientServer->setUsername(username.toStdString());
    updateClientList();
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateClientListView(const std::vector<std::string>& clientList)
{
    QStringList listWithClients;
    for (int j = 0; j < clientList.size(); ++j)
    {
        listWithClients.append(QString(QString::fromUtf8(clientList.at(j).c_str())));
    }

    m_ListModel->setStringList(listWithClients);
    m_ui->m_clientListView->setModel(m_ListModel);
}

void MainWindow::updateMessageBrowser(const std::vector<std::string>& messageList)
{
    m_ui->m_MessageBrowser->clear();
    for (int j = 0; j < messageList.size(); ++j)
    {
        m_ui->m_MessageBrowser->setText(m_ui->m_MessageBrowser->text() + messageList.at(j).c_str() + "\n");
    }
}

void MainWindow::updateClientList()
{
    m_ClientServer->getClientList();
}

void MainWindow::sendMessage()
{
    m_ClientServer->sendMessage(m_ui->m_fieldForMessage->text().toStdString(), m_selectedClientLogin.toStdString());
    m_ui->m_MessageBrowser->setText(m_ui->m_MessageBrowser->text() + QString::fromUtf8(m_ClientServer->getUsername().c_str()) + ": " + m_ui->m_fieldForMessage->text() + "\n");
    m_ui->m_fieldForMessage->clear();
}

void MainWindow::selectClient(const QModelIndex& index)
{
    m_selectedClientLogin = index.data(Qt::DisplayRole).toString();
    m_ClientServer->sendRequestForMessages(m_selectedClientLogin.toStdString());
}
