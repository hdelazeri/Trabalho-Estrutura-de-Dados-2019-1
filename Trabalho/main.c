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

int main(int argc, char* argv[]) //argc conta o número de parâmetros e argv armazena as strings correspondentes aos parâmentros digitados
{
	setlocale(LC_ALL, "Portuguese"); //para imprimir corretamente na tela os caracteres acentuados

	FILE* input;
	FILE* operations;
	FILE* output;

	if (argc != 4)  //o numero de parametros esperado é 3: nome do programa (argv[0]), nome do arq de entrada(argv[1]), nome do arq de saida(argv[2])
	{
		printf("Número incorreto de parâmetros.\n Para chamar o programa digite: trabalho.exe <arq_entrada> <arq_operacoes> <arq_saida>\n");
		return 1;
	}
	else
	{
		input = fopen(argv[1], "r"); // abre o arquivo de entrada para leitura -- argv[1] é o primeiro parâmetro após o nome do arquivo.
		if (input == NULL) //se não conseguiu abrir o arquivo
		{
			printf("Erro ao abrir o arquivo de entrada: %s", argv[1]);
			return 1;
		}
		else // arquivo de entrada OK
		{
			operations = fopen(argv[2], "r"); // abre o arquivo de operações para leitura
			if (operations == NULL) //se não conseguiu abrir o arquivo
			{
				printf("Erro ao abrir o arquivo de operações: %s", argv[2]);
				return 1;
			}
			else {
				output = fopen(argv[3], "w"); // abre o arquivo de saída para escrita
				if (output == NULL) //se não conseguiu abrir o arquivo
				{
					printf("Erro ao abrir o arquivo de saída: %s", argv[3]);
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