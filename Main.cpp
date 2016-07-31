#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Adjacente.h"
#include "Grafo.h"
#include "Vertice.h"

using namespace std;

fstream inputFile, outputFile;
long tamanhoGrafo=1, kRegular;
Grafo grafo;	//cria grafo não direcionado


void apresentacaoTrabalho();

void criaCabecalho(long _tamanhoGrafo);

int exibeMenu();

void criarGrafo(long _tamanhoGrafo);

void lerAdjcencias(bool isContainPeso);

void verificaGrauVertice();

void verificaGrauGrafo();

void verificaAdjacenciaVertices();

void listaAdjacentesVertice();

void geraGrafoInduzido();

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

int main(int argc, char** argv)
{
    bool conexo, bipartido;
    long idVertice, idVerticeOrigem, idVerticeDestino;
    int op, opMenu;

    apresentacaoTrabalho();

    //Usado 4 para rodar com o Cmake, atualizar para 3 quando for rodar no terminal
    if(argc == 3){
        inputFile.open(argv[1], ios::in);   //Mudar para 1 quando for rodar no terminal
        outputFile.open(argv[2], ios::out); //Mudar para 2 quando for rodar no terminal
        //Verificar se arquivo de entrada foi aberto
        if(!inputFile){
            cerr << "ERRO: Arquivo " << argv[2] << " não foi encontrado!" << endl; //voltar para 1 quando executar no terminal
            return -1;
        }
        //Verificar se arquivo de saída foi criado
        if(!outputFile){
            cerr << "ERRO: Arquivo " << argv[3] << " não pode ser criado!" << endl; //voltar para 2 quando executar no terminal
            return -1;
        }
    }
    else{
        cerr << "ERRO: Informar os arquivos de entrada ou saída na execução do algoritmo" << endl;
        return 0;
    }

    cout << "Lendo o Tamanho do Grafo...\nOK\n" << endl;
    //Faz leitura do tamanho do Grafo
    char cTamanhoGrafo[15];
    inputFile.getline(cTamanhoGrafo, 80);

    //Converte char para string e depois string para long
    string sTamanhoGrafo = string(cTamanhoGrafo);
    tamanhoGrafo = stol(sTamanhoGrafo); //voltar para sTamanhoGrafo

    cout << "Criando Grafo...\nOK\n" << endl;
    criarGrafo(tamanhoGrafo);

    cout << "Gerando Adjacências do Grafo...\nOK\n" << endl;
    lerAdjcencias(true);

    criaCabecalho(tamanhoGrafo);

    do{
        opMenu = exibeMenu();
        if(opMenu!=0) {
            chamaFuncaoEscolhida(opMenu);
        }
    }while(opMenu!=0);



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
    cout << "#############################################" << endl;
    cout << "\nObs: Os dados serão gerados automaticamente para o arquivo de saída informado por parâmetro.\n" << endl;

    cout << "Digite 1 + <Enter> para iniciar o algoritmo...";
    cin >> trash;
    cout << "\n\n";
}

void criaCabecalho(long _tamanhoGrafo){
    outputFile << "Trabalho 1 de Grafos" << endl;
    outputFile << "Autor: Helder Linhares Bertoldo dos Reis" << endl;
    outputFile << "Matrícula: 201465555A\n\n" << endl;

    outputFile << "Análise do Grafo" << endl;
    outputFile << "Número de Vértices: " << _tamanhoGrafo << endl;
}

