#include "manipuladorDePostagem.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos M�todos da Classe manipuladorDePostagem                           */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*@brief M�todo que cria todos os documentos nescessarios para o funcionamento das postagens
*Est� fun��o t�m como objetivo abrir 2 arquivos bin�rios importantes para a aplica��o sendo eles o arquivo numeroDePostagensCadastradas.bin (Det�m o numero de postagens da aplica��o)
* e o outro sendo postagens.bin (Guarda as postagens da aplica��o).
*/
void manipuladorDePostagem::criaArquivosNescessarios(){
    //Arquivo de numero de postagens cadastrados
    ifstream ifs("Arquivos/numeroDePostagensCadastradas.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de postagens.");
            return;
        }
        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        cout << "Arquivo de Numero De Postagens criado\n";
        arquivo.close();
    }


    //Arquivo de Postagens
    ifstream ifs3("Arquivos/postagens.bin");
    if (!ifs3) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/postagens.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de postagens.");
            return;
        }
        cout << "Arquivo de Postagens criado\n";
        arquivo.close();
    }
}

/**@brief M�todo que exibe no console todas as postagens dos seguidos do usu�rio
*Este m�todo abre o arquivo de postagens e analisa se o usu�rio cujo o id � igual ao recebido segue, se segue a postagem encontrada � exibida no console, ele se relaciona com a classe manipuladorDeUsuario
* e manipuladorDeComentario.
*@param idUsuarioAtual recebe o id do usu�rio cujo o feed de seguidores deve ser baseado
*/
void manipuladorDePostagem::mostrarFeedDosSeguidos(int idUsuarioAtual){
    int numeroDePrints = 0;
    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if(mUsuario.segue(idUsuarioAtual, post.GetIDusuario()) && !post.Getapagada()){ //Se o usuario segue ao postador e se a postagem n�o foi apagada

                cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
                cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;
                cout << "       " << post.Getconteudo()<< endl;
                cout << "       " << post.Getcurtidas() << "    ";

                if(post.Getcurtidas() == 1){
                    cout <<"Curtida"<< endl;
                }else{
                    cout <<"Curtidas"<< endl;

                }
                cout << "\n         ...............................................................................................................\n";

                cout << "\n\n           Coment�rios: " << endl;
                mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), 2);

                cout << "\n         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";
                numeroDePrints++;
            }
        }
        if(numeroDePrints == 0){
            cout << "\n\n           Sem postagens para exibir :( , tente seguir mais usu�rios para ver postagens!\n\n";
        }
    }

}

/**@brief M�todo que exibe no console todas as postagens do sistema independente de hashtag ou de seguidores come�ando da mais antiga at� a mais atual
*Este m�todo abre o arquivo de postagens e percorre exibindo cada postagem no console, ele se relaciona com a classe manipuladorDeUsuario
* e manipuladorDeComentario. S�o exibidos 2 coment�rios por postagem.
*/
void manipuladorDePostagem::mostrarFeed(){

    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if(!post.Getapagada()){ //Se a postagem n�o est� apagada
                cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
                cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;

                post.hashtag.Getexiste() ? cout << "       " << post.hashtag.Gethashtag() << endl : cout << "";

                cout << "       Conte�do: " << post.Getconteudo()<< endl;
                cout << "       " << post.Getcurtidas() << "    ";

                if(post.Getcurtidas() == 1){
                    cout <<"Curtida"<< endl;
                }else{
                    cout <<"Curtidas"<< endl;

                }
                cout << "\n         ...............................................................................................................\n";

                cout << "\n\n           Coment�rios: " << endl;
                mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), 2);

                cout << "\n         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";

            }
        }
    }

}

