#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

class Reta : public Geometria{
    private:
        Ponto p1, p2;
    public:
        Reta(Ponto p1, Ponto p2);
        void RenderizaPontos();
};
