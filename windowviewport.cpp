#include "windowviewport.h"
#include "iostream"

WindowViewport::WindowViewport()
{
    displayFile = new DisplayFile();
    window = displayFile->obterFiguras().front();
}

WindowViewport::~WindowViewport(){
    delete window;
    delete displayFile;
}

void WindowViewport::resetarWindow(){
    delete(window);
    window = displayFile->criarWindow();
    gerarDescricoesPPC();
}

string WindowViewport::adicionarFigura(Tipo tipo, list<Ponto*> pontos, int vermelho, int verde, int azul)
{
    Cor cor = Cor(vermelho, verde, azul);
    return displayFile->adicionarFigura(tipo, pontos, cor);
}

list<Figura*> WindowViewport::obterFiguras(){
    return displayFile->obterFiguras();
}

void WindowViewport::destruirFigura(string nome){
    displayFile->destruirFigura(nome);
}

void WindowViewport::zoomIn(int percent)
{
    window->escalonar2D(1-(double)percent/100, 1-(double)percent/100);
    //window->escalonar2D((double)100/(percent+100), (double)100/(percent+100));
}

void WindowViewport::zoomOut(int percent)
{
    window->escalonar2D((double)100/(100-percent), (double)100/(100-percent));
    //window->escalonar2D(1+(double)percent/100, 1+(double)percent/100);
}

void WindowViewport::moverParaEsquerda()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+180)*M_PI/180;
    std::cout << teta << std::endl;
    double modulo = 0.1*(obterXMaxDaWindowPPC()-obterXMinDaWindowPPC());
    double vX = modulo*cos(teta);
    double vY = modulo*sin(teta);
    std::cout << vX << " " << vY << std::endl;
    window->transladar2D(vX, vY);
}

void WindowViewport::moverParaDireita()
{
    double teta = obterAnguloDaWindow();
    teta = teta*M_PI/180;
    std::cout << teta << std::endl;
    double modulo = 0.1*(obterXMaxDaWindowPPC()-obterXMinDaWindowPPC());
    double vX = modulo*cos(teta);
    double vY = modulo*sin(teta);
    std::cout << vX << " " << vY << std::endl;
    window->transladar2D(vX, vY);
}

void WindowViewport::moverParaBaixo()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+270)*M_PI/180;
    std::cout << teta << std::endl;
    double modulo = 0.1*(obterYMaxDaWindowPPC()-obterYMinDaWindowPPC());
    double vX = modulo*cos(teta);
    double vY = modulo*sin(teta);
    std::cout << vX << " " << vY << std::endl;
    window->transladar2D(vX, vY);
}

void WindowViewport::moverParaCima()
{
    double teta = obterAnguloDaWindow();
    teta = (teta+90)*M_PI/180;
    std::cout << teta << std::endl;
    double modulo = 0.1*(obterYMaxDaWindowPPC()-obterYMinDaWindowPPC());
    double vX = modulo*cos(teta);
    double vY = modulo*sin(teta);
    std::cout << vX << " " << vY << std::endl;
    window->transladar2D(vX, vY);
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

void WindowViewport::transladar2D(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->transladar2D(vX,vY);
            break;
        }
    }
}

void WindowViewport::escalonar2D(string nomeFigura, double vX, double vY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->escalonar2D(vX,vY);
            break;
        }
    }
}

void WindowViewport::rotacionarNaOrigem2D(string nomeFigura, double teta){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNaOrigem2D(teta);
            break;
        }
    }
}

void WindowViewport::rotacionarNoCentro2D(string nomeFigura, double teta){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoCentro2D(teta);
            break;
        }
    }
}

void WindowViewport::rotacionarNoPonto2D(string nomeFigura, double teta, double pX, double pY){
    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        if((*it)->obterNome()==nomeFigura){
            (*it)->rotacionarNoPonto2D(teta,pX,pY);
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
    Ponto centro = window->obterCentro();
    double wcX = centro.obterX();
    double wcY = centro.obterY();

    double teta = obterAnguloDaWindow();

    list<Figura*> figuras = displayFile->obterFiguras();
    list<Figura*>::iterator it;
    for(it = figuras.begin(); it != figuras.end(); it++){
        (*it)->gerarDescricaoPPC(wcX, wcY, teta);
    }
}

double WindowViewport::obterAnguloDaWindow()
{
    list<Ponto*> pontosWindow = window->obterPontos();
    Ponto* pontoInicial = pontosWindow.front();
    Ponto* pontoFinal = pontosWindow.back();
    Ponto* vetor = new Ponto(pontoFinal->obterX()-pontoInicial->obterX(), pontoFinal->obterY()-pontoInicial->obterY());

    double x = vetor->obterX();
    double y = vetor->obterY();

    double teta = acos(y/sqrt(x*x+y*y));
    teta = (teta*180)/PI;

    if (pontoInicial->obterX()>pontoFinal->obterX())
        teta = 360 - teta;

    return teta;
}
