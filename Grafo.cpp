//
// Created by helder on 27/04/16.
//

#include "Grafo.h"


using namespace std;

Grafo::Grafo(long _ordemGrafo, long _numArestas) {

    //Caso a ordem do grafo seja 1 -> 1/2 = 0 , então é necessário alocar 1 posição pra tabela hash
    _ordemGrafo == 1 ? (tamTabHashVertices = 1) : (tamTabHashVertices = _ordemGrafo/2);


    //usada pra saber o tamanho inicial da tab hash dos adjacentes de um vértice
    if(_numArestas <= _ordemGrafo || _ordemGrafo == 0){
        tamTabHashAdjacentes = 1;
    }else{
        tamTabHashAdjacentes = _numArestas/_ordemGrafo;
    }

    ordemGrafo = 0; //inicializa variável que será incrementada em addVertice()
    numArestas = 0;

    vertices = new list<Vertice>[tamTabHashVertices];

    //inicialização da estrutura pra tabela hash
    for(int i=0; i<tamTabHashVertices; i++){
        vertices[i].clear();
    }

    isGrafoDirecionado = false;
}

Grafo::~Grafo() {
}

/**
 * Seta o atributo do grafo isGrafoDirecionado atráves do valor passado via parâmetro
 * @param _isDirecionado : variável lógica que informa se o grafo é direcionado
 */
void Grafo::setIsGrafoDirecionado(bool _isDirecionado){
    isGrafoDirecionado = _isDirecionado;
}

/**
 * imprime os vértices do grafo
 */
void Grafo::imprimeVertices()
{
    for(int i=0; i< tamTabHashVertices; i++){
        for(int j=0; j< vertices[i].size(); j++) {
            cout << getVertice(i)->getIdVertice() << endl;
        }
    }
}

/**
 * Retorna um ponteiro de um vértice do grafo, se a busca não obtiver
 * resultado retonar end() apontando pra ultima posição da lista relacionada aquele indice
 * da tabela hash
 * @param _idVertice - id do vértice que deseja obter a referência
 * @return referência pro vértice procurado no grafo
 */
list<Vertice>::iterator Grafo::getVertice(long _idVertice)
{
    long indice = calculaIndiceTabela(_idVertice);

    auto v = vertices[indice].begin();

    while(v!= vertices[indice].end()){
        if (v->getIdVertice() == _idVertice) {
            break;
        }
        v++;
    }

    return v;
}

/**
 * Adiciona um vértice ao grafo
 * @param _idVertice: id do vértice que será adicionado
 */
void Grafo::addVertice(long _idVertice)
{
    auto it = isContainVertice(_idVertice);
    //Se não encontrar o vértice é porque ele não está presente e pode ser adicionado
    if(it == itUltimaPosicao(_idVertice)){
        long indice = calculaIndiceTabela(_idVertice);
        Vertice vertice(tamTabHashAdjacentes, _idVertice);
        vertices[indice].push_back(vertice);
        ordemGrafo++;
    }else {
        cout << _idVertice << endl;
        cout << "Esse vértice já existe! \n" << endl;
    }
}

/**
 * Define a adjacência entre dois vértices.
 * Verificações: Se os vértices existem e se a aresta já existe.
 * @param _verticeOrigem
 * @param _verticeDestino
 * @param _pesoAresta
 */
long Grafo::addVerticeAdjacente(long _verticeOrigem, long _verticeDestino, float _pesoAresta)
{

    //verifica existência dos vértices
    auto it = isContainVertice(_verticeOrigem);
    if(it==itUltimaPosicao(_verticeOrigem)){
        cout << "Erro: Não existe vértice com id informado como origem.\n" << endl;
    }
    else {
        it = isContainVertice(_verticeDestino);
        if (it == itUltimaPosicao(_verticeDestino)) {
            cout << "Erro: Não existe vértice com id informado como destino.\n" << endl;
        } else {
            //verifica se a aresta já existe
            if(!verificaAdjacencia(_verticeOrigem, _verticeDestino)) {

                getVertice(_verticeOrigem)->addVerticeAdjacente(_verticeDestino, _pesoAresta);
                numArestas++;

                if (!isGrafoDirecionado) {
                    getVertice(_verticeDestino)->addVerticeAdjacente(_verticeOrigem, _pesoAresta);
                }
            }else{
                //cout << "A aresta já existe! \n" << endl;
            }
        }
    }
}

