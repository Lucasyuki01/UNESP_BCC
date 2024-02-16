/*
Lucas Yuki Nishimoto
Ra:211024678
S.O: Windows 10
DevC++
nota: 7,8
*/

#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

char next = '\0';
int positCode = 0;

string code;

int line = 1;

string atomo;

void PROX(){

    if (positCode >= (int)code.size()){
        next = '\0';
        
        return;
    }

    next = code[positCode++];

    while (next == '\t')
        next = code[positCode++];

    while (next == '\n'){
        next = code[positCode++];
        line++;
    }
}

bool identificador(string token);

string CODIGO(string atomo){
    // : = + * / - , . ; < > ( ) program - var - integer - procedure - begin - if - else - then - div - end - read - while - write - do
    string code;

    if (atomo == ":")
        code = "i_doisPontos";
        
    else if (atomo == "=")
        code = "i_igual";
        
    else if (atomo == ":=")
        code = "i_atribuicao";
        
    else if (atomo == "+")
        code = "i_soma";
        
    else if (atomo == "*")
        code = "i_multiplicacao";
        
    else if (atomo == "/")
        code = "i_divisao";
        
    else if (atomo == "-")
        code = "i_subtracao";
        
    else if (atomo == ",")
        code = "i_virgula";
        
    else if (atomo == ".")
        code = "i_ponto";
        
    else if (atomo == ";")
        code = "i_pontoEVirgula";
        
    else if (atomo == "<")
        code = "i_menor";
        
    else if (atomo == ">")
        code = "i_maior";
        
    else if (atomo == "(")
        code = "i_abreParenteses";
        
    else if (atomo == ")")
        code = "i_fechaParenteses";
        
    else if (atomo == "program")
        code = "i_program";
        
    else if (atomo == "var")
        code = "i_var";
        
    else if (atomo == "integer")
        code = "i_integer";
        
    else if (atomo == "procedure")
        code = "i_procedure";
    
	else if (atomo == "begin")
        code = "i_begin";
    
	else if (atomo == "if")
        code = "i_if";
    
	else if (atomo == "else")
        code = "i_else";
    
	else if (atomo == "then")
        code = "i_then";
    
	else if (atomo == "div")
        code = "i_div";
    
	else if (atomo == "end")
        code = "i_end";
    
	else if (atomo == "read")
        code = "i_read";
    
	else if (atomo == "while")
        code = "i_while";
    
	else if (atomo == "write")
        code = "i_write";
    
	else if (atomo == "do")
        code = "i_do";
    
	else if (identificador(atomo))
        code = "i_identificador";
    
	else
        code = "i_numero";

    return code;
}

void ERRO(int opc){
    cout << "\n\nERRO na linha " << line << " - ";
    
    if (opc == 1)
        cout << "Variavel iniciada com digito: " << atomo << endl;
        
    else
        cout << "Simbolo desconhecido: %c\n"
             << next;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool simbolosEspeciais(char caracter){
    char caracteres[] = {':', '=', '+', '*', '/', '-', ',', '.', ';', '<', '>', '(', ')'};

    for (int i = 0; i < (int)(sizeof(caracteres) / sizeof(char)); i++)
        if (caracter == caracteres[i])
            return true;

    return false;
}

bool palavrasReservadas(string palavra){
    string palavras[] = {"program", "var", "integer", "procedure", "begin", "if", "else", "then", "div", "end", "read", "while", "write", "do"};

    for (int i = 0; i < (int)sizeof(palavras) / sizeof(string); i++)
    {
        if (palavra.compare(palavras[i]) == 0)
            return true;
    }
    return false;
}

bool letras(char letra){
    // de 65 - 90 , de 97 - 122
    int letraInt = (int)letra;
    if ((letraInt >= 65 && letraInt <= 90) || (letraInt >= 97 && letraInt <= 122))
        return true;
    else
        return false;
}

bool digitos(char digito){
    // de 48 - 57
    int digitoInt = (int)digito;
    if (digitoInt >= 48 && digitoInt <= 57)
        return true;
        
    else
        return false;
}


//ANALISADOR LEXICO T1 -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int analex(){

    atomo = "\0";

    if (simbolosEspeciais(next))
    {
        atomo.push_back(next);
        PROX();

        if (atomo[0] == ':' && next == '=')
        {
            atomo.push_back(next);
            PROX();
        }
        else if ((atomo[0] == '<' || atomo[0] == '>') && next == '=')
        {
            atomo.push_back(next);
            PROX();
        }
    }
    else if (letras(next))
    {
        do
        {
            atomo.push_back(next);
            PROX();
        } while ((letras(next) && !palavrasReservadas(atomo)) || digitos(next));
    }
    else if (digitos(next))
    {
        do
        {
            atomo.push_back(next);
            PROX();
        } while (digitos(next));

        if (letras(next))
        {
            while (next != '\0' && !simbolosEspeciais(next) && next != ' ')
            {
                atomo.push_back(next);
                PROX();
            }
            ERRO(1);
            return 0;
        }
    }

    else
    {
        ERRO(2);
        return 0;
    }

    while (next == ' ' || next == '\t')
        PROX();

    return 1;
}


