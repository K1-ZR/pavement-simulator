#include "meshsublayer.h"


meshSubLayer::meshSubLayer(Matrix givenCoo, Matrix givenCon, Matrix givenCoh)
{
    coo = givenCoo;
    con = givenCon;
    coh = givenCoh;
}

/* discritize a rectangular area into many rectangular grid based on xg and yg
 then convert each grid to two triangular element */
meshSubLayer::meshSubLayer(Matrix xg, Matrix yg, QString st, modelLayer theLayer)
{
    xGridCoo = xg;
    yGridCoo = yg;

    /* coo - coordinate matrix */

    /* declare coo */
    numOfNodes = Size(xGridCoo, 1) * Size(yGridCoo, 1);
    coo = Matrix(numOfNodes, 2); /* x y */

    int nodeCounter = 1;

    for (int j = 1; j <= Size(yGridCoo,1); j = j + 1 )
    {
        for (int i = 1; i <= Size(xGridCoo,1); i = i + 1 )
        {
            /* nodes are nubered from left-bottom node to right to up */
            coo(nodeCounter,1) = xGridCoo(i,1); /* x */
            coo(nodeCounter,2) = yGridCoo(j,1); /* y */

            nodeCounter = nodeCounter + 1;
        }
    }

    /* con - connectivity matrix */

    /* declare con */
    numOfElements = 2 * (Size(xGridCoo, 1) - 1) * (Size(yGridCoo, 1) - 1);
    con = Matrix( numOfElements, 5);

    int elementCounter = 1;

    for (int j = 1; j <= (Size(yGridCoo,1) - 1); j = j + 1 )
    {
        for (int i = 1; i <= (Size(xGridCoo,1) - 1); i = i + 1 )
        {
            /* square vertices */
            int lb = i + (j - 1) * Size(xGridCoo,1);
            int rb = lb + 1;
            int lt = lb + Size(xGridCoo,1);
            int rt = lt + 1;

            /* to have a sym mesh, left subsection and right subsection are mirror meshed */
            if(st == "slash")
            {
                /* element 1 in square */
                con(elementCounter,1) = lb;
                con(elementCounter,2) = rt;
                con(elementCounter,3) = lt;
                /* element 2 in square */
                con(elementCounter+1,1) = lb;
                con(elementCounter+1,2) = rb;
                con(elementCounter+1,3) = rt;
             }
             if( st == "backSlash" )
             {
                 /* element 1 in square */
                 con(elementCounter,1) = lb;
                 con(elementCounter,2) = rb;
                 con(elementCounter,3) = lt;
                 /* element 2 in square */
                 con(elementCounter+1,1) = lt;
                 con(elementCounter+1,2) = rb;
                 con(elementCounter+1,3) = rt;
             }

             con(elementCounter,4) = theLayer.constitutiveModel.matSet; /*matset: 1,2,3,4 ...*/
             con(elementCounter,5) = theLayer.constitutiveModel.matType; /*mattype: 1=elastic, 2=ve*/

             con(elementCounter+1,4) = theLayer.constitutiveModel.matSet;
             con(elementCounter+1,5) = theLayer.constitutiveModel.matType;

            elementCounter = elementCounter + 2; /* each square devided into 2 elements */
        }
    }
}


/* find side nodes */
Matrix meshSubLayer::getSideNodes(QString sideLabel)
{
        int axisID = 0;
        double limCoo = 0.0;

        if(sideLabel == "top")         { axisID = 2; limCoo = coo.maxColwise(2); }
        else if(sideLabel == "bottom") { axisID = 2; limCoo = coo.minColwise(2); }
        else if(sideLabel == "left")   { axisID = 1; limCoo = coo.minColwise(1); }
        else if(sideLabel == "right")  { axisID = 1; limCoo = coo.maxColwise(1); }

        int counter = 0;
        for (int i = 1; i <= Size(coo,1); i = i + 1 )
        {
            if ( std::abs(coo(i,axisID) - limCoo)<eps)
            {
                counter = counter + 1;
            }
        }

        Matrix sideNodes = Matrix(counter,1);
        int index = 1;

        for (int i = 1; i <= Size(coo,1); i = i + 1 )
        {
            if ( std::abs(coo(i,axisID) - limCoo)<eps)
            {
                sideNodes(index,1) = i;
                index = index + 1;
            }
        }
        return sideNodes;
}

/* find side edges */
Matrix meshSubLayer::getSideEdges(QString sideLabel)
{/*
    el ID, node 1 ID, node 2 ID, edgecenter x, edgecenter y*/
    int axisID = 0;
    double limCoo = 0.0;

    if(sideLabel == "top")         { axisID = 2; limCoo = coo.maxColwise(2); }
    else if(sideLabel == "bottom") { axisID = 2; limCoo = coo.minColwise(2); }
    else if(sideLabel == "left")   { axisID = 1; limCoo = coo.minColwise(1); }
    else if(sideLabel == "right")  { axisID = 1; limCoo = coo.maxColwise(1); }

    int counter = 0;
    for (int i = 1; i <= Size(con,1); i = i + 1 )
    {
        int node1 = static_cast<int>(con(i, 1));
        int node2 = static_cast<int>(con(i, 2));
        int node3 = static_cast<int>(con(i, 3));

        double coord1 = coo(node1,axisID);
        double coord2 = coo(node2,axisID);
        double coord3 = coo(node3,axisID);

        if ( ( std::abs(coord1 - limCoo)<eps && std::abs(coord2 - limCoo)<eps ) ||
             ( std::abs(coord2 - limCoo)<eps && std::abs(coord3 - limCoo)<eps ) ||
             ( std::abs(coord3 - limCoo)<eps && std::abs(coord1 - limCoo)<eps ) )
        { counter = counter + 1; }
    }

    Matrix sideEdges = Matrix(counter, 5);
    int index = 1;

    for (int i = 1; i <= Size(con,1); i = i + 1 )
    {
        int node1 = static_cast<int>(con(i, 1));
        int node2 = static_cast<int>(con(i, 2));
        int node3 = static_cast<int>(con(i, 3));

        double coord1 = coo(node1,axisID);
        double coord2 = coo(node2,axisID);
        double coord3 = coo(node3,axisID);

        if ( std::abs(coord1 - limCoo)<eps && std::abs(coord2 - limCoo)<eps )
        {
            sideEdges(index, 1) = i;
            sideEdges(index, 2) = con(i,1);
            sideEdges(index, 3) = con(i,2);
            sideEdges(index, 4) = ( coo(node1,1) + coo(node2,1) )/2;
            sideEdges(index, 5) = ( coo(node1,2) + coo(node2,2) )/2;
            index = index + 1;
        }
        else if ( std::abs(coord2 - limCoo)<eps && std::abs(coord3 - limCoo)<eps )
        {
            sideEdges(index, 1) = i;
            sideEdges(index, 2) = con(i, 2);
            sideEdges(index, 3) = con(i, 3);
            sideEdges(index, 4) = ( coo(node2,1) + coo(node3,1) )/2;
            sideEdges(index, 5) = ( coo(node2,2) + coo(node3,2) )/2;
            index = index + 1;
        }
        else if ( std::abs(coord3 - limCoo)<eps && std::abs(coord1 - limCoo)<eps )
        {
            sideEdges(index, 1) = i;
            sideEdges(index, 2) = con(i, 3);
            sideEdges(index, 3) = con(i, 1);
            sideEdges(index, 4) = ( coo(node3,1) + coo(node1,1) )/2;
            sideEdges(index, 5) = ( coo(node3,2) + coo(node1,2) )/2;
            index = index + 1;
        }
    }
    return sideEdges;
}
