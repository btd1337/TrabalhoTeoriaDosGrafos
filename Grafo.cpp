//
// Created by helder on 27/04/16.
//

#include "Grafo.h"
#include "Vertice.h"
#include "Coloracao.h"

using namespace std;

Grafo::Grafo(long _ordemGrafo) {

    //Caso a ordem do grafo seja 1 -> 1/2 = 0 , então é necessário alocar 1 posição pra tabela hash
    _ordemGrafo == 1 ? (tamTabelaHash = 1) : (tamTabelaHash = _ordemGrafo/2);
    ordemGrafo = 0; //inicializa variável que será incrementada em addVertice()
    numArestas = 0;

    list<Vertice> aux(tamTabelaHash);
    vertices = new list<Vertice>[tamTabelaHash];

    //inicialização da estrutura pra tabela hash
    for(int i=0; i<_ordemGrafo/2; i++){
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
    for(int i=0; i< tamTabelaHash; i++){
        for(int j=0; j< vertices[i].size(); j++) {
            cout << getVertice(i)->getIdVertice() << endl;
        }
    }
}

/**
 * Retorna um ponteiro de um vértice do grafo
 * @param _idVertice - id do vértice que deseja obter a referência
 * @return referência pro vértice procurado no grafo
 */
list<Vertice>::iterator Grafo::getVertice(long _idVertice)
{
    long indice = calculaIndiceTabela(_idVertice);

    for(list<Vertice>::iterator v = vertices[indice].begin(); v!= vertices[indice].end(); v++){
        if(v->getIdVertice() == _idVertice){
            return v;
        }
    }
    list<Vertice>::iterator v = vertices[indice].end(); //caso não seja encontrado
    return v;
}

/**
 * Adiciona um vértice ao grafo
 * @param _idVertice: id do vértice que será adicionado
 */
void Grafo::addVertice(long _idVertice)
{
    auto it = isContainVertice(_idVertice);
    if(it != itUltimaPosicao(_idVertice)){
        cout << _idVertice << endl;
        cout << "Esse vértice já existe! \n" << endl;
    }else {
        long indice = calculaIndiceTabela(_idVertice);
        Vertice vertice;
        vertice.setIdVertice(_idVertice);
        vertices[indice].push_back(vertice);
        ordemGrafo++;
    }
}

/**
 * Define a adjacência entre dois vértices.
 * Verificações: Se os vértices existem e se a aresta já existe.
 * @param _verticeOrigem
 * @param _verticeDestino
 * @param _pesoAresta
 */
void Grafo::addVerticeAdjacente(int _verticeOrigem, int _verticeDestino, float _pesoAresta)
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
                cout << "A aresta já existe! \n" << endl;
            }
        }
    }
}

/**
 * Método auxiliar ao método isConexo.
 * @param _vertice: id do vértice onde vai ser feita a verificação
 */
void Grafo::auxIsConexo(int _vertice){
    //Seta vértice atual como visitado
    getVertice(_vertice)->setCorVisita(Coloracao::AZUL);

    list<Adjacente> verticesAdjacentes = getVertice(_vertice)->getVerticesAdjacentes();

    for (list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++) {
        //verifica se o vértice ainda não foi corVisita
        if(getVertice(it->getIdVertice())->getVisitado() == Coloracao::SEMCOR);
            auxIsConexo(it->getIdVertice());
    }

}

/**
 * Verifica se o grafo é conexo
 * @return valor lógico que informa se é o grafo é conexo
 */
bool Grafo::isConexo(){

    //seta os vértices como não visitados
    for(int i=0; i< ordemGrafo; i++){
        getVertice(i)->setCorVisita(Coloracao::SEMCOR);
    }
    auxIsConexo(0);

    for(int i=0; i< ordemGrafo; i++){
        if(getVertice(i)->getVisitado() == Coloracao::SEMCOR){
            return false;
        }

    }

    return true;
}

/**
 * Método auxiliar ao método isBipartido
 * @param _vertice: id do Vértice atual
 * @param _numPasso: número de etapas até então
 * @return true caso o vértice atual tenha sido colorido corretamente, false caso contrário
 */
bool Grafo::auxIsBipartido(long _vertice, long _numPasso){
    bool coloriuCorretamente = false;
    Coloracao corDePreenchimento = Coloracao::SEMCOR;
    _numPasso%2==0 ? corDePreenchimento=Coloracao::AZUL : corDePreenchimento=Coloracao::VERDE;

    if(getVertice(_vertice)->getVisitado() == Coloracao::SEMCOR){
        getVertice(_vertice)->setCorVisita(corDePreenchimento);

        //Adjacente auxAdj(0);
        //percorre a lista dos adjacentes do vértice atual
        //for(auxAdj : getVertice(_vertice)->getVerticesAdjacentes()){
        //Cria Arestas
        for(Adjacente adj : getVertice(_vertice)->getVerticesAdjacentes()){
            coloriuCorretamente = auxIsBipartido(adj.getIdVertice(),_numPasso+1);
            if(!coloriuCorretamente){
                break;
            }
        }
    }
    else{
        if(getVertice(_vertice)->getVisitado() != corDePreenchimento){
            return false;
        }
    }
    return true;
}

