#include "../include/Grupo.h"

Grupo::Grupo(Geometria *g) :
    primeiro(g),
    rotacao(0)
{
        Ponto p;
        p.x = 0;
        p.y = 0;

        translacao = p;

        p.x = 1;
        p.y = 1;

        escala = p;
}

Grupo::Grupo() :
    primeiro(NULL),
    rotacao(0)
{
        Ponto p;
        p.x = 0;
        p.y = 0;

        translacao = p;

        p.x = 0;
        p.y = 0;

        escala = p;
}

Geometria* Grupo::getPrimeiro(){
    return primeiro;
}

GLfloat Grupo::getRotacao(){
    return rotacao;
}
Ponto Grupo::getTranslacao(){
    return translacao;
}
Ponto Grupo::getEscala(){
    return escala;
}

void Grupo::setRotacao(GLfloat angulo){
    rotacao = angulo;
}
void Grupo::setTranslacao(Ponto p){
    translacao = p;
}
void Grupo::setEscala(Ponto p){
    escala = p;
}
