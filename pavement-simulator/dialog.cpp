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
#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent ) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setModel(QStandardItemModel* m)
{
    theModel = m;
}

void Dialog::plotModel()
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resetMatrix();

     // ------------------------------------------------------------------------
    if(theModel->item(2,0)->rowCount() != 0 )
    {/* plot layer */
        modelLayer theLayer = theModel->item(2,0)->child(0,0)->data(Qt::UserRole + 3).value<modelLayer>();
    }

    // ------------------------------------------------------------------------
    if(theModel->item(3,0)->rowCount() != 0 )
    {/* plot mesh */
        meshSubLayer theMesh = meshSubLayer( theModel->item(3,0)->child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().coo_global,
                                             theModel->item(3,0)->child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().con_bulk,
                                             theModel->item(3,0)->child(0,0)->data(Qt::UserRole + 4).value<modelMesh>().con_coh);
        Matrix coo = theMesh.coo;
        Matrix con = theMesh.con;
        Matrix coh = theMesh.coh;

        // ....................................................................
        /* plot bulk mesh */
        QPen pen_bulkMesh = QPen();
        pen_bulkMesh.setCosmetic(true);

        QBrush brush_bulkMes;

        /* plot bulk mesh */
        for(int i = 1; i <= Size(con,1); i = i + 1)
        {
            int node1 = static_cast<int>(con(i,1));
            int node2 = static_cast<int>(con(i,2));
            int node3 = static_cast<int>(con(i,3));

            int pixelX1 = static_cast<int>(   coo(node1, 1) * toPixel);
            int pixelY1 = static_cast<int>(50-coo(node1, 2) * toPixel);
            int pixelX2 = static_cast<int>(   coo(node2, 1) * toPixel);
            int pixelY2 = static_cast<int>(50-coo(node2, 2) * toPixel);
            int pixelX3 = static_cast<int>(   coo(node3, 1) * toPixel);
            int pixelY3 = static_cast<int>(50-coo(node3, 2) * toPixel);

            /* set paint brush for different mat */
            if      (static_cast<int>(con(i,5)) == 1)
            {/* elastic */
                int brushFactor = - 15 * static_cast<int>(con(i,4));
                brush_bulkMes = QBrush( QColor(220+brushFactor, 220+brushFactor, 220+brushFactor, 255) );
            }
            else if (static_cast<int>(con(i,5)) == 2)
            {/* ve */
                int brushFactor = - 15 * static_cast<int>(con(i,4));
                brush_bulkMes = QBrush( QColor(220+brushFactor, 220+brushFactor, 255, 255) );
            }

            QPolygonF polygon;
            polygon << QPointF(pixelX1, pixelY1) << QPointF(pixelX2, pixelY2) << QPointF(pixelX3, pixelY3);
            scene->addPolygon(polygon, pen_bulkMesh, brush_bulkMes);
        }
        // ....................................................................
        /* plot coh mesh */
        QPen pen_cohMesh = QPen();
        pen_cohMesh.setCosmetic(true);

        for(int i = 1; i <= Size(coh,1); i = i + 2)
        {
            int node1 = static_cast<int>(coh(i,1));
            int node2 = static_cast<int>(coh(i+1,1));

            int pixelX1 = static_cast<int>(coo(node1, 1) * toPixel);
            int pixelY1 = static_cast<int>(50-coo(node1, 2) * toPixel);
            int pixelX2 = static_cast<int>(coo(node2, 1) * toPixel);
            int pixelY2 = static_cast<int>(50-coo(node2, 2) * toPixel);

            QPoint point1 = QPoint(pixelX1, pixelY1);
            QPoint point2 = QPoint(pixelX2, pixelY2);

            /* set paint brush for different mat */
            int brushFactor = - 15 * static_cast<int>(coh(i,3));
            pen_cohMesh.setColor( QColor(220+brushFactor, 255, 220+brushFactor, 255) );

            /* except perfect bonding */
            if(static_cast<int>(coh(i,3)) != 1 )
            {
                QLine line = QLine(point1, point2);
                scene->addLine(line, pen_cohMesh);
            }
        }

        // ------------------------------------------------------------------------
        if( theModel->item(4,0)->rowCount() != 0 )
        {/* plot load */
            QBrush brush_load = QBrush( QColor(220, 220, 220, 255) );
            QPen pen_load = QPen();
            pen_load.setCosmetic(true);

            for(int i=0; i < theModel->item(4,0)->rowCount(); i=i+1)
            {/* loop over loadings*/

                modelLoading theLoad  = theModel->item(4,0)->child(i,0)->data(Qt::UserRole + 5).value<modelLoading>();

                double leftCoo = theLoad.tireCentCoo - theLoad.tireWidth/2;
                double rightCoo = theLoad.tireCentCoo + theLoad.tireWidth/2;

                Matrix topNodes = theMesh.getSideNodes("top");
                for(int j=1; j <= Size(topNodes,1); j=j+1)
                {
                    if(coo(static_cast<int>(topNodes(j,1)),1) >= leftCoo &&
                            coo(static_cast<int>(topNodes(j,1)),1) <= rightCoo)
                    {
                        int node1 = static_cast<int>(topNodes(j,1));

                        int pixelX1 = static_cast<int>(coo(node1, 1) * toPixel);
                        int pixelY1 = static_cast<int>(50-coo(node1, 2) * toPixel);

                        double layerWitdth = theModel->item(2,0)->child(0,0)->data(Qt::UserRole + 3).value<modelLayer>().width;
                        int pixelX2 = static_cast<int>(coo(node1, 1) * toPixel);
                        int pixelY2 = static_cast<int>(50 - (coo(node1, 2)+layerWitdth/10) * toPixel);

                        QPoint beginPoint(pixelX2, pixelY2);
                        QPoint   endPoint(pixelX1, pixelY1);

                        /* plotArrow */
                        QLine arrowLine(beginPoint, endPoint);
                        scene->addLine(arrowLine,pen_load);

                        QPolygon arrowHead;
                        int arrowHeadSize = static_cast<int>(layerWitdth/40 * toPixel) + 1;
                        QPoint p1(endPoint.x(), endPoint.y());
                        QPoint p2(endPoint.x()-arrowHeadSize, endPoint.y()-arrowHeadSize);
                        QPoint p3(endPoint.x()+arrowHeadSize, endPoint.y()-arrowHeadSize);

                        arrowHead << p1 << p2 << p3;
                        scene->addPolygon(arrowHead, pen_load, brush_load);
                    }
                }
            }
        }
    }
}

void Dialog::paintEvent(QPaintEvent *)
{

}

void Dialog::wheelEvent(QWheelEvent* event)
{
    const int degrees = event->delta();
//    qreal deltaScale = 1.0 / (10.0/qFabs(degrees)+1);

    QPointF oldPos = ui->graphicsView->mapToScene(event->pos());

    qreal sx = 1.0;
    qreal sy = 1.0;

    if ( degrees > 0)
    {
        sy = sy + .1;
        sx = sx + .1;
    }
    else
    {
        sy = sy - .1;
        sx = sx - .1;
    }

    QPointF newPos = ui->graphicsView->mapToScene(event->pos());

    QPointF deltaPos = newPos - oldPos;

    ui->graphicsView->scale(sx,sy);
    ui->graphicsView->translate(deltaPos.x(), deltaPos.y());

}
