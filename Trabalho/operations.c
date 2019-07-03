#include "operations.h"

// Função que carrega os dados nas estruturas de dados
void loadTweetsOnStructures(Stack* tweets, AVLNode** treeHashtags, AVLNode** treeUsers, AVLNode** treeRetweets, AVLNode** treeMentions, AVLNode** treeInfluencers, AVLNode** treeEngagement, Stack** stackAssociatedHashtags)
{
	// Inicializa as estruturas auxiliares
	Stack* hashtags = StackInitialize();
	Stack* userTweets = StackInitialize();
	Stack* userMentions = StackInitialize();
	Stack* influencers = StackInitialize();
	Stack* engagement = StackInitialize();

	int i = 0;

	// Percorre a pilha de tweets
	for (Stack* aux = tweets; aux != NULL; aux = aux->top) {
		// Converte o dado da pilha para um tweet
		Tweet* tweet = (Tweet*)aux->data;

		/*------------------- Carrega dados para A --------------------*/
		/*---------- Listar as hashtags mais citadas na rede ----------*/

		// Percorre a pilha de hashtags pro tweet e atualiza as informações necessárias
		for (Stack* hashAux = tweet->hashtags; hashAux != NULL; hashAux = hashAux->top) {
			Hashtag* hashtag = (Hashtag*)hashAux->data;

			// Procura a hashtag atual na pilha de hashtags
			Stack* found = StackFind(hashtags, hashtag, comapareHashtagsText);

			if (!found)
				// Se não encontrou adicona na pilha
				hashtags = StackPush(hashtags, hashtag);
			else {
				// Se encontrou incrementa a quantidade de menções
				Hashtag* hashFound = (Hashtag*)found->data;
				hashFound->mentions++;
			}
		}

		/*------------------- Carrega dados para B --------------------*/
		/*------------ Listar os usuários que mais tweetam ------------*/

		// Obtém o usuário do tweet
		User* user = (User*)tweet->user;

		// Procura ele na pilha de usuários
		Stack* found = StackFind(userTweets, user, comapareUsersName);

		if (!found)
			// Se não encontrou adiciona na pilha
			userTweets = StackPush(userTweets, user);
		else {
			// Se encontrou incrementa a quantidade de tweets
			User* userFound = (User*)found->data;
			userFound->tweets++;
		}

		/*------------------- Carrega dados para C --------------------*/
		/*------- Listar os tweets com maior número de retweets -------*/

		// Adicina os dados na árvore de retweets
		*treeRetweets = AVLInsert(*treeRetweets, tweet, &i, comapareTweetsRetweets);

		/*------------------- Carrega dados para D --------------------*/
		/*------ Listar os usuários mais mencionandos nos tweets ------*/

		// Percorre a pilha de menções do tweet
		for (Stack* mentionAux = tweet->mentions; mentionAux != NULL; mentionAux = mentionAux->top) {
			// Obtém o usuário mencionado
			User* mention = (User*)mentionAux->data;

			// Procura o usuário na pilha de menções
			Stack* found = StackFind(userMentions, mention, comapareUsersName);

			if (!found)
				// Se não encontrou coloca na pilha
				userMentions = StackPush(userMentions, mention);
			else {
				// Se encontrou incrementa a quantidade de menções
				User* userFound = (User*)found->data;
				userFound->mentions++;
			}
		}

		/*------------------- Carrega dados para E --------------------*/
		/*------------ Listar os usuários mais influentes ------------*/

		// Procura o usuário na pilha de influenciadores
		found = StackFind(influencers, user, comapareUsersName);

		if (!found) {
			// Se não encontrou adicona na pilha
			user->retweets = tweet->retweets;
			influencers = StackPush(influencers, user);
		} else {
			// Se encontrou atualiza os valores necessários
			User* userFound = (User*)found->data;
			userFound->retweets += tweet->retweets;
		}

		/*------------------- Carrega dados para F --------------------*/
		/*--------- Listar os usuários mais engajados na rede ---------*/

		// Procura o usuário na pilha de engajados
		found = StackFind(engagement, user, comapareUsersName);

		if (!found) {
			// Se não encontrou adiciona na pilha
			user->engagement = tweet->retweets + tweet->likes;
			engagement = StackPush(engagement, user);
		}
		else {
			// Se encontrou atualiza os valores necessários
			User* userFound = (User*)found->data;
			userFound->retweets += tweet->retweets + tweet->likes;
		}

		// Percorre a lista de menções
		for (Stack* mentionAux = tweet->mentions; mentionAux != NULL; mentionAux = mentionAux->top) {
			// Obtém o usuário da menção
			User* mention = (User*)mentionAux->data;

			// Procura o usuário na pilha de engajados
			Stack* found = StackFind(engagement, mention, comapareUsersName);

			if (!found) {
				// Se não encontrou adiciona na pilha
				mention->engagement = 1;
				engagement = StackPush(engagement, mention);
			} else {
				// Se encontrou atualiza os valores
				User* userFound = (User*)found->data;
				userFound->engagement++;
			}
		}

		/*------------------- Carrega dados para G --------------------*/
		/*-------- Listar hashtags associadas a outra hashtag ---------*/
		
		// Percorre a pilha de hashtags do tweet
		for (Stack* hashAux = tweet->hashtags; hashAux != NULL; hashAux = hashAux->top) {
			// Obtém a hashtag
			Hashtag* hashtag = (Hashtag*)hashAux->data;

			// Procura na pilha de hashtags associadas
			Stack* found = StackFind(*stackAssociatedHashtags, hashtag, comapareHashtagsText);

			if (!found)
				// Se não encontrou adiciona na pilha
				*stackAssociatedHashtags = StackPush(*stackAssociatedHashtags, hashtag);
			else
				// Se encontrou atualiza os dados
				hashtag = (Hashtag*)found->data;

			// Percorre pilha de hashtags do tweet novamente
			for (Stack* hashAuxAssociated = tweet->hashtags; hashAuxAssociated != NULL; hashAuxAssociated = hashAuxAssociated->top) {
				// Obtém a hashtag associada
				Hashtag* associatedHashtag = (Hashtag*)hashAuxAssociated->data;

				// Se a hashtag associada for igual a principal ignora
				if (strcmp(hashtag->hashtag, associatedHashtag->hashtag) == 0)
					continue;

				// Procura a hashtag associada na pilha de hashtagas associadas da hashtag principal
				Stack* found = StackFind(hashtag->associated, associatedHashtag, comapareHashtagAssociated);

				if (!found) {
					// Se não encontrou adiciona na pilha
					AssociatedHashtag* associated = malloc(sizeof(AssociatedHashtag));

					strcpy(associated->hashtag, associatedHashtag->hashtag);
					associated->count = 1;

					hashtag->associated = StackPush(hashtag->associated, associated);
				}
				else {
					// Se encontrou atualiza os valores necessários
					AssociatedHashtag* associated = (AssociatedHashtag*)found->data;
					associated->count++;
				}
			}
		}
	}

	// Após percorrer todos os tweets adiciona todos os dados nas AVLs

	for (Stack* aux = hashtags; aux != NULL; aux = aux->top)
		*treeHashtags = AVLInsert(*treeHashtags, aux->data, &i, comapareHashtagsMentions);

	for (Stack* aux = userTweets; aux != NULL; aux = aux->top)
		*treeUsers = AVLInsert(*treeUsers, aux->data, &i, comapareUsersTweets);

	for (Stack* aux = userMentions; aux != NULL; aux = aux->top)
		*treeMentions = AVLInsert(*treeMentions, aux->data, &i, comapareUsersMentions);

	for (Stack* aux = influencers; aux != NULL; aux = aux->top)
		*treeInfluencers = AVLInsert(*treeInfluencers, aux->data, &i, comapareUsersRetweets);

	for (Stack* aux = engagement; aux != NULL; aux = aux->top)
		*treeEngagement = AVLInsert(*treeEngagement, aux->data, &i, comapareUsersEngagement);
}

