//
// Created by helder on 27/04/16.
//

#include "Adjacente.h"

using namespace std;

Adjacente::Adjacente(long _idVerticeAdjacente) {
    pesoAresta = 0.0;
    idVerticeAdjacente = _idVerticeAdjacente;
}

Adjacente::Adjacente(long _idVerticeAdjacente, float _pesoAresta) {
    pesoAresta = _pesoAresta;
    idVerticeAdjacente = _idVerticeAdjacente;
}

long Adjacente::getVerticeAdjacente() {
    //passa pro vértice auxiliar o endereço do vértice adjacente
    return idVerticeAdjacente;
}

float Adjacente::getPesoDaAresta() {
    return pesoAresta;
}

void Adjacente::setPesoDaAresta(float _pesoAresta) {
    pesoAresta = _pesoAresta;
}

Adjacente::~Adjacente() {
    // TODO Auto-generated destructor stub
}
