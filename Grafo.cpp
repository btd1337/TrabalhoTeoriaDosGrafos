//
// Created by helder on 27/04/16.
//

#include "Grafo.h"
#include "Vertice.h"
#include "Coloracao.h"

using namespace std;

Grafo::Grafo() {
    Vertice vertice;
    vertices.push_back(vertice);
    isGrafoDirecionado = false;
}

Grafo::~Grafo() {

}

void Grafo::setIsGrafoDirecionado(bool _isDirecionado){
    isGrafoDirecionado = _isDirecionado;
}

void Grafo::imprimeVertices()
{
    for(unsigned int i=0; i< vertices.size(); i++){
        cout << vertices[i].getIdVertice() << endl;
    }
}

Vertice* Grafo::getVertice(int idVertice)
{
    return &vertices[idVertice];
}

void Grafo::addVertice()
{
    Vertice vertice;
    vertices.push_back(vertice);
}


void Grafo::addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta)
{
    //verifica existência dos vértices
    if(_verticeOrigem<0 || _verticeOrigem>vertices.size()){
        cout << "Vértice de Origem " << _verticeOrigem << " é inválido!" << endl;
    }
    else if(_verticeDestino<0 || _verticeDestino>vertices.size()){
        cout << "Vértice de Destino " << _verticeDestino << " é inválido!" << endl;
    }
    else{
        vertices[_verticeOrigem].addVerticeAdjacente(_verticeDestino,_pesoAresta);

        if(!isGrafoDirecionado){
            vertices[_verticeDestino].addVerticeAdjacente(_verticeOrigem,_pesoAresta);
        }
    }
}

void Grafo::auxIsConexo(int _vertice){
    //Seta vértice atual como visitado
    getVertice(_vertice)->setCorVisita(Coloracao::AZUL);

    list<Adjacente> verticesAdjacentes = getVertice(_vertice)->getVerticesAdjacentes();

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++) {
        //verifica se o vértice ainda não foi corVisita
        if(getVertice(it->getIdVertice())->getVisitado() == Coloracao::SEMCOR);
            auxIsConexo(it->getIdVertice());
    }

}

bool Grafo::isConexo(){

    //seta os vértices como não visitados
    for(int i=0; i< vertices.size(); i++){
        getVertice(i)->setCorVisita(Coloracao::SEMCOR);
    }
    auxIsConexo(0);

    for(int i=0; i< vertices.size(); i++){
        if(getVertice(i)->getVisitado() == Coloracao::SEMCOR){
            return false;
        }

    }

    return true;
}


bool Grafo::isVerticesVisitados() {

    for(int i=0; i<vertices.size(); i++){
        if(vertices[i].getVisitado() == Coloracao::SEMCOR){
            return false;
        }
    }
    return true;
}


bool Grafo::auxIsBipartido(int _vertice, int _numPasso){
    if(vertices[_vertice].getVisitado() == Coloracao::SEMCOR){
        //atribui cor
        _numPasso%2==0? vertices[_vertice].setCorVisita(Coloracao::AZUL) : vertices[_vertice].setCorVisita(Coloracao::VERDE);
        //chama o método para os adjacentes deste vértice
        for(list<Adjacente>::iterator it = vertices[_vertice].getVerticesAdjacentes().begin(); it != vertices[_vertice].getVerticesAdjacentes().end(); it++){
            auxIsBipartido(it->getIdVertice(), _numPasso++);
        }
    }
    else{
        Coloracao corCorreta;
        //Verifica qual a cor correta atual
        _numPasso%2==0? (corCorreta = Coloracao::AZUL) : (corCorreta = Coloracao::VERDE);
        if(vertices[_vertice].getVisitado() != corCorreta){
            isBipartido = false;
        }
    }

    return true;
}

