#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe de Ponto
class Pontinho : public Geometria{
    private:
        Ponto p;
    public:
        Pontinho(Ponto p);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};
