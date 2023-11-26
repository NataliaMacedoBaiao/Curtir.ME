#ifndef MANIPULADORDECOMENTARIO_H
#define MANIPULADORDECOMENTARIO_H

#include "manipuladorDeUsuario.h"
#include "Comentario.h"
#include "Arquivo.h"

#define mostrarTodos -1 // Utilizado no metodo exibirComentariosPorId()

/**
*Est� Classe � respons�vel por Manipular todos os documentos nescess�rios para o funcionamento dos coment�rios e processos de arquivo relacionados a classe Comentario, sendo adicionar coment�rio, printaComentario,e etc. Para isto nela s�o implemantados m�todos importantes para a aplica��o.
*/

class manipuladorDeComentario
{
    public:
        manipuladorDeComentario();
        void criaArquivosNescessarios();
        bool adicionaAoArquivo(Comentario coment);
        void printaComentario(Comentario coment);
        void exibirComentariosPorId(int idPost, int quantidade);


    private:
};

#endif // MANIPULADORDECOMENTARIO_H
