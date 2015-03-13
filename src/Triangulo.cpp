#include "Triangulo.h"

Triangulo::Triangulo(float base, float altura, Ponto cantoesq):
    base(base/2),
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

void Triangulo::RenderizaPontos(){
    glColor3f(red, green, blue);
    glLineWidth(grafite);

    glBegin(GL_TRIANGLES);
        glTexCoord2f(0.0f, 0.0f); glVertex2f(cantoesq.x, cantoesq.y);
        glTexCoord2f(0.5f, 1.0f); glVertex2f(cantoesq.x + base , altura + cantoesq.y);
        glTexCoord2f(1.0f, 0.0f); glVertex2f(cantoesq.x + 2*base, cantoesq.y);

    glEnd();
}
