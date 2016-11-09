#include <iostream>
#include <fstream>
#include <algorithm>
#include "Adjacente.h"
#include "Grafo.h"

using namespace std;

fstream inputFile, outputFile;
long ordemGrafo = 1, kRegular, numArestas;
bool isContainPesoAresta = true;
bool imprimirEmArquivo;
Grafo grafo(1,1);    //cria grafo não direcionado


void apresentacaoTrabalho();

void criaCabecalho(long _ordemGrafo);

int exibeMenu();

void criarGrafo(long _ordemGrafo, long _numArestas);

void lerAdjacencias(bool isContainPeso);

void verificaGrauVertice();

void verificaGrauGrafo();

void verificaAdjacenciaVertices();

void listaAdjacentesVertice();

void geraSubGrafoInduzido();

void verificaKRegularidade();

void geraGrafoComplemetar();

void verificaGrafoCompleto();

void verificaConexo();

//verificaBipartido

void chamaFuncaoEscolhida(int opMenu);


void verificaBipartido();

bool isVerticeArticulacao();

bool isArestaPonte();

void removeAresta();

void removeVertice();

void verificaFechoTransitivo();

void verificaFechoIntransitivo();

void coberturaDeVerticesGuloso();

void adicionaVertice();

void adicionaAresta();

void sequenciaGraus();

void verificaVerticesComponentesConexa();

void imprimeMensagem(string msg);

void mostraIdVerticesAdjacentes();

int main(int argc, char **argv) {

    int opMenu;
    char cOrdemGrafo[15], cNumArestas[15];

    apresentacaoTrabalho();

    //Usado 4 para rodar com o Cmake, atualizar para 3 quando for rodar no terminal
    if (argc == 4) {
        inputFile.open(argv[2], ios::in);   //Mudar para 1 quando for rodar no terminal
        outputFile.open(argv[3], ios::out); //Mudar para 2 quando for rodar no terminal
        //Verificar se arquivo de entrada foi aberto
        if (!inputFile) {
            cerr << "ERRO: Arquivo " << argv[2] << " não foi encontrado!"
                 << endl; //voltar para 1 quando executar no terminal
            return -1;
        }
        //Verificar se arquivo de saída foi criado
        if (!outputFile) {
            cerr << "ERRO: Arquivo " << argv[3] << " não pode ser criado!"
                 << endl; //voltar para 2 quando executar no terminal
            return -1;
        }
    } else {
        cerr << "ERRO: Informar os arquivos de entrada ou saída na execução do algoritmo" << endl;
        return 0;
    }

    cout << "Lendo o Tamanho do grafo...\nOK\n" << endl;
    //Faz leitura do tamanho do Grafo
    inputFile >> cOrdemGrafo >> cNumArestas;

    //Converte char para string e depois string para long
    string sOrdemGrafo = string(cOrdemGrafo);
    string sNumArestas = string(cNumArestas);
    ordemGrafo = stol(sOrdemGrafo); //voltar para sOrdemGrafo
    numArestas = stol(sNumArestas);


    cout << "Criando grafo..." << endl;
    criarGrafo(ordemGrafo, numArestas);

    cout << "Gerando Adjacências do grafo...\nOK\n" << endl;
    lerAdjacencias(isContainPesoAresta);

    criaCabecalho(ordemGrafo);

    cout << "Deseja salvar as informações de consulta em arquivo?" << endl;
    cout << "0-Não\t 1-Sim" << endl;
    cin >> imprimirEmArquivo;

    do {
        opMenu = exibeMenu();
        if (opMenu != 0) {
            chamaFuncaoEscolhida(opMenu);
        }
    } while (opMenu != 0);


    cout << "\nOs dados de análise foram salvos no arquivo de saída" << endl;


    //Fecha IO
    outputFile.close();
    inputFile.close();

    return 0;
}


