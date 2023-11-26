#ifndef USUARIO_H
#define USUARIO_H

#include <string.h>

#define tamanhoNome 50 //Tamanho da string que guarda os nomes de usu�rio
#define tamanhoSenha 50

/**
*Esta classe � respons�vel por guardar informa��es de usu�rio da aplica��o, e tamb�m pelos m�todos de altera��es destas (getters e setters), ela � manipulada pelo manipuladoDeUsu�rio
*/
class Usuario {
public:
    int getId() const;
    char* getSenha() const;
    char* getNome() const;
    void setNome(char nome[]);
    void setSenha(char senha[]);
    void setId(int novoId);
    void limpaUsuario(); // Limpa todas as informa��es do usuario
    bool existe(); // Retorna se o objeto usuario est� vazio ou n�o

    Usuario();

    int numeroSeguidores = 0;
    int numeroSeguindo = 0;
private:
    int id;
    char nome[tamanhoNome];
    char senha[tamanhoSenha];
};

#endif // USUARIO_H
