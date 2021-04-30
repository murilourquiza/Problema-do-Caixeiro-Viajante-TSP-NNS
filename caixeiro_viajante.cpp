#include <iostream>
#include <stdio.h>
#include <string>
#include <algorithm>
#include <cstring>
#include <cmath>
#define MAX 100

using namespace std;

typedef struct elemento { int dado_cidade;    struct elemento *prox; } Elem;
typedef struct elemento* Lista;
typedef struct Ponto { int x, y; } ponto;
 
void takeInput();
void postInput();
Lista* makeList();
void showError(int);
void freeList(Lista*);
void printList(Lista*);
void removeSpaces(char *);
int howManyDigits(int, int);
double calculateDistance(ponto, ponto);
void putCoordinatesInMatrix(int, ponto *);
void insertAsLastElementOfList(Lista*, int);
bool verifyBelonging(int, ponto* , ponto*, bool);
void removeCharsFromString(string &, char*, int);
void allocateCoordinates(ponto *, string &, int, int);
void allocateStartingCoordinates(string &, ponto*, int);
 
int main(void) {
    cout << "\n" << "Problema do Caixeiro Viajante - TSP (metodo do vizinho mais proximo)" << "\n\n";
    takeInput();
    return 0;
}

void takeInput() {
    /* 1. Recebe a quantidade de cidades existentes no universo */

    unsigned int MAX_CIDADES;
    cout << "Insira a quantidade de cidades por onde o vendedor vai passar: ";
    cin >> MAX_CIDADES;
    getchar();
 
    // Se não existirem cidades (ou cidades negativas), o vendedor não pode viajar.
    if(MAX_CIDADES <= 0) {
        showError(422);
    }
 
    /* 2. Recebe as coordenadas das cidades e as armazena no array "coordenadas" */
 
    ponto coordenadas[MAX];         string coordenadas_existentes;
 
    cout << "Insira as coordenadas das cidades e aperte enter." << "\n" << "> ";
    getline(std::cin, coordenadas_existentes);
 
    // Filtra os valores recebidos e coloca-os nas coordenadas
 
    removeCharsFromString(coordenadas_existentes, const_cast<char*>("()!@#$&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMONQRSTUVWXYZ"), coordenadas_existentes.length());
    allocateCoordinates(coordenadas, coordenadas_existentes, coordenadas_existentes.length(), MAX_CIDADES);
 
    /* 3. Recebe a coordenada inicial do vendedor e a filtra, removendo caracteres desnecessários */
 
    ponto p_coordenada_inicial;     string s_coordenada_inicial;

    cout << "Insira a coordenada inicial do vendedor" << "\n" << "> ";
    getline(std::cin, s_coordenada_inicial);
 
    // Filtra os valores iniciais, antes de passá-los para um ponto.
 
    removeCharsFromString(s_coordenada_inicial, const_cast<char*>("()!@#$&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMONQRSTUVWXYZ"), s_coordenada_inicial.length());
    allocateStartingCoordinates(s_coordenada_inicial, &p_coordenada_inicial, s_coordenada_inicial.length());
 
    /*  4. Verificar se a coordenada inserida como coordenada inicial pertence ao universo de coordenadas,
        se pertencer, coloque essas coordenadas numa matriz; senão, vá para a postInput do programa. */
 
    (verifyBelonging(MAX_CIDADES, coordenadas, &p_coordenada_inicial, false) == true ? putCoordinatesInMatrix(MAX_CIDADES, coordenadas) : showError(404));
    postInput();
}
 
