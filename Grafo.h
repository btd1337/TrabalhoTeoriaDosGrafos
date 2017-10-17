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
    long tamTabHashVertices;
    long tamTabHashAdjacentes;
    long ordemGrafo;
    long numArestas;
    bool isVerticesVisitados();
    bool auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino);
    void auxFechoTransitivo(long _idVertice, set<long> *percorridos);
    void auxFechoIntransitivo(Grafo *grafoAux, long _idVertice, set<int> *percorridos);
    void atualizaIDs(int _idVerticeRemovido);
    long calculaIndiceTabela(long _idVertice);
    void auxNumComponentesConexas(long _idVertice);
    string buscaProfundidadeAux(long _idVertice, long _tempo);
public:
    Grafo(long _ordemGrafo, long _numArestas);
    virtual ~Grafo();

    void addVertice(long _idVertice);
    bool removeVertice(long _idVertice);
    long addVerticeAdjacente(long _verticeOrigem, long _verticeDestino, float _pesoAresta);
    bool removeVerticeAdjacente(int _idVerticeOrigem, int _idVerticeDestino);
    long getGrauVertice(long _idVertice);
    multiset<long, greater<long> > sequenciaGraus();
    bool verificaKRegular(long *kRegular);
    bool isCompleto();
    bool verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino);
    string buscaProfundidade(long _idVerticeOrigem);
    string buscaLargura(long _idVerticeOrigem);
    bool verificaVerticesComponentesConexa(long _idVertice1, long _idVertice2);
    bool auxVVCC(list<Vertice>::iterator _vertice1, long _idVertice2);
    long numComponentesConexas();
    void setTamTabHashAdjacentes(long _tam);
    list<Vertice>::iterator getVertice(long _idVertice);
    void imprimeVertices();
    void setIsGrafoDirecionado(bool _isDirecionado);
    bool isConexo();
    bool isDirecionado();
    long verificaGrauGrafo();
    string fechoTransitivo(long _idVertice);
    string fechoIntransitivo(long _idVertice);
    long getOrdemGrafo();
    list<Vertice> *getVertices();
    list<Vertice>::iterator isContainVertice(long _idVertice);
    bool isVerticePresente(long _idVertice);
    long getTamTabHashVertices();
    long getTamTabHashAdj();
    list<Vertice>::iterator itUltimaPosicao(long _idVertice);
    long getNumArestas();
    list<long> getVizinhaAberta(long _idVertice);
    long caminhoMinimoDijkstra(long _idVerticeOrigem, long _idVerticeDestino);
    long caminhoMinimoFloyd(long _idVerticeOrigem, long _idVerticeDestino);
    string agmPrim(long _idVerticeInicial);
};


#endif //TRABALHOGRAFOS_GRAFO_H
