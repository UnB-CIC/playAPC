#pragma once
#include "OpenglBase.h"
#include "Geometria.h"

///Classe de Triângulo isóceles
class Triangulo : public Geometria{
    private:
        float base, altura;
        Ponto cantoesq;
    public:
        Triangulo(float base, float altura, Ponto cantoesq);
        void RenderizaPontos();
        Ponto CalculaDeslocamento(Ponto p);
};
