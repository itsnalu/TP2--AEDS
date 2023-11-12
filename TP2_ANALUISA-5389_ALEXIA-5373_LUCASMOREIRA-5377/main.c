#include "TAD_matriz.h"
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Inicializa o gerador de números aleatórios com o tempo atual
    srand(time(NULL));

    int N;

    // Solicita ao usuário que escolha entre matriz aleatória e matriz carregada de arquivo
    printf("Escolha a opcao(digite o numero):\n");
    printf("1. Usar matriz aleatoria\n");
    printf("2. Carregar matriz de arquivo\n");

    int escolha;

    // Recebe a escolha do usuário
    scanf("%d", &escolha);

    if (escolha == 1) {

        Matriz matrix;
        int num_cidades;
        int visualizacao;
        int fatorial;

        // Solicita informações adicionais para a matriz aleatória
        printf("Qual eh o tipo de visualizacao?\n");
        printf("1. Arquivo\n");
        printf("2. Terminal\n");
        scanf("%d", &visualizacao);
        printf("Qual eh o numero de cidades?\n");
        scanf("%d", &num_cidades);
        
        
        // Inicializa a estrutura da matriz e configura os parâmetros
        clock_t start_time = clock();
        set_Num_Cidades(&matrix, num_cidades);
        Inicializar_Matriz(&matrix, num_cidades);
        Set_Distancias(&matrix); 
        set_Primeira_Cidade(&matrix);
        Faz_Vetor(&matrix);


        // Gerar e armazenar permutações
        Permuta(&matrix, 0, (matrix.num_cidades)-2);
        Calcular_Distancia(&matrix);


        clock_t end_time = clock();

        // Variavel para o tempo de execuçao utilizando funcoes da biblioteca time.h
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


        // Exibe os resultados conforme a opção de visualização escolhida
        if (visualizacao == 1)
        {
            CriaArquivo(&matrix,elapsed_time);
        } else if (visualizacao == 2)
        {
            Imprimir_Matriz(matrix); 
            printf("Melhor caminho: ");
            for (int i = 0; i < matrix.num_cidades+1; i++)
            {
                printf(" %d ", matrix.melhorCaminho[i]);
            }
                printf("\n");
                printf("Menor distancia: %d\n", matrix.dist_total);
                printf("Tempo de execucao: %f segundos\n", elapsed_time);
        }   


        // Liberar memória
        free(matrix.caminhoOriginal);
        free(matrix.distancias);
        free(matrix.melhorCaminho);


    } else if (escolha == 2) {
        char arqName[100];
        int contador = 0;
        int visualizacao;


        // Solicita o caminho do arquivo e informações adicionais
        printf("Digite o caminho do arquivo: ");
        scanf("%s", &arqName);
        printf("Qual eh o tipo de visualizacao?\n");
        printf("1. Arquivo\n");
        printf("2. Terminal\n");
        scanf("%d", &visualizacao);

        Matriz matrix;
        // Inicia a contagem
        clock_t start_time = clock();


        // Inicializa a estrutura da matriz a partir do arquivo, faz as permutacoes e calcula a menor distancia
        Set_Arquivo(&matrix, arqName);
        Permuta(&matrix, 0, (matrix.num_cidades)-2);
        Calcular_Distancia(&matrix);

        //Encerra a contagem
        clock_t end_time = clock();

        // Variavel para o tempo de execuçao utilizando funcoes da biblioteca time.h
        double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;


        // Exibe os resultados conforme a opção de visualização escolhida
        if (visualizacao == 1)
        {
            CriaArquivo(&matrix, elapsed_time);
        } else if (visualizacao == 2)
        {
            Imprimir_Matriz(matrix);
            printf("Melhor caminho: ");
            for (int i = 0; i < matrix.num_cidades+1; i++)
            {
                printf(" %d ", matrix.melhorCaminho[i]);
            }
            printf("\n");
            printf("Menor distancia: %d\n", matrix.dist_total);
            printf("Tempo de execucao: %f segundos\n", elapsed_time);
        }
        

        // Liberar memória
        free(matrix.caminhoOriginal);
        free(matrix.distancias);
        free(matrix.melhorCaminho);

    } else {
        printf("Opção invalida!\n");
    }

    return 0;
}