int exibeMenu(){
    int opMenu;

    cout << " 1- Verificar o Grau de um vértice" << endl;
    cout << " 2- Verificar o Grau de G" << endl;
    cout << " 3- Verificar adjacência entre vértices" << endl;
    cout << " 4- Listar os adjacentes de um vértice" << endl;
    cout << " 5- Dado um conjunto x de vértices, retornar o grafo induzido por x" << endl;
    cout << " 6- Verificar se o Grafo é K-Regular" << endl;
    cout << " 7- Retornar o Grafo Complementar G" << endl;
    cout << " 8- Verificar se o Grafo é Completo" << endl;
    cout << " 9- Verificar se o Grafo é Bipartido" << endl;
    cout << "10- Verificar se o Grafo é conexo" << endl;
    cout << "11- Verificar se um dado Vértice é de Articulação" << endl;
    cout << "12- Verificar se uma dada Aresta é Ponte" << endl;
    cout << "13- Remover Vértice" << endl;
    cout << "14- Remover Aresta" << endl;
    cout << "15- Fecho Transitivo" << endl;
    cout << "16- Fecho Intransitivo" << endl;
    cout << "17- Cobertura de Vértices Guloso" << endl;
    cout << "18- Cobertura de Vértices Guloso Randomizado" << endl;
    cout << "19- Cobertura de Vértices Guloso Randomizado Reativo" << endl;
    cout << " 0- Sair" << endl;
    cout << "\nOpção: ";
    cin >> opMenu;
    return opMenu;
}

void chamaFuncaoEscolhida(int opMenu){
    switch(opMenu){
        case 0: {
            cout << "Algoritmo Encerrado. Os dados foram armazenados em arquivo." << endl;
            break;
        }
        case 1: {
            verificaGrauVertice();
            break;
        }
        case 2: {
            verificaGrauGrafo();
            break;
        }
        case 3: {
            verificaAdjacenciaVertices();
            break;
        }
        case 4: {
            listaAdjacentesVertice();
            break;
        }
        case 5: {
            geraGrafoInduzido();
            break;
        }
        case 6: {
            verificaKRegularidade();
            break;
        }
        case 7: {
            geraGrafoComplemetar();
            break;
        }
        case 8: {
            verificaGrafoCompleto();
            break;
        }
        case 9:{
            verificaBipartido();
            break;
        }
        case 10:{
            verificaConexo();
            break;
        }
        case 11:{
            isVerticeArticulacao();
            break;
        }
        case 12:{
            isArestaPonte();
            break;
        }
        case 13:{
            removeVertice();
            break;
        }
        case 14:{
            removeAresta();
            break;
        }
        case 15:{
            verificaFechoTransitivo();
            break;
        }
        case 16:{
            verificaFechoIntransitivo();
            break;
        }
        case 17:{
            coberturaDeVerticesGuloso();
            break;
        }
        case 18:{
            //coberturaDeVerticesGulosoRandomizado();
            break;
        }
        case 19:{
            //coberturaDeVerticesGulosoRandomizadoReativo();
            break;
        }
        default:{
            cout << "ERRO: Opção Inválida!" << endl;
        }
    }
}

