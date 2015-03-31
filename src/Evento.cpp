#include "../include/Evento.h"

void GLFWCALL Evento::redimensionaJanela(int w, int h){
    float nRange = TAMANHOTELA;

    if (h == 0)  h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho (-nRange, nRange, -nRange, nRange, -nRange, nRange);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

Evento::Evento(int largura, int altura, const char *titulo){
    if(!OpenglBase::inicializaContexto())
        printf("Erro ao inicializar o contexto gráfico! Verifique se possui os arquivos necessários");

    if(!OpenglBase::inicializaJanela(largura, altura))
        printf("Erro ao abrir a janela! Verifique se tudo está devidamente linkado");

    OpenglBase::mudaNomeJanela(titulo);

    glfwSetWindowSizeCallback(GLFWwindowsizefun(&redimensionaJanela)); //rever este callback
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

GLuint Evento::BindImagem(unsigned char *data, int width, int height){
    GLuint texture;

    glGenTextures( 1, &texture );
    glBindTexture( GL_TEXTURE_2D, texture );

    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

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
