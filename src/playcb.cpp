#include "../include/playcb.h"

Evento *evento = NULL;
PlanoCartesiano *plano = NULL;
std::vector<Reta*> reta;
std::vector<Poligono*> poligono;
std::vector<Circulo*> circulo;
std::vector<Circunferencia*> circunferencia;
std::vector<Elipse*> elipse;
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
 *  \param   titulo T�tulo da janela
 */
/************************************************************************/

void AbreJanela(int largura, int altura, const char *titulo){
    evento = new Evento(largura, altura, titulo);
}

/************************************************************************/
/**
 *  \brief   Modifica limite da janela (default � 100)
 *  \ingroup init
 *  \param   limite novo limite do espa�o da janela
 */
/************************************************************************/
void MudaLimitesJanela(int limite){
    Evento::setTamanhoTela(limite);
}

/************************************************************************/
/**
 *  \brief   Cria um novo grupo de geometrias. Se n�o for utilizada, todas as geometrias criadas ser�o de apenas um grupo
 *  \ingroup aux
 *  \return  O �ndice do grupo criado
 *
 *
 *  Um grupo nada mais � que um conjunto de geometrias. Com ele, � poss�vel separar os desenhos em m�dulos. Cada nova
 *  chamada para esta fun��o cria um novo grupo, que poder� realizar transforma��es independentes em rela��o ao cen�rio. � utilizado
 *  para anima��es simples.
 *
 *  No conceito da OpenGL, um grupo define uma nova matriz de proje��o. Corresponde ao comando glPushMatrix.
 */
/************************************************************************/

int CriaGrupo(){

    if(grupo.empty())
        return grupo.size();
    else
        grupo.resize(grupo.size() + 1);

    return (grupo.size() - 1);
}

/************************************************************************/
/**
 *  \brief   Cria um novo super grupo de grupos de geometrias. Se n�o for utilizada, todas os grupos criados est�o em um �nico super grupo
 *  \ingroup aux
 *  \return  O �ndice do super grupo criado
 *
 *
 *  Um super grupo agrupa transforma��es em comum de v�rios grupos. Pode ser utilizados para transformar geometrias complexas
 *  que est�o agrupadas em um grupo
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
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaReta(Ponto p1, Ponto p2){
    reta.push_back(new Reta(p1, p2));

    ultima = reta.back();
    InsereGrupo();

    return reta.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um ponto
 *  \ingroup geo
 *  \param   p Ponto
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaPonto(Ponto p){
    ponto.push_back(new Pontinho(p));

    ultima = ponto.back();
    InsereGrupo();

    return ponto.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um c�rculo a partir do centro
 *  \ingroup geo
 *  \param   raio Raio do c�rculo
 *  \param   meio Ponto indicando o centro do c�rculo
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaCirculo(float raio, Ponto meio){
    circulo.push_back(new Circulo(raio, meio));

    ultima = circulo.back();
    InsereGrupo();

    return circulo.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria uma circunfer�ncia a partir do centro
 *  \ingroup geo
 *  \param   raio Raio da circunfer�ncia
 *  \param   meio Ponto indicando o centro da circunfer�ncia
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaCircunferencia(float raio, Ponto meio){
    circunferencia.push_back(new Circunferencia(raio, meio));

    ultima = circunferencia.back();
    InsereGrupo();

    return circunferencia.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria uma elipse a partir do centro
 *  \ingroup geo
 *  \param   raio Raio da circunfer�ncia
 *  \param   meio Ponto indicando o centro da circunfer�ncia
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaElipse(float a, float b, Ponto meio){
    elipse.push_back(new Elipse(a, b, meio));

    ultima = elipse.back();
    InsereGrupo();

    return elipse.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um ret�ngulo a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do ret�ngulo
 *  \param   altura Altura do ret�ngulo
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaRetangulo(float base, float altura, Ponto cantoesq){
    retangulo.push_back(new Retangulo(base, altura, cantoesq));

    ultima = retangulo.back();
    InsereGrupo();

    return retangulo.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um quadrado a partir do canto esquerdo
 *  \ingroup geo
 *  \param   lado Tamanho do lado do quadrado
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/

int CriaQuadrado(float lado, Ponto cantoesq){
    retangulo.push_back(new Retangulo(lado, lado, cantoesq));

    ultima = retangulo.back();
    InsereGrupo();

    return retangulo.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um tri�ngulo equil�tero a partir do canto esquerdo
 *  \ingroup geo
 *  \param   base Base do tri�ngulo
 *  \param   altura Altura do tri�ngulo
 *  \param   cantoesq Ponto referente ao canto esquerdo inferior
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/
int CriaTriangulo(float base, float altura, Ponto cantoesq){
    triangulo.push_back(new Triangulo(base, altura, cantoesq));

    ultima = triangulo.back();
    InsereGrupo();

    return triangulo.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria uma geometria convexa qualquer
 *  \ingroup geo
 *  \param   qtd Quantidade de Pontos
 *  \param   ... Ponto
 *  \return  O �ndice da geometria criada
  */
