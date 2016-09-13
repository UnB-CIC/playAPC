
/************************************************************************/
/**
 *  \brief   Abre uma imagem bmp de 24bits e separa componentes RGB
 *  \ingroup cor
 *  \param   imagepath Caminho da imagem
 *  \param   largura Largura em pixels da imagem
 *  \param   altura Altura em pixels da imagem
 *  \param   R Matriz do componente vermelho
 *  \param   G Matriz do componente verde
 *  \param   B Matriz do componente azul
 */
/************************************************************************/

template <size_t tam_x, size_t tam_y>
void ExtraiRGBdeBMP(const char *imagepath, int largura, int altura, int (&R)[tam_x][tam_y], int (&G)[tam_x][tam_y], int (&B)[tam_x][tam_y]){

    unsigned char header[54]; // Todo BMP tem um cabeçalho com 54 posições
    unsigned int dataPos;     // Posição do ponteiro onde os dados de RGB de fato começam
    unsigned int imageSize;   // = width*height*3 = largura * altura * (Matriz R + Matriz G + Matriz B)
    //unsigned int width;
    //unsigned int height;
    // Imagem propriamente dita
    unsigned char * data;
    int k;

    // Abrindo o arquivo
    FILE * file = fopen(imagepath,"rb");
    if (!file){
        printf("Erro ao abrir imagem\n");
        exit(0);
    }
    if ( fread(header, 1, 54, file) != 54 ){ // Se o arquivo for menor que o cabeçalho do bmp, problema
        printf("Isso e qualquer coisa, menos uma imagem bmp\n");
        exit(0);
    }
    if ( header[0] != 'B' && header[1] != 'M' ){
        printf("Tipo incorreto de imagem. Eu so consigo ler BMP\n");
        exit(0);
    }
    // Pega informações do cabeçalho
    //Achei na internet :D
    dataPos    = *(int*)&(header[0x0A]);
    imageSize  = *(int*)&(header[0x22]);
    //width      = *(int*)&(header[0x12]);
    //height     = *(int*)&(header[0x16]);

    // Se esse bmp for porco e não tiver as informações corretas
    if (imageSize == 0)
        imageSize = largura*altura*3; // Largura * altura * RGB
    if (dataPos == 0)
        dataPos = 54; // Assim que o cabeçalho termina, provavelmente deve começar a imagem

    // Vetor com dados da imagem
    data = (unsigned char*)malloc(imageSize * sizeof(unsigned char));

    // Lê o arquivo inteiro, de uma vez, PAH
    fread(data,1,imageSize,file);

    //Alguns BMP estão em BGR
    k = 0;
    for(int i = 0; i < largura; i++){
        for(int j = 0; j < altura; j++){
            B[i][j] = data[k];
            k++;

            G[i][j] = data[k];
            k++;

            R[i][j] = data[k];
            k++;
        }
    }
}
