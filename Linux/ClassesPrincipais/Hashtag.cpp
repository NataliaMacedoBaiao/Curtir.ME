#include "Hashtag.h"
#include <cstring>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe Hashtag                                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*M�todos para manipula��o de arquivos*/

/**
*@brief M�todo que cria todos os documentos nescessarios para o funcionamento da classe Hashtags
*Est� fun��o t�m como objetivo abrir o arquivo bin�rio (hashtags.bin) importante para a aplica��o, pois guarda todas as hashtgas utilizadas no aplicativo.
*@return Valor booleano, retorna true caso tenha sido criado com sucesso e false se n�o
*/
bool Hashtag::criaArquivosNescessarios(){
    ifstream ifs("Arquivos/hashtags.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de hashtags.");
            return false;
        }
        cout << "Arquivo de  hashtags criado\n";
        arquivo.close();
    }
    return true;
}

/**
*@brief M�todo que adiciona uma hashtag no sistema, guardando suas informa��es no arquivo hashtags.bin
*Este m�todo recebe uma hashtag e adiciona no arquivo hashtags.bin
*@param hashtag Objeto do tipo Hashtag
*@return Valor booleano, retorna true caso tenha sido adicionado com sucesso e false se n�o
*/
bool Hashtag::adicionaHashtagArquivo(Hashtag hashtag){
        ofstream arquivo("Arquivos/hashtags.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao abrir o arquivo de hashtags.");
            return false;
        }
        arquivo.write((char*)&hashtag, sizeof(Hashtag));
        arquivo.close();
        return true;
}

/**
*@brief M�todo que verifica a existencia de uma hashtag no sistema
*Este m�todo recebe uma hashtag e percorre o arquivo a procura de uma hashtag com o mesmo conte�do se encontrado retorna true e sen�o false
*@param hashtag Objeto do tipo Hashtag
*@return Valor booleano, retorna true caso tenha sido encontrado com sucesso e false se n�o
*/
bool Hashtag::verificaExistencia(Hashtag hashtag){
    ifstream arquivo("Arquivos/hashtags.bin", ios::binary);
    Hashtag aux;
    bool encontrado = false;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de hashtags.");
    }else{
        while (arquivo.read((char*)&aux, sizeof(Hashtag))) {
            if(strcmp(aux.Gethashtag(), hashtag.Gethashtag()) == 0){
                cout << "Encontrado";
                encontrado = true;
            }
        }
    }
    return encontrado;
}
/*M�todos para manipula��o de arquivos*/



/*M�todos para manipula��o da hashtag*/

/**
*@brief M�todo que verifica o formato de uma hashtag
*Este m�todo recebe um texto e verifica se est� em um formato v�lido de hashtag, sendo que para estar no formato correto deve come�ar com '#'
*@param hashtag vetor de caracteres
*@return Valor booleano, retorna true caso tenha sido verificado com sucesso e false se n�o
*/
bool Hashtag::verificaFormato(char hashtag[]){
    if(hashtag[0] == '#'){
        return true;
    }
    return false;
}

/**
*@brief Altera o valor DO conteudo da hashtag
*@param Hashtag ponteiro do tipo char
*/
void Hashtag::Sethashtag(char* Hashtag){
    strcpy( this->hashtag, Hashtag);
}

/**
*@brief retorna o valor do conteudo da hashtag
*@return ponteiro do tipo caractere
*/
char* Hashtag::Gethashtag(){
    return this->hashtag;
}

/**
*@brief Muda o valor de existe da hashtag
*@param valor booleano
*/
void Hashtag::Setexiste(bool valor){
    this->existe = valor;
}

/**
*@brief Este m�todo retorna o valor de existe do objeto
*Este m�todo retorna o valor de existe da hashtag
*@return true se existe e false se n�o
*/
bool Hashtag::Getexiste(){
    return this->existe;
}

Hashtag::Hashtag()
{
}

/**
*@brief Contrutor do objeto
*Este construtor inicia o objeto j� setando o valor da hashtag
*@param hashtag vetor de caracteres
*/
Hashtag::Hashtag(char hashtag[])
{
    this->Sethashtag(hashtag);
    this->Setexiste(true);
}
/*M�todos para manipula��o da hashtag*/
