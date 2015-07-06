#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe de Retângulo/Quadrado
class Retangulo : public Geometria{
    private:
        float base, altura;
        Ponto cantoesq;
    public:
        Retangulo(float base, float altura, Ponto cantoesq);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};
