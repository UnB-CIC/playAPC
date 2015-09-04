#pragma once
#include "OpenglBase.h"
#include "Grupo.h"
#include "SOIL/SOIL.h"

#define N_KEYS GLFW_KEY_LAST

#ifndef GL_BGR
#define GL_BGR 0x80E0
#endif

///Classe de gerenciamentos de eventos da OpenGL
class Evento{
    public:
        ///Inicializa contexto e abre janela
        Evento(int altura, int largura, const char* titulo);

        ///Destr�i tudo o que tem que destruir
        ~Evento();

        ///Renderiza cena
        void renderiza(); //Swap buffer
        void limpaBuffer(); //glClear
        void PintaFundo(float red, float green, float blue); //glClearColor
        void transformacao(Grupo *g, Grupo *sg); //Realiza todas as tr�s transforma��es: scaled, translated, rotated
        GLuint BindImagem(const char *data); //glTexParameter
        void HabilitaImagem(Geometria *g); //glEnable
        void DesabilitaImagem(); //glDisable
        int TeclaPressionada(int key);
        int pegaTecla();

        static int getTamanhoTela();
        static void setTamanhoTela(int novo);

    private:
        float red, green, blue;
        static int tamanhoTela;
        bool keyChanged[N_KEYS], keyPressed[N_KEYS];
        static void GLFWCALL redimensionaJanela(int largura, int altura);
};
