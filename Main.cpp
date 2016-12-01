#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include "Adjacente.h"
#include "Grafo.h"

using namespace std;

fstream inputFile, outputFile;
long ordemGrafo = 1, kRegular, numArestas;
bool isContainPesoAresta = false;   //Informa se o arquivo de leitura do grafo tem peso das arestas
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

Grafo copiarGrafo(Grafo _g);

Grafo copiarGrafoArcosInvertidos(Grafo _g);

void chamaFuncaoEscolhida(int opMenu);


void verificaBipartido();

bool isVerticeArticulacao();

bool isArestaPonte();

void removeAresta();

void removeVertice();

void fechamentoTransitivoDireto();

void verificaFechoIntransitivo();

void coberturaDeVerticesGuloso();

int auxCVGR(double _alfa, bool imprime);

void coberturaDeVerticesGulosoRandomizado();

void adicionaVertice();

void adicionaAresta();

void sequenciaGraus();

void verificaVerticesComponentesConexa();

void imprimeMensagem(string msg);

void mostraIdVerticesAdjacentes();

void mostraVizinhanca();

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

    cout << endl;
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
            mostraVizinhanca();
            break;
        }
        case 17: {
            fechamentoTransitivoDireto();
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
            cout << "Verificando, por favor aguarde...";
            coberturaDeVerticesGuloso();
            break;
        }
        case 33: {
            cout << "Verificando, por favor aguarde...";
            coberturaDeVerticesGulosoRandomizado();
            break;
        }
        case 34: {
            cout << "Verificando, por favor aguarde...";
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

void mostraVizinhanca() {
    long idVertice;
    int op;
    list<long> vizinhancaAberta;
    do{
        cout << "Informe o id do vértice que deseja consultar a vizinhança: ";
        cin >> idVertice;
        vizinhancaAberta = grafo.getVizinhaAberta(idVertice);

        cout << "\nVizinhança Aberta: ";
        for(long it : vizinhancaAberta){
            cout << it << " " ;
        }
        cout << "\nVizinhança Fechada: " << idVertice << " ";
        for(long it : vizinhancaAberta){
            cout << it << " ";
        }

        cout << "\n0-Sair\t 1-Verificar Novamente" << endl;
        cin >> op;

    }while(op == 1);

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

        cout << "Analisando..." << endl;
        isMesmaComponente = grafo.verificaVerticesComponentesConexa(idVertice1, idVertice2);
        cout << "Ok" << endl;

        if (isMesmaComponente) {
            msg = "Os vértices " + to_string(idVertice1) + " e " + to_string(idVertice2) +
                  " estão na mesma componente conexa.\n";

        } else {
            msg = "Os vértices " + to_string(idVertice1) + " e " + to_string(idVertice2) +
                  " não estão na mesma componente conexa.\n";
        }

        cout << msg << endl;
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
    string msg="";
    Grafo grafoAux(ordemGrafo,numArestas);
    grafoAux = copiarGrafo(grafo);
    pair<double, int> infoRankeamento; //pesoParaRankeamento, idVertice
    multiset<pair<double, int>> rankeamentoDeVertices;
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;

    while (!coberto) {
        for(int i=0; i< grafoAux.getTamTabHashVertices(); i++) {
            for (auto it = grafoAux.getVertices()[i].begin(); it != grafoAux.getVertices()[i].end(); it++) {
                if (it->getGrau() != 0) {
                    pesoParaRankeamento = it->getPeso() / (it->getGrau() * 1.0);
                    infoRankeamento = make_pair(pesoParaRankeamento, it->getIdVertice());
                    rankeamentoDeVertices.insert(infoRankeamento);
                } else {
                    //Evita q peso 0 seja escolhido
                    pesoParaRankeamento = 99999;    //verificar int_max do c++
                    infoRankeamento = make_pair(pesoParaRankeamento, it->getIdVertice());
                }
            }
        }
        idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;

        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo

        //Remove as arestas que o vértice cobre
        grafoAux.removeVertice(idVerticeMenorCusto);

        //Verifica se a cobertura está completa
        coberto = true;
        for (int i = 0; i < grafoAux.getTamTabHashVertices(); i++) {
            for(auto it = grafoAux.getVertices()[i].begin(); it != grafoAux.getVertices()[i].end(); it++) {
                if (it->getGrau() > 0) {
                    coberto = false;
                    rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                    break;
                }
            }
            if(!coberto){
                break;
            }
        }
    }
    msg = "\n\nCobertura Mínima: " + to_string(verticesUtilizados.size()) + " vértice(s).\n";
    for (int i = 0; i < verticesUtilizados.size(); i++) {
        msg += to_string(verticesUtilizados[i]);
        if (i < verticesUtilizados.size() - 1) {
            msg += ", ";
        }
    }

    cout << msg << endl;

    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }
}

