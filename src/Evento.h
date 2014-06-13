#pragma once
#include "OpenglBase.h"
#include "Grupo.h"

#define TAMANHOTELA 100
#define N_KEYS GLFW_KEY_LAST

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif

class Evento{
    public:
        ///Inicializa contexto e abre janela
        Evento(int altura, int largura, std::string titulo);

        ///Destrói tudo o que tem que destruir
        ~Evento();

        ///Renderiza cena
        void renderiza(); //Swap buffer
        void limpaBuffer(); //glClear
        void PintaFundo(float red, float green, float blue); //glClearColor
        void transformacao(Grupo *g, Grupo *sg); //Realiza todas as três transformações: scaled, translated, rotated
        GLuint BindImagem(unsigned char *data, int largura, int altura); //glTexParameter
        void HabilitaImagem(Geometria *g); //glEnable
        void DesabilitaImagem(); //glDisable
        int TeclaPressionada(int key);

    private:
        float red, green, blue;
        bool keyChanged[N_KEYS], keyPressed[N_KEYS];
        static void GLFWCALL redimensionaJanela(int largura, int altura);
};
