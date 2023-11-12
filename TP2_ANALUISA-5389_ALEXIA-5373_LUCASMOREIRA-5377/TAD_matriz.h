typedef struct Matriz
{
    int num_cidades;
    int primeira_cidade;
    int** distancias;
    int* melhorCaminho;
    int dist_total; // menor distancia
    int* caminhoOriginal; // vetor sem a primeira cidade


}Matriz;


void Imprimir_Matriz(Matriz matrix);
void Inicializar_Matriz(Matriz *matrix, int num_cidades);
void set_Dist_Total(Matriz *matrix, int distancia);
void set_Num_Cidades(Matriz *matrix, int num_cidades);
void set_Primeira_Cidade(Matriz* matrix);
void Set_Distancias(Matriz *matrix);
void Set_Arquivo(Matriz *matrix, char* nomeArquivo);
void Troca(Matriz *matrix, int i, int j);
void Permuta(Matriz *matrix, int inf, int sup);
void Faz_Vetor(Matriz* matrix);
void Calcular_Distancia(Matriz *matrix);
void Set_Arquivo(Matriz* matrix, char* nomeArquivo);
int CriaArquivo(Matriz *matrix, double tempo);