/*
    pavement-simulator Copyright (C) 2018  Keyvan Zare-Rami

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
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
