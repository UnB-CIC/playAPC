#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe de Tri�ngulo is�celes
class Triangulo : public Geometria{
    private:
        float base, altura;
        Ponto cantoesq;
    public:
        Triangulo(float base, float altura, Ponto cantoesq);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};