void allocateCoordinates(ponto *coordenadas, string &coordenadasInput, int coordenadasLength, int MAX_CIDADES) {
    bool nextDigit = false;         bool negativeNum = false;
    short int valueDigits = 0;      short int allocatedNumbers = 0;
 
    for(int l = 0, i = 0; l < coordenadasLength; ++l) {

        if(coordenadasInput[l] == '-') {    // Se for um número negativo, ativar o negativeNum
            coordenadasInput[l] = ' ';
            negativeNum = true;
        }

        if(isdigit(coordenadasInput[l]) != 0) {
            if(nextDigit == true) { // Armazenar a coordenada Y
                coordenadas[i].y = stoi(coordenadasInput);
                valueDigits = howManyDigits(coordenadas[i].y, 0);
                nextDigit = false;
                allocatedNumbers++;
                i++;
                if(negativeNum == true) {
                    coordenadas[i].y *= (-1);
                    negativeNum = false;
                }
            } else {                // Armazenar a coordenada X
                coordenadas[i].x = stoi(coordenadasInput);
                valueDigits = howManyDigits(coordenadas[i].x, 0);
                nextDigit = true;
                if(negativeNum == true) {
                    coordenadas[i].x *= (-1);
                    negativeNum = false;
                }
            }
 
            if(valueDigits > 0) {
                for(int q = l; q < (l + valueDigits); q++) {
                    coordenadasInput[q] = ' ';
                }
            }
        } else {
            coordenadasInput[l] == ' ';
        }
    }

    if(allocatedNumbers != MAX_CIDADES) {
        showError(400);
    }
}

void allocateStartingCoordinates(string &s_coordenada_inicial, ponto *p_coordenada_inicial, int lengthCoordenadaInicial) {
    for(int j = 0; j < lengthCoordenadaInicial; j++) {
        if(isdigit(s_coordenada_inicial[j]) == 0) {
            s_coordenada_inicial[j] = ' ';
        }
    }
 
    char char_array[lengthCoordenadaInicial + 1];
    strcpy(char_array, s_coordenada_inicial.c_str());

    removeSpaces(char_array);
 
    string someString(char_array);

    p_coordenada_inicial->x = stoi(someString);
    
    for(int w = 0; w < howManyDigits(p_coordenada_inicial->x, 0); w++) {
        someString[w] = ' ';
    }
 
    p_coordenada_inicial->y = stoi(someString);
}

void removeSpaces(char *str) {
    int contador = 0;
  
    int i = 0;
    for (i = 0; str[i]; i++)
        if (str[i] != ' ') {
            str[contador++] = str[i];
            str[contador++] = ' ';
            i++;
        }
    str[contador] = '\0';
}

bool verifyBelonging(int MAX_CIDADES, ponto *coordenadas, ponto *p_coordenada_inicial, bool coordenada_pertence) {
    for(int p = 0; p < MAX_CIDADES; p++) {
        if((p_coordenada_inicial->x == coordenadas[p].x) && (p_coordenada_inicial->y == coordenadas[p].y)) {
            coordenada_pertence = true;
            break;
        }
    }
 
    return coordenada_pertence;
}
 
void putCoordinatesInMatrix(int MAX_CIDADES, ponto *coordenadas) {
    Lista *li;
    li = makeList();
    /* O valor que será utilizado no array será o MAX_CIDADES para linha e coluna */
 
    double pontosDistancia[MAX][MAX] = {};
    
    /* Armazenar as distâncias das coordenadas na matriz pontosDistancia */
 
    for(int h = 0; h < MAX_CIDADES; h++) {
        for(int k = 0; k < MAX_CIDADES; k++) {
 
            /*  Se o h for igual a k, então estamos tratando de uma relação de si para si, e como a distância será 0, não mudaremos o que
                já está definido */
 
            if(h != k) {    // Se não for uma posição de relação si para si, e ainda não tiver sido percorrido, teremos que preencher a
                if(pontosDistancia[h][k] == 0) { // a mesma distância para pontosDistancia[h][k] e [k][h]
                    pontosDistancia[h][k] = pontosDistancia[k][h] = calculateDistance(coordenadas[h], coordenadas[k]);
                }
            }
        }
    }
 
    printf("\nMatriz de custo :\n\n");
    for(int h = 0; h < MAX_CIDADES; h++){
        for(int k = 0; k < MAX_CIDADES; k++){
            printf("%.2f ", pontosDistancia[h][k]);
        }
        printf("\n");
    }
    printf("\n");

    double vetor_auxiliar[MAX_CIDADES - 1];
    int cidade_visitada[MAX_CIDADES] = {};
    double total;
    int i = 0;
    
    printf("Caminho: \n\n");
    while(true) {
        insertAsLastElementOfList(li, i);
        int tamanho = 0, j = 0, contador = 0;
        double vizinho_mais_proximo;
 
        // marcar as cidades já visitadas
        cidade_visitada[i] = 1;
 
        // criando vetor auxiliar com elementos da linha "i";
        for(j = 0; j < MAX_CIDADES; j++){
            if(pontosDistancia[i][j] != 0){ 
                if(cidade_visitada[j] == 0){
                    vetor_auxiliar[tamanho] = pontosDistancia[i][j];
                    tamanho++;
                }
            }
        } 
 
        // no caso onde ja percorreu todas as cidades e tem que voltar para a cidade inicial;
        if(tamanho == 0) {
            total = total + pontosDistancia[i][0];
            printList(li);
            printf("1");
            printf("\n\nO custo encontrado do menor caminho foi %.2f\n\n", total);
            freeList(li);
            return;
        }
 
        // identificar o "vizinho mais proximo"
        vizinho_mais_proximo = vetor_auxiliar[0];
        for(contador = 1; contador < tamanho; contador++) {
            if(vetor_auxiliar[contador] < vizinho_mais_proximo) {
                vizinho_mais_proximo = vetor_auxiliar[contador];
            }
        }
 
        j = 0;
        bool encerrar = false;
        while(encerrar == false) {
            if(cidade_visitada[j] == 0) {
                if(pontosDistancia[i][j] != vizinho_mais_proximo) {
                    j++;
                } else {
                    encerrar = true;
                }
            } else {
                j++;
            }
        }
 
        total = total + pontosDistancia[i][j];
        i = j;
    }
}
 
