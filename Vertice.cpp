//
// Created by helder on 27/04/16.
//

#include "Vertice.h"

Vertice::Vertice(long _tamTabHashAdjacentes, long _idVertice) {
    idVertice = _idVertice;
    tamTabHashAdjacentes = _tamTabHashAdjacentes;
    //cria tab hash na media numArestas/numVertices
    verticesAdjacentes = new list<Adjacente>((unsigned long) tamTabHashAdjacentes);
    corVisita = Coloracao::SEMCOR;  //inicia o vértice sem cor
    grau = 0;
    peso = 1 + idVertice * 2;
    disponivel = true;

    //Limpa as listas de adjacentes
    for(int i=0; i< _tamTabHashAdjacentes; i++){
        verticesAdjacentes[i].clear();
    }
}

Vertice::~Vertice() {
    // TODO Auto-generated destructor stub
}

long Vertice::getIdVertice() {
    return idVertice;
}

void Vertice::setIdVertice(long _idVertice) {
    idVertice = _idVertice;
}

list<Adjacente> *Vertice::getVerticesAdjacentes() {
    return verticesAdjacentes;
}

void Vertice::addVerticeAdjacente(long _idVerticeAdjacente, float _pesoAresta) {
    long indice = calculaIndiceTabela(_idVerticeAdjacente);

    Adjacente verticeAdjacente(_idVerticeAdjacente,_pesoAresta);
    verticesAdjacentes[indice].push_back(verticeAdjacente);
    grau++;
}

/**
 * Remove a aresta de um vértice
 * @param _idVertice
 * @return true se a aresta foi encontra, false caso contrário
 */
bool Vertice::removeVerticeAdjacente(long _idVertice) {

    long indice = calculaIndiceTabela(_idVertice);
    for (auto it = verticesAdjacentes[indice].begin(); it != verticesAdjacentes[indice].end() ; ++it) {
        //Percorre a lista de adjacentes e verifica se o rótulo é o procurado
        if(it->getIdVertice() == _idVertice){
            verticesAdjacentes[indice].erase(it);
            grau--;
            return true;
        }
    }
    return false;
}


string Vertice::listarAdjacentes()
{
    string listaDeAdjacentes = "";
    for(int i=0; i<tamTabHashAdjacentes; i++){
        for(auto it = verticesAdjacentes[i].begin(); it != verticesAdjacentes[i].end(); it++){
            listaDeAdjacentes += to_string(it->getIdVertice());
            listaDeAdjacentes += " ";
        }
    }
    return listaDeAdjacentes;
}

Coloracao Vertice::getColoracao(){
    return corVisita;
}

void Vertice::setCorVisita(Coloracao _corVisita) {
    corVisita = _corVisita;
}

long Vertice::getGrau() const {
    return grau;
}

double Vertice::getPeso() const {
    return peso;
}

void Vertice::setPeso(double peso) {
    Vertice::peso = peso;
}

void Vertice::reduzGrau() {
    grau--;
}

long Vertice::calculaIndiceTabela(long _idVertice) {
    return _idVertice % tamTabHashAdjacentes;
}

bool Vertice::verificaAdjacencia(long _idAdjacente) {
    long indice = calculaIndiceTabela(_idAdjacente);

    for(auto it = verticesAdjacentes[indice].begin(); it != verticesAdjacentes[indice].end(); it++){
        if(it->getIdVertice() == _idAdjacente){
            return true;
        }
    }
    return false;
}

/**
 * Obtém o id do vértice antecessor numa busca
 * @return pi
 */
long Vertice::getPi() const {
    return pi;
}

/**
 * Seta o id do vértice predecessor numa busca
 * @param _idVertice
 */
void Vertice::setPi(long _idVertice) {
    Vertice::pi = pi;
}

void Vertice::mostraIdAdjacentes() {

    for(int i=0; i<tamTabHashAdjacentes; i++) {
        for (auto it = verticesAdjacentes[i].begin(); it != verticesAdjacentes[i].end(); it++) {
            //Percorre a lista de adjacentes e verifica se o rótulo é o procurado
            cout << it->getIdVertice() << " ";
        }
    }
    cout << "\n" << endl;
}

bool Vertice::getDisponivel() {
    return disponivel;
}

void Vertice::setDisponivel(bool _d) {
    disponivel = _d;
}
