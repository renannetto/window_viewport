#ifndef FIGURA_H
#define FIGURA_H

#include <list>
#include <string>
#include <math.h>
#include "ponto.h"
#include "cor.h"

using namespace std;

enum Tipo {PONTO, RETA, POLIGONO, EIXO};

class Figura
{
public:
    Figura(string vNome, Tipo vTipo, list<Ponto*> vPontos, Cor vCor);
    ~Figura();
    list<Ponto*> obterPontos();
    string obterNome();
    Tipo obterTipo();
    Cor obterCor();
    void transladar2D(double,double);
    void escalonar2D(double,double);
    void rotacionarNaOrigem2D(double);
    void rotacionarNoCentro2D(double);
    void rotacionarNoPonto2D(double,double,double);
    void mudarCor(int, int, int);
private:
    double** matrizT;
    void transformar2D();
    string nome;
    Tipo tipo;
    list<Ponto*> pontos;
    Cor cor;
};

#endif // FIGURA_H