/**@brief M�todo que exibe no console todas as postagens com a hashtag recebida
*Este m�todo abre o arquivo de postagens e analisa se a postagem  det�m uma hashtag igual a recebida, se sim a postagem encontrada � exibida no console, ele se relaciona com a classe manipuladorDeUsuario
* e manipuladorDeComentario, s�o exibidos 2 coment�rios por postagem.
*@param hashtag recebe um vetor de caracteres que det�m a hashtag procurada
*/
void manipuladorDePostagem::mostrarFeedPorHashtag(char hashtag[]){

    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if(post.hashtag.Getexiste() && strcmp(post.hashtag.Gethashtag(),hashtag) == 0 && !post.Getapagada()){ //Se t�m uma hashtag, se a hashtag recebida e a do post batem e a postagem n�o esta apagada

                cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
                cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;

                post.hashtag.Getexiste() ? cout << "       " << post.hashtag.Gethashtag() << endl : cout << "";

                cout << "       Conte�do: " << post.Getconteudo()<< endl;
                cout << "       " << post.Getcurtidas() << "    ";

                if(post.Getcurtidas() == 1){
                    cout <<"Curtida"<< endl;
                }else{
                    cout <<"Curtidas"<< endl;

                }
                cout << "\n         ...............................................................................................................\n";

                cout << "\n\n           Coment�rios: " << endl;
                mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), 2);

                cout << "\n         :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n\n";

            }
        }
    }

}

/**@brief M�todo que exibe no console uma postagem determinada com todos seus coment�rios
*Este m�todo abre o arquivo de postagens e analisa se a postagem  det�m o numero de postagem igual a recebida, se sim a postagem encontrada � exibida no console, ele se relaciona com a classe manipuladorDeUsuario
* e manipuladorDeComentario, neste caso todos os comet�rios s�o exibidos.
*@param numeroDaPostagem recebe um inteiro, que referencia ao numero da postagem procurada
*/
void manipuladorDePostagem::detalhar(int numeroPostagem){

    manipuladorDeUsuario mUsuario;
    manipuladorDeComentario mComentario;

    ifstream arquivo("Arquivos/postagens.bin", ios::binary);
    Postagem post;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if(post.GetnumeroPostagem() == numeroPostagem){
                cout << "\n         ...............................................................................................................\n";

                cout << "\n       Id da postagem: " << post.GetnumeroPostagem();
                cout << "  ||  Postado por: "<< mUsuario.procuraUsuarioId(post.GetIDusuario()).getNome() << endl;
                cout << "       " << post.Getconteudo()<< endl;
                cout << "       " << post.Getcurtidas() << "    ";

                if(post.Getcurtidas() == 1){
                    cout <<"Curtida"<< endl;
                }else{
                    cout <<"Curtidas"<< endl;

                }
                cout << "\n\n           Coment�rios: " << endl;
                mComentario.exibirComentariosPorId(post.GetnumeroPostagem(), mostrarTodos);

                cout << "\n         ...............................................................................................................\n\n";
            }

        }
    }

}

/**@brief M�todo que adiciona uma postagem no arquivo bin�rio de postagens
*Este m�todo recebe uma postagem, abre o arquivo de postagens e adiciona a postagem  recebida na ultima posi��o do arquivo
*@param post recebe um objeto do tipo Postagem
*@return valor booleano, retorna true caso tenha sido adicionado com sucesso e false se n�o
*/
bool manipuladorDePostagem::adicionaAoArquivo(Postagem post){
    ofstream arquivo("Arquivos/postagens.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }

    this->aumentarNumeroDePostagens();
    post.SetnumeroPostagem(this->numeroDePostagens());

    arquivo.write((char*)&post, sizeof(Postagem));
    arquivo.close();

    cout << "Postagem cadastrada com sucesso." << endl;

    return true;
}

/**@brief M�todo que verifica se uma postagem com o id recebido como argumento � de quem t�m o id recebido como argumento
*Este m�todo recebe um id de usu�rio e um numero de postagem, abre o arquivo de postagens e procura a postagem recebida, se a postagem recebida for do id de usu�rio recebido returna true sen�o false
*@param idUsuario recebe um int que referencia a um id de usuario
*@param numeroPostagem recebe um int que referencia a um numero de postagem
*@return Um valor booleano, se postagem for do id recebido true, caso contr�rio falso
*/
bool manipuladorDePostagem::ehMinhaPostagem(int idUsuario, int numeroPostagem){
    Postagem post = this->buscaPostagem(numeroPostagem);

    if(post.GetIDusuario() == idUsuario){
        return true;
    }else{
        return false;
    }
}

/**@brief M�todo que retorna o numero de postagens
*Este m�todo abre o arquivo numeroDePostagensCadastradas.bin faz a leitura e retorna o numero de postagens no sistema
*@return Valor Int com o numero de postagens
*/
int manipuladorDePostagem::numeroDePostagens(){
    ifstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo.");
        return -1;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
    }
    return numero;
}

