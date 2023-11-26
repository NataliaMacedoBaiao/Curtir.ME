#include "Comentario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe Coment�rio                                      */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Getters e Setters

/**
*@brief Retorna uma copia do IDusuario do objeto do tipo Comentario
*@return inteiro
*/
int Comentario::GetIDusuario() {
    return IDusuario;
}

/**
*@brief Altera o Idusuario do objetodo tipo Comentario
*@param val inteiro
*/
void Comentario::SetIDusuario(int val) {
    this->IDusuario = val;
}

/**
*@brief Retorna uma copia do numeroComentario do objeto do tipo Comentario
*@return inteiro
*/
int Comentario::GetnumeroComentario() {
    return numeroComentario;
}

/**
*@brief Altera o numeroComentario do objeto do tipo Comentario
*@param val inteiro
*/
void Comentario::SetnumeroComentario(int val) {
    this->numeroComentario = val;
}

/**
*@brief retorna o valor do conteudo do objeto do tipo Comentario
*@return ponteiro do tipo caractere
*/
char* Comentario::Getconteudo(){
    char * copia = new char[tamanhoTextoComentarios];
    strcpy(copia, this->conteudo);
    return copia;
}

/**
*@brief Altera o valor de conte�do do objeto do tipo Comentario
*@param conteudo vetor de caracteres
*/
void Comentario::Setconteudo(char conteudo[]){
    strcpy(this->conteudo, conteudo);
}

/**
*@brief Altera o valor do nomeUsuario do objeto do tipo Comentario
*@param nomeUsuario vetor de caracteres
*/
void Comentario::SetnomeUsuario(char nomeUsuario[]){
    strcpy(this->nomeUsuario, nomeUsuario);
}

/**
*@brief retorna o valor do nomeUsuario do objeto do tipo Comentario
*@return ponteiro do tipo caractere
*/
char* Comentario::GetnomeUsuario(){
    char * copia = new char[tamanhoNome];
    strcpy(copia, this->nomeUsuario);
    return copia;
}

/**
*@brief Retorna uma copia do IDpostagem do objeto do tipo Comentario
*@return inteiro
*/
int Comentario::GetIDpostagem() {
    return IDpostagem;
}

/**
*@brief Altera o valor de IDpostagem do objeto do tipo Comentario
*@param val inteiro
*/
void Comentario::SetIDpostagem(int val) {
    this->IDpostagem = val;
}

//Construtores
/**
*@brief Contrutor do objeto
*Este construtor inicia o objeto setando os valores de ID, nomeUsuario, IDpostagem, numeroC, conteudo
*@param ID inteiro
*@param IDpostagem inteiro
*@param numeroC inteiro
*@param conteudo vetor de caracteres
*@param nomeUsuario vetor de caracteres
*/
Comentario::Comentario(int ID,char nomeUsuario[], int IDpostagem, int numeroC, char conteudo[]){
    this->SetIDusuario(ID);
    this->SetnumeroComentario(numeroC);
    this->Setconteudo(conteudo);
    this->SetIDpostagem(IDpostagem);
    this->SetnomeUsuario(nomeUsuario);
}

/**
*@brief Contrutor vazio do objeto
*Este construtor inicia o objeto totalmente zerado
*/
Comentario::Comentario(){
    this->Setconteudo("");
    this->SetIDusuario(0);
    this->SetnumeroComentario(0);
    this->SetnomeUsuario("");
}

//Metodos complementares

/**
*@brief Este m�todo verifica se o objeto Comentario esta vazio
*Este m�todo verifica se o conteudo e numeroComentario est�o vazios se sim retorna false se n�o true
*@return true se existe e false se n�o
*/
bool Comentario::existe(){
    if(strcmp(this->Getconteudo(),"") == 0 && this->GetnumeroComentario() == 0){
        return false;
    }
    return true;
}
