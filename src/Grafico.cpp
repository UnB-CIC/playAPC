#include "../include/Grafico.h"

Grafico::Grafico(std::deque<Ponto> pontos):
ponto(pontos)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

void Grafico::RenderizaPontos(){
    int tamanho, i;

    tamanho = ponto.size();

    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_LINES);
    for(i = 0; i < tamanho - 1; i++){
        glVertex2f(ponto[i].x, ponto[i].y);
        glVertex2f(ponto[i+1].x, ponto[i+1].y);
    }
    glEnd();
}

Ponto Grafico::CalculaDeslocamento(Ponto p){
    Ponto d;

    d.x = p.x - ponto[0].x;
    d.y = p.y - ponto[0].y;

    return d;
}

