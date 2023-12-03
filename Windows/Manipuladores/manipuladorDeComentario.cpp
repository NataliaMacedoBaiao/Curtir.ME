#include "manipuladorDeComentario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe manipuladorDeComentario                         */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**
*@brief M�todo que cria todos os documentos nescessarios para o funcionamento da classe manipuladorDeComentario
*Est� fun��o t�m como objetivo abrir o arquivo bin�rios (comentarios.bin) importante para a aplica��o. Este Documento guarda todos os coment�rios existentes na aplica��o.
*/
void manipuladorDeComentario::criaArquivosNescessarios(){

    //Arquivos de comentarios
    ifstream ifs2("Arquivos/comentarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de coment�rios.");

            return;
        }
        cout << "Arquivo de coment�rios criado\n";
        arquivo.close();
    }
}

/**@brief M�todo que adiciona um coment�rio no arquivo bin�rio comentarios.bin
*Este m�todo recebe um coment�rio, abre o arquivo de comentarios e adiciona o coment�rio recebido na ultima posi��o do arquivo.
*@param coment recebe um objeto do tipo Comentario
*@return Valor booleano, retorna true caso tenha sido adicionado com sucesso e false se n�o
*/
bool manipuladorDeComentario::adicionaAoArquivo(Comentario coment){
    ofstream arquivo("Arquivos/comentarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de comentarios.");
        return false;
    }

    arquivo.write((char*)&coment, sizeof(Comentario));
    arquivo.close();

    cout << "Coment�rio adicionado." << endl;

    return true;
}

/**@brief M�todo que exibe coment�rios por id de uma postagem
*Este m�todo recebe um id, abre o arquivo de coment�rios e percorre verificando se os id's de postagens batem, se sim ele exibe os coment�rios sem ultrapassar o limite do argumento quantidade,
*caso a quantidade seja -1 ele mostra todos os coment�rios
*@param idPost valor inteiro
*@param quantidade valor inteiro
*/
void manipuladorDeComentario::exibirComentariosPorId(int idPost, int quantidade){
    int i = 0;
    ifstream arquivo("Arquivos/comentarios.bin", ios::binary);
    Comentario coment;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de coment�rios.");
    }else{

        while (arquivo.read((char*)&coment, sizeof(Comentario))) {
            if(quantidade != mostrarTodos){
                if(coment.GetIDpostagem() == idPost && i < quantidade){
                    this->printaComentario(coment);
                    i++;
                }
            }else{
                if(coment.GetIDpostagem() == idPost){
                    this->printaComentario(coment);
                    i++;
                }
            }

        }
    }

    if(i == 0){
        cout << "\n                 Nenhum coment�rio!\n" << endl;
    }

}

/**@brief M�todo que exibe um coment�rio
*Este m�todo recebe um coment�rio, e exibe ele em um formato especial para coment�rios, de modo que diferencie da postagem
*@param coment recebe um objeto do tipo Comentario
*/
void manipuladorDeComentario::printaComentario(Comentario coment){

        cout <<   "\n\n             | - ";
        cout << coment.Getconteudo() << endl;
        cout << "\n               Comentado por "<<  coment.GetnomeUsuario() << endl;
        cout <<   "\n             L \n";
}

 manipuladorDeComentario::manipuladorDeComentario(){
 }
