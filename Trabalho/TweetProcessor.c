#include "TweetProcessor.h"

Stack* readAllTweets(FILE* input) {
	Stack* stack = StackInitialize();
	Tweet* tweet = malloc(sizeof(Tweet));

	while (readTweet(input, tweet)) {
		stack = StackPush(stack, tweet);
		tweet = malloc(sizeof(Tweet));
	}

	free(tweet);

	return stack;
}

int readTweet(FILE* input, Tweet* tweet)
{
	char linha[300], text[240];
	char* palavra;

	if (fgets(linha, 300, input)) {
		User* user = malloc(sizeof(User));
		user->tweets = 1;
		user->mentions = 1;

		palavra = strtok(linha, ";");
		strcpy(user->name, palavra);

		tweet->user = user;

		palavra = strtok(NULL, ";");
		strcpy(tweet->text, palavra);

		palavra = strtok(NULL, ";");
		tweet->retweets = atoi(palavra);

		palavra = strtok(NULL, ";");
		tweet->likes = atoi(palavra);

		strcpy(text, tweet->text);
		tweet->hashtags = StackInitialize();

		palavra = strtok(text, "#");

		if (text[0] != '#')
			palavra = strtok(NULL, "#");

		while (palavra != NULL) {
			Hashtag* hashtag = malloc(sizeof(Hashtag));
			hashtag->mentions = 1;
			hashtag->associated = StackInitialize();

			for (int i = 0; i < 99 && *palavra != ' ' && *palavra != '\0'; i++, palavra++) {
				hashtag->hashtag[i] = *palavra;
				hashtag->hashtag[i + 1] = '\0';
			}

			char buffer[100] = "#";

			strcat(buffer, hashtag->hashtag);

			strcpy(hashtag->hashtag, buffer);

			tweet->hashtags = StackPush(tweet->hashtags, hashtag);
			palavra = strtok(NULL, "#");
		}

		strcpy(text, tweet->text);
		tweet->mentions = StackInitialize();

		palavra = strtok(text, "@");

		if (text[0] != '@')
			palavra = strtok(NULL, "@");

		while (palavra != NULL) {
			User* user = malloc(sizeof(User));
			user->tweets = 1;
			user->mentions = 1;

			for (int i = 0; i < 99 && *palavra != ' ' && *palavra != '\0'; i++, palavra++) {
				user->name[i] = *palavra;
				user->name[i + 1] = '\0';
			}

			char buffer[100] = "@";

			strcat(buffer, user->name);

			strcpy(user->name, buffer);

			tweet->mentions = StackPush(tweet->mentions, user);
			palavra = strtok(NULL, "@");
		}

		return 1;
	}

	return 0;
}

void printAll(Stack* tweets)
{
	for (Stack* aux = tweets; aux != NULL; aux = aux->top) {
		Tweet tweet = *((Tweet*)aux->data);

		User user = *((User*)tweet.user);

		printf("Usuário: %s\nTexto: \"%s\"\nRetweets: %d\nLikes: %d\n", user.name, tweet.text, tweet.retweets, tweet.likes);

		printf("Hastaghs: ");
		for (Stack* hashAux = tweet.hashtags; hashAux != NULL; hashAux = hashAux->top) {
			Hashtag hashtag = *((Hashtag*)hashAux->data);
			printf("%s, ", hashtag.hashtag);
		}

		printf("\nMenções: ");
		for (Stack* mentAux = tweet.mentions; mentAux != NULL; mentAux = mentAux->top) {
			User mention = *((User*)mentAux->data);
			printf("%s, ", mention.name);
		}

		printf("\n\n");
	}
}
