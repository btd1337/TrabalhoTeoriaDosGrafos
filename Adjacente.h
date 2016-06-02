//
// Created by helder on 27/04/16.
//

#ifndef TRABALHOGRAFOS_ADJACENTE_H
#define TRABALHOGRAFOS_ADJACENTE_H

#include "Vertice.h"

using namespace std;

class Vertice;

class Adjacente {

private:
    long idVerticeAdjacente;
    float pesoAresta;

public:
    Adjacente(long _idVerticeAdjacente);
    Adjacente(long _idVerticeAdjacente, float _pesoAresta);
    long getVerticeAdjacente();
    float getPesoDaAresta();
    void setPesoDaAresta(float _pesoAresta);
    virtual ~Adjacente();
};


#endif //TRABALHOGRAFOS_ADJACENTE_H
