/*
 * Grafo.cpp
 *
 *  Created on: 27/04/2016
 *      Author: helder
 */

#ifndef TRABALHOGRAFOS_GRAFO_H
#define TRABALHOGRAFOS_GRAFO_H


#include <vector>
#include <string>
#include <list>
#include <set>

#include "Adjacente.h"


using namespace std;

class Vertice;

class Grafo {

private:
    vector<Vertice> vertices;
    bool isGrafoDirecionado;
    bool isBipartido;
    void atualizaNumeracaoAdjacentes(int _idVertice, int _idVerticeRemovido);
    bool isVerticesVisitados();
    bool auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino);
    void auxFechoTransitivo(long _idVertice, set<int> *percorridos);
    void auxFechoIntransitivo(Grafo *grafoAux, long _idVertice, set<int> *percorridos);
    void atualizaIDs(int _idVerticeRemovido);
    bool auxIsBipartido(long _vertice, long _numPasso);

public:
    Grafo();
    virtual ~Grafo();
    Vertice *getVertice(int _idVertice);
    void addVertice(long _idVertice);
    void addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta);
    void imprimeVertices();
    void setIsGrafoDirecionado(bool _isDirecionado);
    void auxIsConexo(int _vertice);
    bool isConexo();
    bool isGrafoBipartido();
    long verificaGrauGrafo();
    long verificaGrauVertice(long _idVertice);
    bool verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino);
    bool verificaKRegular(long *kRegular);
    bool isCompleto();
    bool removeVertice(int _idVertice);
    bool removeAresta(int _idVerticeOrigem, int _idVerticeDestino);
    string fechoTransitivo(long _idVertice);
    string fechoIntransitivo(long _idVertice);
};


#endif //TRABALHOGRAFOS_GRAFO_H
