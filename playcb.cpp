#include "playcb.h"

Evento *evento = NULL;
PlanoCartesiano *plano = NULL;
std::vector<Reta*> reta;
std::vector<Poligono*> poligono;
std::vector<Circulo*> circulo;
std::vector<Circunferencia*> circunferencia;
std::vector<Retangulo*> retangulo;
std::vector<Triangulo*> triangulo;
std::vector<Pontinho*> ponto;
Geometria *ultima = NULL;
std::vector<Grupo*> grupo;

/************************************************************************/
/**
 *  \brief   Abre uma janela vazia
 *  \ingroup init
 *  \param   largura largura da janela
 *  \param   altura altura da janela
 *  \param   titulo T�tulo da janela
 */
/************************************************************************/

void AbreJanela(int largura, int altura, std::string titulo){
    evento = new Evento(largura, altura, titulo);
}

/************************************************************************/
/**
 *  \brief   Cria um novo grupo de geometrias. Se n�o for utilizada, todas as geometrias criadas ser�o de apenas um grupo
 *  \ingroup aux
 *
 *
 *  Um grupo nada mais � que um conjunto de geometrias. Com ele, � poss�vel separar os desenhos em m�dulos. Cada nova
 *  chamada para esta fun��o cria um novo grupo, que poder� realizar transforma��es independentes em rela��o ao cen�rio. Ou seja,
 *  � poss�vel criar, em um mesmo cen�rio, duas anima��es diferentes e independentes.
 *
 *  No conceito da OpenGL, um grupo define uma nova matriz de proje��o. Corresponde ao comando glPushMatrix.
 */
/************************************************************************/

void CriaGrupo(){
    if(!grupo.empty()){
        grupo.resize(grupo.size() + 1);
    }
}

void InsereGrupo(){
    int index = grupo.size() - 1;
    Geometria *aux;

    if(grupo.empty() || !grupo[index]){
        if(grupo.empty()){
            std::vector<Grupo*>::iterator it;
            it = grupo.end();
            grupo.insert(it, new Grupo(ultima)); //adiciona a �ltima geometria criada em uma nova posi��o no grupo
        }
        else
            grupo[index] = new Grupo(ultima);
    }
    else{
        aux = grupo[index]->getPrimeiro();

        while(aux->getProx())
            aux = aux->getProx();
        aux->Agrupa(ultima);
    }
}

/************************************************************************/
/**
 *  \brief   Cria uma reta
 *  \ingroup geo
 *  \param   p1 Primeiro ponto
 *  \param   p2 Segundo ponto
 */
/************************************************************************/

