#include "formulaview.h"
#include <qevent.h>
#include <qpainter.h>
#include <qwt_mml_document.h>

FormulaView::FormulaView( QWidget *parent ):
    QWidget( parent ),
    d_fontSize( 8 ),
    d_transformation( true ),
    d_scale( false ),
    d_rotation( 0 )
{
}

QString FormulaView::formula() const
{
    return d_formula;
}

void FormulaView::setFormula( const QString &formula )
{
    d_formula = formula;
    update();
}

void FormulaView::setFontSize( const qreal &fontSize )
{
    d_fontSize = fontSize;
    update();
}

void FormulaView::setTransformation( const bool &transformation )
{
    d_transformation = transformation;
    update();
}

void FormulaView::setScale( const bool &scale )
{
    d_scale = scale;
    update();
}

void FormulaView::setRotation( const qreal &rotation )
{
    d_rotation = rotation;
    update();
}

void FormulaView::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    painter.setClipRegion( event->region() );

    renderFormula( &painter );
}

void FormulaView::renderFormula( QPainter *painter ) const
{
    QwtMathMLDocument doc;
    doc.setContent( d_formula );
    doc.setBaseFontPointSize( d_fontSize );

    QRectF docRect;
    docRect.setSize( doc.size() );
    docRect.moveCenter( rect().center() );

    if ( d_transformation )
    {
        const double scaleF = d_scale ? 2.0 : 1.0;

        painter->save();

        painter->translate( docRect.center() );
        painter->rotate( d_rotation );
        painter->scale( scaleF, scaleF );
        painter->translate( docRect.topLeft() - docRect.center() );
        doc.paint( painter, QPointF( 0, 0 ) );

        painter->restore();
    }
    else
    {
        doc.paint( painter, docRect.topLeft().toPoint() );
    }
}
