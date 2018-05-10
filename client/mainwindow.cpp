#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(std::string serverIP, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Endpoint(ip::address::from_string(serverIP), 5555),
    m_ServerConnection(new ServerConnection),
    m_NetworkHandler(m_ServerConnection)
{
    ui->setupUi(this);

    try
    {
        m_ServerConnection->connect(m_Endpoint);
    }
    catch(boost::system::system_error & err)
    {
        std::cout << err.what() << std::endl;
    }

    bool ok;
    QString login = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("User name:"), QLineEdit::Normal,
                                            "", &ok);

    printf("login = %s \n", login.toStdString().c_str());
    m_ServerConnection->setUsername(login.toStdString());
    m_ServerConnection->sendMessage(ui->m_LineEditMessage->text().toStdString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    m_ServerConnection->sendMessage(ui->m_LineEditMessage->text().toStdString());
}

void MainWindow::on_pushButton_3_clicked()
{
    //check for new messages in separated thread
    m_NetworkHandler.start();
}
