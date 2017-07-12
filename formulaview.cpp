#include "formulaview.h"
#include "qwt_mml_document.h"

#include <qdebug.h>
#include <qevent.h>
#include <qpainter.h>

FormulaView::FormulaView( QWidget *parent ):
    QWidget( parent ),
    d_transformation( true ),
    d_scale( false ),
    d_rotation( 0 )
{
    d_mmlDoc = new QwtMathMLDocument;
    d_mmlDoc->setBaseFontPointSize( 8 );
}

FormulaView::~FormulaView()
{
    delete d_mmlDoc;
}

QString FormulaView::formula() const
{
    return d_formula;
}

void FormulaView::setFormula( const QString &formula )
{
    d_formula = formula;
    QString errorMsg;
    int errorLine, errorColumn;
    bool ok = d_mmlDoc->setContent( d_formula, &errorMsg, &errorLine, &errorColumn );
    if (!ok)
    {
        qWarning() << "MathML error at line" << errorLine
                   << "column" << errorColumn
                   << "with message" << errorMsg;
        d_mmlDoc->clear();
    }
    update();
}

void FormulaView::setFontSize( const qreal &fontSize )
{
    d_mmlDoc->setBaseFontPointSize( fontSize );
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
#ifdef MML_TEST
    d_mmlDoc->setDrawFrames( drawFrames );
#else
    Q_UNUSED(drawFrames)
#endif
    update();
}

void FormulaView::setColors( const bool &colors )
{
    if ( colors )
    {
        d_mmlDoc->setBackgroundColor( Qt::darkCyan );
        d_mmlDoc->setForegroundColor( Qt::yellow );
    }
    else
    {
        d_mmlDoc->setBackgroundColor( Qt::white );
        d_mmlDoc->setForegroundColor( Qt::black );
    }
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
    QRect viewRect = rect();
    QRectF docRect;
    docRect.setSize( d_mmlDoc->size() );
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
        d_mmlDoc->paint( painter, QPointF( 0.0, 0.0 ) );

        painter->restore();
    }
    else
    {
        d_mmlDoc->paint( painter, docRect.topLeft() );
    }
}
