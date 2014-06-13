#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

class Grupo{
    private:
        Geometria *primeiro;
        GLfloat rotacao;
        Ponto translacao, escala;

    public:
        Grupo(Geometria *primeiro); //Define transforma��es de um grupo
        Grupo(); //Define transforma��es de um supergrupo

        GLfloat getRotacao();
        Ponto getTranslacao();
        Ponto getEscala();
        Geometria* getPrimeiro(); //Retorna primeiro elemento do grupo

        void setRotacao(GLfloat angulo);
        void setTranslacao(Ponto p);
        void setEscala(Ponto p);
};
