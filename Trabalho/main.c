#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#include "TweetProcessor.h"
#include "operations.h"
#include "avl.h"

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
					// Vari�veis auxiliares
					clock_t start, end;
					char linha[100];

					// Come�a a contabilizar o tempo de carregamento
					start = clock();

					// Le todos os tweets do arquivo
					Stack* tweets = readAllTweets(input);

					// Inicializa as estruturas de dados
					AVLNode* hashtagTree = AVLInitialize();
					AVLNode* usersTree = AVLInitialize();
					AVLNode* retweetsTree = AVLInitialize();
					AVLNode* mentionsTree = AVLInitialize();
					AVLNode* influencersTree = AVLInitialize();
					AVLNode* engagementTree = AVLInitialize();
					Stack* associatedHashtags = StackInitialize();
					
					// Carrega os dados nas estruturas
					loadTweetsOnStructures(tweets, &hashtagTree, &usersTree, &retweetsTree, &mentionsTree, &influencersTree, &engagementTree, &associatedHashtags);

					// Para de contabilizar o tempo de carregamento
					end = clock();

					double loadTime = ((double)(end - start)) / CLOCKS_PER_SEC;

					printf("Time to load data: %f\n\n", loadTime);

					// Come�a a contabilizar o tempo de gera��o do arquivo de sa�da
					start = clock();

					// Executa as opera��es contidas no arquivo de opera��es
					while (fgets(linha, 100, operations)) {
						char* part;

						part = strtok(linha, ";");

						strlwr(part);

						switch (*part) {
							case 'a':
								part = strtok(NULL, ";");
								operationA(output, hashtagTree, atoi(part));
								break;
							case 'b':
								part = strtok(NULL, ";");
								operationB(output, usersTree, atoi(part));
								break;
							case 'c':
								part = strtok(NULL, ";");
								operationC(output, retweetsTree, atoi(part));
								break;
							case 'd':
								part = strtok(NULL, ";");
								operationD(output, mentionsTree, atoi(part));
								break;
							case 'e':
								part = strtok(NULL, ";");
								operationE(output, influencersTree, atoi(part));
								break;
							case 'f':
								part = strtok(NULL, ";");
								operationF(output, engagementTree, atoi(part));
								break;
							case 'g':
								part = strtok(NULL, ";");

								Hashtag hashtag;
								strcpy(hashtag.hashtag, part);

								operationG(output, associatedHashtags, &hashtag);
								break;
						}
					}

					// Para de contabilizar o tempo de gera��o do arquivo de sa�da
					end = clock();

					double fileTime = ((double)(end - start)) / CLOCKS_PER_SEC;

					printf("Time to generate output file: %f\n\n", fileTime);
				}
			}
		}

		fclose(input); //fecha os arquivos
		fclose(operations);
		fclose(output);

		return 0;
	}
}