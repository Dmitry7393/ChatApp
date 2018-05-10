#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{  
    QApplication a(argc, argv);

    if (argc < 2)
    {
        printf("Enter ip \n");
        return 1;
    }

    MainWindow w(argv[1]);
    w.show();

    return a.exec();
}
