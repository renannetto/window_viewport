#ifndef WINDOWVIEWPORT_H
#define WINDOWVIEWPORT_H

#include "displayfile.h"
#include "window.h"
#include <string>
#include <limits>
#include <math.h>

#define PI 3.14159265;

class WindowViewport
{
public:
    WindowViewport();
    ~WindowViewport();
    string adicionarFigura(Tipo tipo, list<Ponto*> pontos, list<Face*> faces, int vermelho, int verde, int azul, int nLinhas = 0, int nColunas = 0);
    list<Figura*> obterFiguras();
    void resetarWindow();
    void destruirFigura(string);
    void zoomIn(int);
    void zoomOut(int);
    void moverParaEsquerda();
    void moverParaDireita();
    void moverParaCima();
    void moverParaBaixo();
    void moverParaFrente();
    void moverParaTras();
    void rotacionarWindow(Ponto vetor, double angulo);
    double obterXMinDaWindow(list<Ponto*> pontos);
    double obterYMinDaWindow(list<Ponto*> pontos);
    double obterXMaxDaWindow(list<Ponto*> pontos);
    double obterYMaxDaWindow(list<Ponto*> pontos);
    double obterXMinDaWindowMundo();
    double obterYMinDaWindowMundo();
    double obterXMaxDaWindowMundo();
    double obterYMaxDaWindowMundo();
    double obterXMinDaWindowPPC();
    double obterYMinDaWindowPPC();
    double obterXMaxDaWindowPPC();
    double obterYMaxDaWindowPPC();
    double obterZWindowPPC();
    double obterCentroXDaWindow();
    double obterCentroYDaWindow();
    void transladar(string,double,double,double);
    void escalonar(string,double,double,double);
    void rotacionarNaOrigem(string,double, Ponto);
    void rotacionarNoCentro(string,double, Ponto);
    void rotacionarNoPonto(string,double,double,double, double, Ponto);
    void mudarCor(string, int, int, int);
    void gerarDescricoesPPC();
    double obterAnguloDaWindow();
    void arrastarCam(Ponto vetor);
    void transformarPontoWindowParaMundo(Ponto &ponto);
    void setarPerspectiva(bool valor);
private:
    DisplayFile *displayFile;
    Figura *window;
    double xMin;
    double xMax;
    double yMin;
    double yMax;
    bool perspectiva;
};

#endif // WINDOWVIEWPORT_H
