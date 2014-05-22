#include "PlanoCartesiano.h"

PlanoCartesiano::PlanoCartesiano(float espaco):
intervalo(espaco)
{
    int i;

    for(i = -TAMANHOTELA; i <= TAMANHOTELA; i += intervalo)
        linha.push_back(i);
}

void PlanoCartesiano::RenderizaPontos(){
    int i, tamanho;

    tamanho = linha.size();

    ///linhas centrais: x = 0 e y = 0
    glColor3f(0, 0, 0);
    glLineWidth(1.0);

    glBegin(GL_LINES); //x
        glVertex2f(0,-TAMANHOTELA);
        glVertex2f(0,TAMANHOTELA);
    glEnd();
    glBegin(GL_LINES); //y
        glVertex2f(-TAMANHOTELA, 0);
        glVertex2f(TAMANHOTELA, 0);
    glEnd();

    ///linhas horizontais
    glColor3f(0.86, 0.86, 0.86);

    for(i = 0; i < tamanho; i++){
        if(linha[i] != 0){
        glBegin(GL_LINES);
            glVertex2f(-TAMANHOTELA, linha[i]);
            glVertex2f(TAMANHOTELA, linha[i]);
        glEnd();
        }
    }

    ///linhas verticais
    for(i = 0; i < tamanho; i++){
        if(linha[i] != 0){
        glBegin(GL_LINES);
            glVertex2f(linha[i],-TAMANHOTELA);
            glVertex2f(linha[i],TAMANHOTELA);
        glEnd();
        }
    }

}