void removeCharsFromString(string &str, char* charsToRemove, int lengthString) {
    for (unsigned int i = 0; i < strlen(charsToRemove); ++i) {
        str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
    }
 
    for(int h = 0; h < lengthString; h++) {
        if((str[h] == ',') || (str[h] == '.')) {
            str[h] = ' ';
        }
    }
}
 
double calculateDistance(ponto coord_um, ponto coord_dois) {
    double coordenada_x = pow(double(coord_dois.x - coord_um.x), 2);
    double coordenada_y = pow(double(coord_dois.y - coord_um.y), 2);
    return sqrt(coordenada_x + coordenada_y);
}
 
int howManyDigits(int num, int i) {
    if(num == 0) {
        return 1;
    }
 
    while(num > 0) {
        num = num / 10;
        i++;
    }
    return i;
}
 
Lista* makeList(){
    Lista* li = (Lista*)malloc(sizeof(Lista));
    if(li != NULL){
        *li = NULL;
    }
    return li;
}
 
void freeList(Lista* li) {
    if(li != NULL) {
        Elem* no;
        while((*li) != NULL) {
            no = *li;
            *li = (*li) -> prox;
            free(no);
        }
        free(li);
    }
}

void insertAsLastElementOfList(Lista* li, int dado){
    if(li == NULL){
        printf("Erro na alocacao\n");
        return;
    }
    Elem* no = (Elem*)malloc(sizeof(Elem));
    if(no == NULL){
        printf("Erro na alocacao\n");
        return;
    }
    no->dado_cidade = dado;
    no->prox = NULL;
    if((*li) == NULL){
        *li = no;
    }else{
        Elem *aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return;
}
 
void printList(Lista* li){
    Elem *no = *li;
    while(no != NULL){
        printf("%i -> ", (no->dado_cidade + 1));
        no = no->prox;
    }
    free(no);
}

void postInput() {
    int opcaoPosPrograma = -1;
    cout << "1. Verificar outra distancia" << "\n" << "2. Encerrar o programa" << "\n";
    cin >> opcaoPosPrograma;
    switch(opcaoPosPrograma) {
        case 1:
            takeInput();
            break;
        case 2:
            break;
        default:
            cout << "Opcao invalida!" << "\n";
            postInput();
            break;
    }
    return;
}

void showError(int codigoErro) {
    switch(codigoErro) {
        case 400:
            cout << "Entrada incompleta - coordenadas insuficientes (400)" << "\n";
            break;
        case 404:
            cout << "Entrada invalida - A coordenada inserida nao pertence ao universo (404)" << "\n";
            break;
        case 422:
            cout << "Entrada invalida - numero negativo ou nulo de cidades (422)" << "\n";
            break;
        default:
            cout << "Erro inesperado (-1)" << "\n";
            break;
    }
    exit(codigoErro);
}