/**
 * Método auxiliar ao método isConexo.
 * @param _vertice: id do vértice onde vai ser feita a verificação
 */
void Grafo::auxIsConexo(long _vertice){
    //Seta vértice atual como visitado
    getVertice(_vertice)->setCorVisita(Coloracao::AZUL);

    list<Adjacente> *verticesAdjacentes = getVertice(_vertice)->getVerticesAdjacentes();

    for(int i=0; i<tamTabHashAdjacentes; i++){
        for (auto it = verticesAdjacentes[i].begin(); it != verticesAdjacentes[i].end() ; it++) {
            //verifica se o vértice ainda não foi corVisita
            if(getVertice(it->getIdVertice())->getColoracao() == Coloracao::SEMCOR);
            auxIsConexo(it->getIdVertice());
        }
    }

}

/**
 * Verifica se o grafo é conexo
 * @return valor lógico que informa se é o grafo é conexo
 */
bool Grafo::isConexo(){
    //função marca inicialmente os vértices de bco e finaliza pintando de pto
    //-1 -> id que não existe, pra não parar a função
    bool aux = verificaVerticesComponentesConexa(0,-1);

    for(int i=0; i<tamTabHashVertices ;i++){
        for(auto it = vertices[i].begin(); it != vertices[i].end(); it++){
            if(it->getColoracao() == Coloracao::BRANCO){    //branco = vértice não visitado
                return false;
            }
        }
    }

    return true;
}

/**
 * Identifica o grau de um grafo
 * @return grau do vértice de maior grau
 */
long Grafo::verificaGrauGrafo(){
    //Associa grauMax ao primeiro vértice da tabela
    long grauMax=getGrauVertice(vertices[0].begin()->getIdVertice());
    long grauVerticeAtual;

    for(int i=0; i<tamTabHashVertices; i++){
        for(list<Vertice>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++) {
            grauVerticeAtual = getGrauVertice(it->getIdVertice());
            if (grauVerticeAtual > grauMax)
                grauMax = grauVerticeAtual;
        }
    }
    return grauMax;
}

/**
 * Verifica adjacencia entre 2 vértices
 * @param _idVerticeOrigem
 * @param _idVerticeDestino
 * @return valor lógico
 */
bool Grafo::verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino){

    return getVertice(_idVerticeOrigem)->verificaAdjacencia(_idVerticeDestino);

}

/**
 * Verifica se o grafo é regular e caso seja, passa por ponteiro a k-regularidade
 * @param kRegular
 * @return valor lógico para a função
 */
bool Grafo::verificaKRegular(long *kRegular){
    *kRegular = vertices[0].begin()->getGrau();

    for(int i=0; i<tamTabHashVertices; i++){
        for(auto it = vertices[i].begin(); it != vertices[i].end(); it++) {
            if (it->getGrau() != *kRegular)
                return false;
        }
    }
    return true;
}

/**
 * Verifica se o grafo é completo
 * @return valor lógico para a função
 */
bool Grafo::isCompleto(){
    long kregular;
    //Condição: Grafo é k-regular e se a k-regularidade é ordem do Grafo - 1;
    return verificaKRegular(&kregular) && kregular == ordemGrafo - 1;

}


bool Grafo::removeVertice(long _idVertice) {

    //it recebe o iterador da posição onde está o vértice ou nullptr
    auto it = isContainVertice(_idVertice);
    list<long> verticesAdj;
    verticesAdj.clear();    //certifica de zerar a lista aux

    if(it == itUltimaPosicao(_idVertice)){  //caso o método isContainVertice não encontrar o vértice
        cout << "Erro: Não existe vértice com este id no Grafo.\n" << endl;
        return false;

    }else{
        //Remove as arestas do vértice
        //Remover diretamente está com erro, por isso está sendo criada lista auxiliar
        auto adjacentes = it->getVerticesAdjacentes();
        for(int j=0; j<tamTabHashAdjacentes; j++) {
            for (auto adj = adjacentes[j].begin(); adj != adjacentes[j].end(); adj++) {
                verticesAdj.push_back(adj->getIdVertice());
            }
        }

        for(int i=0; i<verticesAdj.size(); i++){
            removeVerticeAdjacente(_idVertice,*verticesAdj.begin());
            verticesAdj.erase(verticesAdj.begin());
        }
        long indice = calculaIndiceTabela(_idVertice);
        vertices[indice].erase(it);
        ordemGrafo--;
    }
    return true;
}