//ROTINAS GRAMATICA PASCAL ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool expressao(string atomos[], int *pos);
bool fator(string atomos[], int *pos);
bool listaDeExpressoes(string atomos[], int *pos);
bool comando(string atomos[], int *pos);
bool comandoRepetitivo(string atomos[], int *pos);
bool comandoCondicional(string atomos[], int *pos);
bool comandoComposto(string atomos[], int *pos);
bool desvio(string atomos[], int *pos);
bool chamadaDeProcedimento(string atomos[], int *pos);
bool atribuicao(string atomos[], int *pos);
bool bloco(string atomos[], int *pos);



bool identificador(string token){
    if (!letras(token[0]))
        return false;
        
    for (int i = 1; i < (int)token.length(); i++)
        if ((!letras(token[i]) && !digitos(token[i])) || palavrasReservadas(token))
            return false;
            
    return true;
}

bool numero(string token){
    for (int i = 0; i < (int)token.length(); i++)
        if (!digitos(token[i]))
            return false;
            
    return true;
}

bool variavel(string token){
    return (identificador(token));
}

bool tipo(string token){
    return (token == "integer" || token == "real" || token == "string");
}

bool leitura(string atomos[], int *pos){
    if (atomos[*pos] != "read")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != "(")
        return false;

    *pos = *pos + 1;

    if (!variavel(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ")")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    return true;
}

bool escrita(string atomos[], int *pos){
    if (atomos[*pos] != "write")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != "(")
        return false;

    *pos = *pos + 1;

    if (!variavel(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ")")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    return true;
}

bool listaDeIdentificadores(string atomos[], int *pos){
    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    while (atomos[*pos] == ",")
    {
        *pos = *pos + 1;
        if (!identificador(atomos[*pos]))
            return false;
        *pos = *pos + 1;
    }

    return true;
}

bool secaoDeParametrosFormais(string atomos[], int *pos){
    if (atomos[*pos] == "var")
        *pos = *pos + 1;

    if (!listaDeIdentificadores(atomos, pos))
        return false;

    if (atomos[*pos] != ":")
        return false;

    *pos = *pos + 1;

    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    return true;
}

bool parametrosFormais(string atomos[], int *pos){
    if (!secaoDeParametrosFormais(atomos, pos))
        return false;

    *pos = *pos + 1;

    while (atomos[*pos] == ";")
    {
        *pos = *pos + 1;
        if (!secaoDeParametrosFormais(atomos, pos))
            return false;
        *pos = *pos + 1;
    }

    return true;
}

bool declaracaoDeFuncao(string atomos[], int *pos){
    if (atomos[*pos] != "function")
        return false;

    *pos = *pos + 1;

    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    parametrosFormais(atomos, pos);

    if (atomos[*pos] != ":")
        return false;

    *pos = *pos + 1;

    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    if (!bloco(atomos, pos))
        return false;

    return true;
}

bool declaracaoDeProcedimento(string atomos[], int *pos){
    if (atomos[*pos] != "procedure")
        return false;

    *pos = *pos + 1;

    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    parametrosFormais(atomos, pos);

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    if (!bloco(atomos, pos))
        return false;

    return true;
}

