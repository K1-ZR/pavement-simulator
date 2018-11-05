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
