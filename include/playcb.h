
 /**
 * \file  playcb.h
 * \brief  Responsável pela interface da playcb com o aluno
 *
 * Para seu funcionamento correto, são necessário duas funções: a AbreJanela() e a Desenha() ou Desenha1Frame(). A Desenha(), em especial,
 * cria o loop de desenho travado em 30fps, enquanto a Desenha1Frame() necessariamente precisa estar dentro de um loop ou não funcionará corretamente.
 *
 */

#pragma once
#include "Evento.h"
#include "Reta.h"
#include "PlanoCartesiano.h"
#include "Poligono.h"
#include "Circulo.h"
#include "Circunferencia.h"
#include "Retangulo.h"
#include "Triangulo.h"
#include "Grupo.h"
#include "Pontinho.h"
#include <vector>
#include <algorithm>

/**
 * \enum Geometrias válidas
 * \brief Tipos de geometrias possíveis para serem referenciadas por ::Pintar
 */
typedef enum { /// valor default
    NADA, /// referente a ::CriaPonto
    PONTO, /// referente a ::CriaReta
    RETA, /// referente a ::CriaTriangulo
    TRIANGULO, /// referente a ::CriaQuadrado
    QUADRADO, /// referente a ::CriaRetangulo
    RETANGULO, /// referente a ::CriaCirculo
    CIRCULO, /// referente a ::CriaCircunferencia
    CIRCUNFERENCIA, /// referente a ::CriaPoligono e ::CriaPoligonoVetor
    POLIGONO
}geometrias_validas;

/**
 *  \defgroup init Funções necessárias para o funcionamento da playcb
 *
 *  Este conjunto contém todas as inicializações e chamadas de funções necessárias para a comunicação entre a interface da playcb e a API opengl
 *
 */
void AbreJanela(int largura, int altura, const char *titulo); //Abre janela e prepara eventos da opengl
void Desenha(); //Loop de desenho
int Desenha1Frame(); //Desenha apenas um frame do desenho
void LimpaDesenho(); //Destrói objetos
/**
 *  \defgroup aux Funções para organizar e auxiliar o desenvolvimento
 *
 * Este conjunto cria um modo que o aluno possa organizar as geometrias em grupos (geometrias que partilham a mesma transformação) e exibir um plano cartesiano
 *
 */
void MostraPlanoCartesiano(int intervalo); //Exibe linhas de plano cartesiano de -100 à 100
int CriaGrupo(); //Cria conjunto de geometrias que partilham as mesmas transformações
int CriaSuperGrupo(); //Cria conjunto de grupos que partilham a mesma transformação resultante
void ApagaGrupo(int index); //Apaga um grupo de geometrias
int ApertouTecla(int tecla); //Verifica se tecla foi pressionada

/**
 *  \defgroup cor Funções para associação de cores/imagem
 *
 * Este conjunto define as funções para modificar cores em uma geometria ou o fundo da tela. Além disso, contém as funções de associação de geometria e imagem
 *
 */
void Pintar(int red, int green, int blue, geometrias_validas nome = NADA, int index = -1); //Define cor da última geometria definida
void Grafite(float grossura); //Define largura da borda
void PintarFundo(int red, int green, int blue); //Define cor de fundo
int PreparaImagem(unsigned char *data, int largura, int altura); //Aloca espaço de memória para a imagem ser colocada na imagem
void AssociaImagem(int textura); //Associa textura com geometria

/**
 *  \defgroup transf Funções para animações simples/transformações
 *
 * Este conjunto define as funções que realizam a animação simples ou transformação (rotação, tranlação e redimensionamento) de uma geometria
 *
 */
void Gira(float angulo, int index = -1); //Gira em x um grupo
void Move(Ponto p, int index = -1); //Move em x,y um grupo
void Redimensiona(float x, float y, int index = -1); //Redimensiona um grupo

void SuperGira(float angulo, int index = -1); //Gira em x um grupo
void SuperMove(Ponto p, int index = -1); //Move em x,y um grupo
void SuperRedimensiona(float x, float y, int index = -1); //Redimensiona um grupo

/**
 *  \defgroup geo Funções para criação de geometrias
 *
 * Este conjunto cria objetos já previamente definidos
 *
 */
int CriaPonto(Ponto p);
int CriaReta(Ponto p1, Ponto p2);
int CriaPoligono(short int qtd, ...); //OBS: não tem como colocar uma imagem em um poligno
int CriaPoligonoVetor(short int index, Ponto *p); //OBS: não tem como colocar uma imagem em um poligno
int CriaCirculo(float raio, Ponto meio);
int CriaCircunferencia(float raio, Ponto meio);
int CriaQuadrado(float lado, Ponto cantoesq);
int CriaRetangulo(float base, float altura, Ponto cantoesq);
int CriaTriangulo(float base, float altura, Ponto cantoesq);
