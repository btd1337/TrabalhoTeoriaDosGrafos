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
    Coloracao cor;
    long pi;    //predecessor do vertice
    bool disponivel;
    long distancia;     //usado nas buscas
    long antecessor;    //usado nas buscas
public:
    long getPi() const;
    void mostraIdAdjacentes();
    void setPi(long pi);

private:
    //vértice predecessor em uma busca

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
    Coloracao getColoracao();
    void setCor(Coloracao _cor);
    double getPeso() const;
    void setPeso(double peso);
    long getGrau() const;
    void reduzGrau();
    bool verificaAdjacencia(long _idAdjacente);
    bool getDisponivel();
    void setDisponivel(bool _d);

    long getDistancia() const;
    void setDistancia(long _distancia);

    long getAntecessor() const;

    void setAntecessor(long antecessor);
};


#endif //TRABALHOGRAFOS_VERTICE_H
