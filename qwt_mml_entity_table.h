#ifndef _QWT_MML_ENTITY_TABLE_H_
#define _QWT_MML_ENTITY_TABLE_H_

#include <qstring.h>

class QwtMMLEntityTable
{
public:
    struct Spec
    {
        const char *name;
        const char *value;
    };

    QString entities() const;
    const Spec *search( const QString &value, const Spec *from = 0 ) const;
};

#endif





