#playAPC
Guia de referência: [Clique aqui](http://playapc.zaghetto.com/)

Página de download: [Clique aqui](https://github.com/sinayra/playAPC/releases/latest)

A playAPC é uma biblioteca educacional de programação voltada para os alunos de Computação Básica da UnB que tem
como objetivo ilustrar, de maneira gráfica, os conceitos aprendidos durante o curso com aplicações simples. Com
ela, é possível criar animações simples e desenhos estáticos.
A biblioteca consiste em um conjunto de funções para criação e manipulação de formas 2D e utilização de imagens.
Utiliza a API OpenGL e GLFW
A playAPC foi desenvolvida usando fortemente o conceito de Orientação a Objetos, por praticidade de desenvolvimento
e facilidade de encapsulamento. Entretanto, a playapc.h entrega ao aluno uma interface amigável com
chamadas de funções simples para a criação de todos os objetos, utilizando o paradigma estruturado.

##Avisos

Esta biblioteca está configurada para executar juntamente com a GLFW 2.7 e qualquer versão da OpenGL

##Versões
####1.7.2 (22/09/2016)
*Corrigido problema de compatibilidade

####1.7.1 (19/09/2016)
* Corrigido problemas de anti-aliasing

####1.7 (19/09/2016)
* Input de mouse
* Adição de função de retirar componentes RGB de imagem BMP 24 bits
* Função AssociaImagem recebe nome de geometria e índice de geometria

####1.6 (15/03/2016)
* Mudança de nome

####1.5.1 (11/03/2016)
* Sobrecarga do operadores +, -, =, ==, +=, -= para estruturas do tipo Ponto

####1.5 (24/02/2016)
* Adicionado função CriaGrafico()
* Corrigido problemas de proporção

####1.4.1 (04/09/2015)
* Adicionado função RetornaTecla()
* Consertado outros bugs menores

####1.4 (12/08/2015)
* Modificação da função Move()
* Criação da função de redisionamento de limites da projeção
* Criação da geometria Elipse
* Integração com biblioteca SOIL
* Reformulação do Guia de Referência

####1.3.1 (13/03/2015)
* Enumeração de geometrias válida
* Funções de criar geometrias retorna índice para cada geometria criada
* Função Pintar recebe nome de geometria e índice de geometria

####1.3 (06/06/2014)
* Reformulação da animação (qualquer grupo pode ser animado)
* Inserção de super grupos de grupos
* Reformulação das operações de transformação (para suportar realizar a operação dado um grupo)

####1.2 (23/05/2014)
* Renderização de animações simples (apenas o último grupo poderia ser animado)
* Reformulação das operações de transformação
* Input de tecla

####1.1 (24/03/2014)
* Operações de transformação (move, gira, redimensiona)
* Inserção de grupos de geometrias

####1.0 (11/01/2014)
* Renderização de objetos geométricos


####TO DO
* Reformulação da renderização (uso de Display List) para otimização
* Inserção de objetos 3D
* Renderização de texto
