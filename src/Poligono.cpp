#include "../include/Poligono.h"

Poligono::Poligono(std::deque<Ponto> pontos):
ponto(pontos)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
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

Ponto Poligono::CalculaDeslocamento(Ponto p){
    Ponto d;

    d.x = p.x - ponto[0].x;
    d.y = p.y - ponto[0].y;

    return d;
}

