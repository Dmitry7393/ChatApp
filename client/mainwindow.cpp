#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string serverIP, int port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ClientServer(new ClientServerInteraction(serverIP, port))
{
    ui->setupUi(this);

    model = new QStringListModel(this);

    connect(ui->m_getClientListButton, SIGNAL(clicked()), this, SLOT(updateClientList()));
    connect(ui->m_sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->m_getMessagesButton, SIGNAL(clicked()), this, SLOT(getNewMessages()));
    connect(ui->m_clientListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(selectOtherClient(const QModelIndex&)));

    bool ok;
    QString username = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Your login:"), QLineEdit::Normal,
                                            "", &ok);
    printf(" username = %s \n", username.toStdString().c_str());

    m_ClientServer->setUsername(username.toStdString());
    updateClientList();

    getNewMessages();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateClientList()
{
    std::vector<std::string> clientList = m_ClientServer->getClientList();

    // Make data
    QStringList List;
    for (int j = 0; j < clientList.size(); ++j)
    {
        List.append(QString(QString::fromUtf8(clientList.at(j).c_str())));
    }

    model->setStringList(List);
    ui->m_clientListView->setModel(model);
}

void MainWindow::sendMessage()
{
    m_ClientServer->sendMessage(ui->m_fieldForMessage->text().toStdString(), m_selectedClientLogin.toStdString());
    ui->m_MessageBrowser->append(QString::fromUtf8(m_ClientServer->getUsername().c_str()) + ui->m_fieldForMessage->text());
    ui->m_fieldForMessage->clear();
}

void MainWindow::getNewMessages()
{
    m_ClientServer->getMessages();
    updateView();
}

void MainWindow::updateView()
{
    std::vector<std::string> list = m_ClientServer->getMessagesWithClient(m_selectedClientLogin.toStdString());

    for (int i = 0; i < list.size(); ++i)
    {
        ui->m_MessageBrowser->append(QString::fromUtf8(list.at(i).c_str()));
    }
}

void MainWindow::selectOtherClient(const QModelIndex& index)
{
    m_selectedClientLogin = index.data(Qt::DisplayRole).toString();

    printf("m_selectedClientLogin = %s \n", m_selectedClientLogin.toStdString().c_str());
    updateView();
}
