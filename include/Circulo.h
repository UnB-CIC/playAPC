#pragma once
#include "OpenglBase.h"
#include "Geometria.h"
#include <math.h>

#define PI 3.14159

///Classe de círculo, com PI definido
class Circulo : public Geometria{
    private:
        GLfloat raio;
        Ponto meio;
    public:
        Circulo(GLfloat raio, Ponto meio);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};

