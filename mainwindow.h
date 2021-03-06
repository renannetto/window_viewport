#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <string>
#include <iostream>
#include <math.h>
#include <vector>
#include "Clipping.h"
#include "canvas.h"
#include "dialog.h"
#include "Transformacoes.h"
#include "windowviewport.h"
#include "geradordecurvas.h"


namespace Ui {
    class MainWindow;
}

using namespace std;

static double const VIEWPORTXSIZE = 660;
static double const VIEWPORTYSIZE = 500;
static double const SUBVIEWPORTXMIN = 20;
static double const SUBVIEWPORTXMAX = 639;
static double const SUBVIEWPORTYMIN = 20;
static double const SUBVIEWPORTYMAX = 479;

class Canvas;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void reiniciar();
    void resetarWindow();
    void abrirJanelaDeCriacoes();
    void abrirJanelaDeTransformacoes();
    void abrirJanelaDeAjuda();
    void construirFigura(Tipo, list<Ponto*>, list<Face*> faces, QColor cor, int nLinhas = 0, int nColunas = 0);
    void destruirFigura();
    void receberPonto(double, double);
    void zoomIn();
    void zoomOut();
    void mostrarValorDoZoom(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    void moverParaFrente();
    void moverParaTras();
    void transladar(double,double,double);
    void escalonar(double,double,double);
    void rotacionarNaOrigem(double, double, double, double);
    void rotacionarNoCentro(double, double, double, double);
    void rotacionarNoPonto(double,double,double, double, double, double, double);
    void mudarCor(QColor cor);
    void rotacionarWindowParaDireita();
    void rotacionarWindowParaEsquerda();
    void aumentarRegiaoDeClipping();
    void diminuirRegiaoDeClipping();
    void fixarAlgoritmoDeClipping();
    void arrastarCamera(double, double);
    void fixarForward();
    void ativarPerspectiva();
    void desativarPerspectiva();

private:
    void iniciar();
    void construirMatrizes();
    void desenharFiguras();
    bool clippingDeLinha(Ponto const &p1, Ponto const &p2, Ponto &np1, Ponto &np2);
    void desenharSubViewport();
    double transformadaViewportX(double);
    double transformadaViewportY(double);
    double transformadaInversaViewportX(double);
    double transformadaInversaViewportY(double);
    WindowViewport *windowViewport;
    Ui::MainWindow *ui;
    QGraphicsScene *viewport;
    Dialog *janelaDeCriacoes;
    Transformacoes *janelaDeTransformacoes;
    Canvas *detectorDeEventos;
    Clipping *clipador;
    unsigned int deslocamentoClipador;
    GeradorDeCurvas *geradorDeCurvas;
    double deslocamentoXDaCamera;
    double deslocamentoYDaCamera;
    double deslocamentoZDaCamera;
};

#endif // MAINWINDOW_H
