#include "../include/Evento.h"

int Evento::tamanhoTela = 100;

void GLFWCALL Evento::redimensionaJanela(int w, int h){
    float nRange = Evento::tamanhoTela;
    GLfloat aspect = (GLfloat)w / (GLfloat)h;

    if (h == 0)  h = 1;

    glMatrixMode(GL_PROJECTION); //pega a matriz de projeção
    glLoadIdentity(); //reseta seu valor para identidade

    if (w >= h) {
      glOrtho (-nRange * aspect, nRange * aspect, -nRange, nRange, -1, 1);
   } else {
     glOrtho (-nRange, nRange, -nRange / aspect, nRange / aspect, -1, 1);
   }

    glMatrixMode(GL_MODELVIEW); //matriz de modelagem
    glLoadIdentity(); //reseta para identidade

    glViewport(0, 0, w, h); //ajusta a janela

}

void Evento::redimensionaJanelaManual(int minx, int maxx, int miny, int maxy){
    int w, h;
    glfwGetWindowSize( &w, &h );

    if (h == 0)  h = 1;

    glMatrixMode(GL_PROJECTION); //pega a matriz de projeção
    glLoadIdentity(); //reseta seu valor para identidade

    glOrtho(minx, maxx, miny, maxy, -1, 1);

    glMatrixMode(GL_MODELVIEW); //matriz de modelagem
    glLoadIdentity(); //reseta para identidade

    glViewport(0, 0, w, h); //ajusta a janela

}

Evento::Evento(int largura, int altura, const char *titulo){

    if(!OpenglBase::inicializaContexto())
        printf("Erro ao inicializar o contexto gráfico! Verifique se possui os arquivos necessários");

    if(!OpenglBase::inicializaJanela(largura, altura))
        printf("Erro ao abrir a janela! Verifique se tudo está devidamente linkado");

    OpenglBase::mudaNomeJanela(titulo);

    glfwSetWindowSizeCallback(GLFWwindowsizefun(&redimensionaJanela)); //rever este callback
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int Evento::getTamanhoTela(){
    return tamanhoTela;
}
void Evento::setTamanhoTela(int novo){
    tamanhoTela = novo;
}

Evento::~Evento(){
    glLoadIdentity();
    OpenglBase::encerraContexto();
}

void Evento::transformacao(Grupo *g, Grupo *sg){
    GLfloat rotacao;
    Ponto escala, translacao, p;

    rotacao = g->getRotacao();
    translacao = g->getTranslacao();
    escala = g->getEscala();

    if(sg){
        rotacao += sg->getRotacao();
        p = sg->getTranslacao();
        translacao.x += p.x;
        translacao.y += p.y;
        p = sg->getEscala();
        escala.x += p.x;
        escala.y += p.y;
    }
    glLoadIdentity();

    glTranslated(translacao.x, translacao.y, 0);
    glScaled(escala.x, escala.y, 1);
    glRotated(rotacao, 0, 0, 1);
}

GLuint Evento::BindImagem(const char *data){
    GLuint texture;

    texture = SOIL_load_OGL_texture
    (
     data,
     SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );

    glBindTexture( GL_TEXTURE_2D, texture );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture;

}

int Evento::TeclaPressionada(int tecla){

    if(glfwGetKey(tecla) == GLFW_PRESS){
        keyChanged[tecla] = false;

        if(!keyPressed[tecla]){
            keyPressed[tecla] = true;
            keyChanged[tecla] = true;
        }
    }
    else if(glfwGetKey(tecla) == GLFW_RELEASE){
        keyPressed[tecla] = false;
        keyChanged[tecla] = false;
    }

    return keyChanged[tecla] && keyPressed[tecla];

}

int Evento::BotaoPressionadoMouse(int tecla){

    if(glfwGetMouseButton(tecla) == GLFW_PRESS){

        buttonChanged[tecla] = false;

        if(!buttonPressed[tecla]){
            buttonPressed[tecla] = true;
            buttonChanged[tecla] = true;
        }
    }
    else if(glfwGetMouseButton(tecla) == GLFW_RELEASE){
        buttonPressed[tecla] = false;
        buttonChanged[tecla] = false;
    }

    return buttonChanged[tecla] && buttonPressed[tecla];

}

int Evento::pegaTecla(){
    int i;
    for(i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST; i++){
        if(TeclaPressionada(i))
            break;
    }
    if(i <= GLFW_KEY_LAST)
        return i;
    else
        return -1;

}

int Evento::pegaBotao(){
    int i;
    for(i = GLFW_MOUSE_BUTTON_LEFT; i < N_BUTTONS; i++){
        if(BotaoPressionadoMouse(i))
            break;
    }
    if(i <= GLFW_MOUSE_BUTTON_LAST)
        return i;
    else
        return -1;

}


void Evento::pegaMousePos(int *x, int *y){
    int w, h, xpos, ypos;

    glfwGetWindowSize(&w, &h);
    glfwGetMousePos(&xpos, &ypos);

    *x = (getTamanhoTela() - 2 * getTamanhoTela() * xpos/w) * -1;
    *y = getTamanhoTela() - 2 * getTamanhoTela() * ypos/h;
}

void Evento::HabilitaImagem(Geometria *g){
    GLuint data;

    data = g->getTextura();

    if(data > 0){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D,data);
    }
}

void Evento::DesabilitaImagem(){
    glDisable(GL_TEXTURE_2D);
}

void Evento::renderiza(){
    glfwSwapBuffers();
}

void Evento::limpaBuffer(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void Evento::PintaFundo(float red, float green, float blue){
    glClearColor(red, green, blue, 1.0);
}

void Evento::salvaContexto(){
    glPushMatrix();
}

void Evento::carregaContexto(){
    glPopMatrix();
}

double Evento::getSegundos(){
    return OpenglBase::getSegundos();
}

bool Evento::isJanelaAberta(){
    if(OpenglBase::isJanelaAberta() == GL_TRUE)
        return true;
    else
        return false;
}
