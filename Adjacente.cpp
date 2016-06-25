//
// Created by helder on 27/04/16.
//

#include "Adjacente.h"

using namespace std;

Adjacente::Adjacente(long _idVerticeAdjacente) {
    pesoAresta = 0.0;
    idVertice = _idVerticeAdjacente;
}

Adjacente::Adjacente(long _idVerticeAdjacente, float _pesoAresta) {
    pesoAresta = _pesoAresta;
    idVertice = _idVerticeAdjacente;
}

long Adjacente::getIdVertice() {
    //passa pro vértice auxiliar o endereço do vértice adjacente
    return idVertice;
}

float Adjacente::getPesoDaAresta() {
    return pesoAresta;
}

void Adjacente::setPesoDaAresta(float _pesoAresta) {
    pesoAresta = _pesoAresta;
}

//usado quando um vértice é removido
void Adjacente::updateIdVertice() {
    idVertice--;
}


Adjacente::~Adjacente() {
    // TODO Auto-generated destructor stub
}