void coberturaDeVerticesGuloso() {
    vector<long> verticesUtilizados;
    Grafo grafoAux;
    grafoAux = grafo;
    multiset< pair<double,int>> rankeamentoDeVertices;
    pair<double,int> infoRankeamento; //pesoParaRankeamento, idVertice
    double pesoParaRankeamento;
    bool coberto = false;   //setar para true quando todas as arestas forem cobertas
    long idVerticeMenorCusto;

    while(!coberto){
        for(int i=0; i<grafoAux.getNumVertices();i++){
            if(grafoAux.getVertice(i)->getGrau()!=0) {
                pesoParaRankeamento = grafoAux.getVertice(i)->getPeso() / (grafoAux.getVertice(i)->getGrau() * 1.0);
                infoRankeamento = make_pair(pesoParaRankeamento, grafoAux.getVertice(i)->getIdVertice());
                rankeamentoDeVertices.insert(infoRankeamento);
            }else{
                //Evita q peso 0 seja escolhido
                pesoParaRankeamento = 999999;
                infoRankeamento = make_pair(pesoParaRankeamento,grafo.getVertice(i)->getIdVertice());
            }
        }
        idVerticeMenorCusto = rankeamentoDeVertices.begin()->second;

        verticesUtilizados.push_back(idVerticeMenorCusto);    //utiliza vértice de menor custo

        //Remove as arestas que o vértice cobre
        for(auto adj : grafoAux.getVertice(idVerticeMenorCusto)->getVerticesAdjacentes()){
            long teste = adj.getIdVertice();
            grafoAux.removeAresta(idVerticeMenorCusto,adj.getIdVertice());
        }

        //Verifica se a cobertura está completa
        coberto = true;
        for(int i=0;i<grafoAux.getNumVertices();i++){
            if(grafoAux.getVertice(i)->getGrau()>0){
                coberto = false;
                rankeamentoDeVertices.clear();  //limpa o vetor de rankeamento
                break;
            }
        }
    }

    outputFile << "\nCobertura Mínima: " << verticesUtilizados.size() << " vértice(s)" << endl;
    for(int i=0; i<verticesUtilizados.size();i++){
        outputFile << verticesUtilizados[i];
        if(i<verticesUtilizados.size()-1){
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

        if (idVertice < 0 || idVertice >= tamanhoGrafo) {
            cout << "Vertice inválido!\n " << endl;
        }
        else{
            sFechoTransitivo = grafo.fechoTransitivo(idVertice);

            outputFile << "Fecho Transitivo do Vértice " << idVertice << " -> " ;
            outputFile << sFechoTransitivo << endl;
        }
    }while (idVertice < 0 || idVertice >= tamanhoGrafo);
}

void verificaFechoIntransitivo() {
    long idVertice;
    string sFechoIntransitivo;

    do {
        cout << "Informe o id do Vértice que deseja visitar: ";
        cin >> idVertice;

        if (idVertice < 0 || idVertice >= tamanhoGrafo) {
            cout << "Vertice inválido!\n " << endl;
        }
        else{
            sFechoIntransitivo = grafo.fechoIntransitivo(idVertice);

            outputFile << "Fecho Intransitivo do Vértice " << idVertice << " -> " ;
            outputFile << sFechoIntransitivo << endl;
        }
    }while (idVertice < 0 || idVertice >= tamanhoGrafo);
}

void removeVertice() {
    long idVertice;
    cout << "Qual vértice remover? ";
    cin >> idVertice;
    grafo.removeVertice(idVertice);
}

void removeAresta() {
    long idOrigem, idDestino;
    cout << "Informe o Vértice de Origem: ";
    cin >> idOrigem;
    cout << "\nInforme o Vértice de Destino: ";
    cin >> idDestino;
    grafo.removeAresta(idOrigem,idDestino);
}

bool isArestaPonte() {

}

bool isVerticeArticulacao() {

}

void criarGrafo(long _tamanhoGrafo){
    long i=1;
    int op;

    //O primeiro vértice é criado automaticamente
    grafo.getVertice(0)->setIdVertice(0);


    while(i < _tamanhoGrafo) {
        grafo.addVertice(i);
        i++;
    }

    //Verifica se o grafo é direcionado
    do{
        cout << "O Grafo é direcionado? " << endl;
        cout << "0-Não\t 1-Sim" << endl;
        cin >> op;
        if(op<0 || op>1){
            cout << "ERRO: Opção Inválida!" << endl;
        }else{
            op == 0 ? grafo.setIsGrafoDirecionado(false): grafo.setIsGrafoDirecionado(true);
        }

    }while(op<0 || op>1);
}

void lerAdjcencias(bool isContainPeso){
    char cVerticeOrigem[15], cVerticeDestino[15];
    string sVerticeOrigem, sVerticeDestino;
    long verticeOrigem, verticeDestino;

    if(!isContainPeso){
        while(inputFile >> cVerticeOrigem >> cVerticeDestino){

            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);

            grafo.addVerticeAdjacente(verticeOrigem, verticeDestino, 0.0);
        }
    }
    else{
        char cPesoAresta[15];
        string sPesoAresta;
        float pesoAresta;
        while(inputFile >> cVerticeOrigem >> cVerticeDestino >> cPesoAresta){
            //Faz conversões
            sVerticeOrigem = string(cVerticeOrigem);
            sVerticeDestino = string(cVerticeDestino);
            sPesoAresta = string(cPesoAresta);
            verticeOrigem = stol(sVerticeOrigem);
            verticeDestino = stol(sVerticeDestino);
            pesoAresta = stof(sPesoAresta);

            grafo.addVerticeAdjacente(verticeOrigem,verticeDestino,pesoAresta);
        }
    }
}

