#ifndef MANIPULADORDEPOSTAGEM_H
#define MANIPULADORDEPOSTAGEM_H

#include "Postagem.h"
#include "Arquivo.h"
#include "manipuladorDeUsuario.h"
#include "manipuladorDeComentario.h"

/**
*Est� Classe � respons�vel por Manipular todos os documentos nescess�rios para o funcionamento das postagens e processos de arquivo relacionados a classe Postagem, para isto nela s�o implemantados m�todos importantes para a aplica��o.
*/

class manipuladorDePostagem
{
    public:
        void criaArquivosNescessarios();
        void mostrarFeed();
        void mostrarFeedDosSeguidos(int idUsuarioAtual);
        void mostrarFeedPorHashtag(char hashtag[]);
        bool adicionaAoArquivo(Postagem post);
        bool aumentarNumeroDePostagens();
        bool ehMinhaPostagem(int idUsuario, int numeroPostagem);
        bool apagarPostagem(int numeroPostagem);
        int numeroDePostagens();
        bool salvaPostagem(Postagem post);
        Postagem buscaPostagem(int numeroPostagem);
        bool adicionaCurtida(Postagem post);
        void detalhar(int numeroPostagem);

    private:
};


#endif // MANIPULADORDEPOSTAGEM_H
