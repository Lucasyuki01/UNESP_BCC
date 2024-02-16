//Lucas Yuki Nishimoto
//Ra:211024678
//S.O: Windows10 pro
//DevC++
//Nota: 9,3

#include <stdio.h>
#include <string.h>
#define MAX 50

char simbolo[MAX];

void PROXIMO(char *prox, int *linha, int *pos_codigo, char codigo[], int *tab){
    if (*pos_codigo >= strlen(codigo)){
        *prox = NULL;
        return;
    }

    *prox = codigo[*pos_codigo];
    ++*pos_codigo;

    while (*prox == '\t'){
        *prox = codigo[*pos_codigo];
        ++*pos_codigo;
        ++*tab;
    }
    // printf("linha: %d, outraLinha: %d, prox: %c, posCodigo: %d, strlen(codigo): %d\n", *linha, *outraLinha, *prox, *posCodigo, strlen(codigo));
}

char *CODIGO(char lexema[]){
    // < > ( ) + - * / : , . ; = 

    char codigo[MAX];

	if (strcmp(lexema, "<") == 0){
        strcpy(codigo, "ID_Menor");
    }
    
    else if (strcmp(lexema, ">") == 0){
        strcpy(codigo, "ID_Maior");
    }
    
    else if (strcmp(lexema, "(") == 0){
        strcpy(codigo, "ID_AbreParenteses");
    }
    
    else if (strcmp(lexema, ")") == 0){
        strcpy(codigo, "ID_FechaParenteses");
    }
    
    else if (strcmp(lexema, "+") == 0){
        strcpy(codigo, "ID_Soma");
    } 
    
	else if (strcmp(lexema, "-") == 0){
        strcpy(codigo, "ID_Subtracao");
    }
    
    else if (strcmp(lexema, "*") == 0){
        strcpy(codigo, "ID_Multiplicacao");
    }
    
    else if (strcmp(lexema, "/") == 0){
        strcpy(codigo, "ID_Divisao");
    }
   
    else if (strcmp(lexema, ":") == 0){
        strcpy(codigo, "ID_DoisPontos");
    }
    
    else if (strcmp(lexema, ",") == 0){
        strcpy(codigo, "ID_Virgula");
    }
    
    else if (strcmp(lexema, ".") == 0){
        strcpy(codigo, "ID_Ponto");
    }
    
    else if (strcmp(lexema, ";") == 0){
        strcpy(codigo, "ID_PontoEVirgula");
    }
    
	else if (strcmp(lexema, "=") == 0){
        strcpy(codigo, "ID_Igual");
    }
    
    else if (strcmp(lexema, ":=") == 0){
        strcpy(codigo, "ID_Atribuicao");
    }
    
    //begin div do else end if integer procedure program read then var write while
    else if (strcmp(lexema, "begin") == 0){
        strcpy(codigo, "ID_Begin");
    }
    
    else if (strcmp(lexema, "div") == 0){
        strcpy(codigo, "ID_Div");
    }
    
    else if (strcmp(lexema, "do") == 0){
        strcpy(codigo, "ID_Do");
    }
    
    else if (strcmp(lexema, "else") == 0){
        strcpy(codigo, "ID_Else");
    }
    
    else if (strcmp(lexema, "end") == 0){
        strcpy(codigo, "ID_End");
    }
    
    else if (strcmp(lexema, "if") == 0){
        strcpy(codigo, "ID_If");
    }
    
    else if (strcmp(lexema, "integer") == 0){
        strcpy(codigo, "ID_Integer");
    }
    
    else if (strcmp(lexema, "procedure") == 0){
        strcpy(codigo, "ID_Procedure");
    }
    
	else if (strcmp(lexema, "program") == 0){
        strcpy(codigo, "ID_Program");
    }
    
    else if (strcmp(lexema, "read") == 0){
        strcpy(codigo, "ID_Read");
    }
    
    else if (strcmp(lexema, "then") == 0){
        strcpy(codigo, "ID_Then");
    }
    
    else if (strcmp(lexema, "var") == 0){
        strcpy(codigo, "ID_Var");
    }
    
    else if (strcmp(lexema, "write") == 0){
        strcpy(codigo, "ID_Write");
    }
    
    else if (strcmp(lexema, "while") == 0){
        strcpy(codigo, "ID_While");
    }
    
    return codigo;
}

void ERRO(int linha, char lexema[], char prox, int opc){
    printf("\n\nERRO na linha %d -> ", linha);
    
	if (opc == 1){
        printf("Identificador iniciado por numero: %s\n", lexema);
    }
	
	else{
        printf("Simbolo nao identificado: %c\n", prox);
	}
}

