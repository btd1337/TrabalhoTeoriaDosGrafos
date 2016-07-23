//
// Created by helder on 27/04/16.
//

#ifndef TRABALHOGRAFOS_VERTICE_H
#define TRABALHOGRAFOS_VERTICE_H

#include <iostream>
#include <string>
#include <list>
#include "Adjacente.h"
#include "Coloracao.h"


using namespace std;

class Adjacente;

class Vertice {

private:
    long idVertice;
    list<Adjacente> verticesAdjacentes;
    static long contVertice;
    Coloracao corVisita;

public:
    Vertice();
    virtual ~Vertice();
    int getIdVertice();
    void setIdVertice(long _idVertice);
    list<Adjacente> getVerticesAdjacentes();
    void addVerticeAdjacente(long _idVerticeAdjacente, float _pesoAresta);
    bool removeVerticeAdjacente(long _idVertice);
    string listarAdjacentes();
    Coloracao getVisitado();
    void setCorVisita(Coloracao _corVisita);
};


#endif //TRABALHOGRAFOS_VERTICE_H
