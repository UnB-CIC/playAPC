#include "Geometria.h"

void Geometria::Cor(GLfloat red, GLfloat green, GLfloat blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void Geometria::Grafite(GLfloat grafite){
    this->grafite = grafite;
}

void Geometria::Agrupa(Geometria *prox){
    this->prox = prox;
}

Geometria* Geometria::getProx(){
    return this->prox;
}

GLuint Geometria::getTextura(){
    return textura;
}

void Geometria::setTextura(GLuint data){
    textura = data;
}