int digitos(char digito){
    // 48 - 57 (de 0 ate 9 em ASCII)
    int digito_int = (int)digito;
    
	if (digito_int >= 48 && digito_int <= 57){
        return 1;
    }
    
    else{
        return 0;
    }
}

int letras(char letra){
    // codigo em ascII 65 - 90  (de A ate Z), 97 - 122 (de a ate z)
    int letra_int = (int)letra;
    
	if ((letra_int >= 65 && letra_int <= 90) || (letra_int >= 97 && letra_int <= 122)){
        return 1;
    }
    
    else{
        return 0;
    }
}

int simbolos_especiais(char caracter){
    char caracteres[] = {'<', '>', '(', ')', '+', '-', '*', '/', ':', ',', '.', ';', '='};
    int i;

    for (i = 0; i < (int)(sizeof(caracteres) / sizeof(caracteres[0])); i++){
        if (caracter == caracteres[i]){
            return 1;
		}
	}
    return 0;
}

int palavras_reservadas(char palavra[]){
    char palavras[][MAX] = {"begin", "div", "do", "else", "end", "if", "integer", "procedure", "program", "read", "then", "var", "while", "write"};
	int i;
	
    for (i = 0; i < (int)(sizeof(palavras) / sizeof(palavras[0])); i++){
        if (strcmp(palavra, palavras[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void mostra_simbolos(int linha, int *outra_linha, int tab){
	
    if (*outra_linha){
    	
        if (linha != 1){
            printf("\n");
        }
            
        printf("%d ", linha);
        
		*outra_linha = 0;
        
		while (tab--){
            printf("\t");
        }
    }
    
	printf("%s ", simbolo);
}

int main(){

	FILE *arquivo;
    
	char codigo[400];
	char lexema[MAX] = {""};
    char prox = NULL, prox_string[2];
    
	int linha = 1, outra_linha = 1, i, tab = 0;
	int pos_codigo = 0;

    for (i = 0; i < 400; i++){
        codigo[i] = NULL;
    }

    arquivo = fopen("C:\\Users\\lucas\\Desktop\\Analisador_LEX\\trab_1_compiladores.txt", "r");
    
	fread(codigo, sizeof(char), 400, arquivo);
    fclose(arquivo);

    while (prox == NULL){
        PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
	}
    
	while (prox != NULL){
        for (i = 0; i < strlen(lexema); i++){
            lexema[i] = NULL;
		}
		
        if (simbolos_especiais(prox)){
            char s[3];
            s[0] = prox;
            s[1] = s[2] = NULL;
            
            PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);

            if (s[0] == ':' && prox == '='){
                s[1] = prox;
                PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
            }
            
            strcpy(simbolo, CODIGO(s));

            while (prox == ' '){
                PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
            }
        }
        
		else if (letras(prox)){
            do{
            	//Converte o próximo caractere em uma string para passar como referência
                prox_string[0] = prox;
                prox_string[1] = NULL;
                strcat(lexema, prox_string);
                PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
                
				if (prox == ' '){
                    while (prox == ' '){
                        PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
                    }
					
					break;
                }
                
			}while (letras(prox) || digitos(prox));

            if (palavras_reservadas(lexema)){
                strcpy(simbolo, CODIGO(lexema));
            }
            
            else{
                strcpy(simbolo, "ID_Identificador");
            }
        }

        else if (digitos(prox)){
            do{
            	//Converte o próximo caractere em uma string para passar como referência
                prox_string[0] = prox; 
                prox_string[1] = NULL;
                strcat(lexema, prox_string);
                PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
                
				if (prox == ' '){
                    while (prox == ' '){
                        PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
                    }
                    
                    break;
                }
            } while (digitos(prox));

            if (letras(prox)){
                while (prox!=NULL && !simbolos_especiais(prox) && prox != ' ' && prox != '\n'){
                	//Converte o próximo caractere em uma string para passar como referência
                    prox_string[0] = prox;
                    prox_string[1] = NULL;
                    strcat(lexema, prox_string);
                    PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
                }
                
                ERRO(linha, lexema, prox, 1);
                return 0;
            }

            strcpy(simbolo, "ID_Numero");
        }

        else{
            ERRO(linha, lexema, prox, 2);
            return 0;
        }
        
        // printf("%s", simbolo);
        mostra_simbolos(linha, &outra_linha, tab);

        if (prox == '\n'){
            tab = 0;
            PROXIMO(&prox, &linha, &pos_codigo, codigo, &tab);
            linha++;
            outra_linha = 1;
        }
    }
	
	
    return 0;
}
