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
    list<Vertice> *vertices;   //vetor de lista, usado pra tabela hash
    bool isGrafoDirecionado;
    bool isBipartido;
    long tamTabelaHash;
    long ordemGrafo;
    long numArestas;
    bool isVerticesVisitados();
    bool auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino);
    void auxFechoTransitivo(long _idVertice, set<int> *percorridos);
    void auxFechoIntransitivo(Grafo *grafoAux, long _idVertice, set<int> *percorridos);
    void atualizaIDs(int _idVerticeRemovido);
    bool auxIsBipartido(long _vertice, long _numPasso);
    int calculaIndiceTabela(long _idVertice);

public:
    Grafo(long _ordemGrafo);
    virtual ~Grafo();
    list<Vertice>::iterator getVertice(long _idVertice);
    void addVertice(long _idVertice);
    void addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta);
    void imprimeVertices();
    void setIsGrafoDirecionado(bool _isDirecionado);
    void auxIsConexo(int _vertice);
    bool isConexo();
    bool isGrafoBipartido();
    bool isDirecionado();
    long verificaGrauGrafo();
    long verificaGrauVertice(long _idVertice);
    bool verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino);
    bool verificaKRegular(long *kRegular);
    bool isCompleto();
    bool removeVertice(int _idVertice);
    bool removeAresta(int _idVerticeOrigem, int _idVerticeDestino);
    string fechoTransitivo(long _idVertice);
    string fechoIntransitivo(long _idVertice);
    long getOrdemGrafo();
    list<Vertice> *getVertices();
    list<Vertice>::iterator isContainVertice(long _idVertice);
    long getTamTabelaHash();
    list<Vertice>::iterator itUltimaPosicao(long _idVertice);
};


#endif //TRABALHOGRAFOS_GRAFO_H
