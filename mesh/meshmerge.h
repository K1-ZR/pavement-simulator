#ifndef MESHCOMBINE_H
#define MESHCOMBINE_H

#include <QMessageBox>
#include <QString>

#include <cmath>

#include "meshsublayer.h"
#include "../matrix/matrix.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\matrix\matrix.h"

class meshmerge
{
public:
    double eps = 0.0000000001;

    meshmerge( meshSubLayer meshA, QString sideA, meshSubLayer meshB, QString sideB, int mergeType );

    /* merged */
    Matrix cooM, conM, cohM;
};

#endif // MESHCOMBINE_H