void apresentacaoTrabalho() {
    char trash;
    cout << "\n\n";
    cout << "#############################################" << endl;
    cout << "\tTrabalho de Teoria dos Grafos" << endl;
    cout << "#############################################\n\n" << endl;
    //cout << "\nObs: Os dados serão gerados automaticamente para o arquivo de saída informado por parâmetro.\n" << endl;

    cout << "Digite 1 + <Enter> para iniciar o algoritmo...";
    cin >> trash;
    cout << "\n\n";
}

void criaCabecalho(long _ordemGrafo) {
    outputFile << "Trabalho de Grafos" << endl;
    outputFile << "Autor: Helder Linhares Bertoldo dos Reis" << endl;
    outputFile << "Matrícula: 201465555A\n\n" << endl;

    outputFile << "- Análise do Grafo -\n" << endl;
    outputFile << "Número de Vértices: " << _ordemGrafo << endl;
    outputFile << "Número de Arestas: " << numArestas << "\n" << endl;
}

int exibeMenu() {
    int opMenu;


    cout << " 1- Adicionar Vértice" << endl;
    cout << " 2- Remover Vértice" << endl;
    cout << " 3- Adicionar Aresta" << endl;
    cout << " 4- Remover Aresta" << endl;
    cout << " 5- Verificar o Grau de um vértice" << endl;
    cout << " 6- Verificar sequência de graus" << endl;
    cout << " 7- Verificar se o Grafo é K-Regular" << endl;
    cout << " 8- Verificar se o Grafo é Completo" << endl;
    cout << " 9- Verificar adjacência entre vértices" << endl;
    cout << "10*- Realizar busca em largura" << endl;
    cout << "11*- Realizar busca em profundidade" << endl;
    cout << "12- Verificar se o Grafo é conexo" << endl;
    cout << "13- Verificar se vértices estão na mesma componente conexa" << endl;
    cout << "14- Verificar se um dado Vértice é de Articulação" << endl;
    cout << "15- Verificar se uma dada Aresta é Ponte" << endl;
    cout << "16*- Verificar vizinhança de um vértice" << endl;
    cout << "17- Fecho Transitivo" << endl;
    cout << "18- Fecho Intransitivo" << endl;
    cout << "19- Ordenação Topológica do DAG" << endl;
    cout << "20*- Caminho Mínimo Dijkstra" << endl;
    cout << "21*- Caminho Mínimo Floyd" << endl;
    cout << "22- Verificar o subgrafo induzido por um dado subconjunto de vértices" << endl;
    cout << "23*- Verificar Componentes Conexas" << endl;
    cout << "24*- Verificar o grafo gerado pelo produto cartesiano entre o grafo e outro grafo" << endl;
    cout << "24*- Árvore Geradora Mínima - Prim" << endl;
    cout << "25*- Árvore Geradora Mínima - Kruskal" << endl;
    cout << "26*- Verificar Grafo K-Conexo" << endl;
    cout << "28*- Verificar se grafo é Euleriano" << endl;
    cout << "29- Verificar o Grau de G" << endl;
    cout << "30- Listar os adjacentes de um vértice" << endl;
    cout << "31- Retornar o Grafo Complementar G" << endl;
    cout << "32- Cobertura de Vértices Guloso" << endl;
    cout << "33- Cobertura de Vértices Guloso Randomizado" << endl;
    cout << "34- Cobertura de Vértices Guloso Randomizado Reativo" << endl;
    cout << "35- Informar adjacentes de um vértice" << endl;
    cout << " 0- Sair" << endl;
    cout << "\nOpção: ";
    cin >> opMenu;
    return opMenu;
}

