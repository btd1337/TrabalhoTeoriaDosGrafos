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
    grau = 0;
    peso = 1 + idVertice * 2;
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
    grau++;
}

bool Vertice::removeVerticeAdjacente(long _idVertice) {
    bool isContainVertice = false;

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; ++it) {
        //Percorre a lista de adjacentes e verifica se o rótulo é o procurado
        if(it->getIdVertice() == _idVertice){
            verticesAdjacentes.erase(it);
            grau--;
            isContainVertice = true;
            break;
        }

    }
    if(!isContainVertice){
        return false;
    }
    return true;
}


string Vertice::listarAdjacentes()
{
    string listaDeAdjacentes = "";
    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; ++it) {
        listaDeAdjacentes += to_string(it->getIdVertice());
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

long Vertice::getGrau() const {
    return grau;
}

double Vertice::getPeso() const {
    return peso;
}

void Vertice::setPeso(double peso) {
    Vertice::peso = peso;
}

void Vertice::reduzGrau() {
    grau--;
}
