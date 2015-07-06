#include "../include/Circunferencia.h"

Circunferencia::Circunferencia(GLfloat raio, Ponto meio):
    raio(raio),
    meio(meio)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
}

void Circunferencia::RenderizaPontos(){
    int i;
    float theta, tangetial_factor, radial_factor, x, y;

    theta = 2 * PI/360;
    tangetial_factor = tanf(theta);
    radial_factor = cosf(theta);

    x = raio;
    y = 0;

    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_LINE_LOOP);

    for (i = 0; i < 360; i++){
        glVertex2f(x + meio.x, y + meio.y);

        float tx = -y;
        float ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
   }

   glEnd();

}

Ponto Circunferencia::CalculaDeslocamento(Ponto p){
    Ponto d;

    d.x = p.x - meio.x;
    d.y = p.y - meio.y;

    return d;
}