void coberturaDeVerticesGulosoRandomizado(){
    int op, numAlfas=3;
    bool imprime = false;   //verifica se os vértices da menor cobertura serão impressos
    string msg = "";
    double alfa[numAlfas] = {0.1,0.2,0.3};

    double melhorAlfa;

    int semente;
    //define a primeira semente como melhor
    int melhorSementeAlfa[numAlfas] = {1,1,1};

    srand(1);   //obtem a cobertura de cada alfa usando a semente 1
    long minCobertura[numAlfas];
    for(int i=0; i<numAlfas; i++){
        minCobertura[i] = auxCVGR(alfa[i],false);
    }

    int auxMinCobertura;


    for(semente=2; semente<=30; semente++){

        // inicializa o gerador de números randômicos
        srand(semente); //semente varia de 1 a 30

        for(int i=0; i<numAlfas; i++){
            auxMinCobertura = auxCVGR(alfa[i],false);
            if(auxMinCobertura < minCobertura[i]){
                minCobertura[i] = auxMinCobertura;
                melhorSementeAlfa[i] = semente;
            }
        }
    }

    cout << "\nDeseja que os vértices da melhor cobertura sejam exibidos?" << endl;
    cout << "1- Sim\t 0-Não" << endl;
    cin >> op;
    if(op==1){
        imprime = true;
    }
    cout << endl;
    msg = "\n--- Descrição da Cobertura Mínimal em Custo de Vértices Ponderados ---\n";

    cout << msg << endl;

    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }

    for(int i=0; i < numAlfas; i++){
        msg = "";   //Reseta a msg
        msg += "Alfa: " + to_string(alfa[i]) + "\n";
        msg += "Menor Cobertura: " + to_string(minCobertura[i]) + "\n";
        msg += "Melhor Semente: " + to_string(melhorSementeAlfa[i]) + "\n" ;
        msg += "Vertices utilizados: ";
        cout << msg << endl;

        if(imprimirEmArquivo){
            imprimeMensagem(msg);
        }

        if(imprime){
            srand(melhorSementeAlfa[i]);
            auxCVGR(alfa[i], true);
        }
    }
}

/**
 * Algoritmo auxiliar do metodo Construtivo Guloso Randomizado
 * @param _alfa
 * @param imprime - informar se deve ser impresso os vertices que fazem parte da cobertura
 * @return numero de vertices utilizados
 */

int auxCVGR(double _alfa, bool imprime) {
    long posicaoEscolhida;
    vector<long> verticesUtilizados;
    Grafo grafoAux = copiarGrafo(grafo);
    multiset< pair<double,int>> rankeamentoDeVertices;
    multiset< pair<double,int>>::iterator itRakeamento;
    pair<double,int> infoRankeamento; //pesoParaRankeamento, idVertice
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;
    long rangeMax;  //Vértice escolhido deve ser aleatório no intervalo de 0 a RageMax
    int valRandomico;
    int numVerticesGrauZero;
    string msg = "";

    while(!coberto){

        //Encontrar qual vai ser o vértice escolhido
        rangeMax = grafoAux.getOrdemGrafo() * _alfa;
        if(rangeMax>0){ //evitar divisão por zero
            valRandomico = rand();
            posicaoEscolhida = valRandomico % rangeMax;
        }
        else{
            posicaoEscolhida = 0;
        }

        for(int i=0; i<grafoAux.getTamTabHashVertices();i++){
            for(auto it = grafoAux.getVertices()[i].begin(); it!= grafoAux.getVertices()[i].end(); it++) {
                if (it->getGrau() != 0) {
                    pesoParaRankeamento = it->getPeso() / (it->getGrau() * 1.0);
                    infoRankeamento = make_pair(pesoParaRankeamento, it->getIdVertice());
                    rankeamentoDeVertices.insert(infoRankeamento);
                } else {
                    //Evita q peso 0 seja escolhido
                    pesoParaRankeamento = 999999;
                    infoRankeamento = make_pair(pesoParaRankeamento, it->getIdVertice());
                    rankeamentoDeVertices.insert(infoRankeamento);
                }
            }
        }

        //Posiciona o iterador na posição do elemento escolhido
        itRakeamento = rankeamentoDeVertices.begin();

        //Avança para a posiçao escolhida pela randomizaçao
        for(int i=0; i<posicaoEscolhida; i++){
            itRakeamento++;
        }

        //idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;
        idVerticeMenorCusto = itRakeamento->second;
        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo

        grafoAux.removeVertice(idVerticeMenorCusto);

        //Verifica se a cobertura está completa
        coberto = true;
        for(int i=0;i<grafoAux.getTamTabHashVertices();i++){
            for(auto it = grafoAux.getVertices()[i].begin(); it != grafoAux.getVertices()[i].end(); it++) {
                if (it->getGrau() > 0) {
                    coberto = false;
                    rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                    break;
                }
            }
        }
    }

    if(imprime) {
        for (int i = 0; i < verticesUtilizados.size(); i++) {
            msg += to_string(verticesUtilizados[i]);
            if (i < verticesUtilizados.size() - 1) {
                msg += ", ";
            }
        }
        msg += "\n\n";
        cout << msg << endl;

        if(imprimirEmArquivo){
            imprimeMensagem(msg);
        }
    }

    return verticesUtilizados.size();
}


