//
// Created by helder on 27/04/16.
//

#include "Vertice.h"
#include "Adjacente.h"
#include <list>

long Vertice::contVertice = 0;

Vertice::Vertice() {
    idVertice = contVertice;
    contVertice++;
    corVisita = Coloracao::SEMCOR;  //inicia o vértice sem cor
}

Vertice::~Vertice() {
    // TODO Auto-generated destructor stub
}

int Vertice::getIdVertice() {
    return idVertice;
}

void Vertice::setIdVertice(long _idVertice) {
    idVertice = _idVertice;
}

list<Adjacente> Vertice::getVerticesAdjacentes() {
    return verticesAdjacentes;
}

void Vertice::addVerticeAdjacente(long _idVerticeAdjacente, float _pesoAresta) {
    Adjacente verticeAdjacente(_idVerticeAdjacente,_pesoAresta);
    verticesAdjacentes.push_back(verticeAdjacente);
}

void Vertice::removeVerticeAdjacente(long _idVertice) {
    bool isContainVertice = false;

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; ++it) {
        //Percorre a lista de adjacentes e verifica se o rótulo é o procurado
        if(it->getVerticeAdjacente() == _idVertice){
            verticesAdjacentes.erase(it);
            cout << "Vértice removido!" << endl;
            isContainVertice = true;
            break;
        }
    }
    if(!isContainVertice){
        cout << "ERRO: Vértice não encontrado!" << endl;
    }
}


string Vertice::listarAdjacentes()
{
    string listaDeAdjacentes = "";
    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; ++it) {
        listaDeAdjacentes += to_string(it->getVerticeAdjacente());
        listaDeAdjacentes += " ";
    }
    return listaDeAdjacentes;
}

Coloracao Vertice::getVisitado(){
    return corVisita;
}

void Vertice::setCorVisita(Coloracao _corVisita) {
    corVisita = _corVisita;
}

