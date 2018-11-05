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
