#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string serverIP, int port, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ClientServer(new ClientServerInteraction(serverIP, port))
{
    ui->setupUi(this);

    connect(ui->sendMessageButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    bool ok;
    QString username = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Your login:"), QLineEdit::Normal,
                                            "", &ok);
    printf(" username = %s \n", username.toStdString().c_str());

    m_ClientServer->setUsername(username.toStdString());
    m_ClientServer->authenticate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendMessage()
{
    printf("  slot send message \n");
    m_ClientServer->sendMessage(ui->m_LineEditMessage->text().toStdString());
}

void MainWindow::on_pushButton_3_clicked()
{
    //check for new messages in separated thread
   // m_NetworkHandler.start();
}
