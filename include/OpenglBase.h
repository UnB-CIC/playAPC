#pragma once

// Bibliotecas b�sicas
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <deque>

// Biblioteca gr�ficas
#include <GL/glfw.h>
#include <GL/glu.h>
/// Inicializa tudo referente a opengl
/// E destroi tudo tamb�m

//Defines para todas as classes

class OpenglBase{

    public:
        ///Inicializa GLFW
        static bool inicializaContexto();

        ///Abre janela com altura e largura especificada
        //E inicializa alguns eventos necess�rios
        static bool inicializaJanela(int largura = 800, int altura = 600);

        ///Muda nome da janela
        static void mudaNomeJanela(const char *titulo = "Meu programa");

        ///Atualiza cena
        static void atualizarTela();

        ///Finaliza tudo
        static void encerraContexto();
};