void chamaFuncaoEscolhida(int opMenu) {
    switch (opMenu) {
        case 0: {
            cout << "Algoritmo Encerrado. Os dados foram armazenados em arquivo." << endl;
            break;
        }
        case 1: {
            adicionaVertice();
            break;
        }
        case 2: {
            removeVertice();
            break;
        }
        case 3: {
            adicionaAresta();
            break;
        }
        case 4: {
            removeAresta();
            break;
        }
        case 5: {
            verificaGrauVertice();
            break;
        }
        case 6: {
            sequenciaGraus();
            break;
        }
        case 7: {
            verificaKRegularidade();
            break;
        }
        case 8: {
            verificaGrafoCompleto();
            break;
        }
        case 9: {
            verificaAdjacenciaVertices();
            break;
        }
        case 10: {
            //realizaBuscaLargura();
            break;
        }
        case 11: {
            //realizaBuscaProfundidade();
        }
        case 12: {
            verificaConexo();
            break;
        }
        case 13: {
            verificaVerticesComponentesConexa();
            break;
        }
        case 14: {
            isVerticeArticulacao();
            break;
        }
        case 15: {
            isArestaPonte();
            break;
        }
        case 16: {
            //mostraVizinhanca();
            break;
        }
        case 17: {
            verificaFechoTransitivo();
            break;
        }
        case 18: {
            verificaFechoIntransitivo();
            break;
        }
        case 19: {
            //ordenacaoTopologicaDag();
            break;
        }
        case 20: {
            //caminhoMinimoDijkstra();
            break;
        }
        case 21: {
            //caminhoMinimoFloyd();
            break;
        }
        case 22: {
            geraSubGrafoInduzido();
            break;
        }
        case 23:{
            //verificarComponentesConexas();
            break;
        }
        case 24: {
            //produtoCartesianoGrafos();
            break;
        }
        case 25: {
            //arvoreGeradoraMinimaPrim();
            break;
        }
        case 26: {
            //arvoreGeradoraMinimaKruskal();
            break;
        }
        case 27: {
            //verificaGrafoKConexo();
            break;
        }
        case 28: {
            //verificaGrafoEuleriano();
            break;
        }
        case 29: {
            verificaGrauGrafo();
            break;
        }
        case 30: {
            listaAdjacentesVertice();
            break;
        }
        case 31: {
            geraGrafoComplemetar();
            break;
        }
        case 32: {
            //coberturaDeVerticesGuloso();
            break;
        }
        case 33: {
            //coberturaDeVerticesGulosoRandomizado();
            break;
        }
        case 34: {
            //coberturaDeVerticesGulosoRandomizadoReativo();
            break;
        }
        case 35: {
            mostraIdVerticesAdjacentes();
        }
        default: {
            cout << "ERRO: Opção Inválida!" << endl;
        }
    }
}

void mostraIdVerticesAdjacentes() {
    long _idVertice;
    int op;
    do {
        cout << "\nId do vértice que deseja consultar os adjacentes: ";
        cin >> _idVertice;
        grafo.getVertice(_idVertice)->mostraIdAdjacentes();

        cout << "0 - Sair\t 1- Verificar outro vértice" << endl;
        cin >> op;

    }while(op != 0);

}

/**
 * Verifica se 2 vértices estão na mesma componente conexa
 */
void verificaVerticesComponentesConexa() {
    long idVertice1, idVertice2;
    bool isMesmaComponente;
    string msg;
    int op;

    do {
        cout << "Informe o id dos vértices: " << endl;
        cin >> idVertice1 >> idVertice2;
        isMesmaComponente = grafo.verificaVerticesComponentesConexa(idVertice1, idVertice2);

        if (isMesmaComponente) {
            msg = "Os vértices " + to_string(idVertice1) + " e " + to_string(idVertice2) +
                  " estão na mesma componente conexa.\n";
            cout << msg << endl;
        } else {
            msg = "Os vértices " + to_string(idVertice1) + " e " + to_string(idVertice2) +
                  " não estão na mesma componente conexa.\n";
            cout << msg << endl;
        }

        if(imprimirEmArquivo){
            imprimeMensagem(msg);
        }

        cout << "0-Sair\t 1-Nova verificação" << endl;
        cin >> op;

    }while(op == 1);
}