/************************************************************************/
int CriaPoligono(short int qtd, ...){
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

    return poligono.size() - 1;
}

/************************************************************************/
/**
 *  \brief   Cria um pol�gono qualquer a partir do vetor de pontos
 *  \ingroup geo
 *  \param   index Tamanho do vetor
 *  \param   p Vetor de pontos
 *  \return  O �ndice da geometria criada
 */
/************************************************************************/
int CriaPoligonoVetor(short int index, Ponto *p){
    std::deque <Ponto> pontos;
    int i;

    for(i = 0; i < index; i++)
        pontos.push_front(p[i]);

    poligono.push_back(new Poligono(pontos));

    ultima = poligono.back();
    InsereGrupo();

    return poligono.size() - 1;
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

unsigned int str2int(const char* str, int h = 0){
    return !str[h] ? 5381 : (str2int(str, h+1)*33) ^ str[h];
}

/************************************************************************/
/**
 *  \brief   Modifica a cor de uma geometria
 *  \ingroup cor
 *  \param   red Valor de vermelho de 0 � 255
 *  \param   green Valor de verde de 0 � 255
 *  \param   blue Valor de azul de 0 � 255
 *  \param   nomegeo Tipo de geometria baseada em ::geometrias_validas.
 *  \param   index �ndice da geometria criada
 */
/************************************************************************/
void Pintar(int red, int green, int blue, geometrias_validas nomegeo, int index){
    float vermelho, verde, azul;
    Geometria *aux = NULL;

    vermelho = (float)red/255;
    verde = (float)green/255;
    azul = (float)blue/255;

    if(nomegeo == NADA || index <= -1)
        ultima->Cor(vermelho, verde, azul);
    else{
        switch(nomegeo){
            case PONTO:
                if(index <= (int)ponto.size() - 1){
                    aux = ponto[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case RETA:
                if(index <= (int)reta.size() - 1){
                    aux = reta[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case POLIGONO:
                if(index <= (int)poligono.size() - 1){
                    aux = poligono[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case CIRCULO:
                if(index <= (int)circulo.size() - 1){
                    aux = circulo[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case CIRCUNFERENCIA:
                if(index <= (int)circunferencia.size() - 1){
                    aux = circunferencia[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case QUADRADO:
            case RETANGULO:
                if(index <= (int)retangulo.size() - 1){
                    aux = retangulo[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            case TRIANGULO:
                if(index <= (int)triangulo.size() - 1){
                    aux = triangulo[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            case ELIPSE:
                if(index <= (int)elipse.size() - 1){
                    aux = elipse[index];
                    aux->Cor(vermelho, verde, azul);
                }
                else
                    ultima->Cor(vermelho, verde, azul);
            break;
            default:
                    ultima->Cor(vermelho, verde, azul);
            break;
        }
    }
}

/************************************************************************/
/**
 *  \brief   Exibe linhas do plano cartesiano de -limite � limite, centrada no (0,0)
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
 *  \param   index �ndice do grupo que ser� girado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo grupo criado
 */
/************************************************************************/
void Gira(float angulo, int index){
    if(index <= -1 || index > (int)(grupo.size() - 1))
        index = grupo.size() - 1;
    grupo[index]->setRotacao(angulo);
}

/************************************************************************/
/**
 *  \brief   Gira um super grupo de grupos em x
 *  \ingroup transf
 *  \param   angulo �ngulo em graus
 *  \param   index �ndice do super grupo que ser� girado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo super grupo criado
 */
/************************************************************************/
void SuperGira(float angulo, int index){
    if(index < 0 || index > (int)(supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    supergrupo[index]->setRotacao(angulo);
}

/************************************************************************/
/**
 *  \brief   Translada um grupo para o ponto p
 *  \ingroup transf
 *  \param   p Coordenadas para o qual o grupo deve ser transladado
 *  \param   index �ndice do grupo que ser� transladado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo grupo criado
 */
/************************************************************************/
void Move(Ponto p, int index){
    if(index <= -1 || index > (int)(grupo.size() - 1))
        index = grupo.size() - 1;
    grupo[index]->setTranslacao(p);
}

/************************************************************************/
/**
 *  \brief   Translada um super grupo para o ponto p
 *  \ingroup transf
 *  \param   p Coordenadas para o qual o super grupo deve ser transladado
 *  \param   index �ndice do super grupo que ser� transladado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo super grupo criado
 */
/************************************************************************/
void SuperMove(Ponto p, int index){
    if(index <= -1 || index > (int)(supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    supergrupo[index]->setTranslacao(p);
}

/************************************************************************/
/**
 *  \brief   Redimensiona um grupo em x e em y
 *  \ingroup transf
 *  \param   x Porcentagem que deve ser redimensionado em x
 *  \param   y Porcentagem que deve ser redimensionado em y
 *  \param   index �ndice do grupo que ser� redimensionado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo grupo criado
 */
/************************************************************************/
void Redimensiona(float x, float y, int index){
    Ponto p;

    if(index <= -1 || index > (int)(grupo.size() - 1))
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
 *  \param   index �ndice do super grupo que ser� redimensionado. Se n�o for passado algum �ndice v�lido, ser� considerado o �ndice do �ltimo super grupo criado
 */
/************************************************************************/
void SuperRedimensiona(float x, float y, int index){
    Ponto p;

    if(index <= -1 || index > (int)(supergrupo.size() - 1))
        index = supergrupo.size() - 1;
    p.x = x;
    p.y = y;
    supergrupo[index]->setEscala(p);
}

void mostraGeometria(){
    Geometria *aux;

    std::vector<Grupo*>::iterator it1;
    std::vector<Grupo*>::iterator it;

    //se plano n�o for nulo, mostre

    if(plano){
        glPushMatrix();
            plano->RenderizaPontos();
        glPopMatrix();
    }

    if(supergrupo.empty()){
        std::vector<Grupo*>::iterator it3;
        it = supergrupo.end();
        supergrupo.insert(it, new Grupo()); //adiciona o novo grupo de geometrias
    }

    for(it1 = supergrupo.begin(); it1 != supergrupo.end(); ++it1){
        for(it = grupo.begin(); it != grupo.end(); ++it){
            if((*it) != NULL){
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

int PreparaImagem(const char* data){
    return evento->BindImagem(data);
}
/************************************************************************/
/**
 *  \brief   Associa o �ndice de uma imagem com a �ltima geometria de um grupo
 *  \ingroup cor
 *  \param   index_textura �ndice da imagem
 */
/************************************************************************/
void AssociaImagem(int textura){
    ultima->setTextura(textura);
}

int AbreImagem(const char *src){
    GLuint texture = PreparaImagem(src);

    if(texture == 0)
        printf("Erro: %d\n Talvez a imagem nao esteja num formato legal :(\n", SOIL_last_result());

	return texture;
}

void ApagaDesenho(){
    LimpaDesenho();
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

/************************************************************************/
/**
 *  \brief   Apaga grupo de geometrias
 *  \param   index �ndica do grupo a ser removido
 *  \ingroup aux
 */
/************************************************************************/
void ApagaGrupo(int index){
    Grupo *ultimogrupo;
    Geometria *aux;

    if((unsigned int)index == (unsigned int)grupo.size() - 1){
        grupo.pop_back();
        delete(ultima);

        ultimogrupo = grupo[(grupo.size() - 1)];
        aux = ultimogrupo->getPrimeiro();
        do{
            ultima = aux;
            aux = aux->getProx();
        }while(aux);
    }
    else{
        ultimogrupo = grupo[index];
        do{
            aux = ultimogrupo->getPrimeiro();
            aux->Desagrupa(&aux, aux);
        }while(aux);
        grupo[index] = NULL;
    }
}

void ApagaUltimoGrupo(){
    printf("Esta funcao foi atualizada para a funcao ApagaGrupo(int index).\n Verifique a documentacao.\n\nEncerrando...");
    ApagaDesenho();
    exit(0);
}

template <class geometria_qualquer>
void LimpaObjetoVetor(std::vector<geometria_qualquer*> *v){ //Rever esta fun��o
    (*v).clear();
}

/************************************************************************/
/**
 *  \brief   Renderiza somente um frame do desenho, sendo necess�ria estar em um loop. Usada para anima��es, uma vez que as cenas podem mudar a cada frame.
 *
 *  Aten��o: ela n�o possui controle de FPS
 *  \ingroup init
 *  \return  1 se a janela continua aberta e 0 se a janela foi fechada/tecla ESC foi pressionada
 */
/************************************************************************/
int Desenha1Frame(){
    bool running;

    evento->limpaBuffer();

    mostraGeometria();

    evento->renderiza();

    running = !glfwGetKey( GLFW_KEY_ESC ) && glfwGetWindowParam( GLFW_OPENED );

    if(!running){
        ApagaDesenho();
        return 0;
    }
    return 1;
}

/************************************************************************/
/**
 *  \brief   Realiza o loop de desenho. Sai do loop quando a tecla ESC � pressionada. Usada para renderiza��o de desenhos est�ticos, j� que n�o h� a necessidade de mudan�a entre frames.
 *
 *  Aten��o: ela renderiza uma cena a 30 fps.
 *  \ingroup init
 */
/************************************************************************/
void Desenha(){
    bool running = true;

    //Controle de fps
    double currentTime = glfwGetTime();

    do{
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;

        if(frameTime < 1000/30 - frameTime)
            glfwSleep(1000/30 - frameTime);

        currentTime = newTime;

        running = Desenha1Frame();

    }while( running );


}

/************************************************************************/
/**
 *  \brief   Destr�i todos os elementos da cena
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
    LimpaObjetoVetor(&elipse);
    LimpaObjetoVetor(&ponto);
    LimpaObjetoVetor(&grupo);
}
