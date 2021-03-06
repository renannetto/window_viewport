#include "windowviewport.h"
#include <stdio.h>

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = displayFile->obterFiguras().front();
    perspectiva = true;
    gerarDescricoesPPC();
}

WindowViewport::~WindowViewport(){
    delete window;
    delete displayFile;
}

void WindowViewport::resetarWindow(){
    list<Ponto*> &pontosWindow = window->obterPontos();
    pontosWindow.clear();
    pontosWindow.push_back(new Ponto(-640, -480, 200));
    pontosWindow.push_back(new Ponto(640, -480, 200));
    pontosWindow.push_back(new Ponto(640, 480, 200));
    pontosWindow.push_back(new Ponto(-640, 480, 200));
    window->setarDistanciaCop(300);
    gerarDescricoesPPC();
}

string WindowViewport::adicionarFigura(Tipo tipo, list<Ponto*> pontos, list<Face*> faces, int vermelho, int verde, int azul, int nLinhas, int nColunas)
{
    Cor cor = Cor(vermelho, verde, azul);
    return displayFile->adicionarFigura(tipo, pontos, faces, cor, nLinhas, nColunas);
}

list<Figura*> WindowViewport::obterFiguras(){
    return displayFile->obterFiguras();
}

void WindowViewport::destruirFigura(string nome){
    displayFile->destruirFigura(nome);
}

void WindowViewport::zoomIn(int percent)
{
    window->mudarDistanciaCop(percent*5);
//    window->escalonar(1-(double)percent/100, 1-(double)percent/100, 1-(double)percent/100);
//    window->escalonar2D((double)100/(percent+100), (double)100/(percent+100));
//    window->transladar(0, 0,-10);
}

void WindowViewport::zoomOut(int percent)
{
    window->mudarDistanciaCop(-percent*5);
//    window->escalonar((double)100/(100-percent), (double)100/(100-percent), (double)100/(100-percent));
//    window->escalonar2D(1+(double)percent/100, 1+(double)percent/100);
//    window->transladar(0, 0,10);
}

void WindowViewport::moverParaEsquerda()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor(ponto1Window->obterX()-ponto2Window->obterX(), ponto1Window->obterY()-ponto2Window->obterY(), ponto1Window->obterZ()-ponto2Window->obterZ());

    double vX = 0.1*vetor.obterX();
    double vY = 0.1*vetor.obterY();
    double vZ = 0.1*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::moverParaDireita()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());

    double vX = 0.1*vetor.obterX();
    double vY = 0.1*vetor.obterY();
    double vZ = 0.1*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::moverParaBaixo()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto2Window = pontosWindow.back();

    Ponto vetor(ponto1Window->obterX()-ponto2Window->obterX(), ponto1Window->obterY()-ponto2Window->obterY(), ponto1Window->obterZ()-ponto2Window->obterZ());

    double vX = 0.1*vetor.obterX();
    double vY = 0.1*vetor.obterY();
    double vZ = 0.1*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::moverParaCima()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto2Window = pontosWindow.back();

    Ponto vetor(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());

    double vX = 0.1*vetor.obterX();
    double vY = 0.1*vetor.obterY();
    double vZ = 0.1*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::moverParaFrente(){
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    Ponto vetor(-xOrtogonal, -yOrtogonal, -zOrtogonal);
    vetor.normalizarVetor();

    double vX = 20*vetor.obterX();
    double vY = 20*vetor.obterY();
    double vZ = 20*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::moverParaTras(){
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    Ponto vetor(xOrtogonal, yOrtogonal, zOrtogonal);
    vetor.normalizarVetor();

    double vX = 20*vetor.obterX();
    double vY = 20*vetor.obterY();
    double vZ = 20*vetor.obterZ();
    window->transladar(vX, vY, vZ);
}

void WindowViewport::rotacionarWindow(Ponto vetor, double angulo){
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());
    vetor1.normalizarVetor();
    vetor2.normalizarVetor();

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    Ponto vetor3(xOrtogonal, yOrtogonal, zOrtogonal);
    vetor3.normalizarVetor();

    double x = vetor1.obterX()*vetor.obterX() + vetor2.obterX()*vetor.obterY() + vetor3.obterX()*vetor.obterZ();
    double y = vetor1.obterY()*vetor.obterX() + vetor2.obterY()*vetor.obterY() + vetor3.obterY()*vetor.obterZ();
    double z = vetor1.obterZ()*vetor.obterX() + vetor2.obterZ()*vetor.obterY() + vetor3.obterZ()*vetor.obterZ();

    Ponto vetorMundo(x,y,z);
    vetorMundo.normalizarVetor();
    Ponto cop = window->obterCop();

    window->rotacionarNoPonto(angulo,cop.obterX(),cop.obterY(),cop.obterZ(),vetorMundo);

}