void imprimeMensagem(string msg) {
    outputFile << msg << endl;
}

void adicionaAresta() {
    long idVerticeOrigem, idVerticeDestino, peso = 0;

    cout << "Informe a aresta que deseja inserir: " << endl;
    cout << "Vértice de Origem: ";
    cin >> idVerticeOrigem;
    cout << "Vértice de Destino: ";
    cin >> idVerticeDestino;
    if (isContainPesoAresta) {
        cout << "Peso: ";
        cin >> peso;
    }
    grafo.addVerticeAdjacente(idVerticeOrigem, idVerticeDestino, peso);
    cout << endl;

}

void adicionaVertice() {
    long idVertice;
    cout << "Informe o id do vértice que deseja adicionar: ";
    cin >> idVertice;

    grafo.addVertice(idVertice);
    cout << endl;

}

void coberturaDeVerticesGuloso() {
    vector<long> verticesUtilizados;

    Grafo grafoAux(ordemGrafo,numArestas);
    grafoAux = grafo;
    multiset<pair<double, int>> rankeamentoDeVertices;
    pair<double, int> infoRankeamento; //pesoParaRankeamento, idVertice
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;

    while (!coberto) {
        for (int i = 0; i < grafoAux.getOrdemGrafo(); i++) {
            if (grafoAux.getVertice(i)->getGrau() != 0) {
                pesoParaRankeamento = grafoAux.getVertice(i)->getPeso() / (grafoAux.getVertice(i)->getGrau() * 1.0);
                infoRankeamento = make_pair(pesoParaRankeamento, grafoAux.getVertice(i)->getIdVertice());
                rankeamentoDeVertices.insert(infoRankeamento);
            } else {
                //Evita q peso 0 seja escolhido
                pesoParaRankeamento = 999999;
                infoRankeamento = make_pair(pesoParaRankeamento, grafo.getVertice(i)->getIdVertice());
            }
        }
        idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;

        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo
        long teste;

        //Remove as arestas que o vértice cobre
        auto it = grafoAux.getVertice(idVerticeMenorCusto)->getVerticesAdjacentes();
        for (int i=0; i< grafo.getTamTabHashAdj(); i++) {
            for(auto adj = it[i].begin(); adj != it[i].end(); adj++) {
                teste = adj->getIdVertice();
                grafoAux.removeVerticeAdjacente(idVerticeMenorCusto, adj->getIdVertice());
            }
        }

        //Verifica se a cobertura está completa
        coberto = true;
        for (int i = 0; i < grafoAux.getOrdemGrafo(); i++) {
            if (grafoAux.getVertice(i)->getGrau() > 0) {
                coberto = false;
                rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                break;
            }
        }
    }

    outputFile << "\nCobertura Mínima: " << verticesUtilizados.size() << " vértice(s)" << endl;
    for (int i = 0; i < verticesUtilizados.size(); i++) {
        outputFile << verticesUtilizados[i];
        if (i < verticesUtilizados.size() - 1) {
            outputFile << ", ";
        }
    }

}

void verificaFechoTransitivo() {

    long idVertice;
    string sFechoTransitivo;

    do {
        cout << "Informe o id do Vértice que deseja visitar: ";
        cin >> idVertice;

        if (idVertice < 0 || idVertice >= ordemGrafo) {
            cout << "Vertice inválido!\n " << endl;
        } else {
            sFechoTransitivo = grafo.fechoTransitivo(idVertice);

            outputFile << "Fecho Transitivo do Vértice " << idVertice << " -> ";
            outputFile << sFechoTransitivo << endl;
        }
    } while (idVertice < 0 || idVertice >= ordemGrafo);
}

