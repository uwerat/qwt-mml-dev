#include "mainwindow.h"
#include "formulaview.h"
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qfiledialog.h>
#include <qbuffer.h>
#include <qstatusbar.h>
#include <qdebug.h>
#include <qcombobox.h>
#include <qapplication.h>
#include <qcheckbox.h>

MainWindow::MainWindow()
{
    d_view = new FormulaView( this );
    setCentralWidget( d_view );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnLoad = new QToolButton( toolBar );

    btnLoad->setText( "Load" );
    btnLoad->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnLoad );

    QComboBox *comboFontSizes = new QComboBox( toolBar );
    QStringList fontSizes;
    for ( int i = 8; i <= 128; i += 2 )
        fontSizes << QString::number( i );
    comboFontSizes->addItems( fontSizes );
    comboFontSizes->setCurrentIndex( 3 );
    toolBar->addWidget( comboFontSizes );

    QCheckBox *checkTransformation = new QCheckBox( toolBar );
    checkTransformation->setText( "Transformation" );
    checkTransformation->setChecked( true );
    toolBar->addWidget( checkTransformation );

    d_checkScale = new QCheckBox( toolBar );
    d_checkScale->setText( "Scale" );
    toolBar->addWidget( d_checkScale );

    d_comboRotations = new QComboBox( toolBar );
    QStringList rotations;
    for ( int i = 0; i < 360; i += 15 )
        rotations << QString::number( i );
    d_comboRotations->addItems( rotations );
    d_comboRotations->setCurrentIndex( 0 );
    toolBar->addWidget( d_comboRotations );

    addToolBar( toolBar );

    connect( btnLoad, SIGNAL( clicked() ), this, SLOT( load() ) );
    connect( comboFontSizes, SIGNAL( currentIndexChanged( const QString & ) ), this, SLOT( updateFontSize( const QString & ) ) );
    connect( checkTransformation, SIGNAL( toggled( bool ) ), this, SLOT( updateTransformation( const bool & ) ) );
    connect( d_checkScale, SIGNAL( toggled( bool ) ), this, SLOT( updateScaling( const bool & ) ) );
    connect( d_comboRotations, SIGNAL( currentIndexChanged( const QString & ) ), this, SLOT( updateRotation( const QString & ) ) );

    updateFontSize( comboFontSizes->currentText() );
    updateTransformation( checkTransformation->isChecked() );
    updateScaling( d_checkScale->isChecked() );
    updateRotation( d_comboRotations->currentText() );
};

void MainWindow::load()
{
    const QString fileName = QFileDialog::getOpenFileName( NULL,
        "Load a MathML File", QString::null, "MathML Files (*.mml)" );

    if ( !fileName.isEmpty() )
        loadFormula( fileName );

    statusBar()->showMessage( fileName );
}

void MainWindow::loadFormula( const QString &fileName )
{
    QFile file( fileName );
    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
        return;

    const QByteArray document = file.readAll();
    file.close();

    d_view->setFormula( document );
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