bool Grafo::auxRemoveAresta(int _idVerticeOrigem, int _idVerticeDestino) {
    if(isGrafoDirecionado){
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
    }
    else{
        getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino);
        getVertice(_idVerticeDestino)->removeVerticeAdjacente(_idVerticeOrigem);
    }
    return true;
}


bool Grafo::removeVerticeAdjacente(int _idVerticeOrigem, int _idVerticeDestino) {

    //verifica se os vértices são válidos
    auto it = isContainVertice(_idVerticeOrigem);
    if(it == itUltimaPosicao(_idVerticeOrigem)){
        cout << "Erro: Não existe vértice com o id informado como Origem!\n" << endl;
        return false;
    }
    it = isContainVertice(_idVerticeDestino);
    if(it == itUltimaPosicao(_idVerticeDestino)){
        cout << "Erro: Não existe vértice com o id informado como Destino!\n" << endl;
        return false;
    }

    if(isGrafoDirecionado){
        //Verifica se existe a aresta
        if(!getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino)){
            cout << "ERRO: Aresta Não Existente!\n" << endl;
        }
    }
    else{
        //Verifica se existe a aresta
        if(getVertice(_idVerticeOrigem)->removeVerticeAdjacente(_idVerticeDestino)) {
            getVertice(_idVerticeDestino)->removeVerticeAdjacente(_idVerticeOrigem);
        }else{
            cout << "ERRO: Aresta Não Existente!\n" << endl;
        }
    }
    return true;
}


void Grafo::auxFechoTransitivo(long _idVertice, set<int> *percorridos) {
    /*
    if(_idVertice<0 || _idVertice >= ordemGrafo){
        cout << "Vertice inválido" << endl;
    }
    else {
        //Percorre apenas se o vértice já não tiver sido verificado

        percorridos->insert(_idVertice); //insere à lista de vértices percorridos

        getVertice(_idVertice)->setCorVisita(Coloracao::AZUL); //define como visitado


        for(Adjacente it : getVertice(_idVertice)->getVerticesAdjacentes()){

            long adj = it.getIdVertice();

            if(getVertice(adj)->getColoracao() == Coloracao::SEMCOR) {

                auxFechoTransitivo(adj, percorridos);  //chama recursivamente a função passando os vértices adjacentes
            }
        }
    }
    */
}


string Grafo::fechoTransitivo(long _idVertice) {
    string sFechoTransitivo = "";
    set<int> verticesPercorridos;

    //Seta todos como não-visitados
    for(int i=0; i<ordemGrafo;i++){
        getVertice(i)->setCorVisita(Coloracao::SEMCOR);
    }

    auxFechoTransitivo(_idVertice, &verticesPercorridos);

    cout << _idVertice << "-> ";
    for(auto percorridoAtual : verticesPercorridos) {
        if(percorridoAtual != _idVertice) {   //Não inclui o próprio vértice
            cout << percorridoAtual << " ";
            sFechoTransitivo += to_string(percorridoAtual);
            sFechoTransitivo += " ";
        }
    }

    cout << "\n\n" << endl;
    return sFechoTransitivo;
}


void Grafo::auxFechoIntransitivo(Grafo *grafoAux, long _idVertice, set<int> *percorridos) {
    /*
    //Percorre apenas se o vértice já não tiver sido verificado

    percorridos->insert(_idVertice); //insere à lista de vértices percorridos

    grafoAux->getVertice(_idVertice)->setCorVisita(Coloracao::AZUL); //define como visitado

    for(Adjacente it : grafoAux->getVertice(_idVertice)->getVerticesAdjacentes()){

        long adj = it.getIdVertice();

        if(grafoAux->getVertice(adj)->getColoracao() == Coloracao::SEMCOR) {

            auxFechoIntransitivo(grafoAux, adj, percorridos);  //chama recursivamente a função passando os vértices adjacentes
        }
    }
     */
}


