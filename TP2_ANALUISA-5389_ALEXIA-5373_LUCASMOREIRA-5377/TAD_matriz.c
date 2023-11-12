#include "TAD_matriz.h"
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


// Funcao para imprimir a matriz de distancias
void Imprimir_Matriz(Matriz matrix) {
    for (int i = 0; i < matrix.num_cidades; i++) {
        for (int j = 0; j < matrix.num_cidades; j++) {
            printf("%d\t", matrix.distancias[i][j]);
        }
        printf("\n");
    }
}

// Funcao para inicializar alocando dinamicamente e verifica se a alocação de memória foi bem-sucedida
void Inicializar_Matriz(Matriz *matrix, int num_cidades){
    

    matrix->distancias = (int**) malloc(num_cidades * sizeof(int));
    for (int i = 0; i < num_cidades; i++)
    {
        matrix->distancias[i] = (int*) malloc(num_cidades * sizeof(int));
    }
    if (matrix->distancias == NULL) {
    printf("Erro ao alocar memória para matrix->distancias\n");
    }
    matrix->melhorCaminho = (int*) malloc((num_cidades + 1) * sizeof(int));
    if (matrix->melhorCaminho == NULL) {
    printf("Erro ao alocar memória para matrix->melhorCaminho\n");
    }

    // Distancia total vai receber o maior valor inteiro possivel, pois na logica do calcular distancia ele é util.
    matrix->dist_total = INT_MAX;
    
    matrix->caminhoOriginal = (int*) malloc((num_cidades-1) * sizeof(int));
    if (matrix->caminhoOriginal == NULL) {
    printf("Erro ao alocar memória para matrix->caminhoOriginal\n");
    }
    
}


// Funcao para setar a distancia total
void set_Dist_Total(Matriz *matrix, int distancia){
    matrix->dist_total = distancia;
}


// Funcao para setar o numero de cidades
void set_Num_Cidades(Matriz *matrix, int num_cidades){
    matrix->num_cidades = num_cidades;
}



// Funcao para setar a primeira cidade 
void set_Primeira_Cidade(Matriz* matrix){
    int ana, alexia, lucas, soma;
    ana = 5389;
    alexia = 5373;
    lucas = 5377;
    soma = 0;


    //utiliza a soma dos digitos da matricula de cada integrante do grupo e divide pelo numero de cidades
    for (int i = 0; i < 4; i++)
    {
        soma+= ana%10;
        ana/=10;
        soma+= alexia%10;
        alexia/=10;
        soma+= lucas%10;
        lucas/=10;
    }
    matrix->primeira_cidade = soma % matrix->num_cidades;
}



// Funcao para setar a matriz de distancias, com distancias aleatorias com valores até 100, utilizando a funcao rand()
void Set_Distancias(Matriz *matrix) {

    for (int i = 0; i < matrix->num_cidades; i++) {
        for (int j = 0; j < matrix->num_cidades; j++) {
            if (i == j) {
                matrix->distancias[i][j] = 0;
            } else {
                matrix->distancias[i][j] = 1 + rand() % 100;
            }
        }
    }
}


// Funcao abrir o arquivo e preenche a matriz de distancias de acordo com a distrubuicao do arquivo
void Set_Arquivo(Matriz* matrix, char* nomeArquivo){
    FILE *arq = fopen(nomeArquivo, "r");
    int N;
    fscanf(arq, "%d", &N);
    printf("%d", N);
    printf("\n");
    set_Num_Cidades(matrix, N);
    Inicializar_Matriz(matrix, N);
    set_Primeira_Cidade(matrix);
    Faz_Vetor(matrix);


// logica para colocar "0" na diagonal principal quando i = j e verifica se foi possivel abrir o arquivo.
    if (arq != NULL) {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                {
                    matrix->distancias[i][j] = 0;
                }else
                {
                    fscanf(arq, "%d ", &matrix->distancias[i][j]);
                }
                
            }
        }
        
    }else{
        printf("Erro! Nao foi possivel abrir o arquivo.");
    }
    
    fclose(arq);
}


// Funcao para trocar os valores do vetor com o caminho a ser permutado(sem a primeira cidade) de lugar
void Troca(Matriz *matrix, int i, int j) {
    int aux = matrix->caminhoOriginal[i];
    matrix->caminhoOriginal[i] = matrix->caminhoOriginal[j];
    matrix->caminhoOriginal[j] = aux;
}


