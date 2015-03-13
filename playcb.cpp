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
std::vector<Grupo*> supergrupo;

/************************************************************************/
/**
 *  \brief   Abre uma janela vazia
 *  \ingroup init
 *  \param   largura largura da janela
 *  \param   altura altura da janela
 *  \param   titulo Título da janela
 */
/************************************************************************/

void AbreJanela(int largura, int altura, std::string titulo){
    evento = new Evento(largura, altura, titulo);
}

/************************************************************************/
/**
 *  \brief   Cria um novo grupo de geometrias. Se não for utilizada, todas as geometrias criadas serão de apenas um grupo
 *  \ingroup aux
 *  \return  O índice do grupo criado
 *
 *
 *  Um grupo nada mais é que um conjunto de geometrias. Com ele, é possível separar os desenhos em módulos. Cada nova
 *  chamada para esta função cria um novo grupo, que poderá realizar transformações independentes em relação ao cenário. É utilizado
 *  para animações simples.
 *
 *  No conceito da OpenGL, um grupo define uma nova matriz de projeção. Corresponde ao comando glPushMatrix.
 */
/************************************************************************/

int CriaGrupo(){

    if(!grupo.empty()){
        grupo.resize(grupo.size() + 1);
    }

    return (grupo.size() - 1);
}

/************************************************************************/
/**
 *  \brief   Cria um novo super grupo de grupos de geometrias. Se não for utilizada, todas os grupos criados estão em um único super grupo
 *  \ingroup aux
 *  \return  O índice do super grupo criado
 *
 *
 *  Um super grupo agrupa transformações em comum de vários grupos. Pode ser utilizados para transformar geometrias complexas
 *  que estão agrupadas em um grupo
 */
/************************************************************************/

int CriaSuperGrupo(){
    int index = supergrupo.size();

    if(!supergrupo.empty()){
        supergrupo.resize(supergrupo.size() + 1);
    }

    if(supergrupo.empty() || !supergrupo[index]){
        std::vector<Grupo*>::iterator it;
        it = supergrupo.end();

        if(grupo.empty()){
            printf("Nao crie um supergrupo antes de definir um grupo! Encerrando...");
            exit(0);
        }
        supergrupo.insert(it, new Grupo()); //adiciona o novo grupo de geometrias
    }
    return (supergrupo.size() - 1);
}

