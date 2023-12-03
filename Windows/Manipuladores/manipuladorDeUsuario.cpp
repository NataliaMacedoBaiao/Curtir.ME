#include "manipuladorDeUsuario.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*                                          Implementa��o dos Metodos da Classe manipuladorDeUsuario                            */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
*@brief M�todo que cria todos os documentos nescess�rios para o funcionamento dos usu�rios
*Este m�todo t�m como objetivo abrir 2 arquivos bin�rios importantes para a aplica��o sendo eles o arquivo numeroDeUsuariosCadastrados.bin (Det�m o numero de usuarios da aplica��o)
* e o outro sendo usuarios.bin (Guarda todos os usuarios da aplica��o).
*/
void manipuladorDeUsuario::criaArquivosNescessarios(){
    //Arquivo de numero de usuarios cadastrados
    ifstream ifs("Arquivos/numeroDeUsuariosCadastrados.bin");
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de usu�rios.");
            return;
        }

        int numeroInicial = 0;
        arquivo.write((char*)&numeroInicial, sizeof(int));
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }

    //Arquivos de usuarios
    ifstream ifs2("Arquivos/usuarios.bin");
    if (!ifs2) { //Verifica se Existe o Arquivo
        ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de usu�rios.");
            return;
        }
        cout << "Arquivo de usuario criado\n";
        arquivo.close();
    }
}


/*Parte de Usuarios*/

/**
*@brief M�todo que cadastra um usu�rio no sistema, guardando suas informa��es no arquivo usu�rios.bin
*Este m�todo recebe um nome e uma senha, cria um objeto de usu�rio adicionando as informa��es no objeto e salva no arquivo usuarios.bin
*@param nome Vetor de char's, recebe um nome de usuario
*@param senha Vetor de char's, recebe uma senha de usuario
*/
void manipuladorDeUsuario::cadastrarUsuario(char nome[], char senha[]) {
    ofstream arquivo("Arquivos/usuarios.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
        return;
    }

    Usuario usuario;

    usuario.setNome(nome); //Define o nome para o usuario
    usuario.setSenha(senha);
    usuario.setId(this->numeroDeUsuarios()+1); //Seta o id sendo o numero de usuarios mais 1

    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    const char* idUsuario = to_string(usuario.getId()).c_str();
    //Cria arquivo de seguidores para o novo usuario

    char parte1[] = "Arquivos/Seguidores/Seguidores#";
    char parte2[] = ".bin";
    char *nomeArquivo = strcat(strcat(parte1,idUsuario),parte2);

    ifstream ifs(nomeArquivo);
    if (!ifs) { //Verifica se Existe o Arquivo
        ofstream arquivo(nomeArquivo, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidores.");
            return;
        }
        arquivo.close();
    }



    char parte1b[] = "Arquivos/Seguidores/Segue#";
    char *nomeArquivo2 = strcat(strcat(parte1b,idUsuario),parte2);
    ifstream ifs2(nomeArquivo2);
    if (!ifs2) { //Verifica se Existe o Arquivo
        arquivo.open(nomeArquivo2, ios::binary | ios::app);
        if (!arquivo.is_open()) {
            geraExcecao("Erro ao criar o arquivo de numero de seguidos.");
            return;
        }
        cout << "Arquivo de seguidores criado.\n";
        arquivo.close();
    }


    cout << "Usu�rio cadastrado com sucesso." << endl;
    this->aumentarNumeroDeUsuarios();
}

/**
*@brief M�todo que autentica se um usu�rio e senha batem no sistema
*Este m�todo recebe um nome e uma senha, verifica no arquivo de usu�rios se existe um
* usu�rio que bate com o nome e a senha e retorna true se foi encontrado e autentificado, e false se n�o foi encontrado ou n�o foi autenticado
*@param nome Vetor de char's, recebe um nome de usuario
*@param senha Vetor de char's, recebe uma senha de usuario
*@return se o usu�rio foi autenticado ou n�o, true para sim e false para n�o
*/
bool manipuladorDeUsuario::autenticarUsuario(char nome[], char senha[]) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
        return false;
    }else{
        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0 && strcmp(usuario.getSenha(),senha) == 0) {
                usuarioAtual = usuario;
                arquivo.close();
                return true;
            }
        }
    }
    arquivo.close();

    return false;
}