void CriaReta(Ponto p1, Ponto p2){
    reta.push_back(new Reta(p1, p2));

    ultima = reta.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um ponto
 *  \ingroup geo
 *  \param   p Ponto
 */
/************************************************************************/

void CriaPonto(Ponto p){
    ponto.push_back(new Pontinho(p));

    ultima = ponto.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um c�rculo a partir do centro
 *  \ingroup geo
 *  \param   raio Raio do c�rculo
 *  \param   meio Ponto indicando o centro do c�rculo
 */
/************************************************************************/

void CriaCirculo(float raio, Ponto meio){
    circulo.push_back(new Circulo(raio, meio));

    ultima = circulo.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria uma circunfer�ncia a partir do centro
 *  \ingroup geo
 *  \param   raio Raio da circunfer�ncia
 *  \param   meio Ponto indicando o centro da circunfer�ncia
 */
/************************************************************************/

void CriaCircunferencia(float raio, Ponto meio){
    circunferencia.push_back(new Circunferencia(raio, meio));

    ultima = circunferencia.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um ret�ngulo a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do ret�ngulo
 *  \param   altura Altura do ret�ngulo
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 */
/************************************************************************/

void CriaRetangulo(float base, float altura, Ponto cantoesq){
    retangulo.push_back(new Retangulo(base, altura, cantoesq));

    ultima = retangulo.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um quadrado a partir do canto esquerdo
 *  \ingroup geo
 *  \param   lado Tamanho do lado do quadrado
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 */
/************************************************************************/

void CriaQuadrado(float lado, Ponto cantoesq){
    retangulo.push_back(new Retangulo(lado, lado, cantoesq));

    ultima = retangulo.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um tri�ngulo equil�tero a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do tri�ngulo
 *  \param   altura Altura do tri�ngulo
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 */
/************************************************************************/
void CriaTriangulo(float base, float altura, Ponto cantoesq){
    triangulo.push_back(new Triangulo(base, altura, cantoesq));

    ultima = triangulo.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria uma geometria convexa qualquer
 *  \ingroup geo
 *  \param   qtd Quantidade de Pontos
 *  \param   ... Ponto
  */
/************************************************************************/
void CriaPoligono(short int qtd, ...){
    int i;
    Ponto p; //auxiliar
    std::deque <Ponto> pontos;
    va_list pn; //Lista de pontos (p1, p2, ..., pn) que foram passados como argumentos

    va_start(pn, qtd);

    for(i = 0; i < qtd; i++){
        p = va_arg(pn, Ponto);
        pontos.push_front(p); //adiciona os pontos na ordem que foi colocado na fun��o
    }
    poligono.push_back(new Poligono(pontos));

    ultima = poligono.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um pol�gono qualquer a partir do vetor de pontos
 *  \ingroup geo
 *  \param   index Tamanho do vetor
 *  \param   p Vetor de pontos
 */
/************************************************************************/
void CriaPoligonoVetor(short int index, Ponto *p){
    std::deque <Ponto> pontos;
    int i;

    for(i = 0; i < index; i++)
        pontos.push_front(p[i]);

    poligono.push_back(new Poligono(pontos));

    ultima = poligono.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Modifica a largura da borda de uma geometria
 *  \ingroup cor
 *  \param   grossura Largura da borda
 */
/************************************************************************/
void Grafite(float grossura){
    ultima->Grafite(grossura);
}

/************************************************************************/
/**
 *  \brief   Modifica a cor de uma geometria
 *  \ingroup cor
 *  \param   red Valor de vermelho de 0 � 255
 *  \param   green Valor de verde de 0 � 255
 *  \param   blue Valor de azul de 0 � 255
 */
/************************************************************************/
void Pintar(int red, int green, int blue){
    float vermelho, verde, azul;

    vermelho = (float)red/255;
    verde = (float)green/255;
    azul = (float)blue/255;

    ultima->Cor(vermelho, verde, azul);
}

/************************************************************************/
/**
 *  \brief   Exibe linhas do plano cartesiano de -100 � 100, centrada no (0,0)
 *  \ingroup aux
 *  \param   intervalo Intervalo entre uma linha e outra
 */
/************************************************************************/
void MostraPlanoCartesiano(int intervalo){
    plano = new PlanoCartesiano(intervalo);
}

/************************************************************************/
/**
 *  \brief   Gira um grupo de geometrias em x
 *  \ingroup transf
 *  \param   angulo �ngulo em graus
 */
/************************************************************************/
void Gira(float angulo){
    int index = grupo.size() - 1;
    grupo[index]->setRotacao(angulo);
}

/************************************************************************/
/**
 *  \brief   Translada um grupo para o ponto p
 *  \ingroup transf
 *  \param   p Coordenadas para o qual o grupo deve ser transladado
 */
/************************************************************************/
void Move(Ponto p){
    int index = grupo.size() - 1;
    grupo[index]->setTranslacao(p);
}

/************************************************************************/
/**
 *  \brief   Redimensiona um grupo em x e em y
 *  \ingroup transf
 *  \param   x Porcentagem que deve ser redimensionado em x
 *  \param   y Porcentagem que deve ser redimensionado em y
 */
/************************************************************************/
void Redimensiona(float x, float y){
    int index = grupo.size() - 1;
    Ponto p;
    p.x = x;
    p.y = y;
    grupo[index]->setEscala(p);
}

void mostraGeometria(){
    Geometria *aux;
    std::vector<Grupo*>::iterator it;

    //se plano n�o for nulo, mostre
    glPushMatrix();
    if(plano)
        plano->RenderizaPontos();
    glPopMatrix();

    for(it = grupo.begin(); it != grupo.end(); ++it){
        aux = (*it)->getPrimeiro();

        glPushMatrix();
        evento->transformacao(*it);
        while(aux){
            evento->HabilitaImagem(aux);
                aux->RenderizaPontos();
            evento->DesabilitaImagem();

            aux = aux->getProx();
        }
        glPopMatrix();

    }
}

/************************************************************************/
/**
 *  \brief   Modifica a cor de fundo da tela
 *  \ingroup cor
 *  \param   red Valor de vermelho de 0 � 255
 *  \param   green Valor de verde de 0 � 255
 *  \param   blue Valor de azul de 0 � 255
 */
/************************************************************************/
void PintarFundo(int red, int green, int blue){
    evento->PintaFundo((float)red/255, (float)green/255, (float)blue/255);
}

/************************************************************************/
/**
 *  \brief   Realiza opera��es necess�rias para a playcb saber que aquela imagem ser� utilizada em alguma geometria
 *  \ingroup cor
 *  \param   data Vetor da imagem
 *  \param   largura Largura da imagem
 *  \param   altura Altura da imagem
 *  \return  �ndice da imagem na mem�ria
 */
/************************************************************************/
int PreparaImagem(unsigned char* data, int largura, int altura){
    return evento->BindImagem(data, largura, altura);
}
/************************************************************************/
/**
 *  \brief   Associa o �ndice de uma imagem com uma geometria
 *  \ingroup cor
 *  \param   textura �ndice da imagem
 */
/************************************************************************/
void AssociaImagem(int textura){
    ultima->setTextura(textura);
}

void ApagaDesenho(){
    delete(evento);
}

/************************************************************************/
/**
 *  \brief   Verifica se usu�rio apertou uma tecla. Estas teclas s�o as definidas pela API GLFW
 *  \ingroup aux
 *  \param   tecla Tecla
 */
/************************************************************************/
int ApertouTecla(int tecla){
    return (evento->TeclaPressionada(tecla) ? 1 : 0);
}

void ApagaUltimoGrupo(){
    Grupo *ultimogrupo;
    Geometria *aux;

    grupo.pop_back();
    delete(ultima);

    ultimogrupo = grupo[(grupo.size() - 1)];
    aux = ultimogrupo->getPrimeiro();
    do{
        ultima = aux;
        aux = aux->getProx();
    }while(aux);
}

template <class geometria_qualquer>
void LimpaObjetoVetor(std::vector<geometria_qualquer*> *v){ //Rever esta fun��o
    /*int t = (*v).size();

    if(t > 0){
        for ( int i = 0; i < t; i++ ){
            if((*v)[i])
                delete (*v)[i];
        }
    */
        (*v).clear();
    //}
}

/************************************************************************/
/**
 *  \brief   Realiza o loop de desenho. Sai do loop quando a tecla ESC � pressionada. Usada para renderiza��o de desenhos est�ticos, j� que n�o h� a necessidade de mudan�a entre frames
 *  \ingroup init
 */
/************************************************************************/
void Desenha(){
    bool running = true;

    //Controle de fps
    double dt = 1 / 60.0;
    double currentTime = glfwGetTime();

    do{
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        currentTime = newTime;

        while ( frameTime > 0.0 ){
            const float deltaTime = (frameTime < dt ? frameTime : dt);
            frameTime -= deltaTime;
         }

        evento->limpaBuffer();

        mostraGeometria();

        evento->renderiza();

        running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );
    }while( running );


    ApagaDesenho();
}

/************************************************************************/
/**
 *  \brief   Renderiza somente um frame do desenho, sendo necess�ria estar em um loop. Usada para anima��es, uma vez que as cenas podem mudar a cada frame
 *  \ingroup init
 */
/************************************************************************/
int Desenha1Frame(){
    bool running;

    //Controle de fps
    double dt = 1 / 60.0;
    double currentTime = glfwGetTime();

    double newTime = glfwGetTime();
    double frameTime = newTime - currentTime;
    currentTime = newTime;

    while ( frameTime > 0.0 ){
        const float deltaTime = (frameTime < dt ? frameTime : dt);
        frameTime -= deltaTime;
     }

    evento->limpaBuffer();

    mostraGeometria();

    evento->renderiza();

    running = glfwGetWindowParam( GLFW_OPENED );

    if(!running){
        ApagaDesenho();
        return 0;
    }
    return 1;
}

void LimpaDesenho(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    delete plano;
    plano = NULL;
    delete ultima;
    ultima = NULL;

    LimpaObjetoVetor(&reta);
    LimpaObjetoVetor(&poligono);
    LimpaObjetoVetor(&circulo);
    LimpaObjetoVetor(&circunferencia);
    LimpaObjetoVetor(&retangulo);
    LimpaObjetoVetor(&triangulo);
    LimpaObjetoVetor(&ponto);
    LimpaObjetoVetor(&grupo);
}
