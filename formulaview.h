#ifndef _FORMULA_VIEW_H_
#define _FORMULA_VIEW_H_

#include <qwidget.h>

class QPainter;

class FormulaView: public QWidget
{
    Q_OBJECT

public:
    FormulaView( QWidget *parent = NULL );

    QString formula() const;

public Q_SLOTS:
    void setFormula( const QString & );
    void setFontSize( const qreal & );
    void setTransformation( const bool &transformation );
    void setScale( const bool &scale );
    void setRotation( const qreal & );

protected:
    virtual void paintEvent( QPaintEvent * );

private:
    void renderFormula( QPainter * ) const;

private:
    QString d_formula;
    qreal d_fontSize;
    bool d_transformation;
    bool d_scale;
    qreal d_rotation;
};

#endif
