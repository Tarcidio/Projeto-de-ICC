void login(char *name){
    for(;;){                                            //mantendo a tela de login até a entrada do usuário
        limparTela();
        int comando = 0;
        FILE *nick;

        cout << "--------------------------------------------------------------------------------\n";
        cout << "\nEnvie um comando:\n";
        cout << "1 - Entrar\n\n";
        cout << "2 - Se registrar\n";
        cout << "\n--------------------------------------------------------------------------------";

        //sugestão: colocar getch
        scanf("%d", &comando);                          //escolha do comando
        fflush(stdin);

        limparTela();
        //Seria interessante se pudessemos tratar o erro em que o usuário tentar logar quando ainda não há
        //nenhum registro de conta
        if(comando == 1){                                               //comando "entrar no app"
            char nome[30],senha[30],teste[30];
            int caso = 2;

            nick = fopen("dadosLogin.txt","r");
            cout << "\nDigite seu usuário:\n";
            scanf("%[^\n]s", nome);
            setbuf(stdin, NULL);

            limparTela();
            while( !feof(nick) ){
                fgets(teste,30,nick);                                              //testando os nomes
                if(strncmp(teste,nome,strlen(nome)) == 0){
                    caso = 1;
                    break;
                }
            }

            //Todos esses casos poderiam virar uma função
            if(caso == 1){
                FILE *pass;
                char pas[100];

                strcpy(pas,"senhas/");
                strcat(pas,nome);
                strcat(pas,".txt");
                pass = fopen(pas,"r");

                cout << "\nDigite sua senha:\n";                                        //caso em que o usuario foi encontrado no arquivo
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

                cout << "\nSenha Errada! Tente Novamente\n\n";                         //Se a senha estiver errada
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
                cout << "\nEscreva seu nome de usuário (use, no máximo, 30 caracteres):\n";
                scanf("%[^\n]s", nome);
                setbuf(stdin, NULL);
                //Podemos colocar uma função que veriica se o usuario tem menos de 20 caracteres

                cout << "\nQual será sua senha, " << nome <<  "?\n";
                scanf("%[^\n]s", senha);
                setbuf(stdin, NULL);

                cout << "\nSeu nome é: " << nome;
                cout << "\nSua senha é: " << senha;

                cout << "\n\nGostaria de finalizar ou reiniciar o cadastro?" ;
                cout << "Caso reinicie, esse usuário e essa senha não serão cadastradas\n";
                cout << "1 - Finalizar\n";
                cout << "2 - Reiniciar\n\n";
                //Podeira ter a opção de cancelar o registro
                scanf("%d", &sair);
                fflush(stdin);
            }
            strcpy(pas,"senhas/");
            strcat(pas,nome);
            strcat(pas,".txt");
            pass = fopen(pas,"a");
            fprintf(pass,"%s",senha);

            nick = fopen("dadosLogin.txt","a");
            fprintf(nick,"%s\n",nome);
            fclose(nick);
            fclose(pass);
            free(nick);
            free(pass);
        }
        if(comando != 1 && comando != 2){
            printf("\nComando Inválido!\n\n");
            system("pause");
        }
    }
}