void verificaFechoIntransitivo() {
    long idVertice;
    string sFechoIntransitivo;

    do {
        cout << "Informe o id do Vértice que deseja visitar: ";
        cin >> idVertice;

        if (idVertice < 0 || idVertice >= ordemGrafo) {
            cout << "Vertice inválido!\n " << endl;
        } else {
            sFechoIntransitivo = grafo.fechoIntransitivo(idVertice);

            outputFile << "Fecho Intransitivo do Vértice " << idVertice << " -> ";
            outputFile << sFechoIntransitivo << endl;
        }
    } while (idVertice < 0 || idVertice >= ordemGrafo);
}

void removeVertice() {
    long idVertice;
    cout << "Qual vértice remover? ";
    cin >> idVertice;
    grafo.removeVertice(idVertice);
    cout << endl;
}

void removeAresta() {
    long idOrigem, idDestino;
    cout << "Informe o Vértice de Origem: ";
    cin >> idOrigem;
    cout << "Informe o Vértice de Destino: ";
    cin >> idDestino;

    if (grafo.removeVerticeAdjacente(idOrigem, idDestino)) {
        cout << "Aresta removida corretamente" << endl;
    }
    cout << endl;
}

bool isArestaPonte() {

}

bool isVerticeArticulacao() {

}

void criarGrafo(long _ordemGrafo, long _numArestas) {
    Grafo grafoAux(_ordemGrafo,_numArestas);   //cria grafo auxiliar

    grafo = grafoAux;

    long i = 0;
    int op;

    while (i < _ordemGrafo) {
        grafo.addVertice(i);
        i++;
    }

    cout << "OK\n" << endl;

    //Verifica se o grafo é direcionado
    do {
        cout << "O Grafo é direcionado? " << endl;
        cout << "0-Não\t 1-Sim" << endl;
        cin >> op;
        if (op < 0 || op > 1) {
            cout << "ERRO: Opção Inválida!" << endl;
        } else {
            op == 0 ? grafo.setIsGrafoDirecionado(false) : grafo.setIsGrafoDirecionado(true);
        }

    } while (op < 0 || op > 1);
}

void lerAdjacencias(bool isContainPeso) {
    char cVerticeOrigem[15], cVerticeDestino[15];
    string sVerticeOrigem, sVerticeDestino;
    long verticeOrigem, verticeDestino;

    if (!isContainPeso) {
        while (inputFile >> cVerticeOrigem >> cVerticeDestino) {

            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);

            grafo.addVerticeAdjacente(verticeOrigem, verticeDestino, 0.0);
        }
    } else {
        char cPesoAresta[15];
        string sPesoAresta;
        float pesoAresta;
        while (inputFile >> cVerticeOrigem >> cVerticeDestino >> cPesoAresta) {
            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            sPesoAresta = string(cPesoAresta);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);
            pesoAresta = stof(sPesoAresta);

            grafo.addVerticeAdjacente(verticeOrigem, verticeDestino, pesoAresta);
        }
    }
}

void verificaGrauVertice() {

    int idVertice, op;
    do {
        cout << "Digite o id do Vértice que deseja consultar seu Grau: ";
        cin >> idVertice;
        auto it = grafo.isContainVertice(idVertice);

        if (it == grafo.itUltimaPosicao(idVertice)) {  //it não encontrou o vértice
            cout << "Erro: O grafo não possui vértice com o id informado!\n" << endl;
        } else {
            cout << "Verificando Grau do Vértice " << idVertice << "...\nOK\n" << endl;
            outputFile << "gr(" << idVertice << "): " << grafo.getGrauVertice(idVertice) << endl;
        }
        cout << "0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    } while (op != 0);
}

void verificaGrauGrafo() {
    outputFile << "gr(G): " << grafo.verificaGrauGrafo() << endl;
    cout << "Verificando Grau do grafo...\nOK\n" << endl;
}

void verificaAdjacenciaVertices() {
    int idVerticeOrigem, idVerticeDestino, op;
    do {
        cout << "Digite o id dos vértices que deseja verificar adjacência: \n";
        cout << "Vértice de Origem: ";
        cin >> idVerticeOrigem;
        cout << "Vértice de Destino: ";
        cin >> idVerticeDestino;

        if (idVerticeOrigem < 0 || idVerticeDestino >= ordemGrafo) {
            cout << "ERRO: Vértice de Origem Inválido!" << endl;
        } else if (idVerticeDestino < 0 || idVerticeDestino >= ordemGrafo) {
            cout << "ERRO: Vértice de Destino Inválido!" << endl;
        } else {
            cout << "Verificando Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << ")...\nOK\n" << endl;
            if (grafo.verificaAdjacencia(idVerticeOrigem, idVerticeDestino)) {
                outputFile << "Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << "): SIM" << endl;
            } else {
                outputFile << "Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << "): NÃO" << endl;
            }
        }
        cout << "0- Encerrar Função    1-Escolher Outros Vértices" << endl;
        cin >> op;
    } while (op != 0);
}


