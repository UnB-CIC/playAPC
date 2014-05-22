#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

class Pontinho : public Geometria{
    private:
        Ponto p;
    public:
        Pontinho(Ponto p);
        void RenderizaPontos();
};
