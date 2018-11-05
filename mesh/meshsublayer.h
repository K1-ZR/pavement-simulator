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
