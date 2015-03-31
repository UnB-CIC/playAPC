#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe do Plano Cartesiano 2D
class PlanoCartesiano : public Geometria{
    private:
        std::deque<int> linha;
        float intervalo;
    public:
        PlanoCartesiano(float intervalo);
        void RenderizaPontos();
};

