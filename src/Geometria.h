#pragma once
#include "OpenglBase.h"

#define TAMANHOTELA 100

typedef struct{
    GLfloat x;
    GLfloat y;
}Ponto;

typedef enum {
    NADA,
    PONTO,
    RETA,
    TRIANGULO,
    QUADRADO,
    RETANGULO,
    CIRCULO,
    CIRCUNFERENCIA,
    POLIGONO
}geometrias_validas;

class Geometria{
    protected:
        GLfloat red, green, blue;
        GLfloat grafite;
        Geometria *prox;
        GLuint textura;
    public:
        ///M�todos virtuais
        virtual void RenderizaPontos() = 0; //M�todo para desenhar as geometrias, com glBegin() e glEnd()
        ///M�todos em comum de todas as geometrias
        void Cor(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0); //Define cores
        void Grafite(GLfloat grafite = 1.0); //Define grossura da borda
        void Agrupa(Geometria *prox); //Cria lista de geometrias
        Geometria *getProx(); //Pega o pr�ximo elemento da lista
        GLuint getTextura(); //Retorna �rea alocada para textura
        void setTextura(GLuint data); //Seta �rea alocada para textura
};