bool Grafo::isGrafoBipartido(){
    vector<bool> verticesVisitados;
    int passo=0;
    int j=0;
    isBipartido = true; //seta o grafo como bipartido, caso provado que não seja, a variável é setada com false

    //cria um vetor auxiliar e determina que todos não foram visitados.
    for(int i=0; i < vertices.size(); i++){
        verticesVisitados.push_back(false);
        vertices[i].setCorVisita(Coloracao::SEMCOR);    //marca vértice como não visitado
    }

    while(!isVerticesVisitados()){
        auxIsBipartido(vertices[j].getIdVertice(),passo);
    }
    return true;
}

long Grafo::verificaGrauVertice(long _idVertice){
    return getVertice(_idVertice)->getVerticesAdjacentes().size();
}

long Grafo::verificaGrauGrafo(){
    long grauMax=verificaGrauVertice(0);
    long grauVerticeAtual;
    for(int i=1; i<vertices.size(); i++){
        grauVerticeAtual = verificaGrauVertice(i);
        if(grauVerticeAtual > grauMax)
            grauMax = grauVerticeAtual;
    }
    return grauMax;
}

bool Grafo::verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino){
    list<Adjacente> verticesAdjacentes = getVertice(_idVerticeOrigem)->getVerticesAdjacentes();

    for(list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++){
        if(it->getIdVertice() == _idVerticeDestino)
            return true;
    }
    return false;
}

bool Grafo::verificaKRegular(long *kRegular){
    *kRegular = getVertice(0)->getVerticesAdjacentes().size();

    for(int i=1; i < vertices.size(); i++){
        if(getVertice(i)->getVerticesAdjacentes().size() != *kRegular)
            return false;
    }
    return true;
}

bool Grafo::isCompleto(){
    for(int i=0; i < vertices.size(); i++){
        if(getVertice(i)->getVerticesAdjacentes().size() != vertices.size() - 1);
        return false;
    }
    return true;
}


void Grafo::atualizaNumeracaoAdjacentes(int _idVertice, int _idVerticeRemovido){
    //Percorre adjacentes do vértice
    for (list<Adjacente>::iterator it = vertices[_idVertice].getVerticesAdjacentes().begin(); it != vertices[_idVertice].getVerticesAdjacentes().end() ; it++) {
        //verifica se id de algum adjacente está acima do valor do vértice removido
        if(it->getIdVertice() >= _idVerticeRemovido)
            it->updateIdVertice();
    }
}

bool Grafo::removeVertice(int _idVertice) {
    int idVerticeRemovido = _idVertice;
    if(_idVertice<1 || _idVertice>vertices.size()){
        cout << "Vértice inválido!" << endl;
        return false;
    }
    for(int i=0; i< vertices[_idVertice].getVerticesAdjacentes().size();i++){

        //Percorre adjacentes do vértice
        for (list<Adjacente>::iterator it = vertices[_idVertice].getVerticesAdjacentes().begin(); it != vertices[_idVertice].getVerticesAdjacentes().end() ; it++) {
            removeAresta(_idVertice, it->getIdVertice());
        }

        //Atualiza ids dos vértices
        for(int i=0; i<vertices.size();i++){
            atualizaNumeracaoAdjacentes(i, idVerticeRemovido);

            //caso o vértice atual esteja acima do vértice removido atualiza a numeração dele.
            if(i>_idVertice){
                vertices[i].setIdVertice(i-1);
            }
        }

    }
    return true;
}

bool Grafo::removeAresta(int _idVerticeOrigem, int _idVerticeDestino) {
    _idVerticeOrigem++; //corrige o id
    _idVerticeDestino++;    //corrige o id

    //verifica se os vértices são válidos
    if(_idVerticeOrigem<1 || _idVerticeDestino<1 || _idVerticeOrigem>vertices.size() || _idVerticeDestino>vertices.size()){
        cout << "O id dos vértices deve estar entre 1 e " << vertices.size() << endl;
        return false;
    }


    if(isGrafoDirecionado){
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
    }
    else{
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
        getVertice(_idVerticeDestino)->removeVerticeAdjacente(_idVerticeOrigem);
    }
    return true;
}


