#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include <string>
#include <math.h>
#include "ponto.h"
#include "cor.h"
#include "face.h"

#include <iostream>

using namespace std;

enum Tipo {POLIEDRO, CURVASPLINE, CURVABEZIER, PONTO, RETA, POLIGONO, POLIGONOPREENCHIDO, EIXO, WINDOW};

class Figura
{
public:
    Figura(string vNome, Tipo vTipo, list<Ponto *> vPontos, list<Face*> vFaces, Cor vCor, Ponto vrp, double tetaX, double tetaY, Ponto centroDaCamera, double teta);
    ~Figura();
    list<Ponto*> obterPontos();
    list<Face*> obterFaces();
    list<Ponto*> obterPontosPPC();
    string obterNome();
    Tipo obterTipo();
    Cor obterCor();
    void transladar(double,double,double);
    void escalonar(double,double,double);
    void rotacionar(double);
    void rotacionarNaOrigem(double, Ponto);
    void rotacionarNoCentro(double, Ponto);
    void rotacionarNoPonto(double,double,double, double, Ponto);
    void mudarCor(int, int, int);
    void alinharComZ(double tetaX, double tetaY, Ponto centroDaCamera);
    void gerarDescricaoPPC(double teta);
    void teste(Ponto vX, Ponto vY, Ponto vZ, Ponto centro);
    Ponto obterCentro();
private:
    double** matrizT;
    void transformar();
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
    list<Ponto*> pontosPPC;
    list<Face*> faces;
    Cor cor;
};

#endif // FIGURA_H
