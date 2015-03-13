 /**
 * \file  playcb.h
 * \brief  Respons�vel pela interface da playcb com o aluno
 *
 * Para seu funcionamento correto, s�o necess�rio duas fun��es: a AbreJanela() e a Desenha() ou Desenha1Frame(). A Desenha(), em especial,
 * cria o loop de desenho travado em 30fps, enquanto a Desenha1Frame() necessariamente precisa estar dentro de um loop ou n�o funcionar� corretamente.
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
 *  \defgroup init Fun��es necess�rias para o funcionamento da playcb
 *
 *  Este conjunto cont�m todas as inicializa��es e chamadas de fun��es necess�rias para a comunica��o entre a interface da playcb e a API opengl
 *
 */
void AbreJanela(int largura, int altura, std::string titulo); //Abre janela e prepara eventos da opengl
void Desenha(); //Loop de desenho
int Desenha1Frame(); //Desenha apenas um frame do desenho
void LimpaDesenho(); //Destr�i objetos
/**
 *  \defgroup aux Fun��es para organizar e auxiliar o desenvolvimento
 *
 * Este conjunto cria um modo que o aluno possa organizar as geometrias em grupos (geometrias que partilham a mesma transforma��o) e exibir um plano cartesiano
 *
 */
void MostraPlanoCartesiano(int intervalo); //Exibe linhas de plano cartesiano de -100 � 100
int CriaGrupo(); //Cria conjunto de geometrias que partilham as mesmas transforma��es
int CriaSuperGrupo(); //Cria conjunto de grupos que partilham a mesma transforma��o resultante
void ApagaGrupo(int index); //Apaga um grupo de geometrias
int ApertouTecla(int tecla); //Verifica se tecla foi pressionada

/**
 *  \defgroup cor Fun��es para associa��o de cores/imagem
 *
 * Este conjunto define as fun��es para modificar cores em uma geometria ou o fundo da tela. Al�m disso, cont�m as fun��es de associa��o de geometria e imagem
 *
 */
void Pintar(int red, int green, int blue); //Define cor da �ltima geometria definida
void Grafite(float grossura); //Define largura da borda
void PintarFundo(int red, int green, int blue); //Define cor de fundo
int PreparaImagem(unsigned char *data, int largura, int altura); //Aloca espa�o de mem�ria para a imagem ser colocada na imagem
void AssociaImagem(int textura); //Associa textura com geometria

/**
 *  \defgroup transf Fun��es para anima��es simples/transforma��es
 *
 * Este conjunto define as fun��es que realizam a anima��o simples ou transforma��o (rota��o, tranla��o e redimensionamento) de uma geometria
 *
 */
void Gira(float angulo, int index = -1); //Gira em x um grupo
void Move(Ponto p, int index = -1); //Move em x,y um grupo
void Redimensiona(float x, float y, int index = -1); //Redimensiona um grupo

void SuperGira(float angulo, int index = -1); //Gira em x um grupo
void SuperMove(Ponto p, int index = -1); //Move em x,y um grupo
void SuperRedimensiona(float x, float y, int index = -1); //Redimensiona um grupo

/**
 *  \defgroup geo Fun��es para cria��o de geometrias
 *
 * Este conjunto cria objetos j� previamente definidos
 *
 */
void CriaPonto(Ponto p);
void CriaReta(Ponto p1, Ponto p2);
void CriaPoligono(short int qtd, ...); //OBS: n�o tem como colocar uma imagem em um poligno
void CriaPoligonoVetor(short int index, Ponto *p); //OBS: n�o tem como colocar uma imagem em um poligno
void CriaCirculo(float raio, Ponto meio);
void CriaCircunferencia(float raio, Ponto meio);
void CriaQuadrado(float lado, Ponto cantoesq);
void CriaRetangulo(float base, float altura, Ponto cantoesq);
void CriaTriangulo(float base, float altura, Ponto cantoesq);
