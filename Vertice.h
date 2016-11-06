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
    long grau;
    double peso;
    list<Adjacente> *verticesAdjacentes;
    long tamTabHashAdjacentes;
    Coloracao corVisita;

    long calculaIndiceTabela(long _idVertice);

public:
    Vertice(long _tamTabHashAdjacentes, long _idVertice);
    virtual ~Vertice();
    long getIdVertice();
    void setIdVertice(long _idVertice);
    list<Adjacente> *getVerticesAdjacentes();
    void addVerticeAdjacente(long _idVerticeAdjacente, float _pesoAresta);
    bool removeVerticeAdjacente(long _idVertice);
    string listarAdjacentes();
    Coloracao getVisitado();
    void setCorVisita(Coloracao _corVisita);
    double getPeso() const;
    void setPeso(double peso);
    long getGrau() const;
    void reduzGrau();
    bool verificaAdjacencia(long _idAdjacente);
};


#endif //TRABALHOGRAFOS_VERTICE_H
