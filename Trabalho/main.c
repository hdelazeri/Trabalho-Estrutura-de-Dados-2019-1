#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#include "TweetProcessor.h"
#include "operations.h"
#include "avl.h"

void printHashtag(void* a) {
	Hashtag hashtag = *((Hashtag*)a);

	printf("%s - %d\n", hashtag.hashtag, hashtag.mentions);
}

void printUser(void* a) {
	User user = *((User*)a);

	printf("%s - %d\n", user.name, user.tweets);
}

void printRetweets(void* a) {
	Tweet tweet = *((Tweet*)a);

	printf("%s - %d\n", tweet.text, tweet.retweets);
}

void printMentions(void* a) {
	User user = *((User*)a);

	printf("%s - %d\n", user.name, user.mentions);
}

int main(int argc, char* argv[]) //argc conta o n�mero de par�metros e argv armazena as strings correspondentes aos par�mentros digitados
{
	setlocale(LC_ALL, "Portuguese"); //para imprimir corretamente na tela os caracteres acentuados

	FILE* input;
	FILE* operations;
	FILE* output;

	if (argc != 4)  //o numero de parametros esperado � 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
	{
		printf("N�mero incorreto de par�metros.\n Para chamar o programa digite: trabalho.exe <arq_entrada> <arq_operacoes> <arq_saida>\n");
		return 1;
	}
	else
	{
		input = fopen(argv[1], "r"); // abre o arquivo de entrada para leitura -- argv[1] � o primeiro par�metro ap�s o nome do arquivo.
		if (input == NULL) //se n�o conseguiu abrir o arquivo
		{
			printf("Erro ao abrir o arquivo de entrada: %s", argv[1]);
			return 1;
		}
		else // arquivo de entrada OK
		{
			operations = fopen(argv[2], "r"); // abre o arquivo de opera��es para leitura
			if (operations == NULL) //se n�o conseguiu abrir o arquivo
			{
				printf("Erro ao abrir o arquivo de opera��es: %s", argv[2]);
				return 1;
			}
			else {
				output = fopen(argv[3], "w"); // abre o arquivo de sa�da para escrita
				if (output == NULL) //se n�o conseguiu abrir o arquivo
				{
					printf("Erro ao abrir o arquivo de sa�da: %s", argv[3]);
					return 1;
				}
				else {
					Stack* tweets = readAllTweets(input);

					AVLNode* hashtagTree = AVLInitialize();
					AVLNode* usersTree = AVLInitialize();
					AVLNode* retweetsTree = AVLInitialize();
					AVLNode* mentionsTree = AVLInitialize();
					
					loadTweetsOnStructures(tweets, &hashtagTree, &usersTree, &retweetsTree, &mentionsTree);

					printAll(tweets);

					/*printf("\n\n\n\n\n\n");

					CenteredRight(hashtagTree, printHashtag);

					printf("\n\n\n\n\n\n");

					CenteredRight(usersTree, printUser);

					printf("\n\n\n\n\n\n");

					CenteredRight(retweetsTree, printRetweets);

					printf("\n\n\n\n\n\n");

					CenteredRight(mentionsTree, printMentions);*/
				}
			}
		}

		fclose(input); //fecha os arquivos
		fclose(operations);
		fclose(output);

		return 0;
	}
}