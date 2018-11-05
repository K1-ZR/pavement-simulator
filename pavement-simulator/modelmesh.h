#ifndef MODELMESH_H
#define MODELMESH_H

#include <QMetaType>

#include "../matrix/matrix.h"

struct modelMesh
{
    double meshSize;

    Matrix coo_global;
    Matrix con_bulk;
    Matrix con_coh;

    int numOfNodes;
    int numOfBulkEl;
    int numOfIntEl;

};

Q_DECLARE_METATYPE(modelMesh)

#endif // MODELMESH_H