/**@brief M�todo que retorna o numero de usu�rios
*Este m�todo abre o arquivo numeroDeUsuariosCadastrados.bin faz a leitura e retorna o numero de usu�rios no sistema
*@return retorna um valor Int com o numero de usu�rios no arquivo
*/
int manipuladorDeUsuario::numeroDeUsuarios(){
    ifstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary);
    int numero;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de numero de usu�rios.");
        return 0;
    }else{
        arquivo.read((char*)&numero, sizeof(int));
        arquivo.close();
        return numero;
    }
}

/**@brief M�todo que aumenta o numero de usu�rios no sistema
*Este m�todo abre o arquivo numeroDeUsuariosCadastrados.bin faz a leitura do numero de usu�rios, soma mais um no numero de usu�rios e substitui no arquivo
*@see numeroDeUsuarios()
*@return valor int, true se foi adicionado com sucesso e false se n�o foi
*/
bool manipuladorDeUsuario::aumentarNumeroDeUsuarios(){
    int numero = numeroDeUsuarios()+1;
    limparArquivoBinario("Arquivos/numeroDeUsuariosCadastrados.bin");
    //Aumenta numero de usuarios cadastrados
    ofstream arquivo("Arquivos/numeroDeUsuariosCadastrados.bin", ios::binary | ios::app);

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de numero de usu�rios.");
        return false;
    }

    arquivo.write((char*)&numero, sizeof(int));
    arquivo.close();

    return true;
}

/**@brief M�todo que recebe um id de usuario e retorna o usuario contido no arquivo
*Este m�todo recebe um id de usuario, percorre o arquivo de usu�rios procurando algum usu�rio que tenha o id recebido como argumento se encontrado retorna o usu�rio de id encontrado
*@param id int numero de postagem
*@return O usu�rio procurado
*/
Usuario manipuladorDeUsuario::procuraUsuarioId(int id) {

    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (usuario.getId() == id) {
                arquivo.close();

                return usuario;
            }
        }
    }

    arquivo.close();


    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}

/**@brief M�todo que recebe um nome de usu�rio e retorna o usu�rio contido no arquivo
*Este m�todo recebe um nome de usuario, percorre o arquivo de usu�rios procurando algum usu�rio que tenha o nome recebido como argumento se encontrado retorna o usu�rio
*@param nome vetor de caracteres
*@return O usu�rio procurado
*/
Usuario manipuladorDeUsuario::procuraUsuarioNome(char nome[]){
    ifstream arquivo("Arquivos/usuarios.bin", ios::binary);
    Usuario usuario;

    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
    }else{

        while (arquivo.read((char*)&usuario, sizeof(Usuario))) {

            if (strcmp(usuario.getNome(),nome) == 0) {
                arquivo.close();

                return usuario;
            }
        }
    }


    arquivo.close();

    usuario.setNome("");
    usuario.setSenha("");
    usuario.setId(0);

    return usuario;
}

/*Parte de Seguidores*/

