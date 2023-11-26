#ifndef HASHTAG_H
#define HASHTAG_H

#define tamanhoHashtag 51

#include "Arquivo.h"
#include <fstream>
#include <iostream>

/**
*Esta classe � respons�vel por guardar informa��es de uma Hashtag da aplica��o, e tamb�m pelos m�todos de altera��es destas (getters e setters)o
*/

class Hashtag
{
    public:
        Hashtag();
        bool criaArquivosNescessarios();
        bool adicionaHashtagArquivo(Hashtag hashtag);
        bool verificaExistencia(Hashtag hashtag);

        char* Gethashtag();
        void Sethashtag(char* Hashtag);
        bool verificaFormato(char* Hashtag);
        void Setexiste(bool valor);
        bool Getexiste();

    private:
        char hashtag[tamanhoHashtag];
        bool existe = false; //Fala se t�m uma hashtag ou n�o
};


#endif // HASHTAG_H