string Grafo::fechoIntransitivo(long _idVertice) {
    string sFechoIntransitivo = "";
    /*
    set<int> verticesPercorridos;

    //Seta todos como não-visitados
    for(int i=0; i<ordemGrafo;i++){
        getVertice(i)->setCorVisita(Coloracao::SEMCOR);
    }


    if(!isGrafoDirecionado) {   //Grafo não-direcionado o caminho de ida é o mesmo de volta
        auxFechoTransitivo(_idVertice, &verticesPercorridos);
    }else{
        //Cria grafo auxiliar, invertendo o sentido de ligação das arestas
        long i=1;
        long tamanhoGrafo = ordemGrafo;

        Grafo grafoAux(ordemGrafo);

        //O primeiro vértice é criado automaticamente
        grafoAux.getVertice(0)->setIdVertice(0);

        while(i < tamanhoGrafo){
            grafoAux.addVertice(i);
            i++;
        }
        grafoAux.setIsGrafoDirecionado(true);

        //Cria Arestas
        for(i=0; i<tamanhoGrafo; i++){
            for(Adjacente adj : getVertice(i)->getVerticesAdjacentes()){
                grafoAux.getVertice(adj.getIdVertice())->addVerticeAdjacente(i,adj.getPesoDaAresta());
            }
        }

        auxFechoIntransitivo(&grafoAux,_idVertice,&verticesPercorridos);

    }


    cout << _idVertice << "-> ";
    for(auto percorridoAtual : verticesPercorridos) {
        if(percorridoAtual != _idVertice) {   //Não inclui o próprio vértice
            cout << percorridoAtual << " ";
            sFechoIntransitivo += to_string(percorridoAtual);
            sFechoIntransitivo += " ";
        }
    }

    cout << "\n\n" << endl;
     */
    return sFechoIntransitivo;

}

long Grafo::getOrdemGrafo() {
    return ordemGrafo;
}

/**
 * Função hash pra determinar a posição que um vértice será inserido na tabela hash
 * @param _idVertice
 * @return indice para a posição
 */

long Grafo::calculaIndiceTabela(long _idVertice) {
    return _idVertice % tamTabHashVertices;
}

/**
 * Método que verifica se um vértice pertence ao grafo. O retorno de um iterator evita que
 * outra função tenha que percorrer o grafo novamente.
 * @param _idVertice
 * @return iterator para a posição do vértice buscado
 */

list<Vertice>::iterator Grafo::isContainVertice(long _idVertice) {

    //identifica em qual posição da tabela hash o vértice deveria estar
    long posicao = calculaIndiceTabela(_idVertice);
    long idVerticeAtual;
    list<Vertice>::iterator it;

    for(it = vertices[posicao].begin(); it != vertices[posicao].end(); it++){
        //Se encontrar o vértice
        idVerticeAtual = it->getIdVertice();
        if(idVerticeAtual == _idVertice){
            return it;
        }
    }
    //Se vértice não estiver presente, vai retornar it apontando pro end do último elemento do vetor
    return it;
}

/**
 * @return numero de elementos do vetor de posições para a tabela hash dos vértices
 */
long Grafo::getTamTabHashVertices() {
    return tamTabHashVertices;
}

list <Vertice> *Grafo::getVertices() {
    return vertices;
}

/**
 * Retorna iterator apontando pra end() na lista da posicao em que deveria estar o vértice.
 * Permite verificar se uma busca não encontrou elementos
 * @return
 */
list<Vertice>::iterator Grafo::itUltimaPosicao(long _idVertice) {

    long posicao = calculaIndiceTabela(_idVertice);
    return vertices[posicao].end();
}

/**
 *
 * @return informação se o grafo é direcionado
 */
bool Grafo::isDirecionado() {
    return isGrafoDirecionado;
}

long Grafo::getGrauVertice(long _idVertice) {
    return getVertice(_idVertice)->getGrau();
}

multiset<long, greater<long> > Grafo::sequenciaGraus() {
    multiset<long, greater<long> > listaGraus;

    for(int i=0; i<tamTabHashVertices; i++){
        for(auto it = vertices[i].begin(); it != vertices[i].end(); it++){
            listaGraus.insert(it->getGrau());
        }
    }

    return listaGraus;
}