// Função que executa a operação A
void operationA(FILE* destination, AVLNode* hashtags, int quantity) {
	fprintf(destination, "--- OP A\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(hashtags, i, &count);

		if (node == NULL)
			break;

		Hashtag hashtag = *((Hashtag*)node->info);

		fprintf(destination, "%s,%d\n", hashtag.hashtag, hashtag.mentions);
	}
}

// Função que executa a operação B
void operationB(FILE* destination, AVLNode* users, int quantity) {
	fprintf(destination, "--- OP B\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(users, i, &count);

		if (node == NULL)
			break;

		User user = *((User*)node->info);

		fprintf(destination, "%s,%d\n", user.name, user.tweets);
	}
}

// Função que executa a operação C
void operationC(FILE* destination, AVLNode* retweets, int quantity) {
	fprintf(destination, "--- OP C\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(retweets, i, &count);

		if (node == NULL)
			break;

		Tweet tweet = *((Tweet*)node->info);

		fprintf(destination, "%s,%d\n", tweet.text, tweet.retweets);
	}
}

// Função que executa a operação D
void operationD(FILE* destination, AVLNode* mentions, int quantity) {
	fprintf(destination, "--- OP D\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(mentions, i, &count);

		if (node == NULL)
			break;

		User user = *((User*)node->info);

		fprintf(destination, "%s,%d\n", user.name, user.mentions);
	}
}

// Função que executa a operação E
void operationE(FILE* destination, AVLNode* influencers, int quantity) {
	fprintf(destination, "--- OP E\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(influencers, i, &count);

		if (node == NULL)
			break;

		User user = *((User*)node->info);

		fprintf(destination, "%s,%d\n", user.name, user.retweets);
	}
}

// Função que executa a operação F
void operationF(FILE* destination, AVLNode* engagements, int quantity) {
	fprintf(destination, "--- OP F\n");

	int printAll = 0;

	if (quantity == 0)
		printAll = 1;

	for (int i = 1; printAll || i <= quantity; i++) {
		int count = 0;

		AVLNode* node = AVLNNodeCenteredRight(engagements, i, &count);

		if (node == NULL)
			break;

		User user = *((User*)node->info);

		fprintf(destination, "%s,%d\n", user.name, user.engagement);
	}
}

// Função que executa a operação G
void operationG(FILE* destination, Stack* associatedHashtags, Hashtag* hashtag) {
	fprintf(destination, "--- OP G\n");

	Stack* found = StackFind(associatedHashtags, hashtag, comapareHashtagsText);

	if (found) {
		*hashtag = *((Hashtag*)found->data);

		for (Stack* associatedAux = hashtag->associated; associatedAux != NULL; associatedAux = associatedAux->top) {
			AssociatedHashtag associated = *((AssociatedHashtag*)associatedAux->data);

			fprintf(destination, "%s,%d\n", associated.hashtag, associated.count);
		}
	}
}