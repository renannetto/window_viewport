#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include "dialog.h"
#include "ponto.h"

namespace Ui {
    class MainWindow;
}

static double const VIEWPORTXSIZE = 640;
static double const VIEWPORTYSIZE = 480;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void abrirJanela();
    void drawDot(double,double);
    void drawLine(double,double,double,double);
    void zoomIn();
    void zoomOut();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    qreal fx(double);
    qreal fy(double);

private:
    Ui::MainWindow *ui;
    Dialog *newObjectWindow;
    QGraphicsScene * viewport;
    void drawObjects();
    qreal xMin;
    qreal yMin;
    qreal xMax;
    qreal yMax;
};

#endif // MAINWINDOW_H