#include "meshmerge.h"

meshmerge::meshmerge(meshSubLayer meshA, QString sideA, meshSubLayer meshB, QString sideB, int bondingType )
{
    Matrix cooA = meshA.coo;
    Matrix conA = meshA.con;
    Matrix cohA = meshA.coh;
    Matrix sideEdgeA = meshA.getSideEdges(sideA);

    Matrix cooB = meshB.coo;
    Matrix conB = meshB.con;
    Matrix cohB = meshB.coh;
    Matrix sideEdgeB = meshB.getSideEdges(sideB);

    Matrix newCohEls = Matrix(Size(sideEdgeA,1) * 2, 3);

  /* make
     no overlapped nodes are removed
     coh elements are defined between overlapped nodes */
    int counter = 1;
    /* A1----B1
       A2----B2 */
    for( int i = 1; i <= Size(sideEdgeA,1); i = i + 1)
    {
        for( int j = 1; j <= Size(sideEdgeB, 1); j = j + 1)
        {
            int nodeA1 = static_cast<int>(sideEdgeA(i,2));
            int nodeA2 = static_cast<int>(sideEdgeA(i,3));
            double edgeCenA_x = sideEdgeA(i,4);
            double edgeCenA_y = sideEdgeA(i,5);

            int nodeB1 = static_cast<int>(sideEdgeB(j,2));
            int nodeB2 = static_cast<int>(sideEdgeB(j,3));
            double edgeCenB_x = sideEdgeB(j,4);
            double edgeCenB_y = sideEdgeB(j,5);

            if( std::abs(edgeCenA_x-edgeCenB_x)<eps && std::abs(edgeCenA_y-edgeCenB_y)<eps )
            {
                if( std::abs(cooA(nodeA1,1)-cooB(nodeB1,1))<eps && std::abs(cooA(nodeA1,2)-cooB(nodeB1,2))<eps )
                {
                    newCohEls(counter,1) = nodeA1;
                    newCohEls(counter,2) = nodeB1;

                    newCohEls(counter+1,1) = nodeA2;
                    newCohEls(counter+1,2) = nodeB2;
                }else
                {
                    newCohEls(counter,1) = nodeA1;
                    newCohEls(counter,2) = nodeB2;

                    newCohEls(counter+1,1) = nodeA2;
                    newCohEls(counter+1,2) = nodeB1;
                }

                /* new method */
                /* 1---2
                   3---4 */
                int oNode1 = static_cast<int>(newCohEls(counter,1)); /*original numbering*/
                int oNode2 = static_cast<int>(newCohEls(counter,2));
                int oNode3 = static_cast<int>(newCohEls(counter+1,1));
                int oNode4 = static_cast<int>(newCohEls(counter+1,2));

                double vecX = cooA(oNode3,1) - cooA(oNode1,1);
                double vecY = cooA(oNode3,2) - cooA(oNode1,2);

                if( (vecX< 0 && vecY >= 0) || (vecX< 0 && vecY <= 0) ) /*quadrant 2, 3*/
                {
                    newCohEls(counter,1) = oNode3;
                    newCohEls(counter,2) = oNode4;
                    newCohEls(counter+1,1) = oNode1;
                    newCohEls(counter+1,2) = oNode2;
                }

                /* correct numbering */
// based on MIDAS VT
//                CACB = El_Cen_B - El_Cen_A;
//                A1_A2 = Coor(A2,2:3) - Coor(A1,2:3);

//                if sum(cross([A1_A2 0],[CACB 0]))<=0
//                    NewCohEl=[A2 A1 B1 B2];
//                end
//                if sum(cross([A1_A2 0],[CACB 0]))>=0
//                    NewCohEl=[A1 A2 B2 B1];
//                end
//                %
//                A1_A2 = Coor(NewCohEl(2),2:3) - Coor(NewCohEl(1),2:3);

//                if     A1_A2(1)>=0  && A1_A2(2)>=0; Quadrant=1;
//                elseif A1_A2(1)<0   && A1_A2(2)>0;  Quadrant=2;
//                elseif A1_A2(1)<=0  && A1_A2(2)<=0; Quadrant=3;
//                elseif A1_A2(1)>0   && A1_A2(2)<0;  Quadrant=4;end

//                if Quadrant==2 || Quadrant==3
//                    NewCohEl = [NewCohEl(3) NewCohEl(4) NewCohEl(1) NewCohEl(2)];
//                end

                /* adjust node numbering */
                newCohEls(counter,2) = newCohEls(counter,2) + Size(cooA, 1);
                newCohEls(counter+1,2) = newCohEls(counter+1,2) + Size(cooA, 1);
                /* define bonding type */
                newCohEls(counter,3) = bondingType;
                newCohEls(counter+1,3) = bondingType;

                counter = counter + 2;
            }
        }
    }

    /* merge coh*/
    Matrix auxK1;
    Matrix auxK2;
    Matrix auxK10 = vertCat(cohA, auxK2);

    if(Size(cohA,1)==0 && Size(cohB,1)==0)
    {

    }else if(Size(cohA,1)!=0 && Size(cohB,1)==0)
    {
        auxK10 = cohA;
    }else if(Size(cohA,1)==0 && Size(cohB,1)!=0)
    {
        auxK1 = horzCat(Ones(Size(cohB,1), 2), Zeros(Size(cohB,1), 1));
        auxK2 = cohB + auxK1.Multiply(Size(cooA, 1));
        auxK10 = auxK2;
    }else if(Size(cohA,1)!=0 && Size(cohB,1)!=0)
    {
        /* increase cohB node numbers by A number of nodes */
        auxK1 = horzCat(Ones(Size(cohB,1), 2), Zeros(Size(cohB,1), 1));
        auxK2 = cohB + auxK1.Multiply(Size(cooA, 1));
        auxK10 = vertCat(cohA, auxK2);
    }
    cohM = vertCat(auxK10, newCohEls);

    /* merge con*/
    Matrix auxK100 = vertCat(conA.partial(1,Size(conA,1),1,3),
                             conB.partial(1,Size(conB,1),1,3).Add(Size(cooA, 1)) );
    Matrix auxK200 = vertCat(conA.partial(1,Size(conA,1),4,Size(conA,2)),
                             conB.partial(1,Size(conB,1),4,Size(conB,2)) );
    conM = horzCat(auxK100, auxK200);

    /* merge coo*/
    cooM = vertCat(cooA, cooB);
}
