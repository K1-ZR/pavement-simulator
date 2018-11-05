#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    modelLayer layer = modelLayer();

     Matrix ap_a = progression_arithmetic(0,2,1);
     Matrix ap_b = progression_arithmetic(2,4,1);

     meshSubLayer box1 = meshSubLayer(ap_a, ap_a, "slash", );
     meshSubLayer box2 = meshSubLayer(ap_b, ap_a, "backSlash", );

 //    matrixPrint(box1.getSideNodes("right"));
 //    matrixPrint(box1.getSideEdges("right"));

     meshSubLayer box3 = meshSubLayer(ap_a, ap_b, "slash");
     meshSubLayer box4 = meshSubLayer(ap_b, ap_b, "backSlash");

     meshmerge layer1 = meshmerge(box1, "right", box2, "left", "cohBonded");
     meshmerge layer2 = meshmerge(box3, "right", box4, "left", "cohBonded");

     meshSubLayer layer1_mesh = meshSubLayer(layer1.cooM, layer1.conM, layer1.cohM);
     meshSubLayer layer2_mesh = meshSubLayer(layer2.cooM, layer2.conM, layer2.cohM);

     meshmerge structure = meshmerge(layer1_mesh, "top", layer2_mesh, "bottom", "cohBonded");



 //    matrixPrint(layer1.cooM);
 //    matrixPrint(layer1.conM);
 //    matrixPrint(layer1.cohM);

     matrixPrint(structure.cooM);
     matrixPrint(structure.conM);
     matrixPrint(structure.cohM);
}

MainWindow::~MainWindow()
{
    delete ui;
}


/* arithmetic progression*/
Matrix MainWindow::progression_arithmetic(double progStart, double progEnd, double progDiff)
{ /* make a arithmetic progression */
    int numOfmembers = floor( (progEnd - progStart)/ progDiff ) + 1;

    // make a arithmetic progression
    // the last increment might be bigger than others
    Matrix progSeries = Matrix(numOfmembers,1);

    int counter = 1;

    for (double loc = progStart; loc < progEnd; loc = loc + progDiff)
    {
        progSeries(counter,1) = loc;
        counter = counter + 1;
    }
    progSeries(numOfmembers,1) = progEnd;

    return progSeries;
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
