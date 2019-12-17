/*****************************************************************************************|
|* Compilado e funcionando com C++11.                                                     |
|* Utilizar este arquivo como entrega de trabalho na disciplina eh por sua conta e risco. |
|*****************************************************************************************/
#include "Elemento.hpp"
#include <functional>
#include <stdexcept>
#include <stdio.h>

template <typename T>

/**
 * Classe lista encadeada.
 * Implementacao da classe lista encadeada.
 * OBS.: Utilizei documentacao padrao do JavaDoc
 */
class ListaEnc {
private:
  Elemento<T> *head; /// Indica onde esta a cabeca da lista (onde comeca)
  int size;          /// Define o tamanho da lista

public:
  /**
   * Construtor.
   * Inicializa os atributos da classe definidos em private.
   */
  ListaEnc() {
    size = 0;
    head = NULL;
  }
  /**
   * Destrutor.
   *
   * @see 	destroiLista().
   */
  ~ListaEnc() { destroiLista(); }
  /**
   * Operator overload. Serve para retornar um valor em uma posicao especifica utilizando o operador
   * []. Ex.: lista[9].
   *
   * @see getElemento().
   * @param posicao Tipo int.
   * @return getElemento() Tipo T.
   */
  Elemento<T> *operator[](int posicao) { return getElemento(posicao); }
  /**
   * Retorna o tamanho da lista.
   *
   * @return size Tipo int.
   */
  int getSize() { return size; }
  /**
   * Pegar o valor de head. Primeiro elemento da lista.
   *
   * @return head 	Tipo Elemento<T>*.
   */
  Elemento<T> *getHead() { return head; }
  /**
   * Pega um elemento em posicao especifica na lista.
   *
   * @param pos 	Tipo int.
   * @return head 	Tipo Elemento<T>*.
   */
  Elemento<T> *getElemento(int pos) {
    if (pos >= size || pos < 0)
      throw std::out_of_range("Posicao invalida");

    Elemento<T> *verifica = head;
    for (int i = 0; i != pos; ++i)
      verifica = verifica->getProximo();

    return verifica;
  }
  /**
   * Insere um dado no inicio da lista.
   *
   * @param dado 	Tipo T&, que eh o dado a ser inserido.
   */
  void adicionaNoInicio(const T &dado) {
    Elemento<T> *novo = new Elemento<T>(dado, head);
    if (novo == NULL)
      throw std::invalid_argument("Erro ao criar objeto // adicionaNoInicio()");

    head = novo;
    size += 1;
  }
  /**
   * Remove um dado do inicio.
   *
   * @return volta 	Tipo T, que eh valor do dado removido.
   */
  T retiraDoInicio() {
    if (listaVazia())
      throw std::invalid_argument("A lista esta vazia // retiraDoInicio()");

    Elemento<T> *saiu = head;
    T volta = saiu->getInfo();
    head = saiu->getProximo();
    size -= 1;
    delete saiu;
    return volta;
  }
  /**
   * Elimina o dado do inicio.
   **/
  void eliminaDoInicio() {
    if (listaVazia())
      throw std::invalid_argument("A lista esta vazia // retiraDoInicio()");

    Elemento<T> *saiu = head;
    head = saiu->getProximo();
    size -= 1;
    delete saiu;
  }
  /**
   * Insere um dado em uma posicao especifica.
   *
   * @param dado 	Tipo T&, eh o dado a ser inserido.
   * @param pos 	Tipo inteiro, eh a posicao a ser inserida.
   */
  void adicionaNaPosicao(const T &dado, int pos) {
    if (pos > size || pos < 0)
      throw std::out_of_range("Posicao invalida // adicionaNaPosicao()");

    if (pos == 0)
      return adicionaNoInicio(dado);

    Elemento<T> *anterior = getElemento(pos - 1);

    Elemento<T> *novo = new Elemento<T>(dado, anterior->getProximo());
    anterior->setProximo(novo);
    size += 1;
  }
  /**
   * Indica a posicao em que se encontra o dado X. Se nao encontrado retorna size.
   *
   * @see size
   * @param dado 	Tipo T&, eh o dado que precisa ser achado.
   * @return i 	Tipo int, valor da posicao.
   */
  int posicao(const T &dado) const {
    Elemento<T> *verifica = head;

    int i = 0;
    for (i; i < size && verifica->getInfo() != dado; ++i)
      verifica = verifica->getProximo();

    return i;
  }
  /**
   * Indica o endereco de memoria que se encontra o dado. Retorna NULL se nada encontrado
   *
   * @param dado 				Tipo T&, que eh o dado a ser achado.
   * @return verifica->info	Tipo T*, pointer onde se localiza o dado na memoria.
   */
  T *posicaoMem(const T &dado) const {
    Elemento<T> *verifica = head;
    for (int i = 0; i < size && verifica->getInfo() != dado; ++i)
      verifica = verifica->getProximo();

    if (verifica == NULL)
      return NULL;

    return verifica->info;
  }
  /**
   * Verifica se o dado existe na lista.
   *
   * @param dado 		Tipo T&, eh o dado a ser verificado se existe.
   * @return boolean	TRUE se existe e FALSE se nao existe.
   */
  bool contem(const T &dado) {
    Elemento<T> *verifica = head;

    for (int i = 0; i < size && dado != verifica->getInfo(); ++i)
      verifica = verifica->getProximo();

    return verifica != NULL;
  }
  /**
   * Remove um dado de uma posicao especifica.
   *
   * @param pos		Tipo int, eh a posicao a ser removida.
   * @return volta		Tipo T, eh a informacao que foi removida.
   */
  T retiraDaPosicao(int pos) {
    if (listaVazia())
      throw std::invalid_argument("Lista vazia // retiraDaPosicao()");

    if (pos >= size || pos < 0)
      throw std::out_of_range("posicao errada // retiraDaPosicao()");

    if (pos == 0)
      return retiraDoInicio();

    Elemento<T> *anterior = getElemento(pos - 1);

    Elemento<T> *eliminar = anterior->getProximo();
    T volta = eliminar->getInfo();
    anterior->setProximo(eliminar->getProximo());
    size -= 1;
    delete eliminar;
    return volta;
  }
  /**
  * Insere um dado no final da lista.
  *
  * @see adicionaNaPosicao(const T& dado, int pos).
  * @var size 	Tipo int, eh passado o size para inserir \n
                                  no final da lista (imagine um array).
  * @param dado	Tipo T&, eh o dado a ser inserido.
  */
  void adiciona(const T &dado) { adicionaNaPosicao(dado, size); }
  /**
   * Remove um dado do final da lista.
   *
   * @see retiraDaPosicao(int pos).
   * @var size - 1 	eh passado pois remove o elemento da posicao \n
   * 					anterior ao tamanho total (imagine um array).
   * @return @see retiraDaPosicao(size - 1).
   */
  T retira() {
    if (listaVazia())
      throw std::invalid_argument("A lista esta vazia // retira()");

    return retiraDaPosicao(size - 1);
  }
  /**
   * Remove um dado especifico.
   *
   * Utiliza-se os metodos ja criados retiraDaPosicao()¹ e \n
   * posicao()² para reaproveitar o codigo e fazer a mesma funcao \n
   * entao passa-se o metodo² como parametro para o metodo¹ e passa \n
   * dado como parametro do metodo¹.
   *
   * @param dado 	Tipo T&, eh o dado a ser removido.
   * @see retiraDaPosicao(int pos).
   * @see posicao(const T& dado).
   */
  T retiraEspecifico(const T &dado) { return retiraDaPosicao(posicao(dado)); }
  /**
   * Insere os dados de acordo com uma funcao booleana que receba dois argumentos do Tipo T.
   *
   * @param data	Tipo T&, eh o dado a ser inserido.
   * @see listaVazia().
   * @see adicionaNaPosicao(const T& dado, int pos).
   */
  void adicionaEmOrdem(const T &data, std::function<bool(T, T)> f) {
    if (listaVazia())
      return adicionaNoInicio(data);

    Elemento<T> *atual = head;

    int posicao = 0;
    for (posicao; posicao < size; ++posicao, atual = atual->getProximo())
      if (!f(data, atual->getInfo()))
        break;

    adicionaNaPosicao(data, posicao);
  }
  /**
   * Chama a funcao gemea utilizando a funcao maior() como parametro. (Essa funcao eh utilizada como
   * padrao caso apenas um argumento eh passado)
   *
   * @param data	Tipo T&, eh o dado a ser inserido.
   * @see listaVazia().
   * @see maior(T dado1, T dado2).
   * @see adicionaNaPosicao(const T& dado, int pos).
   */
  void adicionaEmOrdem(const T &data) { adicionaEmOrdem(data, &maior); }
  /**
   * Verifica se a lista esta vazia.
   *
   * @return boolean	TRUE para vazia e FALSE para nao vazia.
   */
  bool listaVazia() const { return size == 0; }
  /**
   * Verifica se os dados sao iguais.
   *
   * @return boolean	TRUE para igual e FALSE para diferente.
   * @param dado1 		Tipo T, primeiro dado a ser verificado.
   * @param dado2 		Tipo T, segundo dado a ser verificado.
   */
  bool igual(T dado1, T dado2) { return dado1 == dado2; }
  /**
   * Verifica se o dado1 eh maior que dado2.
   *
   * @return boolean	TRUE para maior e FALSE para menor.
   * @param dado1 		Tipo T, primeiro dado a ser verificado.
   * @param dado2 		Tipo T, segundo dado a ser verificado.
   */
  bool maior(T dado1, T dado2) { return dado1 > dado2; }
  /**
   * Verifica se o dado1 eh menor que dado2.
   *
   * @return boolean	TRUE para menor e FALSE para maior.
   * @param dado1 		Tipo T, primeiro dado a ser verificado.
   * @param dado2 		Tipo T, segundo dado a ser verificado.
   */
  bool menor(T dado1, T dado2) { return dado1 < dado2; }
  /**
   * Destroi a lista, limpando todos os elementos nela contida.
   *
   * Enquanto a lista nao esta vazia ele faz recursivamente \n
   * a limpeza da lista chamando o metodo eliminaDoInicio().
   *
   * @see eliminaDoInicio().
   * @see listaVazia().
   */
  void destroiLista() {
    while (!listaVazia())
      eliminaDoInicio();
  }
};
