#include "Poligono.h"

Poligono::Poligono(std::deque<Ponto> pontos):
ponto(pontos)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
}

void Poligono::RenderizaPontos(){
    int tamanho, i;

    tamanho = ponto.size();

    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_POLYGON);
    for(i = 0; i < tamanho; i++)
        glVertex2f(ponto[i].x, ponto[i].y);

    glEnd();
}

