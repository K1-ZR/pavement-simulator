#ifndef MODELLAYER_H
#define MODELLAYER_H

#include <QMetaType>
#include <QString>

#include "modelconstitutive.h"
#include "modelcohesive.h"

struct modelLayer
{
    QString label;
    double thickness;
    double width;
    double crackDepth;
    double crackWidth;

    modelConstitutive constitutiveModel;
    modelCohesive midlineCohModel;
    modelCohesive bottomCohModel;

    /* those should be friend and defined inside the struct */
    friend QDataStream &operator<< (QDataStream &out, const modelLayer &rhs)
    {
        out << rhs.label
            << rhs.thickness << rhs.width
            << rhs.crackDepth << rhs.crackWidth
            << rhs.constitutiveModel
            << rhs.midlineCohModel
            << rhs.bottomCohModel;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, modelLayer &rhs)
    {
        in >> rhs.label
           >> rhs.thickness >> rhs.width
           >> rhs.crackDepth >> rhs.crackWidth
           >> rhs.constitutiveModel
           >> rhs.midlineCohModel
           >> rhs.bottomCohModel;

        return in;
    }

};

Q_DECLARE_METATYPE(modelLayer) // add this line

#endif // MODELLAYER_H
