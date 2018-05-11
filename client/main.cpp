#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{  
    QApplication a(argc, argv);

    if (argc < 3)
    {
        printf("Enter server ip and port \n");
        return 1;
    }

    MainWindow w(argv[1], atoi(argv[2]));
    w.show();

    return a.exec();
}
