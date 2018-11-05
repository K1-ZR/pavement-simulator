#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "/Users/keyvanzarerami/Documents/gitrepo/rcProject/matrix/matrix.h"
#include "meshsublayer.h"
#include "meshmerge.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Matrix progression_arithmetic(double progStart, double progEnd, double progDiff);
    void matrixPrint(Matrix A);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
