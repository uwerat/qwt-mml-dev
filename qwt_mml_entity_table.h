#ifndef _QWT_MML_ENTITY_TABLE_H_
#define _QWT_MML_ENTITY_TABLE_H_

#ifdef NO_QWT
#define QWT_EXPORT
#else
#include <qwt_global.h>
#endif

#include <qstring.h>

class QWT_EXPORT QwtMMLEntityTable
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





