#include "Pontinho.h"

Pontinho::Pontinho(Ponto p):
    p(p)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
}

void Pontinho::RenderizaPontos(){
    glColor3f(red, green, blue);
    glPointSize(grafite);
    glBegin(GL_POINTS);
        glVertex2f(p.x,p.y);
    glEnd();
}

