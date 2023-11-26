#include "Usuario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe Usuario                                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*@brief Retorna uma copia do id do objeto do tipo Usu�rio
*@return inteiro
*/
int Usuario::getId() const {
    return id;
}

/**
*@brief Retorna uma copia da senha do objeto do tipo Usu�rio
**@return ponteiro do tipo char
*/
char* Usuario::getSenha() const {
    int tamanho = strlen(senha);
    char* copia = new char[tamanho + 1];
    strcpy(copia, senha);
    return copia;
}

/**
*@brief Retorna uma copia do nome do objeto do tipo Usu�rio
*@return ponteiro do tipo char
*/
char* Usuario::getNome() const {
    int tamanho = strlen(nome);
    char* copia = new char[tamanho + 1];
    strcpy(copia, nome);
    return copia;
}

/**
*@brief Altera o nome de usu�rio do objeto
*@param nome Vetor de caracteres
*/
void Usuario::setNome(char nome[]) {
    strcpy(this->nome, nome);
}

/**
*@brief Altera a senha de usu�rio do objeto
*@param senha Vetor de caracteres
*/
void Usuario::setSenha(char senha[]) {
    strcpy(this->senha, senha);
}

/**
*@brief Altera o id de usu�rio do objeto
*@param novoId inteiro
*/
void Usuario::setId(int novoId){
    this->id = novoId;
}

/**
*@brief Contrutor vazio do objeto
*Este construtor inicia o objeto totalmente zerado
*/
Usuario::Usuario(){
    strcpy(this->nome, "");
    strcpy(this->senha, "");
    this->setId(0);
}

/**
*@brief Este m�todo verifica se o objeto Usuario esta vazio
*Este m�todo verifica se o nome e senha est�o vazios se sim retorna false se n�o true
*@return true se existe e false se n�o
*/
bool Usuario::existe()
{
    return strcmp(this->getNome(), "") == 0 || strcmp(this->getSenha(), "") == 0 ?  false : true;
}

/**
*@brief Este m�todo zera o objeto
*Este m�todo limpa todos os atributos da classe
*/
void Usuario::limpaUsuario()
{
    this->id = 0;
    strcpy(this->nome, "");
    strcpy(this->senha, "");
    this->numeroSeguidores = 0;
    this->numeroSeguindo = 0;
}
