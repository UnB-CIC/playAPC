#include "../include/Reta.h"

Reta::Reta(Ponto ponto1, Ponto ponto2):
    p1(ponto1),
    p2(ponto2)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

void Reta::RenderizaPontos(){
    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_LINES);
        glVertex2f(p1.x,p1.y);
        glVertex2f(p2.x,p2.y);
    glEnd();
}

Ponto Reta::CalculaDeslocamento(Ponto p){
    Ponto d;

    d.x = p.x - p1.x;
    d.y = p.y - p1.y;

    return d;
}