/**@brief M�todo para um usu�rio seguir outro usu�rio por id
*Este m�todo verifica se os usu�rios j� se seguem, sen�o recebe dois id's, sendo um do seguidor e outro do seguido, acessa os documentos de seguidores e seguidos dos respectivos usu�rios
*e adiciona os id's dos respectivos usu�rios, assim fazendo com que o usu�rio do primeiro id siga o usuario do segundo id.
*@see segue(int idSeguidor, int idSeguido)
*@param idSeguidor um argumento inteiro
*@param idSeguido um argumento inteiro
*@return True se foi seguido com sucesso e False se n�o
*/
bool manipuladorDeUsuario::seguir(int idSeguidor, int idSeguido){
    if(this->segue(idSeguidor, idSeguido)){
        cout << "Voc� j� segue este usuario\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario n�o existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ofstream arquivo(nomeArquivoSeguidor, ios::binary | ios::app);
    if (!arquivo.is_open()) {
        string erro = "";
        erro.append("Erro ao abrir o arquivo ");
        erro.append(nomeArquivoSeguidor);
        geraExcecao(erro);
        return false;
    }

    arquivo.write((char*)&idSeguido, sizeof(int));
    arquivo.close();

    //Adiciona no arquivo "Seguidor"
    arquivo.open(nomeArquivoSeguido, ios::binary | ios::app);
    if (!arquivo.is_open()) {
        string erro = "";
        erro.append("Erro ao abrir o arquivo ");
        erro.append(nomeArquivoSeguido);
        geraExcecao(erro);
        return false;
    }

    arquivo.write((char*)&idSeguidor, sizeof(int));
    arquivo.close();

    return true;
}

/**@brief M�todo para um usu�rio seguir outro usu�rio por nome
*Este m�todo verifica se os usu�rios j� se seguem, sen�o recebe um id e um nome, procura o id do nome e chama o m�todo seguir
*@see seguir(int idSeguidor, int idSeguido)
*@see existe()
*@param idSeguidor um argumento inteiro
*@param  nomeSeguidor um argumento vetor de caracteres
*@return True se foi seguido com sucesso e False se n�o
*/
bool manipuladorDeUsuario::seguir(int idSeguidor, char* nomeSeguidor){
    if(this->procuraUsuarioNome(nomeSeguidor).existe()){
        return this->seguir(idSeguidor, this->procuraUsuarioNome(nomeSeguidor).getId());
    }else{
        cout << "O usu�rio com este nome n�o existe\n\n";
    }

    return false;
}

/**@brief Retira um numero inteiro de algum arquivo utilizado para guardar inteiros
*Este m�todo recebe um nome de arquivo e um inteiro, o arquivo deve ter somente inteiros, o m�todo procura o inteiro recebido como argumento e retira do arquivo, � utilizado para deixar de seguir principalmente.
*@param nomeArquivo um argumento vetor de caracteres
*@param  inteiro um argumento inteiro
*@return True se foi retirado com sucesso e False se n�o
*/
bool manipuladorDeUsuario::retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro){
    bool encontrado = false;
    fstream arquivo(nomeArquivo, ios::binary | std::ios::in | std::ios::out); //Abre arquivo
    ofstream arquivoAux("Arquivos/aux.bin", ios::binary | ios::app); //Abre arquivo auxiliar
    limparArquivoBinario("Arquivos/aux.bin");

    int valorAtual;

    if (!arquivoAux.is_open()) {

        geraExcecao("Erro ao abrir o arquivo aux.bin");
        return false;
    }

    if (!arquivo.is_open()) {
        string erro = "Erro ao abrir o arquivo ";
        erro.append(nomeArquivo);
        geraExcecao(erro);
        return false;
    }else{
            while (arquivo.read((char*)&valorAtual, sizeof(int))) {

                if (inteiro == valorAtual) {
                    encontrado = true;
                    break;
                }
                arquivoAux.write((char*)&valorAtual, sizeof(int));
            }

            if(!encontrado){
                string erro = "Inteiro n�o encontrado no arquivo";
                erro.append(nomeArquivo);
                geraExcecao(erro);
                return false;
            }else{
                copiarArquivo(nomeArquivo, "Arquivos/aux.bin");

            }

    }

    arquivoAux.close();
    arquivo.close();
    return true;
}

/**@brief Este m�todo � utilizado para um usu�rio deixar de seguir outro usu�rio por id
*Este m�todo recebe dois id's sendo um o id do seguidor e outro do seguido, ele verifica se um id segue o outro, se sim, ele retira os id's respectivos nos arquivos de seguidos e de seguidos respectivos aos id's
*@param  idSeguidor um argumento inteiro
*@param  idSeguido um argumento inteiro
**@see existe()
*@see retiraDeArquivoDeInteiros(char nomeArquivo[], int inteiro)
*@return True se foi deixado de seguir com sucesso e False se n�o
*/
bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, int idSeguido){
    if(!this->segue(idSeguidor, idSeguido)){
        cout << "Voc� n�o segue este usuario.\n\n";
        return false;
    }
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);
    char parte1b[] = "Arquivos/Seguidores/Seguidores#";
    char parte2b[] = ".bin";
    char *nomeArquivoSeguido = strcat(strcat(parte1b,to_string(idSeguido).c_str()),parte2b);

    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    if(!seguido.existe()){
        geraExcecao("Usuario n�o existe!!\n");
        return false;
    }

    //Retira do arquivo "Segue"

    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguidor, idSeguido)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }
    //Retira do arquivo "Seguidor"
    if(!this->retiraDeArquivoDeInteiros(nomeArquivoSeguido, idSeguidor)){
        geraExcecao("Erro ao retirar do arquivo!\n");
        return false;
    }

    if(this->segue(idSeguidor, idSeguido)){
        geraExcecao("Erro ao deixar de seguir!\n");
        return false;
    }

    return true;
}

