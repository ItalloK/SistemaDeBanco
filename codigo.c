// meu programa de registros, by: italo gabriel - 044704
// Deve criar um arquivo com nome " dados.txt "

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int logado = 0;
float saldo = 0;
char nick[50], senha[50];

int contaExiste(const char *nick) {
    FILE *arquivo = fopen(nick, "r");
    if (arquivo != NULL) {
        fclose(arquivo); 
        return 1;
    }
    return 0; 
}

void logina(char *nick, char *senha) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "%s.txt", nick); 
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo != NULL) {
        char usuarioArquivo[50];
        char senhaArquivo[50];
        float saldoArquivo;
        fscanf(arquivo, "%s\n%s\n%f", usuarioArquivo, senhaArquivo, &saldoArquivo); 
        if (strcmp(nick, usuarioArquivo) == 0 && strcmp(senha, senhaArquivo) == 0) {
            printf("---------------------------------------------------------\n");
            printf("Login bem-sucedido! Bem-vindo, %s.\n", nick);
            printf("---------------------------------------------------------\n");
			logado = 1;
            main();
        } else {
            printf("Nome de usuario ou senha incorretos.\n");
            main();
        }
        fclose(arquivo);
    } else {
        printf("Usuario nao encontrado.\n");
        main();
    }
}

void registroa(char *nick, char *senha, float saldo) {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "%s.txt", nick); 
    if (contaExiste(nomeArquivo)) {
        printf("Ja existe uma conta com este nome.\n");
        main();
    } else {
        FILE *arquivo = fopen(nomeArquivo, "w");
        if (arquivo != NULL) {
            fprintf(arquivo, "%s\n%s\n%f", nick, senha, saldo); 
            fclose(arquivo);
            printf("Usuario registrado com sucesso.\n");
            main();
        } else {
            printf("Erro ao registrar usuario.\n");
        }
    }
}

void saldoa(){
	char nomeArquivo[50];
    sprintf(nomeArquivo, "%s.txt", nick); 
    FILE *arquivo = fopen(nomeArquivo, "r"); 
	char usuarioArquivo[50];
    char senhaArquivo[50];
    float saldoArquivo;
    fscanf(arquivo, "%s\n%s\n%f", usuarioArquivo, senhaArquivo, &saldoArquivo);     
	printf("--------------------------\n");
	printf("Seu saldo e R$: %.2f", saldoArquivo);
	printf("\n--------------------------\n");
	main();	
}

void saquea() {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "%s.txt", nick); 
    FILE *arquivo = fopen(nomeArquivo, "r+"); 
    char usuarioArquivo[50];
    char senhaArquivo[50];
    float saldoArquivo;
    fscanf(arquivo, "%s\n%s\n%f", usuarioArquivo, senhaArquivo, &saldoArquivo);
    float valor;
    printf("Digite quanto voce quer sacar: ");
    scanf("%f", &valor);
    if (saldoArquivo < valor) {
        printf("Saldo indisponivel.\n");
        printf("Voce so tem: R$ %.2f\n", saldoArquivo);
    } else {
        printf("--------------------------\n");
        printf("Voce sacou R$: %.2f\n", valor);
        printf("--------------------------\n");
        saldoArquivo = saldoArquivo - valor;
        fseek(arquivo, 0, SEEK_SET);
        fprintf(arquivo, "%s\n%s\n%.2f", usuarioArquivo, senhaArquivo, saldoArquivo);
    }

    fclose(arquivo);
    main();
}

void depositoa() {
    char nomeArquivo[50];
    sprintf(nomeArquivo, "%s.txt", nick); 
    FILE *arquivo = fopen(nomeArquivo, "r+");
    char usuarioArquivo[50];
    char senhaArquivo[50];
    float saldoArquivo;
    fscanf(arquivo, "%s\n%s\n%f", usuarioArquivo, senhaArquivo, &saldoArquivo);
    float valor;
    printf("\nDigite o valor para deposito: ");
    scanf("%f", &valor);
    printf("--------------------------\n");
    printf("Voce depositou R$: %.2f\n", valor);
    printf("--------------------------\n");
    saldoArquivo = saldoArquivo + valor;
    fseek(arquivo, 0, SEEK_SET);
    fprintf(arquivo, "%s\n%s\n%.2f", usuarioArquivo, senhaArquivo, saldoArquivo);
    fclose(arquivo);
    main();
}

int main(){		
	int opcao;
	float saldoreg;
	printf("0 - Login\n1 - Registro\n2 - Saldo\n3 - Saque\n4 - Deposito\n5 - Sair\n");
	printf("Digite a opcao Desejada:");
	scanf("%d", &opcao);
	switch(opcao){
		case 0:
			if(logado == 0){
				printf("Digite o nick: ");
				scanf("%s", &nick);
				printf("Digite a senha: ");
				scanf("%s", &senha);
				logina(nick, senha);	
			}else{
				printf("Voce ja esta logado!!\n");
				main();
			}
			break;
		case 1:
			printf("Digite o nick: ");
			scanf("%s", nick);
			printf("Digite a senha: ");
			scanf("%s", senha);
			registroa(nick, senha, 0);
			break;
		case 2:
			if(logado == 0){
				printf("Faca login primeiro...\n");
				main();
			}else{
				saldoa();	
			}
			break;
		case 3:
			if(logado == 0){
				printf("Faca login primeiro...\n");
				main();
			}else{
				saquea();	
			}
			break;
		case 4:
			if(logado == 0){
				printf("Faca login primeiro...\n");
				main();
			}else{
				depositoa();	
			}
			break;
		case 5:
			printf("Obrigado por utilizar nosso programa.\n");
			exit(0);
			break;
			
		default:
			printf("Opcao invalida!\n");
			return main(); 
			break;
	}
}