// Função recursiva para gerar todas as permutações do caminho
void Permuta(Matriz *matrix, int inf, int sup) {
    // Se a posição inicial (inf) for igual à posição final (sup),
    // então uma permutação foi gerada completa.
    if (inf == sup) {
        // Calcula a distância para a permutação atual
        Calcular_Distancia(matrix);
    } else {
        // Loop através de todas as posições possíveis a partir da posição atual (inf)
        // até a posição final (sup)

        for (int i = inf; i <= sup; i++) {

            // Troca os elementos nas posições inf e i na matriz
            Troca(matrix, inf, i);

            // Chama recursivamente a função para gerar as permutações restantes
            Permuta(matrix, inf + 1, sup);

             // Desfaz a troca para restaurar a matriz ao seu estado original
            Troca(matrix, inf, i);
        }
    }
}



// Funcao para criar um vetor SEM incluir a primeira cidade nesse vetor
void Faz_Vetor(Matriz *matrix) {
    int valor = 0;
    int indice = 0;
    while (indice < matrix->num_cidades-1)
    {
        if ((matrix->primeira_cidade) != valor)
        {
            matrix->caminhoOriginal[indice] = valor;
            indice++;
        }  
        valor++;
    }
}


// Função para calcular a distância total de um caminho dado e verificar se ela é menor que a salva anteriormente
void Calcular_Distancia(Matriz *matrix){

    // Variável para armazenar a distância total calculada
    int DistanciaCalculada = 0;


    // Adiciona a distância da primeira cidade até a cidade com indice 0 do caminho original
    DistanciaCalculada += matrix->distancias[matrix->primeira_cidade][matrix->caminhoOriginal[0]]; 
    
    // Loop para percorrer as cidades do caminho original e somar as distâncias entre elas
    for (int k = 0; k < matrix->num_cidades -2; k++){
        DistanciaCalculada += matrix->distancias[matrix->caminhoOriginal[k]][matrix->caminhoOriginal[k+1]];
    }    

    // Adiciona a distância da última cidade do caminho original até a primeira cidade 
    DistanciaCalculada += matrix->distancias[matrix->caminhoOriginal[matrix->num_cidades-2]][matrix->primeira_cidade];
        

    // Verifica se a distância calculada é menor que a distância total atual
    if (DistanciaCalculada < matrix->dist_total)
    {

        // Se for menor, atualiza a distância total na estrutura da matriz
        matrix->dist_total = DistanciaCalculada;

         // Armazena a primeira cidade no indice 0 do vetor melhor caminho encontrado
        matrix->melhorCaminho[0] = matrix->primeira_cidade;

        // Preenche o restante do melhor caminho com as cidades do caminho original
        // Começa de 1, pq a primeira cidade ja foi adicionada
        for (int j = 1; j < matrix->num_cidades; j++)
        {
            matrix->melhorCaminho[j] = matrix->caminhoOriginal[j-1];
            }

        // Completa o ciclo retornando para a primeira cidade, adicionando ela no final do melhor caminho
        matrix->melhorCaminho[matrix->num_cidades] = matrix->primeira_cidade;
    }

    }

// Funcao para visualizaçao de arquivo
int CriaArquivo(Matriz *matrix, double tempo){


    int numDeCidades = matrix->num_cidades;
    char nomeDoArquivo[20]; // Assume um limite de 20 caracteres para o nome do arquivo

    // Cria o nome do arquivo formatado com o número de cidades
    sprintf(nomeDoArquivo, "%d.txt", numDeCidades);

    // Abrindo o arquivo para escrita (modo "w" para criar um novo arquivo)
    FILE *arquivo;
    arquivo = fopen(nomeDoArquivo, "w");

    // Verificando se o arquivo foi aberto corretamente
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 1;
    }

   else{
        for (int i = 0; i < matrix->num_cidades; i++) {
            for (int j = 0; j < matrix->num_cidades; j++) {
            fprintf(arquivo, "%d\t", matrix->distancias[i][j]);
            }
        fprintf(arquivo, "\n");
        }
        fprintf(arquivo, "Melhor caminho: ");
        for (int i = 0; i < matrix->num_cidades+1; i++)
        {
            fprintf(arquivo, " %d ", matrix->melhorCaminho[i]);
        }
        fprintf(arquivo, "\n");
        fprintf(arquivo, "Menor distancia: %d\n", matrix->dist_total);
        fprintf(arquivo, "Tempo de execucao: %f segundos\n", tempo);
    }
    // Fechando o arquivo após a escrita
    fclose(arquivo);

    printf("Valores da matriz foram armazenados no arquivo '%d.txt'.\n", matrix->num_cidades);

    return 0;
}