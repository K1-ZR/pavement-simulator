#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include <vector>
#include <cmath>

#include <QtMath>
#include <QStandardItemModel>
#include <QTreeView>
#include <QTableWidget>
#include <QMessageBox>
#include <QDebug>
#include <QString>
#include <QList>
#include <QGraphicsView>

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTextStream>
#include <QDataStream>
#include <QFileDialog>

#include <QProcess>

#include "modelconstitutive.h"
#include "modelcohesive.h"
#include "modellayer.h"
#include "modelmesh.h"
#include "modelloading.h"
#include "modeltime.h"

#include "dialog.h"

#include "../matrix/matrix.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\matrix\matrix.h"

#include "../mesh/meshsublayer.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\mesh\meshsublayer.h"

#include "../mesh/meshmerge.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\mesh\meshmerge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /* create a model for treeview */
    QStandardItemModel standardModel;

    /* define items */
    QStandardItem item_constitutive;
    QStandardItem item_cohesive;
    QStandardItem item_structure;
    QStandardItem item_mesh;
    QStandardItem item_load;
    QStandardItem item_analysis;

    double eps = std::numeric_limits<double>::epsilon();

    Dialog dialogPlotMesh;

    void initializeUI();
    void initializeQTable(QTableWidget *table);
    void initializeTreeView();
    void getConstitutiveInput();
    void getCohesiveInput();
    void getStructureInput();
    void getMeshInput();
    void getLoadingInput();
    void getTimeInput();

    void saveToBin();
    void loadFromBin();

    /*  */
    void writeInputfile();
    void runFESolver();
    void visualizeModel();

    QList<double> readFromTable(QTableWidget *table, int startRow, int columnIndex);
    int isStrChildMember(QStandardItem *item, QString str);
    Matrix progression_arithmetic(double progStart, double progEnd, double progDiff);
    Matrix placeBinA(Matrix A, Matrix B, int m, int n);
    
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_tabWidget_tabBarClicked(int index);

    void on_comboBox_9_currentIndexChanged(int index);

    void on_lineEdit_17_editingFinished();


    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionWriteinput_triggered();

    void on_actionRun_triggered();
    void on_actionPlot_model_triggered();

    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

};

QDataStream &operator<<(QDataStream &, const modelConstitutive &);
QDataStream &operator>>(QDataStream &, modelConstitutive &);

#endif // MAINWINDOW_H