bool Grafo::isGrafoBipartido(){
    int passo=0;
    int j=0;
    isBipartido = true; //seta o grafo como bipartido, caso provado que não seja, a variável é setada com false

    //determina que todos vértices não foram visitados.
    for(int i=0; i < ordemGrafo; i++){
        getVertice(i)->setCorVisita(Coloracao::SEMCOR);    //marca vértice como não visitado
    }

    isBipartido = auxIsBipartido(0,passo);

}

long Grafo::verificaGrauVertice(long _idVertice){
    //return getVertice(_idVertice)->getVerticesAdjacentes().size();
    return getVertice(_idVertice)->getGrau();
}

/**
 * Identifica o grau de um grafo
 * @return grau do vértice de maior grau
 */
long Grafo::verificaGrauGrafo(){
    //Associa grauMax ao primeiro vértice da tabela
    long grauMax=verificaGrauVertice(vertices[0].begin()->getIdVertice());
    long grauVerticeAtual;

    for(int i=0; i<tamTabelaHash; i++){
        for(list<Vertice>::iterator it = vertices[i].begin(); it != vertices[i].end(); it++) {
            grauVerticeAtual = verificaGrauVertice(it->getIdVertice());
            if (grauVerticeAtual > grauMax)
                grauMax = grauVerticeAtual;
        }
    }
    return grauMax;
}

bool Grafo::verificaAdjacencia(long _idVerticeOrigem, long _idVerticeDestino){
    list<Adjacente> verticesAdjacentes = getVertice(_idVerticeOrigem)->getVerticesAdjacentes();

    for(list<Adjacente>::iterator it = verticesAdjacentes.begin(); it != verticesAdjacentes.end() ; it++){
        if(it->getIdVertice() == _idVerticeDestino)
            return true;
    }
    return false;
}

bool Grafo::verificaKRegular(long *kRegular){
    *kRegular = getVertice(0)->getVerticesAdjacentes().size();

    for(int i=1; i < ordemGrafo; i++){
        if(getVertice(i)->getVerticesAdjacentes().size() != *kRegular)
            return false;
    }
    return true;
}

bool Grafo::isCompleto(){
    for(int i=0; i < ordemGrafo; i++){
        if(getVertice(i)->getVerticesAdjacentes().size() != ordemGrafo - 1);
        return false;
    }
    return true;
}


bool Grafo::removeVertice(int _idVertice) {

    //it recebe o iterador da posição onde está o vértice ou nullptr
    list<Vertice>::iterator it = isContainVertice(_idVertice);

    if(it == itUltimaPosicao(_idVertice)){  //caso o método isContainVertice não encontrar o vértice
        cout << "Erro: Não existe vértice com este id no Grafo.\n" << endl;

    }else{
        //Remove as arestas do vértice
        for(Adjacente adjacente : it->getVerticesAdjacentes()){
            removeAresta(it->getIdVertice(),adjacente.getIdVertice());
        }
        long indice = calculaIndiceTabela(_idVertice);
        vertices[indice].erase(it);
        cout << "Vértice removido com sucesso.\n" <<endl;
        ordemGrafo--;
    }
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


bool Grafo::removeAresta(int _idVerticeOrigem, int _idVerticeDestino) {

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

    bool isRemovido;

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

    if(_idVertice<0 || _idVertice >= ordemGrafo){
        cout << "Vertice inválido" << endl;
    }
    else {
        //Percorre apenas se o vértice já não tiver sido verificado

        percorridos->insert(_idVertice); //insere à lista de vértices percorridos

        getVertice(_idVertice)->setCorVisita(Coloracao::AZUL); //define como visitado


        for(Adjacente it : getVertice(_idVertice)->getVerticesAdjacentes()){

            long adj = it.getIdVertice();

            if(getVertice(adj)->getVisitado() == Coloracao::SEMCOR) {

                auxFechoTransitivo(adj, percorridos);  //chama recursivamente a função passando os vértices adjacentes
            }
        }
    }

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

    //Percorre apenas se o vértice já não tiver sido verificado

    percorridos->insert(_idVertice); //insere à lista de vértices percorridos

    grafoAux->getVertice(_idVertice)->setCorVisita(Coloracao::AZUL); //define como visitado

    for(Adjacente it : grafoAux->getVertice(_idVertice)->getVerticesAdjacentes()){

        long adj = it.getIdVertice();

        if(grafoAux->getVertice(adj)->getVisitado() == Coloracao::SEMCOR) {

            auxFechoIntransitivo(grafoAux, adj, percorridos);  //chama recursivamente a função passando os vértices adjacentes
        }
    }
}


string Grafo::fechoIntransitivo(long _idVertice) {
    string sFechoIntransitivo = "";
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

int Grafo::calculaIndiceTabela(long _idVertice) {
    return _idVertice % tamTabelaHash;
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
    list<Vertice>::iterator it;

    for(it = vertices[posicao].begin(); it != vertices[posicao].end(); it++){
        //Se encontrar o vértice
        if(it->getIdVertice() == _idVertice){
            return it;
        }
    }
    //Se vértice não estiver presente, vai retornar it apontando pro end do último elemento do vetor
    it = vertices[posicao].end();
    return it;
}

/**
 * @return numero de elementos do vetor de posições para a tabela hash dos vértices
 */
long Grafo::getTamTabelaHash() {
    return tamTabelaHash;
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




