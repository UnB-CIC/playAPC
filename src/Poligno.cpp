#include "Poligno.h"

Poligno::Poligno(std::deque<Ponto> pontos):
ponto(pontos)
{
    prox = NULL;
    grafite = 1.0;
}

void Poligno::RenderizaPontos(){
    int tamanho, i;
    Ponto p; //auxiliar

    tamanho = ponto.size();

    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_POLYGON);
    for(i = 0; i < tamanho; i++){
        p = ponto[i];
        glVertex2f(p.x, p.y);
    }
    glEnd();
}