bool parteDeDeclaracoesDeSubRotinas(string atomos[], int *pos){
    if (!declaracaoDeProcedimento(atomos, pos) && !declaracaoDeFuncao(atomos, pos))
    {
        return false;
    }

    return true;
}

bool declaracaoDeVariaveis(string atomos[], int *pos){
    if (!listaDeIdentificadores(atomos, pos))
        return false;

    if (atomos[*pos] != ":")
        return false;

    *pos = *pos + 1;

    if (!tipo(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    return true;
}

bool parteDeDeclaracoesDeVariaveis(string atomos[], int *pos){
    if (atomos[*pos] != "var")
        return false;

    *pos = *pos + 1;

    if (!declaracaoDeVariaveis(atomos, pos))
        return false;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    while (declaracaoDeVariaveis(atomos, pos))
    {

        if (atomos[*pos] != ";")
            return false;

        *pos = *pos + 1;
    }

    return true;
}

bool parteDeDeclaracoesDeRotulos(string atomos[], int *pos){
    if (atomos[*pos] != "label")
        return false;

    *pos = *pos + 1;

    if (!numero(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    while (atomos[*pos] == ",")
    {
        *pos = *pos + 1;

        if (!numero(atomos[*pos]))
            return false;

        *pos = *pos + 1;
    }

    return true;
}

bool relacao(string atomos[], int *pos){
    //  = | <> | < | <= | >= | >
    if (atomos[*pos] == "=" || atomos[*pos] == "<>" || atomos[*pos] == "<" || atomos[*pos] == "<=" || atomos[*pos] == ">=" || atomos[*pos] == ">")
    {
        *pos = *pos + 1;
        return true;
    }
    return false;
}

bool bloco(string atomos[], int *pos){
    parteDeDeclaracoesDeRotulos(atomos, pos);
    parteDeDeclaracoesDeVariaveis(atomos, pos);
    parteDeDeclaracoesDeSubRotinas(atomos, pos);

    if (!comando(atomos, pos))
        return false;

    return true;
}

bool comandoSemRotulo(string atomos[], int *pos){
    if (atribuicao(atomos, pos) || chamadaDeProcedimento(atomos, pos) || escrita(atomos, pos) || leitura(atomos, pos) || comandoRepetitivo(atomos, pos) || comandoCondicional(atomos, pos) || desvio(atomos, pos) || comandoComposto(atomos, pos))
        return true;
    return false;
}

bool comandoComposto(string atomos[], int *pos){
    if (atomos[*pos] != "begin")
        return false;

    *pos = *pos + 1;

    if (!comando(atomos, pos))
        return false;

    while (atomos[*pos - 1] == ";" && atomos[*pos] != "end")
    {
        if (!comando(atomos, pos))
            return false;
    }

    if (atomos[*pos] != "end")
        return false;

    *pos = *pos + 1;

    return true;
}

bool comando(string atomos[], int *pos){
    if (numero(atomos[*pos]))
    {
        *pos = *pos + 1;

        if (atomos[*pos] != ":")
            return false;
    }

    if (!comandoSemRotulo(atomos, pos))
        return false;

    return true;
}

bool desvio(string atomos[], int *pos){
    if (atomos[*pos] != "goto")
        return false;

    *pos = *pos + 1;

    if (!numero(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    return true;
}

bool atribuicao(string atomos[], int *pos){
    if (!variavel(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ":=")
    {
        *pos = *pos - 1;
        return false;
    }

    *pos = *pos + 1;

    if (!expressao(atomos, pos))
        return false;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    return true;
}

bool chamadaDeProcedimento(string atomos[], int *pos){
    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
    {
        *pos = *pos - 1;
        return false;
    }

    *pos = *pos + 1;

    return true;
}

bool comandoCondicional(string atomos[], int *pos){
    if (atomos[*pos] != "if")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != "(")
        return false;

    *pos = *pos + 1;

    if (!expressao(atomos, pos))
        return false;

    if (atomos[*pos] != ")")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != "then")
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] == "begin")
        comandoComposto(atomos, pos);

    if (!comandoSemRotulo(atomos, pos))
        return false;

    if (atomos[*pos] == "else")
    {
        *pos = *pos + 1;

        if (!comandoSemRotulo(atomos, pos))
            return false;
    }

    return true;
}

bool comandoRepetitivo(string atomos[], int *pos){
    if (atomos[*pos] != "while")
        return false;

    *pos = *pos + 1;

    if (!expressao(atomos, pos))
        return false;

    if (atomos[*pos] != "do")
        return false;

    *pos = *pos + 1;

    if (!comandoComposto(atomos, pos))
        return false;

    return true;
}

bool termo(string atomos[], int *pos){
    bool parenteses = false;
    if (atomos[*pos] == "(")
    {
        *pos = *pos + 1;
        parenteses = true;
    }

    if (!fator(atomos, pos))
        return false;

    while (atomos[*pos] == "*" || atomos[*pos] == "div" || atomos[*pos] == "and")
    {
        *pos = *pos + 1;
        if (!fator(atomos, pos))
            return false;
    }

    if (parenteses)
    {
        if (atomos[*pos] != ")")
            return false;
        *pos = *pos + 1;
    }

    if (atomos[*pos] == "*" || atomos[*pos] == "div" || atomos[*pos] == "and")
    {
        *pos = *pos + 1;
        if (!termo(atomos, pos))
            return false;
    }

    return true;
}

bool expressaoSimples(string atomos[], int *pos){
    if (atomos[*pos] == "+" || atomos[*pos] == "-")
    {
        *pos = *pos + 1;
    }

    if (!termo(atomos, pos))
        return false;

    while (atomos[*pos] == "+" || atomos[*pos] == "-" || atomos[*pos] == "or")
    {
        *pos = *pos + 1;
        if (!termo(atomos, pos))
            return false;
    }

    return true;
}

bool expressao(string atomos[], int *pos){
    if (!expressaoSimples(atomos, pos))
        return false;

    if (relacao(atomos, pos))
    {
        if (!expressaoSimples(atomos, pos))
            return false;
    }

    return true;
}

bool listaDeExpressoes(string atomos[], int *pos){
    if (!expressao(atomos, pos))
        return false;

    while (atomos[*pos] == ",")
    {
        *pos = *pos + 1;

        if (!expressao(atomos, pos))
            return false;
    }

    return true;
}

bool chamadaDeFuncao(string atomos[], int *pos){
    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    listaDeExpressoes(atomos, pos);

    return true;
}

bool fator(string atomos[], int *pos){
    if (variavel(atomos[*pos]) || numero(atomos[*pos]) || chamadaDeFuncao(atomos, pos) || expressao(atomos, pos) || !fator(atomos, pos))
    {
        *pos = *pos + 1;
        return true;
    }
    return false;
}

bool programa(string atomos[], int *pos){
    if (atomos[*pos] != "program")
        return false;

    *pos = *pos + 1;

    if (!identificador(atomos[*pos]))
        return false;

    *pos = *pos + 1;

    if (atomos[*pos] != ";")
        return false;

    *pos = *pos + 1;

    if (!bloco(atomos, pos))
        return false;

    if (atomos[*pos] != ".")
        return false;

    return true;
}

bool analiseSintatica(string atomos[], int *pos){
    if (!programa(atomos, pos)){
        positCode = 0;
        line = 1;

        PROX();

        for (int i = 0; i < *pos; i++)
            analex();

        return false;
    }

    return true;
}

int main(){
    string atomos[500];
    int qtdAtomos = 0;
    
//LEITURA DO ARQUIVO---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    FILE *arquivo;
    char codigoLeitura[500];

    for (int i = 0; i < 500; i++)
        codigoLeitura[i] = '\0';

    arquivo = fopen("Exemplo1_Trab2_Compiladores.txt", "r");
    fread(codigoLeitura, sizeof(char), 500, arquivo);
    fclose(arquivo);

    code = codigoLeitura;

    while (next == '\0')
        PROX();

	//Guarda todos os atomos em um vetor
    for (int i = 0; next != '\0'; i++){
        if (analex()){
            atomos[i] = atomo;
            qtdAtomos++;
        }
    }

    int pos = 0;

    if (analiseSintatica(atomos, &pos))
        cout << "Analise Sintatica realizada com sucesso" << endl;
    
	else
        cout << "ERRO!\nLINHA-> " << line << endl
             << "Atomo-> " << atomos[pos] << endl;
    return 0;
}
