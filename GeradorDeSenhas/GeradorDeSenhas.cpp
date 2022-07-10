#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

void GeraSenha(int tam, char tipo, char *senha);

int main(int argc, char **argv){
	setlocale(LC_ALL, "portuguese");
	FILE *entrada, *saida;
	char tipo, *senhas, aux;
	int tamanho, i, m;
	
	entrada = fopen("MATR.TXT", "r");
	saida = fopen("SENHAS.TXT", "w");
	if(entrada == NULL || saida == NULL){
		printf("Erro ao abrir os arquivos!");
		exit(1);
	}
	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                               Projeto Programa 4 - Gerador de Senhas                                |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                    Adilson de Jesus Candido Oliveira - N� Matr�cula/RA: 21207318                    |\n");
	printf("|                    Carina Roberta Rodrigues da Silva - N� Matr�cula/RA: 20200081                    |\n");
	printf("|                    Diego Silva e Sousa               - N� Matr�cula/RA: 21207407                    |\n");
	printf("|                    Fabio Hideki Kina Senda           - N� Matr�cula/RA: 21207120                    |\n");
	printf("|                    Mogica Catarino Ianson            - N� Matr�cula/RA: 22119766                    |\n");
	printf("|                    Pedro Pires Ianson                - N� Matr�cula/RA: 22119770                    |\n");	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                                         Tipos de Senha:                                             |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|     a. Num�rica � conter� apenas algarismos;                                                        |\n");
	printf("|     b. Alfab�tica � conter� apenas letras mai�sculas e min�sculas;                                  |\n");
	printf("|     c. Alfanum�rica 1 � conter� letras mai�sculas e algarismos;                                     |\n"); 
	printf("|     d. Alfanum�rica 2 � conter� letras mai�sculas, min�sculas e algarismos;                         |\n");
	printf("|     e. Geral � conter� algarismos, letras e os caracteres \"-\", \"_\", \":\", \"@\", \"#\", \"$\", \"&\", \"?\"    |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|                                  Escolha um tipo de senha: ");
	tipo = getche();
	printf("                                        |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|                                 Escolha o tamanho da senha: ");
	scanf("%d", &tamanho);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	
	
	senhas = (char *) malloc(sizeof(char)*tamanho);
	
	while(fscanf(entrada, "%d", &m) != EOF){
		GeraSenha(tamanho, tipo, senhas);
		fprintf(saida, "%d;", m);
		for(i = 0; i < tamanho; i++){
			fprintf(saida, "%c", senhas[i]);
		}
		fprintf(saida, "\n");
	}
	printf("|                                Senhas criadas com sucesso !!!                                       |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	
	free(senhas);
	fclose(entrada);
	fclose(saida);
	
	return 0;
}

void GeraSenha(int tam, char tipo, char *senha){
	char aux;
	int i, a = 0;
	bool maiusculas = false, minusculas = false, numeros = false, caracteres = false;
	
	switch(tipo){
		case 'a':
			//alg  48-57
			for(i = 0; i < tam; i++){
				senha[i] = rand() % 10 + 48; // apenas numeros
			}
			break;
		case 'b':
			//mai  65-90    min 97-122
			while(!(maiusculas && minusculas)){
				maiusculas = minusculas = false;
				for(i = 0; i < tam; i++){
					aux = rand() % (26 + 26); // maiusculas e minusculas
					if(aux < 26){
						aux += 65;
						maiusculas = true;
					}
					else{
						aux += 97 - 26;
						minusculas = true;
					}
					senha[i] = aux;
				}
			}
			break;
		case 'c':
			while(!(maiusculas && numeros)){
			maiusculas = numeros = false;
				for(i = 0; i < tam; i++){
					aux = rand() % (10 + 26); // numeros e maiusculas
					if(aux < 10){
						aux += 48;
						numeros = true;
					}
					else{
						aux += 65 - 10;
						maiusculas = true;
					}
					senha[i] = aux;
				}
			}
			break;
		case 'd':
			while(!(maiusculas && minusculas && numeros)){
				maiusculas = minusculas = numeros = false;
				for(i = 0; i < tam; i++){
					aux = rand() % (10 + 26 + 26); // numeros, maiusculas e minusculas
					if(aux < 10){
						aux += 48;
						numeros = true;
					}
					else if(aux < 10+26){
						aux += 65 - 10;
						maiusculas = true;
					}
					else{
						aux += 97 - 10 - 26;
						minusculas = true;
					}
					senha[i] = aux;
				}
			}
			break;
		case 'e':
			//35 36 38 45 58 63 64 95
			// #  $  &  -  :  ?  @  _
			while(!(maiusculas && minusculas && numeros && caracteres)){
				maiusculas = minusculas = numeros = caracteres = false;
				for(i = 0; i < tam; i++){
					aux = rand() % (10 + 26 + 26 + 8); // numeros, maiusculas e minusculas e caracteres
					if(aux < 10){
						aux += 48;
						numeros = true;
					}
					else if(aux < 10+26){
						aux += 65 - 10;
						maiusculas = true;
					}
					else if(aux < 10+26+26){
						aux += 97 - 10 - 26;
						minusculas = true;
					}
					else if(aux < 10+26+26+2){
						aux += 35 - 10 - 26 -26;
						caracteres = true;
					}
					else {
						aux -= (10 + 26 + 26 + 2);
						caracteres = true;
						switch(aux){
							case 0:
								aux = 38;
								break;
							case 1:
								aux = 45;
								break;
							case 2:
								aux = 58;
								break;
							case 3:
								aux = 63;
								break;
							case 4:
								aux = 64;
								break;
							case 5:
								aux = 95;
								break;
							default:
								printf("algo deu errado");
								break;
						}
					}
				senha[i] = aux;
				}
			}
			break;
		default:
			printf("|                                         TIPO INV�LIDO!!!                                            |\n");
			printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
			exit(0);
			break;
	}
}
