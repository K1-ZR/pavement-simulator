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
#ifndef MODELLOADING_H
#define MODELLOADING_H

#include <QString>
#include <QMetaType>
#include <QDataStream>

struct modelLoading
{
    QString label;
    QString loadingType;

    double tireWidth;
    double tireCentCoo;
    double amplitude;

    /* sine */
    double s_cycleDuration;

    /* sine-pulse */
    double sp_pulseDuration;
    double sp_cycleDuration;

    /* those should be friend and defined inside the struct */
    friend QDataStream &operator<< (QDataStream &out, const modelLoading &rhs)
    {
        out << rhs.label
            << rhs.loadingType
            << rhs.tireWidth << rhs.tireCentCoo
            << rhs.amplitude
            << rhs.s_cycleDuration << rhs.sp_pulseDuration << rhs.sp_cycleDuration;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, modelLoading &rhs)
    {
        in >> rhs.label
           >> rhs.loadingType
           >> rhs.tireWidth >> rhs.tireCentCoo
           >> rhs.amplitude
           >> rhs.s_cycleDuration >> rhs.sp_pulseDuration >> rhs.sp_cycleDuration;

        return in;
    }
};

Q_DECLARE_METATYPE(modelLoading) // add this line

#endif // MODELLOADING_H