void verificaGrauVertice(){
    int idVertice, op;
    do {
        cout << "Digite o id do Vértice que deseja consultar seu Grau: ";
        cin >> idVertice;
        if(idVertice<0 || idVertice>=tamanhoGrafo){
            cout << "Erro: Vértice Inválido!\n" << endl;
        }else{
            cout << "Verificando Grau do Vértice " << idVertice << "...\nOK\n" << endl;
            outputFile << "gr(" << idVertice << "): " << grafo.verificaGrauVertice(idVertice) << endl;
        }
        cout << "0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    }while(op!=0);
}

void verificaGrauGrafo() {
    outputFile << "gr(G): " << grafo.verificaGrauGrafo() << endl;
    cout << "Verificando Grau do Grafo...\nOK\n" << endl;
}

void verificaAdjacenciaVertices() {
    int idVerticeOrigem, idVerticeDestino,op;
    do{
        cout << "Digite o id do Vértice de Origem e do Vértice de Destino que deseja verificar adjacência: ";
        cin >> idVerticeOrigem >> idVerticeDestino;
        if(idVerticeOrigem < 0 || idVerticeDestino >= tamanhoGrafo){
            cout << "ERRO: Vértice de Origem Inválido!" << endl;
        }
        else if(idVerticeDestino < 0 || idVerticeDestino >= tamanhoGrafo){
            cout << "ERRO: Vértice de Destino Inválido!" << endl;
        }
        else{
            cout << "Verificando Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << ")...\nOK\n" << endl;
            if(grafo.verificaAdjacencia(idVerticeOrigem,idVerticeDestino)){
                outputFile << "Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << "): SIM" << endl;
            }
            else{
                outputFile << "Adjacência(" << idVerticeOrigem << "," << idVerticeDestino << "): NÃO" << endl;
            }
        }
        cout << "0- Encerrar Função    1-Escolher Outros Vértices" << endl;
        cin >> op;
    }while(op != 0);
}


void listaAdjacentesVertice() {//4- Lista os Adjacentes de um Vértice
    int idVertice, op;
    do{
        cout << "Digite o id do Vértice que deseja consultar seus adjacentes: ";
        cin >> idVertice;
        if(idVertice<0 || idVertice>=tamanhoGrafo){
            cout << "Erro: Vértice Inválido!\n" << endl;
        }else {
            cout << "Verificando Vértices Adjacentes ao Vértice " << idVertice<< "...\nOK\n" << endl;
            outputFile << "Vértices Adjacentes ao Vértice " << idVertice << ":\n";
            outputFile << idVertice << " -> " << grafo.getVertice(idVertice)->listarAdjacentes() << endl;
        }
        cout << "0- Encerrar Função    1-Escolher Outro Vértice" << endl;
        cin >> op;
    }while(op != 0);
}

