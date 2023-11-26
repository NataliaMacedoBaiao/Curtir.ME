#ifndef COMENTARIO_H
#define COMENTARIO_H

#define tamanhoTextoComentarios 201
#define tamanhoNome 50

/**
*Esta classe � respons�vel por guardar informa��es de um coment�rio da aplica��o, e tamb�m pelos m�todos de altera��es destas (getters e setters), ela � manipulada pelo manipuladorDeComentario
*/

class Comentario
{
    public:
        int GetIDusuario();
        void SetIDusuario(int val);
        int GetnumeroComentario();
        void SetnumeroComentario(int val);
        char* Getconteudo();
        void Setconteudo(char conteudo[]);
        void SetnomeUsuario(char nomeUsuario[]);
        char* GetnomeUsuario();
        int GetIDpostagem();
        void SetIDpostagem(int val);
        Comentario(int ID,char nomeUsuario[], int IDpostagem, int numeroC, char conteudo[]);
        Comentario();
        bool existe();

    private:
        int IDusuario;
        char nomeUsuario[tamanhoNome];
        int numeroComentario;
        int IDpostagem;
        char conteudo[tamanhoTextoComentarios];
};

#endif // COMENTARIO_H
