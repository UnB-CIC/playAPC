#PlayCB


A PlayCB é uma API educacional de programação voltada para os alunos de Computação Gráfica da UnB que tem
como objetivo ilustrar, de maneira gráfica, os conceitos aprendidos durante o curso com aplicações simples. Com
ela, é possível criar animações simples e desenhos estáticos.
A biblioteca consiste em um conjunto de funções para criação e manipulação de formas 2D e utilização de imagens.
Utiliza a API OpenGL e GLFW
A PlayCB foi desenvolvida usando fortemente o conceito de Orientação a Objetos, por praticidade de desenvolvimento
e facilidade de encapsulamento. Entretanto, a playcb.h entrega ao aluno uma interface amigável com
chamadas de funções simples para a criação de todos os objetos, utilizando o paradigma Imperativo.

##Avisos

Esta biblioteca está configurada para executar juntamente com a GLFW 2.7 e qualquer versão da OpenGL

##Versões

####1.0
* Renderização de objetos geométricos

####1.1
* Operações de transformação (move, gira, redimensiona)
* Inserção de grupos de geometrias

####1.2
* Renderização de animações simples (apenas o último grupo poderia ser animado)
* Reformulação das operações de transformação
* Input de tecla

####1.3
* Reformulação da animação (qualquer grupo pode ser animado)
* Inserção de super grupos de grupos
* Reformulação das operações de transformação (para suportar realizar a operação dado um grupo)

####TO DO
* Reformulação da renderização (uso de Display List) para otimização
* Inserção de objetos 3D
