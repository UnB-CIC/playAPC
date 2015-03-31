#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe de Reta
class Reta : public Geometria{
    private:
        Ponto p1, p2;
    public:
        Reta(Ponto p1, Ponto p2);
        void RenderizaPontos();
};
