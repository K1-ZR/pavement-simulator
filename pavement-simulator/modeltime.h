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
