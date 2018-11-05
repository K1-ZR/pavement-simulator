#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Matrix A = Ones(4,4);
    Matrix B = A.partial(1,3,1,4);

    matrixPrint(B);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::matrixPrint(Matrix A)
{
    QString printObj;

    if(Size(A,1)==0)
    {
        qDebug() << "matrix is empty";
    }else
    {
        for(int i = 1; i<=Size(A,1); i = i+1)
        {
            for(int j = 1; j<=Size(A,2); j = j+1)
            {
                printObj.append( QVariant(A(i,j)).toString() );
                printObj.append( " " );
            }
            qDebug() << printObj;
            printObj.clear();
        }
    }
}