void fechamentoTransitivoDireto() {

    long idVertice;
    int op;
    string msg;

    do {
        cout << "Informe o id do Vértice que deseja visitar: ";
        cin >> idVertice;

        if (!grafo.isVerticePresente(idVertice)) {
            cout << "Vertice inválido!\n " << endl;
        } else {
            msg = "Fechamento Transitivo Direto do Vértice " + to_string(idVertice) + " -> ";
            msg += grafo.fechoTransitivo(idVertice);
            cout << msg << endl;

            if(imprimirEmArquivo){
                imprimeMensagem(msg);
            }
        }
        cout << "\n0-Sair\t 1-Verificar Novamente" << endl;
        cin >> op;
    } while (op == 1);
}

void verificaFechoIntransitivo() {
    long idVertice;
    int op;
    Grafo auxGrafo = copiarGrafoArcosInvertidos(grafo);

    string msg;

    do {
        cout << "Informe o id do Vértice que deseja visitar: ";
        cin >> idVertice;

        if (!auxGrafo.isVerticePresente(idVertice)) {
            cout << "Vertice inválido!\n " << endl;
        } else {
            msg = "Fechamento Transitivo Indireto do Vértice " + to_string(idVertice) + " -> ";
            msg += auxGrafo.fechoTransitivo(idVertice);
            cout << msg << endl;

            if(imprimirEmArquivo){
                imprimeMensagem(msg);
            }
        }
        cout << "\n0-Sair\t 1-Verificar Novamente" << endl;
        cin >> op;
    } while (op == 1);
}

