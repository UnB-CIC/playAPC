#pragma once
#include "OpenglBase.h"
#include "Geometria.h"
#include <math.h>

#define PI 3.14159

///Classe do círculo, com PI definido
class Circunferencia : public Geometria{
    private:
        GLfloat raio;
        Ponto meio;
    public:
        Circunferencia(GLfloat raio, Ponto meio);
        void RenderizaPontos();
};

