#pragma once
#include "OpenglBase.h"
#include "Geometria.h"
#include <math.h>

///Classe de Grafico
class Grafico : public Geometria{
    private:
        std::deque<Ponto> ponto;
    public:
        Grafico(std::deque<Ponto> pontos);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};

