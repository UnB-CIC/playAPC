#pragma once
#include "OpenglBase.h"

struct Ponto{
    GLfloat x;
    GLfloat y;

    inline Ponto operator+(const Ponto& rhs) const{
        return {x + rhs.x,y + rhs.y};
    }

    inline Ponto operator+=(const Ponto& rhs){
        x += rhs.x;
        y += rhs.y;

        return {x,y};
    }

    inline Ponto operator-(const Ponto& rhs) const{
        return {x - rhs.x,y - rhs.y};
    }

    inline Ponto operator-=(const Ponto& rhs){
        x -= rhs.x;
        y -= rhs.y;

        return {x,y};
    }

    inline bool operator==(const Ponto& rhs) const{
        return (x == rhs.x && y == rhs.y);
    }

    inline bool operator!=(const Ponto& rhs) const{
        return !(x == rhs.x && y == rhs.y);
    }

    inline Ponto operator=(const Ponto& rhs){
        x = rhs.x;
        y = rhs.y;

        return {x,y};
    }
};

///Classe abstrata de Geometria
class Geometria{
    protected:
        GLfloat red, green, blue;
        GLfloat grafite;
        Geometria *prox;
        GLuint textura;
    public:
        ///M�todos virtuais
        virtual void RenderizaPontos() = 0; //M�todo para desenhar as geometrias, com glBegin() e glEnd()
        virtual Ponto CalculaDeslocamento(Ponto p) = 0;
        ///M�todos em comum de todas as geometrias
        void Cor(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0); //Define cores
        void Grafite(GLfloat grafite = 1.0); //Define grossura da borda
        void Agrupa(Geometria *prox); //Cria lista de geometrias
        void Desagrupa(Geometria **atual, Geometria *primeiro); //Tira da lista algum elemento
        Geometria *getProx(); //Pega o pr�ximo elemento da lista
        GLuint getTextura(); //Retorna �rea alocada para textura
        void setTextura(GLuint data); //Seta �rea alocada para textura
};
