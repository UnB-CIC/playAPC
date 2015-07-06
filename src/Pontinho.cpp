#include "../include/Pontinho.h"

Pontinho::Pontinho(Ponto p):
    p(p)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

void Pontinho::RenderizaPontos(){
    glColor3f(red, green, blue);
    glPointSize(grafite);
    glBegin(GL_POINTS);
        glVertex2f(p.x,p.y);
    glEnd();
}

Ponto Pontinho::CalculaDeslocamento(Ponto p1){
    Ponto d;

    d.x = p1.x - p.x;
    d.y = p1.y - p.y;

    return d;
}


