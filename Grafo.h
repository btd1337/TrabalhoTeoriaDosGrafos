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


using namespace std;

class Vertice;

class Grafo {

private:
    vector<Vertice> vertices;
    bool isGrafoDirecionado;
    bool isBipartido;
    void atualizaNumeracaoAdjacentes(int _idVertice, int _idVerticeRemovido);
    bool isVerticesVisitados();

public:
    Grafo();
    virtual ~Grafo();
    Vertice *getVertice(int _idVertice);
    void addVertice();
    void addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta);
    void imprimeVertices();
    void setIsGrafoDirecionado(bool _isDirecionado);
    void auxIsConexo(int _vertice);
    bool isConexo();
    bool auxIsBipartido(int _vertice, int _numPasso);
    bool isGrafoBipartido();
    long verificaGrauGrafo();
    long verificaGrauVertice(long _idVertice);
    bool verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino);
    bool verificaKRegular(long *kRegular);
    bool isCompleto();
    bool removeVertice(int _idVertice);
    bool removeAresta(int _idVerticeOrigem, int _idVerticeDestino);
};


#endif //TRABALHOGRAFOS_GRAFO_H
