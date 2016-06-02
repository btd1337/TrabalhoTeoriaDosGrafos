//
// Created by helder on 27/04/16.
//

#ifndef TRABALHOGRAFOS_VERTICE_H
#define TRABALHOGRAFOS_VERTICE_H

#include <iostream>
#include <string>
#include <list>
#include "Adjacente.h"

using namespace std;

class Adjacente;

class Vertice {

private:
    long idVertice;
    list<Adjacente> verticesAdjacentes;
    static long contVertice;
    int visitado;

public:
    Vertice();
    virtual ~Vertice();
    int getIdVertice();
    void setIdVertice(long _idVertice);
    list<Adjacente> getVerticesAdjacentes();
    void addVerticeAdjacente(long _idVerticeAdjacente, float _pesoAresta);
    void removeVerticeAdjacente(long _idVertice);
    string listarAdjacentes();
    int getVisitado();
    void setVisitado(int _visitado);
};


#endif //TRABALHOGRAFOS_VERTICE_H