void InsereGrupo(){
    int index = grupo.size() - 1;
    Geometria *aux;

    if(grupo.empty() || !grupo[index]){
        if(grupo.empty()){
            std::vector<Grupo*>::iterator it;
            it = grupo.end();
            grupo.insert(it, new Grupo(ultima)); //adiciona a última geometria criada em uma nova posição no grupo
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
 *  \brief   Cria um círculo a partir do centro
 *  \ingroup geo
 *  \param   raio Raio do círculo
 *  \param   meio Ponto indicando o centro do círculo
 */
/************************************************************************/

void CriaCirculo(float raio, Ponto meio){
    circulo.push_back(new Circulo(raio, meio));

    ultima = circulo.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria uma circunferência a partir do centro
 *  \ingroup geo
 *  \param   raio Raio da circunferência
 *  \param   meio Ponto indicando o centro da circunferência
 */
/************************************************************************/

void CriaCircunferencia(float raio, Ponto meio){
    circunferencia.push_back(new Circunferencia(raio, meio));

    ultima = circunferencia.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um retângulo a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do retângulo
 *  \param   altura Altura do retângulo
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
 *  \brief   Cria um triângulo equilátero a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do triângulo
 *  \param   altura Altura do triângulo
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
        pontos.push_front(p); //adiciona os pontos na ordem que foi colocado na função
    }
    poligono.push_back(new Poligono(pontos));

    ultima = poligono.back();
    InsereGrupo();
}

/************************************************************************/
/**
 *  \brief   Cria um polígono qualquer a partir do vetor de pontos
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
 *  \param   red Valor de vermelho de 0 à 255
 *  \param   green Valor de verde de 0 à 255
 *  \param   blue Valor de azul de 0 à 255
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
 *  \brief   Exibe linhas do plano cartesiano de -100 à 100, centrada no (0,0)
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
 *  \param   angulo Ângulo em graus
 *  \param   index índice do grupo que será girado. Se não for passado algum índice válido, será considerado o índice do último grupo criado
 */
/************************************************************************/
void Gira(float angulo, int index){
    if(index <= -1 || index > (grupo.size() - 1))
        index = grupo.size() - 1;
    grupo[index]->setRotacao(angulo);
}

/************************************************************************/
/**
 *  \brief   Gira um super grupo de grupos em x
 *  \ingroup transf
 *  \param   angulo Ângulo em graus
 *  \param   index índice do super grupo que será girado. Se não for passado algum índice válido, será considerado o índice do último super grupo criado
 */
/************************************************************************/
void SuperGira(float angulo, int index){
    if(index < 0 || index > (supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    supergrupo[index]->setRotacao(angulo);
}

/************************************************************************/
/**
 *  \brief   Translada um grupo para o ponto p
 *  \ingroup transf
 *  \param   p Coordenadas para o qual o grupo deve ser transladado
 *  \param   index índice do grupo que será transladado. Se não for passado algum índice válido, será considerado o índice do último grupo criado
 */
/************************************************************************/
void Move(Ponto p, int index){
    if(index <= -1 || index > (grupo.size() - 1))
        index = grupo.size() - 1;
    grupo[index]->setTranslacao(p);
}

/************************************************************************/
/**
 *  \brief   Translada um super grupo para o ponto p
 *  \ingroup transf
 *  \param   p Coordenadas para o qual o super grupo deve ser transladado
 *  \param   index índice do super grupo que será transladado. Se não for passado algum índice válido, será considerado o índice do último super grupo criado
 */
/************************************************************************/
void SuperMove(Ponto p, int index){
    if(index <= -1 || index > (supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    supergrupo[index]->setTranslacao(p);
}

/************************************************************************/
/**
 *  \brief   Redimensiona um grupo em x e em y
 *  \ingroup transf
 *  \param   x Porcentagem que deve ser redimensionado em x
 *  \param   y Porcentagem que deve ser redimensionado em y
 *  \param   index índice do grupo que será redimensionado. Se não for passado algum índice válido, será considerado o índice do último grupo criado
 */
/************************************************************************/
void Redimensiona(float x, float y, int index){
    Ponto p;

    if(index <= -1 || index > (grupo.size() - 1))
        index = grupo.size() - 1;
    p.x = x;
    p.y = y;
    grupo[index]->setEscala(p);
}

/************************************************************************/
/**
 *  \brief   Redimensiona um grupo em x e em y
 *  \ingroup transf
 *  \param   x Porcentagem que deve ser redimensionado em x
 *  \param   y Porcentagem que deve ser redimensionado em y
 *  \param   index índice do super grupo que será redimensionado. Se não for passado algum índice válido, será considerado o índice do último super grupo criado
 */
/************************************************************************/
void SuperRedimensiona(float x, float y, int index){
    Ponto p;

    if(index <= -1 || index > (supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    p.x = x;
    p.y = y;
    supergrupo[index]->setEscala(p);
}

void mostraGeometria(){
    Geometria *aux;

    std::vector<Grupo*>::iterator it1;
    std::vector<Grupo*>::iterator it;

    //se plano não for nulo, mostre
    glPushMatrix();
    if(plano)
        plano->RenderizaPontos();
    glPopMatrix();

    if(supergrupo.empty()){
        std::vector<Grupo*>::iterator it3;
        it = supergrupo.end();
        supergrupo.insert(it, new Grupo()); //adiciona o novo grupo de geometrias
    }

    for(it1 = supergrupo.begin(); it1 != supergrupo.end(); ++it1){
        for(it = grupo.begin(); it != grupo.end(); ++it){
            aux = (*it)->getPrimeiro();

            glPushMatrix();
            evento->transformacao(*it, *it1);
            while(aux){
                evento->HabilitaImagem(aux);
                    aux->RenderizaPontos();
                evento->DesabilitaImagem();

                aux = aux->getProx();
            }
            glPopMatrix();
        }
    }
}

/************************************************************************/
/**
 *  \brief   Modifica a cor de fundo da tela
 *  \ingroup cor
 *  \param   red Valor de vermelho de 0 à 255
 *  \param   green Valor de verde de 0 à 255
 *  \param   blue Valor de azul de 0 à 255
 */
/************************************************************************/
void PintarFundo(int red, int green, int blue){
    evento->PintaFundo((float)red/255, (float)green/255, (float)blue/255);
}

/************************************************************************/
/**
 *  \brief   Realiza operações necessárias para a playcb saber que aquela imagem será utilizada em alguma geometria
 *  \ingroup cor
 *  \param   data Vetor da imagem
 *  \param   largura Largura da imagem
 *  \param   altura Altura da imagem
 *  \return  Índice da imagem na memória
 */
/************************************************************************/
int PreparaImagem(unsigned char* data, int largura, int altura){
    return evento->BindImagem(data, largura, altura);
}
/************************************************************************/
/**
 *  \brief   Associa o índice de uma imagem com a última geometria de um grupo
 *  \ingroup cor
 *  \param   index_textura Índice da imagem
 */
/************************************************************************/
void AssociaImagem(int textura){
    ultima->setTextura(textura);
}

void ApagaDesenho(){
    LimpaDesenho();
    delete(evento);
}

/************************************************************************/
/**
 *  \brief   Verifica se usuário apertou uma tecla. Estas teclas são as definidas pela API GLFW
 *  \ingroup aux
 *  \param   tecla Tecla
 */
/************************************************************************/
int ApertouTecla(int tecla){
    return (evento->TeclaPressionada(tecla) ? 1 : 0);
}

/************************************************************************/
/**
 *  \brief   Apaga grupo de geometrias
 *  \param   index índica do grupo a ser removido
 *  \ingroup aux
 */
/************************************************************************/
void ApagaGrupo(int index){
    Grupo *ultimogrupo;
    Geometria *aux;

    if(index == grupo.size() - 1){
        grupo.pop_back();
        delete(ultima);

        ultimogrupo = grupo[(grupo.size() - 1)];
        aux = ultimogrupo->getPrimeiro();
        do{
            ultima = aux;
            aux = aux->getProx();
        }while(aux);
    }
    else
        grupo.erase(grupo.begin() + index);
}

void ApagaUltimoGrupo(){
    printf("Esta funcao foi atualizada para a funcao ApagaGrupo(int index).\n Verifique a documentacao.\n\nEncerrando...");
    ApagaDesenho();
    exit(0);
}

template <class geometria_qualquer>
void LimpaObjetoVetor(std::vector<geometria_qualquer*> *v){ //Rever esta função
    (*v).clear();
}

/************************************************************************/
/**
 *  \brief   Realiza o loop de desenho. Sai do loop quando a tecla ESC é pressionada. Usada para renderização de desenhos estáticos, já que não há a necessidade de mudança entre frames.
 *
 *  Atenção: ela renderiza uma cena a 30 fps.
 *  \ingroup init
 */
/************************************************************************/
void Desenha(){
    bool running = true;

    //Controle de fps
    double dt = 1 / 30.0;
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
 *  \brief   Renderiza somente um frame do desenho, sendo necessária estar em um loop. Usada para animações, uma vez que as cenas podem mudar a cada frame.
 *
 *  Atenção: ela não possui controle de FPS
 *  \ingroup init
 *  \return  1 se a janela continua aberta e 0 se a janela foi fechada
 */
/************************************************************************/
int Desenha1Frame(){
    bool running;

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

/************************************************************************/
/**
 *  \brief   Destrói todos os elementos da cena
 *  \ingroup init
 */
/************************************************************************/
void LimpaDesenho(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //REVER
    glLoadIdentity(); //REVER

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
