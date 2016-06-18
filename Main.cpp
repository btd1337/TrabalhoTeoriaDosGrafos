#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "Adjacente.h"
#include "Grafo.h"
#include "Vertice.h"

using namespace std;

fstream inputFile, outputFile;
long tamanhoGrafo=1;
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

int main(int argc, char** argv)
{
    bool conexo, bipartido;
    long idVertice, idVerticeOrigem, idVerticeDestino, kRegular;
    int op, opMenu;

    apresentacaoTrabalho();

    //Usado 4 para rodar com o Cmake, atualizar para 3 quando for rodar no terminal
    if(argc == 4){
        cout << argc << endl;
        inputFile.open(argv[2], ios::in);   //Mudar para 1 quando for rodar no terminal
        outputFile.open(argv[3], ios::out); //Mudar para 2 quando for rodar no terminal
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
        chamaFuncaoEscolhida(opMenu);
    }while(opMenu!=0);



    cout << "\nOs dados de análise foram salvos no arquivo de saída" << endl;


    //Fecha IO
    outputFile.close();
    inputFile.close();

    return 0;
}


void apresentacaoTrabalho() {
    char trash;
    cout << "Trabalho 1 de Teoria dos Grafos\n" << endl;
    cout << "Obs: Os dados serão gerados automaticamente para o arquivo de saída informado por parâmetro.\n" << endl;

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
    cout << " 4- Listar os adjacentes de um nó" << endl;
    cout << " 5- Dado um conjunto x de vértices, retornar o grafo induzido por x" << endl;
    cout << " 6- Verificar se o Grafo é K-Regular" << endl;
    cout << " 7- Retornar o Grafo Complementar G" << endl;
    cout << " 8- Verificar se o Grafo é Completo" << endl;
    cout << " 9- Verificar se o Grafo é Bipartido" << endl;
    cout << "10- Verificar se o Grafo é conexo" << endl;
    cout << "11- Verificar se um dado Vértice é de Articulação" << endl;
    cout << "12- Verificar se uma dada Aresta é Ponte" << endl;
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
            verificaConexo();
            break;
        }
        case 10:{
            verificaBipartido();
            break;
        }
    }
}

void criarGrafo(long _tamanhoGrafo){
    while(--_tamanhoGrafo>0)
        grafo.addVertice();

    grafo.setIsGrafoDirecionado(false);	//informa se o grafo é direcionado
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

            //acrescenta 1 para os vértices iniciados por 0
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
                if (it->getVerticeAdjacente() == verticesGrafoInduzido[j])
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
        grafoComplementar.addVertice();
    }
    grafoComplementar.setIsGrafoDirecionado(false);	//informa se o grafo é direcionado


    for(long i=0; i<tamanhoGrafo; i++){

        //obtem os adjacentes do vértice
        verticesAdjacentes = grafo.getVertice(i)->getVerticesAdjacentes();

        //Marca todos adjacentes como true no vetor auxiliar
        for(list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end(); ++it){
            pos = it->getVerticeAdjacente();
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
    outputFile << (grafo.isBipartido() ? "Grafo Bipartido: SIM" : "Grafo Bipartido: NÃO") << endl;

    cout << "\nOK\n\n" << endl;
}
