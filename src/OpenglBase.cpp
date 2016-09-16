#include "../include/OpenglBase.h"

bool OpenglBase::inicializaContexto(){
    if (!glfwInit())
        return false;
    glfwSwapInterval(0);
    return true;
}

bool OpenglBase::inicializaJanela(int largura, int altura){
    if( !glfwOpenWindow( largura, altura, 0,0,0,0, 32,0, GLFW_WINDOW ) )
        return false;

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    return true;
}

void OpenglBase::mudaNomeJanela(const char *titulo){
    glfwSetWindowTitle(titulo);
}

void OpenglBase::encerraContexto(){
    glfwCloseWindow();
    glfwTerminate();
}

double OpenglBase::getSegundos(){
    return glfwGetTime();
}

int OpenglBase::isJanelaAberta(){
    return glfwGetWindowParam(GLFW_OPENED);
}
