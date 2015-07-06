
#include "../include/Elipse.h"

Elipse::Elipse(float a, float b, Ponto meio):
    a(a),
    b(b),
    meio(meio)
{
    prox = NULL;
    grafite = 1.0;
    textura = 0;
    red = 0.0;
    green = 0.0;
    blue = 0.0;
    DEG2RAD = 3.14159/180.0;
}

void Elipse::RenderizaPontos(){

    glColor3f(red, green, blue);
    glLineWidth(grafite);
    glBegin(GL_TRIANGLE_FAN);

	for(int i=0; i < 360; i++){
		float degInRad = i*DEG2RAD;
		glTexCoord2f((cos(degInRad) + 1.0) * 0.5, (sin(degInRad) + 1.0) * 0.5);
		glVertex2f(cos(degInRad)*a + meio.x,sin(degInRad)*b + meio.y);
	}
	glEnd();

}

Ponto Elipse::CalculaDeslocamento(Ponto p){
    Ponto d;

    d.x = p.x - meio.x;
    d.y = p.y - meio.y;

    return d;
}
