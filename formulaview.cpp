#include "formulaview.h"
#include "qwt_mml_document.h"

#include <qdebug.h>
#include <qevent.h>
#include <qpainter.h>

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

void FormulaView::setDrawFrames( const bool &drawFrames )
{
    d_drawFrames = drawFrames;
    update();
}

void FormulaView::setColors( const bool &colors )
{
    d_colors = colors;
    update();
}

void FormulaView::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    painter.setClipRegion( event->region() );

    painter.fillRect( event->rect(), Qt::white );

    renderFormula( &painter );
}

void FormulaView::renderFormula( QPainter *painter ) const
{
    QwtMathMLDocument doc;
    doc.setContent( d_formula );
    if ( d_colors )
    {
        doc.setBackgroundColor( Qt::darkCyan );
        doc.setForegroundColor( Qt::yellow );
    }
    else
    {
        doc.setBackgroundColor( Qt::white );
        doc.setForegroundColor( Qt::black );
    }
    doc.setBaseFontPointSize( d_fontSize );
#ifdef MML_TEST
    doc.setDrawFrames( d_drawFrames );
#endif

    QRect viewRect = rect();
    QRectF docRect;
    docRect.setSize( doc.size() );
    docRect.moveCenter( viewRect.center() );

    if ( d_transformation )
    {
        double scaleF = 1;
        if ( d_scale )
        {
            const double scaleX = viewRect.width() / docRect.width();
            const double scaleY = viewRect.height() / docRect.height();
            scaleF = qMin(scaleX, scaleY);
         }

        painter->save();

        painter->translate( docRect.center() );
        painter->rotate( d_rotation );
        painter->scale( scaleF, scaleF );
        painter->translate( docRect.topLeft() - docRect.center() );
        doc.paint( painter, QPointF( 0.0, 0.0 ) );

        painter->restore();
    }
    else
    {
        doc.paint( painter, docRect.topLeft() );
    }
}
