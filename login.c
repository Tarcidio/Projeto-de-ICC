#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void limparTela(){
    system("CLS");
    return;
}
void login(char *name){
    for(;;){                                            //mantendo a tela de login até a entrada do usuário
        int comando = 0;
        FILE *nick;
        printf("--------------------------------------------------------------------------------\nDigite o número para:\n\n1 - Entrar\n\n2 - Se registrar\n\n--------------------------------------------------------------------------------");
        scanf("%d", &comando);                          //escolha do comando
        fflush(stdin);
        limparTela();
        if(comando == 1){                                               //comando "entrar no app"
            char nome[30],senha[30],teste[70];
            int caso = 2;
            nick = fopen("dadosLogin.txt","r");
            printf("\nDigite seu usuário:\n");
            scanf("%[^\n]s", nome);
            fflush(stdin);
            limparTela();
            while(!feof(nick)){
                fgets(teste,30,nick);                                              //testando os nomes
                if(strncmp(teste,nome,strlen(nome)) == 0){
                    caso = 1;
                    break;
                }
            }
            if(caso == 1){
                FILE *pass;
                char pas[100];
                strcpy(pas,"SENHAS/");
                strcat(pas,nome);
                strcat(pas,".txt");
                pass = fopen(pas,"r");
                printf("\nDigite sua senha:\n");                                        //caso em que o usuario foi encontrado no arquivo
                scanf("%[^\n]s", senha);
                fflush(stdin);
                limparTela();
                fgets(teste,30,pass);
                if(strncmp(teste,senha,strlen(senha)) == 0){                            //inscrição da senha
                    fclose(nick);
                    fclose(pass);
                    limparTela();
                    strcpy(name,nome);
                    return;

                }
                printf("\nSenha Errada! Tente Novamente\n\n");                         //Se a senha estiver errada
                fclose(nick);
                fclose(pass);
            }
            if(caso == 2)                                                             //caso em que o usuario é inexistente
                printf("\n Usuario Inexistente, por favor registre-se ou reescreva corretamente.\n\n");

        }
        if(comando == 2){                                                               //Comando de cadastro
            int sair = 0;
            char nome[30], senha[30], pas[100];
            FILE *pass;
            while(sair != 1){
                printf("\nEscreva seu nome de usuário:\n");
                scanf("%[^\n]s", nome);
                fflush(stdin);
                limparTela();
                printf("\nQual será sua senha %s?\n", nome);
                scanf("%[^\n]s", senha);
                fflush(stdin);
                limparTela();
                printf("\nSeu nome é: %s\nSua senha é: %s\n\nGostaria de finalizar o cadastro?\n\n1 - Sim\n2 - Não\n\n", nome, senha);
                scanf("%d", &sair);
                fflush(stdin);
                limparTela();
            }
            strcpy(pas,"SENHAS/");
            strcat(pas,nome);
            strcat(pas,".txt");
            pass = fopen(pas,"a");
            fprintf(pass,"%s",senha);
            nick = fopen("dadosLogin.txt","a");
            fprintf(nick,"%s\n",nome);
            fclose(nick);
            fclose(pass);
        }
        if(comando != 1 && comando != 2)
            printf("\nComando Inválido!\n\n");
    }
}
int main()
{
    char logado[30];
    login(logado);
    printf("%s", logado);
    system("pause");
    return 0;
}