void listaAdjacentesVertice() {//4- Lista os Adjacentes de um Vértice
    int idVertice, op;
    do {
        cout << "Digite o id do Vértice que deseja consultar seus adjacentes: ";
        cin >> idVertice;

        list<Vertice>::iterator it = grafo.isContainVertice(idVertice);

        if (it == grafo.itUltimaPosicao(idVertice)) {
            cout << "Erro: Vértice Inválido!\n" << endl;
        } else {
            cout << "Verificando Vértices Adjacentes ao Vértice " << idVertice << "...\nOK\n" << endl;
            outputFile << "Vértices Adjacentes ao Vértice " << idVertice << ":\n";
            outputFile << idVertice << " -> " << grafo.getVertice(idVertice)->listarAdjacentes() << endl;
        }
        cout << "0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    } while (op != 0);
}

void geraSubGrafoInduzido() {
    long numVertices, idVertice;
    int i;
    list <Adjacente> *verticesAdjacentes;

    cout << "Gerar Grafo Induzido" << endl;
    cout << "Informe a quantidade de vértices do Grafo Induzido: ";
    cin >> numVertices;

    vector<long> verticesGrafoInduzido(numVertices);

    cout << "Informe os vértices(Um a Um):" << endl;
    for (i = 0; i < numVertices; i++) {
        cout << "v[" << i << "]:";
        cin >> idVertice;

        //verifica vertices informados
        if (idVertice < 0 || idVertice >= ordemGrafo) {
            cout << "Erro: Vértice Inválido!\n" << endl;
            i--;    //não atualiza contagem
        } else {
            verticesGrafoInduzido[i] = idVertice;
        }
    }

    //Ordena o Vetor
    sort(verticesGrafoInduzido.begin(), verticesGrafoInduzido.end());

    cout << "Gerando Grafo Induzido...\n";

    outputFile << "\nGrafo Induzido do conjunto de Vértices(";
    for (i = 0; i < numVertices; i++) {
        outputFile << verticesGrafoInduzido[i];
        //não mostrar vírgula pro último elemento
        if (i != numVertices - 1) {
            outputFile << ", ";
        }
    }
    outputFile << ")\n";

    //Para cada vértice informado, percorre o seu conjunto de adjacências em busca dos vértices adjacentes que foram informados
    for (i = 0; i < numVertices; i++) {

        outputFile << verticesGrafoInduzido[i] << " -> ";
        verticesAdjacentes = grafo.getVertice(verticesGrafoInduzido[i])->getVerticesAdjacentes();

        //verifica os não adjacentes
        for(int j=0; j<grafo.getTamTabHashAdj(); j++){
            for(auto it=verticesAdjacentes[j].begin(); it != verticesAdjacentes[j].end(); it++){
                for (int k = 0; k < numVertices; k++) {
                    if (it->getIdVertice() == verticesGrafoInduzido[k])
                        outputFile << verticesGrafoInduzido[k] << " ";
                }
            }
        }

        outputFile << endl;
    }
    cout << "Ok\n" << endl;
}

void verificaKRegularidade() {
    cout << "Verificando K-Regularidade...";
    if (grafo.verificaKRegular(&kRegular)) {
        outputFile << "Grafo K-Regular? SIM, Grafo " << kRegular << "-Regular" << endl;
    } else {
        outputFile << "Grafo K-Regular? NÃO" << endl;
    }
    cout << "\nOk\n" << endl;
}

/**
 * Gera o grafo complementar a um grafo dado grafo
 */
void geraGrafoComplemetar() {
    cout << "Gerando Grafo Complementar...\nOK\n" << endl;

    //Cria a tabela hash dos adjacentes com base no numero de arestas que complementam as atuais
    long numArestasComplementar = (grafo.getOrdemGrafo() * grafo.getOrdemGrafo()-1) - numArestas;

    Grafo grafoComplementar(grafo.getOrdemGrafo(),numArestasComplementar);

    vector<bool> idVerticesAdjacentes((unsigned long) ordemGrafo);
    list <Adjacente> *verticesAdjacentes;
    long pos;

    outputFile << "\n\nGrafo Complementar:" << endl;

    long tamanhoGrafoAux = ordemGrafo;
    //Zera vetor
    for (int k = 0; k < ordemGrafo; k++) {
        idVerticesAdjacentes[k] = false;
    }

    //Cria Grafo
    while (--tamanhoGrafoAux >= 0) {
        grafoComplementar.addVertice(tamanhoGrafoAux);
    }
    grafoComplementar.setIsGrafoDirecionado(false);    //informa se o grafo é direcionado


    for (long i = 0; i < ordemGrafo; i++) {

        //obtem os adjacentes do vértice
        verticesAdjacentes = grafo.getVertice(i)->getVerticesAdjacentes();

        //Marca todos adjacentes como true no vetor auxiliar
        for(int j=0; j<grafo.getTamTabHashAdj(); j++){
            for(auto it = verticesAdjacentes[j].begin(); it != verticesAdjacentes[j].end(); j++){
                pos = it->getIdVertice();
                idVerticesAdjacentes[pos] = true;
            }
        }

        //escreve no arquivo os vértices que não são adjacentes
        outputFile << i << " -> ";
        for (long j = 0; j < ordemGrafo; j++) {
            if (i != j && idVerticesAdjacentes[j] == false) {
                outputFile << j << " ";
            }
        }
        outputFile << "\n" << endl;

        //Zera vetor
        for (int k = 0; k < ordemGrafo; k++) {
            idVerticesAdjacentes[k] = false;
        }
    }
}

void verificaGrafoCompleto() {
    cout << "Verificando se Grafo é Completo...";
    outputFile << (grafo.isCompleto() ? "Grafo Completo: SIM" : "Grafo Completo: NÃO") << endl;
    cout << "\nOk\n" << endl;
}

void verificaConexo() {
    bool conexo;
    string msg;
    cout << "Verificando se Grafo é Conexo..." << endl;
    conexo = grafo.isConexo();
    cout << "\nOK\n" << endl;

    msg = (conexo ? "Grafo Conexo: SIM\n" : "Grafo Conexo: NÃO\n");

    cout << msg << endl;

    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }
}


/**
 * Informa a sequência de graus do grafo
 */
void sequenciaGraus(){
    multiset<long, greater<long> > sequencia = grafo.sequenciaGraus();  //ordenação decrescente
    auto setIni = sequencia.begin();
    auto setFim = sequencia.end();

    outputFile << "Sequência de Graus do Grafo: <";

    while(setIni != setFim){
        outputFile << *setIni;
        setIni++;

        if(setIni != setFim){
            outputFile << ", ";
        }else{
            outputFile << ">\n";
        }
    }
}
