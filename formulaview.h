#ifndef _FORMULA_VIEW_H_
#define _FORMULA_VIEW_H_

#include <qframe.h>

class QPainter;

class QwtMathMLDocument;

class FormulaView: public QFrame
{
    Q_OBJECT

public:
    FormulaView( QWidget *parent = NULL );
    ~FormulaView();

    QString formula() const;

    void loadFormula(const QString& fileName);
    void clearFormula();

    void setPaddings( const QMargins &value );
    void setPaddings( const int &value );

public Q_SLOTS:
    void setFormula( const QString & );
    void setFontSize( const qreal & );
    void setTransformation( const bool &transformation );
    void setScale( const bool &scale );
    void setRotation( const qreal & );
    void setDrawFrames( const bool &drawFrames );
    void setColors( const bool &colors );

protected:
    virtual void paintEvent( QPaintEvent * );

private:
    void renderFormula( QPainter *, const QRect & ) const;

private:
    QMargins d_paddings;
    QwtMathMLDocument* d_mmlDoc;
    QString d_formula;
    bool d_transformation;
    bool d_scale;
    qreal d_rotation;
};

#endif