/**@brief M�todo que apaga uma postagem do sistema
*Este m�todo abre o arquivo busca uma postagem atraves do numero de postagem e a muda para apagada, uma vez apagada n�o � possivel recuperar por�m ela n�o sai do sistema
*@param numeroPostagem Int
*@return booleano true se foi apagada com sucesso e false se n�o
*/
bool manipuladorDePostagem::apagarPostagem(int numeroPostagem){
    Postagem post = this->buscaPostagem(numeroPostagem);
    if(post.existe()){
        post.Setapagada(true);
        this->salvaPostagem(post);
        return true;
    }

    return false;
}

/**@brief M�todo que aumenta o numero de postagens no sistema
*Este m�todo abre o arquivo numeroDePostagensCadastradas.bin faz a leitura soma mais um e substitui no arquivo
*@see numeroDePostagens()
*@return valor booleano, true se foi adicionado com sucesso e false se n�o foi
*/
bool manipuladorDePostagem::aumentarNumeroDePostagens(){
    int numero = this->numeroDePostagens();

    ofstream arquivo("Arquivos/numeroDePostagensCadastradas.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }

    limparArquivoBinario("Arquivos/numeroDePostagensCadastradas.bin");

    numero++;
    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return true;
}

/**@brief M�todo que salva uma postagem com altera��es no arquivo
*Este m�todo t�m como objetivo salvar uma postagem j� existente, mas que foi alterada no funcionamento da aplica��o, ela recebe um objeto do tipo postagem
*Porcura um objeto com o mesmo numero de postagem e substitui ele no arquivo.
*@param post do tipo Postagem
*@return valor booleano, true se foi substituido com sucesso e false se n�o foi
*/
bool manipuladorDePostagem::salvaPostagem(Postagem post){
    fstream arquivo("Arquivos/postagens.bin", ios::binary | std::ios::in | std::ios::out);
    Postagem postAux;
    int i = 0;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de postagens.");
        return false;
    }else{

        while (arquivo.read((char*)&postAux, sizeof(Postagem))) {
            if (postAux.GetnumeroPostagem() == post.GetnumeroPostagem()) {
                break;
            }
            i++;
        }

    }

    arquivo.seekg(i*sizeof(Postagem), ios_base::beg);
    arquivo.write((char*)&post, sizeof(Postagem));
    arquivo.close();
    return true;
}

/**@brief M�todo que aumenta uma curtida em uma postagem recebida
*Este m�todo recebe uma postagem e adiciona uma curtida nela e depois a salva com as modifica��es no arquivo
*@param post do tipo Postagem
*@return valor booleano, true se foi adicionado com sucesso e false se n�o foi
*/
bool manipuladorDePostagem::adicionaCurtida(Postagem post){
    post.Setcurtidas(post.Getcurtidas()+1);
    this->salvaPostagem(post);
    return true;
}

/**@brief M�todo que recebe um numero de postagem e retorna a postagem contida no arquivo
*Este m�todo recebe um numero de postagem, percorre o arquivo de postagem procurando alguma postagem que tenha o numero de postagem recebido como argumento se encontrado retorna a postagem
*@param id int numero de postagem
*@return valor booleano, true se foi adicionado com sucesso e false se n�o foi
*/
Postagem manipuladorDePostagem::buscaPostagem(int numeroPostagem){
    ifstream arquivo("Arquivos/postagens.bin", ios::binary | std::ios::in);
    Postagem post;
    Postagem vazio;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
        return vazio;
    }else{

        while (arquivo.read((char*)&post, sizeof(Postagem))) {
            if (post.GetnumeroPostagem() == numeroPostagem) {
                arquivo.close();
                return post;
            }
        }
    }

    arquivo.close();
    return vazio;
}
