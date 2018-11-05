#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QPainter>
#include <QGraphicsScene>
#include <QtMath>
#include <QStandardItem>

#include "../matrix/matrix.h"
#include "modellayer.h"
#include "modelmesh.h"
#include "../mesh/meshsublayer.h"
#include "modelloading.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QGraphicsScene* scene;

    int toPixel = 1000;

    QStandardItemModel* theModel;

    void setModel(QStandardItemModel* m);
    void plotModel();

private:
    Ui::Dialog *ui;

protected:
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent* event);

private slots:
};

#endif // DIALOG_H