/**@brief Este m�todo � utilizado para um usu�rio deixar de seguir outro usu�rio por nome
*Este m�todo recebe um id e um nome, procura o id do respctivo nome e chama o m�todo deixarDeSeguir() passando como parametro os id's
*@param  idSeguidor um argumento inteiro
*@param  nomeSeguido um argumento vetor de caracteres
*@see deixarDeSeguir(int idSeguidor, int idSeguido)
*@return True se foi deixado de seguir com sucesso e False se n�o
*/
bool manipuladorDeUsuario::deixarDeSeguir(int idSeguidor, char nomeSeguido[]){
    if(this->procuraUsuarioNome(nomeSeguido).existe()){
        return this->deixarDeSeguir(idSeguidor, this->procuraUsuarioNome(nomeSeguido).getId());
    }else{
        geraExcecao("O usu�rio com este nome n�o existe\n\n");
    }

    return false;
}

/**@brief Este m�todo � utilizado para verificar se um usu�rio segue outro
*Este m�todo recebe dois id's sendo um o id do seguidor e outro do seguido, ele verifica se um id segue o outro,
* verificando os arquivos de seguidores e seguidos respectivos, retorna true se segue e false sen�o
*@param  idSeguidor um argumento inteiro
*@see existe()
*@param  idSeguido um argumento inteiro
*@return True se segue e False se n�o
*/
bool manipuladorDeUsuario::segue(int idSeguidor, int idSeguido){
    //Nomes dos arquivos
    char parte1[] = "Arquivos/Seguidores/Segue#";
    char parte2[] = ".bin";
    char *nomeArquivoSeguidor = strcat(strcat(parte1,to_string(idSeguidor).c_str()),parte2);


    //Usuarios
    Usuario seguido = this->procuraUsuarioId(idSeguido);
    Usuario seguidor = this->procuraUsuarioId(idSeguidor);

    if(!seguido.existe()){
        geraExcecao("Usuario n�o existe!!\n");
        return false;
    }

    //Adiciona no arquivo "Segue"

    ifstream arquivo(nomeArquivoSeguidor, ios::binary);
    int id;
    if (!arquivo.is_open()) {
        string erro = "Erro ao abrir o arquivo ";
        erro.append(nomeArquivoSeguidor);
        geraExcecao(erro);
        return false;
    }else{

        while (arquivo.read((char*)&id, sizeof(int))) {

            if (id == idSeguido) {
                arquivo.close();
                return true;
            }
        }
    }

    return false;
}

/**@brief M�todo que salva um usuario com altera��es no arquivo
*Este m�todo t�m como objetivo salvar um usuario j� existente, mas que foi alterado no funcionamento da aplica��o, ela recebe um objeto do tipo Usuario
*Porcura um objeto com o mesmo id e substitui ele no arquivo.
*@param post do tipo Usuario
*@return valor booleano, true se foi substituido com sucesso e false se n�o foi
*/
bool manipuladorDeUsuario::salvarUsuario(Usuario usuario){
    fstream arquivo("Arquivos/usuarios.bin", ios::binary | std::ios::in | std::ios::out);
    Usuario userAux;
    int i = 0;
    if (!arquivo.is_open()) {
        geraExcecao("Erro ao abrir o arquivo de usu�rios.");
        return false;
    }else{

        while (arquivo.read((char*)&userAux, sizeof(Usuario))) {
            if (userAux.getId() == usuario.getId()) {
                break;
            }
            i++;
        }

    }

    arquivo.seekg(i*sizeof(Usuario), ios_base::beg);
    arquivo.write((char*)&usuario, sizeof(Usuario));
    arquivo.close();
    return true;
}
/*Parte de Usuarios*/
