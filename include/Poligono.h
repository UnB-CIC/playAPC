#pragma once
#include "OpenglBase.h"
#include "Geometria.h"
#include <math.h>

///Classe de Poligono
class Poligono : public Geometria{
    private:
        std::deque<Ponto> ponto;
    public:
        Poligono(std::deque<Ponto> pontos);
        void RenderizaPontos();
};

