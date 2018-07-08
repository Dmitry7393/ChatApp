#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string serverIP, int port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ClientServer(new ClientServerInteraction(serverIP, port))
{
    ui->setupUi(this);

    m_ClientServer->setGUIUpdater((GUIUpdater*) this);
    model = new QStringListModel(this);

    connect(ui->m_getClientListButton, SIGNAL(clicked()), this, SLOT(updateClientList()));
    connect(ui->m_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->m_clientListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectClient(const QModelIndex&)));

    //doesn't work in qt - try later
    //QObject::connect(m_ClientServer.data(), SIGNAL(updateClientList(const std::vector<std::string>&)), this, SLOT(updateClientListView(const std::vector<std::string>&)));

    bool ok;
    QString username = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Your login:"), QLineEdit::Normal,
                                            "", &ok);
    printf(" username = %s \n", username.toStdString().c_str());

    m_ClientServer->setUsername(username.toStdString());
    updateClientList();
    m_ClientServer->readDataFromServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClientListView(const std::vector<std::string>& clientList)
{
    printf(" MainWindow::updateClientListView (slot function) \n");
    QStringList listWithClients;
    for (int j = 0; j < clientList.size(); ++j)
    {
        listWithClients.append(QString(QString::fromUtf8(clientList.at(j).c_str())));
    }

    model->setStringList(listWithClients);
    ui->m_clientListView->setModel(model);
}

void MainWindow::updateMessageBrowser(std::vector<std::string> messageList)
{
    printf("MainWindow::updateMessageBrowser 1 \n");
  //  ui->m_MessageBrowser->append("sssssssssssssssss");
    ui->m_MessageBrowser->clear();
    printf("MainWindow::updateMessageBrowser 2 \n");
    for (int j = 0; j < messageList.size(); ++j)
    {
        printf(" message == %s \n", messageList.at(j).c_str());
        ui->m_MessageBrowser->setText(ui->m_MessageBrowser->text() + messageList.at(j).c_str() + "\n");
       // ui->m_MessageBrowser->append(QString::fromUtf8(messageList.at(j).c_str()));
    }
}

void MainWindow::updateClientList()
{
    m_ClientServer->getClientList();
}

void MainWindow::sendMessage()
{
    m_ClientServer->sendMessage(ui->m_fieldForMessage->text().toStdString(), m_selectedClientLogin.toStdString());
    ui->m_MessageBrowser->setText(ui->m_MessageBrowser->text() + QString::fromUtf8(m_ClientServer->getUsername().c_str()) + ": " + ui->m_fieldForMessage->text() + "\n");
   // ui->m_MessageBrowser->append(QString::fromUtf8(m_ClientServer->getUsername().c_str()) + ": " + ui->m_fieldForMessage->text());
    ui->m_fieldForMessage->clear();
}

void MainWindow::selectClient(const QModelIndex& index)
{
    m_selectedClientLogin = index.data(Qt::DisplayRole).toString();
    m_ClientServer->getMessagesWithClient(m_selectedClientLogin.toStdString());
}
