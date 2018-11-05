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
#ifndef MESHSUBLAYER_H
#define MESHSUBLAYER_H

#include <QString>
#include <cmath>

#include "../matrix/matrix.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\matrix\matrix.h"
#include "modellayer.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\rcSimulator\modellayer.h"

class meshSubLayer
{
public:
    /*input variables*/
    double eps= 0.0000000001;

    QString meshOrientation;

    Matrix xGridCoo, yGridCoo;

    int numOfNodes, numOfElements;
    Matrix coo, con, coh;

    /* constructor */
    meshSubLayer(Matrix givenCoo, Matrix givenCon, Matrix givenCoh);
    meshSubLayer(Matrix xg, Matrix yg, QString st, modelLayer theLayer);

    /* functions */
    Matrix getSideNodes(QString sideLabel);
    Matrix getSideEdges(QString sideLabel);

};
#endif // MESHSUBLAYER_H