void Grafo::setTamTabHashAdjacentes(long _tam) {
    tamTabHashAdjacentes = _tam;
}

/**
 * @return tamanho da tabela hash dos adjacentes de um vértice
 */
long Grafo::getTamTabHashAdj() {
    return tamTabHashAdjacentes;
}

/**
 * Verifica se 2 vértices estão numa mesma componente conexa
 * @param _vertice1
 * @param _idVertice2
 * @return valor lógico da operação
 */

bool Grafo::auxVVCC(list<Vertice>::iterator _vertice1, long _idVertice2) {
    list<Vertice>::iterator adjAtual;
    _vertice1->setCorVisita(Coloracao::CINZA);
    auto verticesAdj = _vertice1->getVerticesAdjacentes();
    long idVerticeAtual;

    for(int j=0; j<tamTabHashAdjacentes; j++){
        for(auto it2 = verticesAdj[j].begin(); it2 != verticesAdj[j].end(); it2++){
            idVerticeAtual = it2->getIdVertice();
            adjAtual = getVertice(idVerticeAtual);   //Necessário obter o ponteiro pro vértice adjacente atual pra poder manipular ele

            //Caso o vértice adjacente seja o vértice procurado retorna true
            if(adjAtual->getIdVertice() == _idVertice2){
                return true;
            }
            //Caso o vértice adj atual não tenha sido visitado, fazer busca nele
            else if(adjAtual->getColoracao() == Coloracao::BRANCO){
                auxVVCC(adjAtual,_idVertice2);
            }
        }
    }

    _vertice1->setCorVisita(Coloracao::PRETO);
    return false;   //Verificar este retorno;
}

bool Grafo::verificaVerticesComponentesConexa(long _idVertice1, long _idVertice2) {

    bool isMesmaComponenteConexa;

    //Inicializa todos os vértices com cor branca
    for(int i=0; i<tamTabHashVertices; i++){
        for(auto it=vertices[i].begin(); it!= vertices[i].end(); it++){
            it->setCorVisita(Coloracao::BRANCO);
        }
    }

    auto vertice = getVertice(_idVertice1);

    isMesmaComponenteConexa = auxVVCC(vertice, _idVertice2);

    return isMesmaComponenteConexa;
}

/**
 * Função utilizada para verificar se um vértice está contido na mesma componente conexa de outro
 * @param _idVerticeOrigem
 * @param _idVerticeDestino
 * @return valor lógico
 */
bool Grafo::buscaProfundidade(long _idVerticeOrigem, long _idVerticeDestino) {
    return false;
}

/**
 * @return número de componentes conexas do grafo
 */
long Grafo::numComponentesConexas() {

    long numComponentesConexas = 0;
    for(int i=0; i<tamTabHashVertices; i++){
        for(auto it=vertices[i].begin(); it != vertices[i].end(); it++){
            it->setCorVisita(Coloracao::BRANCO);
        }
    }

    for(int i=0; i<tamTabHashVertices; i++){
        for(auto it=vertices[i].begin(); it!=vertices[i].end(); it++){
            //verifica se o vértice não foi percorrido e se ele está disponível
            if(it->getColoracao() == Coloracao::BRANCO){
                numComponentesConexas++;
                auxNumComponentesConexas(it->getIdVertice());
            }
        }
    }

    return numComponentesConexas;
}

void Grafo::auxNumComponentesConexas(long _idVertice) {
    auto vertice = getVertice(_idVertice);
    list<Vertice>::iterator adjAtual;
    vertice->setCorVisita(Coloracao::CINZA);

    for(int j=0; j<tamTabHashAdjacentes; j++){
        for(auto itAux = vertice->getVerticesAdjacentes()[j].begin(); itAux != vertice->getVerticesAdjacentes()[j].end(); itAux ++){
            adjAtual = getVertice(itAux->getIdVertice());
            //Verifica se o adj atual não foi visitado
            if(adjAtual->getColoracao() == Coloracao::BRANCO){
                auxNumComponentesConexas(adjAtual->getIdVertice());
            }
        }
    }

    vertice->setCorVisita(Coloracao::PRETO);
}

long Grafo::getNumArestas() {
    return numArestas;
}

/**
 * Verifica se um vértice é de articulação
 * @param _idVertice
 * @return
 */







