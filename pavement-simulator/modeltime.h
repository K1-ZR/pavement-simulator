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
#ifndef MODELTIME_H
#define MODELTIME_H

#include <QMetaType>
#include <QDataStream>

struct modelTime
{
    double totalTime;
    double timeIncrement;

    /* those should be friend and defined inside the struct */
    friend QDataStream &operator<< (QDataStream &out, const modelTime &rhs)
    {
        out << rhs.totalTime
            << rhs.timeIncrement;

        return out;
    }

    friend QDataStream &operator>> (QDataStream &in, modelTime &rhs)
    {
        in >> rhs.totalTime
           >> rhs.timeIncrement;

        return in;
    }
};

Q_DECLARE_METATYPE(modelTime)

#endif // MODELTIME_H
