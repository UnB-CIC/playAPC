#include "../include/Retangulo.h"

Retangulo::Retangulo(float base, float altura, Ponto cantoesq):
    base(base),
    altura(altura),
    cantoesq(cantoesq)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

void Retangulo::RenderizaPontos(){
    glColor3f(red, green, blue);
    glLineWidth(grafite);

    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(cantoesq.x, cantoesq.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(cantoesq.x + base, cantoesq.y);
        glTexCoord2f(1.0f, 1.0f); glVertex2f(cantoesq.x + base, cantoesq.y + altura);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(cantoesq.x, cantoesq.y + altura);
    glEnd();
}

