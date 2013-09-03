#ifndef _MAIN_WINDOW_H_
#define _MAIN_WINDOW_H_

#include <qmainwindow.h>

class FormulaView;

class QCheckBox;
class QComboBox;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private Q_SLOTS:
    void load();
    void loadFormula( const QString & );
    void updateFontSize( const QString & );
    void updateTransformation( const bool & );
    void updateScaling( const bool & );
    void updateRotation( const QString & );

private:
    FormulaView *d_view;

    QCheckBox *d_checkScale;
    QComboBox *d_comboRotations;
};

#endif