double WindowViewport::obterXMinDaWindow(list<Ponto*> pontos){
    double xMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() < xMin){
            xMin = (*it)->obterX();
        }
    }
    return xMin;
}

double WindowViewport::obterYMinDaWindow(list<Ponto*> pontos){
    double yMin = numeric_limits<double>::max();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() < yMin){
            yMin = (*it)->obterY();
        }
    }
    return yMin;
}

double WindowViewport::obterXMaxDaWindow(list<Ponto*> pontos){
    double xMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterX() > xMax){
            xMax = (*it)->obterX();
        }
    }
    return xMax;
}

double WindowViewport::obterYMaxDaWindow(list<Ponto*> pontos){
    double yMax = numeric_limits<double>::min();
    list<Ponto*>::iterator it;
    for(it = pontos.begin(); it != pontos.end(); it++){
        if ((*it)->obterY() > yMax){
            yMax = (*it)->obterY();
        }
    }
    return yMax;
}

double WindowViewport::obterXMaxDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterXMaxDaWindow(pontos);
}

double WindowViewport::obterXMinDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterXMinDaWindow(pontos);
}

double WindowViewport::obterYMaxDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterYMaxDaWindow(pontos);
}

double WindowViewport::obterYMinDaWindowMundo(){
    list<Ponto*> pontos = window->obterPontos();
    return obterYMinDaWindow(pontos);
}

double WindowViewport::obterXMaxDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterXMaxDaWindow(pontos);
}

double WindowViewport::obterXMinDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterXMinDaWindow(pontos);
}

double WindowViewport::obterYMaxDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterYMaxDaWindow(pontos);
}

double WindowViewport::obterYMinDaWindowPPC(){
    list<Ponto*> pontos = window->obterPontosPPC();
    return obterYMinDaWindow(pontos);
}

double WindowViewport::obterZWindowPPC() {
    list<Ponto*> pontos = window->obterPontosPPC();
    return pontos.front()->obterZ();
}

double WindowViewport::obterCentroXDaWindow(){
    return window->obterCentro().obterX();
}

double WindowViewport::obterCentroYDaWindow(){
    return window->obterCentro().obterY();
}

void WindowViewport::transladar(string nomeFigura, double vX, double vY, double vZ){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
	    (*it)->transladar(vX,vY,vZ);
            break;
        }
    }
}

void WindowViewport::escalonar(string nomeFigura, double vX, double vY, double vZ){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
	    (*it)->escalonar(vX,vY,vZ);
            break;
        }
    }
}

void WindowViewport::rotacionarNaOrigem(string nomeFigura, double teta, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNaOrigem(teta, vetor);
            break;
        }
    }
}

void WindowViewport::rotacionarNoCentro(string nomeFigura, double teta, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoCentro(teta, vetor);
            break;
        }
    }
}

void WindowViewport::rotacionarNoPonto(string nomeFigura, double teta, double pX, double pY, double pZ, Ponto vetor){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoPonto(teta,pX,pY, pZ, vetor);
            break;
        }
    }
}

void WindowViewport::mudarCor(string nomeFigura, int vermelho, int verde, int azul){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->mudarCor(vermelho, verde, azul);
            break;
        }
    }
}

