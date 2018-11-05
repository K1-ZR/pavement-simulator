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
#ifndef MODELCOHESIVE_H
#define MODELCOHESIVE_H

#include <QMetaType>
#include <QString>
#include <QList>
#include <QDataStream>

#include "../matrix/matrix.h"
//#include "C:\Users\keyvanzare-rami\iCloudDrive\Documents\gitrepo\rcProject\matrix\matrix.h"

struct modelCohesive
{
    /* general info */
    QString label;

    int cohType; /* 1: vecz*/
    int cohSet; /* 1, 2, 3, 4 ... */

    /* Bonding - Cohesive Zone - CZ */
    double czSigmaN;
    double czSigmaT;
    double czDeltaN;
    double czDeltaT;

    double czVERelaxModuInf;
    QList<double> czVERelaxModuPS;
    QList<double> czVERelaxTimePS;


    /* Damage functions */
    int bondingDamageIndex; /* 1 is power function; 2 is gaussian function*/

    double czDamagePowerFunC;
    double czDamagePowerFunN;
    double czDamagePowerFunM;

    double czDamageGaussFunA;
    double czDamageGaussFunM;
    double czDamageGaussFunL;
    double czDamageGaussFunD;


    /* those should be friend and defined inside the struct */
    friend QDataStream &operator<< (QDataStream &out, const modelCohesive &rhs)
    {
        out << rhs.label
            << rhs.cohType << rhs.cohSet
            << rhs.czSigmaN << rhs.czSigmaT << rhs.czDeltaN << rhs.czDeltaT
            << rhs.czVERelaxModuInf << rhs.czVERelaxModuPS << rhs.czVERelaxTimePS
            << rhs.bondingDamageIndex
            << rhs.czDamagePowerFunC << rhs.czDamagePowerFunN << rhs.czDamagePowerFunM
            << rhs.czDamageGaussFunA << rhs.czDamageGaussFunM << rhs.czDamageGaussFunL << rhs.czDamageGaussFunD;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, modelCohesive &rhs)
    {
        in >> rhs.label
            >> rhs.cohType >> rhs.cohSet
            >> rhs.czSigmaN >> rhs.czSigmaT >> rhs.czDeltaN >> rhs.czDeltaT
            >> rhs.czVERelaxModuInf >> rhs.czVERelaxModuPS >> rhs.czVERelaxTimePS
            >> rhs.bondingDamageIndex
            >> rhs.czDamagePowerFunC >> rhs.czDamagePowerFunN >> rhs.czDamagePowerFunM
            >> rhs.czDamageGaussFunA >> rhs.czDamageGaussFunM >> rhs.czDamageGaussFunL >> rhs.czDamageGaussFunD;

        return in;
    }
};

Q_DECLARE_METATYPE(modelCohesive) // add this line

#endif // MODELCOHESIVE_H
