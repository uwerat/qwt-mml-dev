#include "formulaview.h"
#include "mainwindow.h"

#include <qcheckbox.h>
#include <qcombobox.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <qlabel.h>
#include <qmimedata.h>
#include <qstatusbar.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

MainWindow::MainWindow() : QMainWindow()
{
    d_view = new FormulaView( this );
    setCentralWidget( d_view );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnLoad = new QToolButton( toolBar );

    btnLoad->setText( "Load" );
    btnLoad->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnLoad );

    toolBar->addSeparator();

    toolBar->addWidget( new QLabel( "Font size" ) );

    QComboBox *comboFontSizes = new QComboBox( toolBar );
    QStringList fontSizes;
    for ( int i = 8; i <= 128; i += 2 )
        fontSizes << QString::number( i );
    comboFontSizes->addItems( fontSizes );
    comboFontSizes->setCurrentIndex( 32 );
    toolBar->addWidget( comboFontSizes );

    toolBar->addSeparator();

    QCheckBox *checkTransformation = new QCheckBox( toolBar );
    checkTransformation->setText( "Transformations" );
    checkTransformation->setChecked( true );
    toolBar->addWidget( checkTransformation );

    d_checkScale = new QCheckBox( toolBar );
    d_checkScale->setText( "Fit to window" );
    toolBar->addWidget( d_checkScale );

    toolBar->addWidget( new QLabel( "Rotation" ) );

    d_comboRotations = new QComboBox( toolBar );
    QStringList rotations;
    for ( int i = 0; i <= 360; i += 15 )
        rotations << QString::number( i );
    d_comboRotations->addItems( rotations );
    d_comboRotations->setCurrentIndex( 0 );
    toolBar->addWidget( d_comboRotations );

    toolBar->addSeparator();

#ifdef MML_TEST
    QCheckBox *checkDrawFrames = new QCheckBox( toolBar );
    checkDrawFrames->setText( "Draw frames" );
    toolBar->addWidget( checkDrawFrames );
#endif

    QCheckBox *checkColors = new QCheckBox( toolBar );
    checkColors->setText( "Colors" );
    toolBar->addWidget( checkColors );

    addToolBar( toolBar );

    connect( btnLoad, SIGNAL( clicked() ), this, SLOT( load() ) );
    connect( comboFontSizes, SIGNAL( currentIndexChanged( const QString & ) ), this, SLOT( updateFontSize( const QString & ) ) );
    connect( checkTransformation, SIGNAL( toggled( bool ) ), this, SLOT( updateTransformation( const bool & ) ) );
    connect( d_checkScale, SIGNAL( toggled( bool ) ), this, SLOT( updateScaling( const bool & ) ) );
    connect( d_comboRotations, SIGNAL( currentIndexChanged( const QString & ) ), this, SLOT( updateRotation( const QString & ) ) );
#ifdef MML_TEST
    connect( checkDrawFrames, SIGNAL( toggled( bool ) ), this, SLOT( updateDrawFrames( const bool & ) ) );
#endif
    connect( checkColors, SIGNAL( toggled( bool ) ), this, SLOT( updateColors( const bool & ) ) );

    updateFontSize( comboFontSizes->currentText() );
    updateTransformation( checkTransformation->isChecked() );
    updateScaling( d_checkScale->isChecked() );
    updateRotation( d_comboRotations->currentText() );
#ifdef MML_TEST
    updateDrawFrames( checkDrawFrames->isChecked() );
#endif
    updateColors( checkColors->isChecked() );

    setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if ( event->mimeData()->urls().count() == 1 )
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    QString fileName = event->mimeData()->urls().first().toLocalFile();
    QFileInfo fileInfo( fileName );

    if ( fileInfo.exists() && fileInfo.completeSuffix() == "mml" )
        event->acceptProposedAction();
    else
        event->ignore();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    loadFormula( event->mimeData()->urls().first().toLocalFile() );

    event->acceptProposedAction();
}

void MainWindow::load()
{
    const QString fileName = QFileDialog::getOpenFileName( NULL,
        "Load a MathML File", QString::null, "MathML Files (*.mml)" );

    if ( !fileName.isEmpty() )
        loadFormula( fileName );
    else
        statusBar()->showMessage( QString::null );
}

void MainWindow::loadFormula( const QString &fileName )
{
    statusBar()->showMessage( fileName );

    d_view->loadFormula( fileName );
}

void MainWindow::updateFontSize( const QString &fontSize )
{
    d_view->setFontSize( fontSize.toInt() );
}

void MainWindow::updateTransformation( const bool &transformation )
{
    d_checkScale->setEnabled( transformation );
    d_comboRotations->setEnabled( transformation );

    d_view->setTransformation( transformation );
}

void MainWindow::updateScaling( const bool &scale )
{
    d_view->setScale( scale );
}

void MainWindow::updateRotation( const QString &rotation )
{
    d_view->setRotation( rotation.toInt() );
}

void MainWindow::updateDrawFrames( const bool &drawFrames )
{
    d_view->setDrawFrames( drawFrames );
}

void MainWindow::updateColors( const bool &colors )
{
    d_view->setColors( colors );
}
