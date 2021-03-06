#include <iostream>

//classe que representa cada rota/caminho entre cada dois v�rtices/pontos
class Aresta
{
public:
    int v1;
    int v2;
    float distancia;
    float feromonio;
    float probabilidade;
    float feromonioAux;
};

//fun��o utilizada para setar os valores no grafo,
Aresta setAresta(int v1, int v2, float distancia)
{
    Aresta aux;
    aux.v1 = v1;
    aux.v2 = v2;
    aux.distancia = distancia;
    aux.feromonio = 0.1;
    aux.feromonioAux = 0;
    return aux;
}

//fun��o que recebe dois pontos e busca qual a posi��o da aresta no vetor
int retornarAresta(int v1, int v2, Aresta A[], int numArestas)
{
    int i = 0;
    while(i <= numArestas)
    {
        if((A[i].v1 == v1 && A[i].v2 == v2) || (A[i].v1 == v2 && A[i].v2 == v1))
            return i;
        i++;
    }
    return -1;
}

//fun��o principal,calcula probabilidades, caminhos, distancia e niveis de feromonio
void retornarRota(int numIteracoes, int numVertices, int numArestas, Aresta A[])
{
    int verticesVisitados[numVertices];
    int rota[numVertices + 1];
    int cont = 0, i, verticeAtual, aux, distanciaPercorrida;
    float P = 0, somatorio = 0, aleatorio;

    while(numIteracoes > 0)
    {
        printf("\n\n ======================== Iteracao ========================\n");
        //laco que calcula rota partindo de cada ponto
        for(int v = 0; v < numVertices; v++)
        {
            cont = 0;
            verticeAtual = v;
            distanciaPercorrida = 0;

            //la�o que limpa os vetores utilizados
            for(i = 0; i <= numVertices; i++)
            {
                verticesVisitados[i] = 0;
                rota[i] = -1;
            }
            verticesVisitados[verticeAtual] = 1;
            rota[0] = verticeAtual;

            //la�o responsavel por tracar uma rota
            while(cont <= numVertices)
            {
                cont ++;
                somatorio = 0;

                //la�o que faz o somatorio usado no calculo da probabilidade
                for(i = 0; i < numVertices; i++)
                {
                    if(verticeAtual != i && verticesVisitados[i] == 0)
                    {
                        aux = retornarAresta(verticeAtual, i, A, numArestas);
                        if(aux >= 0)
                            somatorio += (A[aux].feromonio/A[aux].distancia);
                    }
                }

                aleatorio = rand() % 1000;
                aleatorio = aleatorio/10;
                P = 0;

                //la�o que calcula a probabilidade, e em seguida desloca para o pr�ximo v�rtice
                for(i = 0; i < numVertices; i++)
                {
                    if(verticeAtual != i && verticesVisitados[i] == 0)
                    {
                        //seleciona aresta
                        aux = retornarAresta(verticeAtual, i, A, numArestas);
                        P += (( A[aux].feromonio/A[aux].distancia)/somatorio)*100;
                        //condicional para simular o grafico de pizza, fazendo uma escolha aleat�ria,
                        //quanto maior a probabilidade maior a chance de escolha
                        if(aleatorio <= P || P > 99.9)
                        {
                            verticesVisitados[i] = 1;
                            rota[cont] = i;
                            distanciaPercorrida += A[aux].distancia;
                            verticeAtual = i;
                            i = numVertices;
                        }
                    }
                }
            }

            //adiciona o vertice inicial ao final do vetor
            rota[cont - 1] = rota[0];
            aux = retornarAresta(rota[cont - 2], rota[0], A, numArestas);
            distanciaPercorrida += A[aux].distancia;

            //atualizar feromonio de cadas trecho, guardar em uma auxiliar, e s� atualizar no original ap�s rodar todos os v�rtices
            for(i = 0; i < 5; i++)
            {
                aux = retornarAresta(rota[i], rota[i+1], A, numArestas);
                A[aux].feromonioAux += 10/(float)distanciaPercorrida;
            }

            printf("\n rota partindo de v(%d): |", v);
            for(i = 0; i <= numVertices; i++)
            {
                printf(" %d ", rota[i]);
            }
            printf("| distancia: %d", distanciaPercorrida);
        }
        //atualiza dados feromonio
        for(i = 0; i < numArestas; i++)
        {
            A[i].feromonio = (A[i].feromonio * 0.99) + A[i].feromonioAux;
            A[i].feromonioAux = 0;
        }
        numIteracoes--;
    }
    printf("\n");
}

//funcao teste, onde foi criado um grafo para exemplo
void Grafo1(int numeroIte)
{
    int numVertices = 5;
    int numArestas = (numVertices * (numVertices - 1))/2;//numero de arestas calculado assumindo grafo completo

    //cria vetor com todos os caminhos
    Aresta A[numArestas];

    //armazena as informa��es de cada caminho, n�o faz a duplica��ode caminhos
    A[0] = setAresta(0, 1, 26);
    A[1] = setAresta(0, 2, 18);
    A[2] = setAresta(0, 3, 63);
    A[3] = setAresta(0, 4, 22);
    A[4] = setAresta(1, 2, 35);
    A[5] = setAresta(1, 3, 41);
    A[6] = setAresta(1, 4, 38);
    A[7] = setAresta(2, 3, 19);
    A[8] = setAresta(2, 4, 30);
    A[9] = setAresta(3, 4, 32);

    retornarRota(numeroIte, numVertices, numArestas, A);
}

int main ()
{

    int numeroIte;
    printf("\n ---------- Algoritmo Colonia de Formigas - Aplicado Ao Problema do Caixeiro Viajante ----------");
    printf("\n\n\n\nInforme o numero de iteracoes desejadas: ");
    scanf(" %d", &numeroIte);

    Grafo1(numeroIte);

    return 0;
}
