#include "../include/Geometria.h"

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

void Geometria::Desagrupa(Geometria **atual, Geometria *primeiro){
    Geometria *aux, *ant;

    ant = primeiro;
    aux = primeiro->prox;
    if(aux){
        while((*atual) != aux){
            ant = aux;
            aux = aux->prox;
        }
        ant->prox = aux->prox;
    }
    delete(*atual);
    *atual = NULL;
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