void removeVertice() {
    long idVertice;
    cout << "Qual vértice remover? ";
    cin >> idVertice;
    if(grafo.removeVertice(idVertice)){
        cout << "Vértice removido com sucesso.\n" <<endl;
    }
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

/**
 * Verifica se uma aresta é ponte
 * @return valor lógico
 */
bool isArestaPonte() {
    string msg;
    int op;
    long idVertice1, idVertice2, numCompConexasInicio, numCompConexasFim;
    do {
        cout << "Informe o id das duas extremidades da aresta: ";
        cin >> idVertice1 >> idVertice2;
        msg = "A aresta (" + to_string(idVertice1) + "," + to_string(idVertice2) + ") ";
        cout << "Verificando..." << endl;
        numCompConexasInicio = grafo.numComponentesConexas();
        //cria grafo auxiliar e remove a aresta dele para fazer a verificação
        Grafo auxGrafo = copiarGrafo(grafo);
        auxGrafo.removeVerticeAdjacente(idVertice1, idVertice2);
        numCompConexasFim = auxGrafo.numComponentesConexas();

        cout << "Ok" << endl;
        msg += (numCompConexasInicio < numCompConexasFim ? "é ponte." : "não é ponte.");

        cout << msg << endl;

        if (imprimirEmArquivo) {
            imprimeMensagem(msg);
        }
        cout << "0-Sair\t 1-Verificar Novamente" << endl;
        cin >> op;

    }while(op==1);
}


/*
 * Verifica se um vértice é de articulação
 * @return valor lógico

bool isVerticeArticulacao() {
    string msg;
    long idVertice, numCompConexasInicio, numCompConexasFim;
    int op;
    //do {
        cout << "Informe o id do vértice que deseja testar: ";
        cin >> idVertice;
        msg = "O vértice " + to_string(idVertice) + " ";
        cout << "Verificando..." << endl;
        numCompConexasInicio = grafo.numComponentesConexas(); //Verifica o num de componentes conexas inicialmente

        //Cria grafo auxiliar e remove o vértice dele para fazer a verificação
        Grafo aux = grafo;
        aux.removeVertice(idVertice);
        numCompConexasFim = aux.numComponentesConexas();

        cout << "Ok" << endl;
        msg += (numCompConexasInicio < numCompConexasFim ? "é de articulação." : "não é de articulação.");

        cout << msg << endl;

        if (imprimirEmArquivo) {
            imprimeMensagem(msg);
        }

      //  cout << "0-Sair\t 1-Verificar Novamente" << endl;
        //cin >> op;

    //}while(op == 1);

}
*/

bool isVerticeArticulacao() {
    string msg;
    long idVertice, numCompConexasInicio, numCompConexasFim;
    int op;
    do {
    cout << "Informe o id do vértice que deseja testar: ";
    cin >> idVertice;
    msg = "O vértice " + to_string(idVertice) + " ";
    cout << "Verificando..." << endl;
    numCompConexasInicio = grafo.numComponentesConexas(); //Verifica o num de componentes conexas inicialmente

    //cria grafo auxiliar pra realizar operações
    Grafo auxGrafo = copiarGrafo(grafo);
    auxGrafo.removeVertice(idVertice);

    //verifica o num de componentes conexas depois de remover o vértice
    numCompConexasFim = auxGrafo.numComponentesConexas();

    cout << "Ok" << endl;
    msg += (numCompConexasInicio < numCompConexasFim ? "é de articulação." : "não é de articulação.");

    cout << msg << endl;

    if (imprimirEmArquivo) {
        imprimeMensagem(msg);
    }

    cout << "0-Sair\t 1-Verificar Novamente" << endl;
    cin >> op;

    }while(op == 1);

}

void criarGrafo(long _ordemGrafo, long _numArestas) {
    Grafo grafoAux(_ordemGrafo,_numArestas);   //cria grafo auxiliar

    grafo = grafoAux;

    long i = 1; //Caso onde instancia nao possui id=0
    int op;

    while (i <= _ordemGrafo) {
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

    string msg;
    int idVertice, op;
    do {
        cout << "Digite o id do Vértice que deseja consultar seu Grau: ";
        cin >> idVertice;
        auto it = grafo.isContainVertice(idVertice);

        if (it == grafo.itUltimaPosicao(idVertice)) {  //it não encontrou o vértice
            cout << "Erro: O grafo não possui vértice com o id informado!\n" << endl;
        } else {
            cout << "Verificando Grau do Vértice " << idVertice << "..." << endl;
            cout << "OK" << endl;
            msg = "gr(" + to_string(idVertice) + "): " + to_string(grafo.getGrauVertice(idVertice)) + "\n";
        }
        cout << msg << endl;

        if(imprimirEmArquivo){
            imprimeMensagem(msg);
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
    string msg;
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
                msg = "Adjacência(" + to_string(idVerticeOrigem) + "," + to_string(idVerticeDestino) + "): SIM\n";
            } else {
                msg = "Adjacência(" + to_string(idVerticeOrigem) + "," + to_string(idVerticeDestino) + "): NÃO\n";
            }
        }
        cout << msg << endl;
        if(imprimirEmArquivo){
            imprimeMensagem(msg);
        }
        cout << "0- Encerrar Função    1-Escolher Outros Vértices" << endl;
        cin >> op;
    } while (op != 0);
}


void listaAdjacentesVertice() {//4- Lista os Adjacentes de um Vértice
    int idVertice, op;
    string msg;
    do {
        cout << "Digite o id do Vértice que deseja consultar seus adjacentes: ";
        cin >> idVertice;

        if (!grafo.isVerticePresente(idVertice)) {
            cout << "Erro: Vértice Inválido!\n" << endl;
        } else {
            msg = "Vértices Adjacentes ao Vértice ";
            cout << "Verificando Vértices Adjacentes ao Vértice " << idVertice << "...\nOK\n" << endl;
            msg += (to_string(idVertice) + ":\n");
            msg += (to_string(idVertice) + " -> " + grafo.getVertice(idVertice)->listarAdjacentes() + "\n");

            cout << msg << endl;

            if(imprimirEmArquivo){
                imprimeMensagem(msg);
            }
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

/**
 * Função que verifica se um grafo é k-regular
 */
void verificaKRegularidade() {
    string msg;
    cout << "Verificando K-Regularidade...\n";
    if (grafo.verificaKRegular(&kRegular)) {
        msg = "Grafo K-Regular? SIM, Grafo " + to_string(kRegular) + "-Regular\n";
    } else {
        msg = "Grafo K-Regular? NÃO\n";
    }
    cout << "Ok" << endl;
    cout << msg << endl;
    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }
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
    string msg;
    cout << "Verificando se Grafo é Completo...";
    msg = (grafo.isCompleto() ? "Grafo Completo: SIM\n" : "Grafo Completo: NÃO\n");
    cout << "\nOk\n" << endl;

    cout << msg << endl;
    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }
}

void verificaConexo() {
    bool conexo;
    string msg;
    cout << "Verificando se Grafo é Conexo..." << endl;
    conexo = grafo.isConexo();
    cout << "OK" << endl;

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
    string msg = "Sequência de Graus do Grafo: <";
    multiset<long, greater<long> > sequencia = grafo.sequenciaGraus();  //ordenação decrescente
    auto setIni = sequencia.begin();
    auto setFim = sequencia.end();

    while(setIni != setFim){
        msg += to_string(*setIni);
        //outputFile << *setIni;
        setIni++;

        if(setIni != setFim){
            msg += ", ";
            //outputFile << ", ";
        }else{
            msg += ">\n";
            //outputFile << ">\n";
        }
    }
    cout << msg << endl;

    if(imprimirEmArquivo){
        imprimeMensagem(msg);
    }
}


/**
 * Cria cópia de um grafo
 * @param _g
 * @return
 */
Grafo copiarGrafo(Grafo _g) {
    Grafo auxG(_g.getOrdemGrafo(),_g.getNumArestas());

    //cria os vértices
    for(int i=0; i<_g.getTamTabHashVertices(); i++){
        for(auto it = _g.getVertices()[i].begin(); it != _g.getVertices()[i].end(); it++){
            auxG.addVertice(it->getIdVertice());
        }
    }

    //cria as arestas
    for(int i=0; i<_g.getTamTabHashVertices(); i++){
        for(auto it = _g.getVertices()[i].begin(); it != _g.getVertices()[i].end(); it++){
            for(int j=0; j<_g.getTamTabHashAdj(); j++){
                for(auto it2 = it->getVerticesAdjacentes()[j].begin(); it2 != it->getVerticesAdjacentes()[j].end(); it2++){
                    auxG.addVerticeAdjacente(it->getIdVertice(),it2->getIdVertice(),0);
                }
            }
        }
    }

    return auxG;
}

/**
 * Cria cópia de um grafo com os arcos invertidos: usado para fecho transitivo indireto
 * @param _g
 * @return
 */
Grafo copiarGrafoArcosInvertidos(Grafo _g) {
    Grafo auxG(_g.getOrdemGrafo(),_g.getNumArestas());

    //cria os vértices
    for(int i=0; i<_g.getTamTabHashVertices(); i++){
        for(auto it = _g.getVertices()[i].begin(); it != _g.getVertices()[i].end(); it++){
            auxG.addVertice(it->getIdVertice());
        }
    }

    //cria as arestas
    for(int i=0; i<_g.getTamTabHashVertices(); i++){
        for(auto it = _g.getVertices()[i].begin(); it != _g.getVertices()[i].end(); it++){
            for(int j=0; j<_g.getTamTabHashAdj(); j++){
                for(auto it2 = it->getVerticesAdjacentes()[j].begin(); it2 != it->getVerticesAdjacentes()[j].end(); it2++){
                    auxG.addVerticeAdjacente(it2->getIdVertice(),it->getIdVertice(),0);
                }
            }
        }
    }

    return auxG;
}
