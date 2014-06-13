 /**
 * \file  playcb.h
 * \brief  Responsável pela interface da playcb com o aluno
 *
 * Para seu funcionamento correto, são necessário duas funções: a AbreJanela() e a Desenha() ou Desenha1Frame(). A Desenha(), em especial,
 * cria o loop de desenho travado em 30fps, enquanto a Desenha1Frame() necessariamente precisa estar dentro de um loop ou não funcionará corretamente.
 *
 */

#pragma once
#include "src/Evento.h"
#include "src/Reta.h"
#include "src/PlanoCartesiano.h"
#include "src/Poligono.h"
#include "src/Circulo.h"
#include "src/Circunferencia.h"
#include "src/Retangulo.h"
#include "src/Triangulo.h"
#include "src/Grupo.h"
#include "src/Pontinho.h"
#include <vector>
#include <algorithm>

/**
 *  \defgroup init Funções necessárias para o funcionamento da playcb
 *
 *  Este conjunto contém todas as inicializações e chamadas de funções necessárias para a comunicação entre a interface da playcb e a API opengl
 *
 */
void AbreJanela(int largura, int altura, std::string titulo); //Abre janela e prepara eventos da opengl
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
void Pintar(int red, int green, int blue); //Define cor da última geometria definida
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
void CriaPonto(Ponto p);
void CriaReta(Ponto p1, Ponto p2);
void CriaPoligono(short int qtd, ...); //OBS: não tem como colocar uma imagem em um poligno
void CriaPoligonoVetor(short int index, Ponto *p); //OBS: não tem como colocar uma imagem em um poligno
void CriaCirculo(float raio, Ponto meio);
void CriaCircunferencia(float raio, Ponto meio);
void CriaQuadrado(float lado, Ponto cantoesq);
void CriaRetangulo(float base, float altura, Ponto cantoesq);
void CriaTriangulo(float base, float altura, Ponto cantoesq);
