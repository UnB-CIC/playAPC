#pragma once
#include "OpenglBase.h"

///Classe abstrata de Geometria
class Geometria{
    protected:
        GLfloat red, green, blue;
        GLfloat grafite;
        Geometria *prox;
        GLuint textura;
    public:
        ///Métodos virtuais
        virtual void RenderizaPontos() = 0; //Método para desenhar as geometrias, com glBegin() e glEnd()
        virtual Ponto CalculaDeslocamento(Ponto p) = 0;
        ///Métodos em comum de todas as geometrias
        void Cor(GLfloat red = 0, GLfloat green = 0, GLfloat blue = 0); //Define cores
        void Grafite(GLfloat grafite = 1.0); //Define grossura da borda
        void Agrupa(Geometria *prox); //Cria lista de geometrias
        void Desagrupa(Geometria **atual, Geometria *primeiro); //Tira da lista algum elemento
        Geometria *getProx(); //Pega o próximo elemento da lista
        GLuint getTextura(); //Retorna área alocada para textura
        void setTextura(GLuint data); //Seta área alocada para textura
};
