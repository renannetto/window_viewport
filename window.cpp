#include "window.h"

Window::Window()
{
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
}

void Window::resetarCoordenadas(){
    xMin = 0;
    yMin = 0;
    xMax = 640;
    yMax = 480;
}

void Window::zoomIn(int percent){
    double passoX = (double)percent*(xMax-xMin)/200;
    double passoY = (double)percent*(yMax-yMin)/200;
    xMin += passoX;
    xMax -= passoX;
    yMin += passoY;
    yMax -= passoY;
}

void Window::zoomOut(int percent){
    double passoX = (double)percent*(xMax-xMin)/((100-percent)*2);
    double passoY = (double)percent*(yMax-yMin)/((100-percent)*2);
    xMin -= passoX;
    yMin -= passoY;
    xMax += passoX;
    yMax += passoY;
}

void Window::moverParaEsquerda(){
    double passoX = 0.1*(xMax-xMin);
    xMin -= passoX;
    xMax -= passoX;
}

void Window::moverParaDireita(){
    double passoX = 0.1*(xMax-xMin);
    xMin += passoX;
    xMax += passoX;
}

void Window::moverParaBaixo(){
    double passoY = 0.1*(yMax-yMin);
    yMin -= passoY;
    yMax -= passoY;
}

void Window::moverParaCima(){
    double passoY = 0.1*(yMax-yMin);
    yMin += passoY;
    yMax += passoY;
}

double Window::obterXMinDaWindow(){
    return xMin;
}

double Window::obterYMinDaWindow(){
    return yMin;
}

double Window::obterXMaxDaWindow(){
    return xMax;
}

double Window::obterYMaxDaWindow(){
    return yMax;
}
