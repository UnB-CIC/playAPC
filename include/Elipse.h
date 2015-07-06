#pragma once
#include "OpenglBase.h"
#include "Geometria.h"
#include <math.h>

#define PI 3.14159

///Classe de círculo, com PI definido
class Elipse : public Geometria{
    private:
        Ponto foco1, foco2;
        Ponto meio;
        float DEG2RAD, a, b;
    public:
        Elipse(float a, float b, Ponto meio);
        void RenderizaPontos();
};

