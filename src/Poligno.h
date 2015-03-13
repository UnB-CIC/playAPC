#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

class Poligno : public Geometria{
    private:
        std::deque<Ponto> ponto;
    public:
        Poligno(std::deque<Ponto> pontos);
        void RenderizaPontos();
};

