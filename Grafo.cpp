//
// Created by helder on 27/04/16.
//

#include "Grafo.h"
#include "Vertice.h"


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
    getVertice(_vertice)->setVisitado(1);

    list<Adjacente> verticesAdjacentes = getVertice(_vertice)->getVerticesAdjacentes();

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++) {
        //verifica se o vértice ainda não foi visitado
        if(getVertice(it->getVerticeAdjacente())->getVisitado() == 0)
            auxIsConexo(it->getVerticeAdjacente());
    }

}

bool Grafo::isConexo(){

    //seta os vértices como não visitados
    for(int i=0; i< vertices.size(); i++){
        getVertice(i)->setVisitado(0);
    }
    auxIsConexo(0);

    for(int i=0; i< vertices.size(); i++){
        if(getVertice(0)->getVisitado() == 0){
            return false;
        }

    }

    return true;
}

bool Grafo::auxIsBipartido(int _vertice, int _numPasso, bool isOk){
    getVertice(_vertice)->setVisitado(_numPasso%2);
    _numPasso++;    //próximo passo
    list<Adjacente> verticesAdjacentes = getVertice(_vertice)->getVerticesAdjacentes();

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++) {
        //verifica se o vértice ainda não foi visitado
        if(getVertice(it->getVerticeAdjacente())->getVisitado() == -1)
            auxIsConexo(it->getVerticeAdjacente());
        if(getVertice(it->getVerticeAdjacente())->getVisitado() != _numPasso%2)
            return false;
    }
    return true;
}

bool Grafo::isBipartido(){
    //seta os vértices como não visitados
    for(int i=0; i< vertices.size(); i++){
        getVertice(i)->setVisitado(-1);
    }

    if(!auxIsBipartido(0,1,true)){
        return false;
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
        if(it->getVerticeAdjacente() == _idVerticeDestino)
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