void WindowViewport::gerarDescricoesPPC(){
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();
    Ponto vetor3(xOrtogonal,yOrtogonal,zOrtogonal);
    vetor3.normalizarVetor();
    window->atualizarCop(vetor3);
    cout << "XCop = " << vetor3.obterX() << endl;
    cout << "YCop = " << vetor3.obterY() << endl;
    cout << "ZCop = " << vetor3.obterZ() << endl;
    Ponto centroDaWindow = window->obterCentro();

    double moduloVnp = sqrt(xOrtogonal*xOrtogonal + yOrtogonal*yOrtogonal + zOrtogonal*zOrtogonal);
    double moduloZX = sqrt(xOrtogonal*xOrtogonal + zOrtogonal*zOrtogonal);
    double tetaY = acos(xOrtogonal/moduloZX);
    double tetaX = acos(yOrtogonal/moduloVnp);

    if(zOrtogonal > 0)
        tetaY = 2*M_PI - tetaY;

    Ponto cop = window->obterCop();
//    std::cout << "Centrooo " << centro.obterX() << " " << centro.obterY() << " " << centro.obterZ() << " " << std::endl;

    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    if(perspectiva) {
        for(it = figuras.begin(); it != figuras.end(); it++){
            (*it)->alinharComZ(tetaX, tetaY, cop, true);
        }
    } else {
        for(it = figuras.begin(); it != figuras.end(); it++){
            (*it)->alinharComZ(tetaX, tetaY, centroDaWindow, false);
        }
    }
    double teta = obterAnguloDaWindow();
    for(it = figuras.begin(); it != figuras.end(); it++){
        (*it)->gerarDescricaoPPC(teta);
    }
}

double WindowViewport::obterAnguloDaWindow()
{
    return displayFile->obterAnguloDaWindow();
}

void WindowViewport::arrastarCam(Ponto vetorDirecao)
{
    Ponto centroDaCam = window->obterCentro();
    Ponto cop = window->obterCop();
    Ponto vetorCop(centroDaCam.obterX() - cop.obterX(),centroDaCam.obterY() - cop.obterY(),centroDaCam.obterZ() - cop.obterZ());

    double xOrtogonal = vetorCop.obterY()*vetorDirecao.obterZ() - vetorCop.obterZ()*vetorDirecao.obterY();
    double yOrtogonal = vetorCop.obterZ()*vetorDirecao.obterX() - vetorCop.obterX()*vetorDirecao.obterZ();
    double zOrtogonal = vetorCop.obterX()*vetorDirecao.obterY() - vetorCop.obterY()*vetorDirecao.obterX();
    Ponto vetor(xOrtogonal,yOrtogonal,zOrtogonal);

    rotacionarWindow(vetor,20);
}

void WindowViewport::transformarPontoWindowParaMundo(Ponto &ponto){
    Ponto centro = window->obterCentro();
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto *ponto1Window = pontosWindow.front();
    Ponto *ponto4Window = pontosWindow.back();
    pontosWindow.pop_front();
    Ponto *ponto2Window = pontosWindow.front();
    pontosWindow.push_front(ponto1Window);

    Ponto vetor1(ponto2Window->obterX()-ponto1Window->obterX(), ponto2Window->obterY()-ponto1Window->obterY(), ponto2Window->obterZ()-ponto1Window->obterZ());
    Ponto vetor2(ponto4Window->obterX()-ponto1Window->obterX(), ponto4Window->obterY()-ponto1Window->obterY(), ponto4Window->obterZ()-ponto1Window->obterZ());
    vetor1.normalizarVetor();
    vetor2.normalizarVetor();

    double xOrtogonal = vetor1.obterY()*vetor2.obterZ() - vetor1.obterZ()*vetor2.obterY();
    double yOrtogonal = vetor1.obterZ()*vetor2.obterX() - vetor1.obterX()*vetor2.obterZ();
    double zOrtogonal = vetor1.obterX()*vetor2.obterY() - vetor1.obterY()*vetor2.obterX();

    Ponto vetor3(xOrtogonal, yOrtogonal, zOrtogonal);
    vetor3.normalizarVetor();

    double x = vetor1.obterX()*ponto.obterX() + vetor2.obterX()*ponto.obterY() + vetor3.obterX()*ponto.obterZ() + centro.obterX();
    double y = vetor1.obterY()*ponto.obterX() + vetor2.obterY()*ponto.obterY() + vetor3.obterY()*ponto.obterZ() + centro.obterY();
    double z = vetor1.obterZ()*ponto.obterX() + vetor2.obterZ()*ponto.obterY() + vetor3.obterZ()*ponto.obterZ() + centro.obterZ();
    ponto.setarX(x);
    ponto.setarY(y);
    ponto.setarZ(z);
}

void WindowViewport::setarPerspectiva(bool valor) {
    perspectiva = valor;
    gerarDescricoesPPC();
}
