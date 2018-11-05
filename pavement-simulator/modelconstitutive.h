#ifndef MODELCONSTITUTIVE_H
#define MODELCONSTITUTIVE_H

#include <QMetaType>
#include <QString>
#include <QList>
#include <QDataStream>

#include "../matrix/matrix.h"
// #include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\matrix\matrix.h"

struct modelConstitutive
{
    /* general info */
    QString label;

    int matType; /* 1:elastic, 2:viscoelastic */
    int matSet; /* 1, 2, 3, 4 ... */

    /* Elastic */
    double elElasticModulus;
    double elPoissonRatio;

    /* ViscoElastic */
    double vePoissonRatio;
    double veRelaxModuInf;
    QList<double> veRelaxModuPS;
    QList<double> veRelaxTimePS;


    /* those should be friend and defined inside the struct */
    friend QDataStream &operator<< (QDataStream &out, const modelConstitutive &rhs)
    {
        out << rhs.label
            << rhs.matType << rhs.matSet
            << rhs.elElasticModulus << rhs.elPoissonRatio
            << rhs.vePoissonRatio << rhs.veRelaxModuInf << rhs.veRelaxModuPS << rhs.veRelaxTimePS;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, modelConstitutive &rhs)
    {
        in >> rhs.label
           >> rhs.matType >> rhs.matSet
           >> rhs.elElasticModulus >> rhs.elPoissonRatio
           >> rhs.vePoissonRatio >> rhs.veRelaxModuInf >> rhs.veRelaxModuPS >> rhs.veRelaxTimePS;

        return in;
    }
};

Q_DECLARE_METATYPE(modelConstitutive) // add this line

#endif // MODELCONSTITUTIVE_H