void geraGrafoInduzido(){
    long numVertices, idVertice;
    int i;
    list<Adjacente> verticesAdjacentes;

    cout << "Gerar Grafo Induzido" << endl;
    cout << "Informe a quantidade de vértices do Grafo Induzido: ";
    cin >> numVertices;

    vector<long> verticesGrafoInduzido(numVertices);

    cout << "Informe os vértices(Um a Um):" << endl;
    for(i=0; i<numVertices; i++){
        cout << "v[" << i << "]:";
        cin >> idVertice;

        //verifica vertices informados
        if(idVertice<0 || idVertice>=tamanhoGrafo){
            cout << "Erro: Vértice Inválido!\n" << endl;
            i--;    //não atualiza contagem
        }else{
            verticesGrafoInduzido[i] = idVertice;
        }
    }

    //Ordena o Vetor
    sort(verticesGrafoInduzido.begin(),verticesGrafoInduzido.end());

    cout << "Gerando Grafo Induzido...\n";

    outputFile << "\nGrafo Induzido do conjunto de Vértices(";
    for(int i=0; i<numVertices; i++){
        outputFile << verticesGrafoInduzido[i];
        //não mostrar vírgula pro último elemento
        if(i!=numVertices-1){
            outputFile << ", ";
        }
    }
    outputFile << ")\n";

    //Para cada vértice informado, percorre o seu conjunto de adjacências em busca dos vértices adjacentes que foram informados
    for(i=0; i<numVertices; i++){

        outputFile << verticesGrafoInduzido[i] << " -> ";
        verticesAdjacentes = grafo.getVertice(verticesGrafoInduzido[i])->getVerticesAdjacentes();

        //verifica os não adjacentes
        for(list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++){

            for(int j=0; j<numVertices; j++) {
                if (it->getIdVertice() == verticesGrafoInduzido[j])
                    outputFile << verticesGrafoInduzido[j] << " ";
            }
        }

        outputFile << endl;
    }
    cout << "Ok\n" << endl;
}

void verificaKRegularidade() {//6- Verifica se Grafo é K-Regular
    if(grafo.verificaKRegular(&kRegular)){
        outputFile << "K-Regular: SIM - Grafo " << kRegular << "-Regular" << endl;
    }
    else{
        outputFile << "K-Regular: NÃO" << endl;
    }
}

void geraGrafoComplemetar() {//7 - Retorna o Grafo Complementar
    cout << "Gerando Grafo Complementar...\nOK\n" << endl;

    Grafo grafoComplementar;
    vector<bool> idVerticesAdjacentes(tamanhoGrafo);
    list<Adjacente> verticesAdjacentes;
    long pos;

    outputFile << "\n\nGrafo Complementar:" << endl;

    long tamanhoGrafoAux = tamanhoGrafo;
    //Zera vetor
    for(int k=0; k < tamanhoGrafo; k++){
        idVerticesAdjacentes[k] = false;
    }

    //Cria Grafo
    while(--tamanhoGrafoAux>=0) {
        grafoComplementar.addVertice(0);
    }
    grafoComplementar.setIsGrafoDirecionado(false);	//informa se o grafo é direcionado


    for(long i=0; i<tamanhoGrafo; i++){

        //obtem os adjacentes do vértice
        verticesAdjacentes = grafo.getVertice(i)->getVerticesAdjacentes();

        //Marca todos adjacentes como true no vetor auxiliar
        for(list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end(); ++it){
            pos = it->getIdVertice();
            idVerticesAdjacentes[pos] = true;
        }

        //escreve no arquivo os vértices que não são adjacentes
        outputFile << i << " -> ";
        for(long j=0; j<tamanhoGrafo; j++){
            if(i!=j && idVerticesAdjacentes[j] == false){
                outputFile << j << " ";
            }
        }
        outputFile << "\n" << endl;

        //Zera vetor
        for(int k=0; k < tamanhoGrafo; k++){
            idVerticesAdjacentes[k] = false;
        }
    }
}

void verificaGrafoCompleto() {//8- Verifica se G é completo
    cout << "Verificando se Grafo é Completo...\nOK\n" << endl;
    outputFile << (grafo.isCompleto() ? "Grafo Completo: SIM" : "Grafo Completo: NÃO") << endl;
}

void verificaConexo() {
    bool conexo;
    cout << "Verificando se Grafo é Conexo...\nOK\n" << endl;
    conexo = grafo.isConexo();
    outputFile << (conexo ? "Grafo Conexo: SIM" : "Grafo Conexo: NÃO") << endl;

}

void verificaBipartido() {

    cout << "Verificando se Grafo é Bipartido...";
    outputFile << (grafo.isGrafoBipartido() ? "Grafo Bipartido: SIM" : "Grafo Bipartido: NÃO") << endl;

    cout << "\nOK\n\n" << endl;
}
