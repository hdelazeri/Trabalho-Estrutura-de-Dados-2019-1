#include "operations.h"

void loadTweetsOnStructures(Stack* tweets, AVLNode** treeHashtags, AVLNode** treeUsers, AVLNode** treeRetweets, AVLNode** treeMentions, AVLNode** treeInfluencers, AVLNode** treeEngagement, Stack** stackAssociatedHashtags)
{
	Stack* hashtags = StackInitialize();
	Stack* userTweets = StackInitialize();
	Stack* userMentions = StackInitialize();
	Stack* influencers = StackInitialize();
	Stack* engagement = StackInitialize();

	int i = 0;

	for (Stack* aux = tweets; aux != NULL; aux = aux->top) {
		Tweet* tweet = (Tweet*)aux->data;

		/*------------------- Carrega dados para A --------------------*/
		for (Stack* hashAux = tweet->hashtags; hashAux != NULL; hashAux = hashAux->top) {
			Hashtag* hashtag = (Hashtag*)hashAux->data;

			Stack* found = StackFind(hashtags, hashtag, comapareHashtagsText);

			if (!found)
				hashtags = StackPush(hashtags, hashtag);
			else {
				Hashtag* hashFound = (Hashtag*)found->data;
				hashFound->mentions++;
			}
		}

		/*------------------- Carrega dados para B --------------------*/
		User* user = (User*)tweet->user;

		Stack* found = StackFind(userTweets, user, comapareUsersName);

		if (!found)
			userTweets = StackPush(userTweets, user);
		else {
			User* userFound = (User*)found->data;
			userFound->tweets++;
		}

		/*------------------- Carrega dados para C --------------------*/
		*treeRetweets = AVLInsert(*treeRetweets, tweet, &i, comapareTweetsRetweets);

		/*------------------- Carrega dados para D --------------------*/
		for (Stack* mentionAux = tweet->mentions; mentionAux != NULL; mentionAux = mentionAux->top) {
			User* mention = (User*)mentionAux->data;

			Stack* found = StackFind(userMentions, mention, comapareUsersName);

			if (!found)
				userMentions = StackPush(userMentions, mention);
			else {
				User* userFound = (User*)found->data;
				userFound->mentions++;
			}
		}

		/*------------------- Carrega dados para E --------------------*/
		found = StackFind(influencers, user, comapareUsersName);

		if (!found) {
			user->retweets = tweet->retweets;
			influencers = StackPush(influencers, user);
		} else {
			User* userFound = (User*)found->data;
			userFound->retweets += tweet->retweets;
		}

		/*------------------- Carrega dados para F --------------------*/
		found = StackFind(engagement, user, comapareUsersName);

		if (!found) {
			user->engagement = tweet->retweets + tweet->likes;
			engagement = StackPush(engagement, user);
		}
		else {
			User* userFound = (User*)found->data;
			userFound->retweets += tweet->retweets + tweet->likes;
		}

		for (Stack* mentionAux = tweet->mentions; mentionAux != NULL; mentionAux = mentionAux->top) {
			User* mention = (User*)mentionAux->data;

			Stack* found = StackFind(engagement, mention, comapareUsersName);

			if (!found) {
				mention->engagement = 1;
				engagement = StackPush(engagement, mention);
			} else {
				User* userFound = (User*)found->data;
				userFound->engagement++;
			}
		}

		/*------------------- Carrega dados para G --------------------*/
		for (Stack* hashAux = tweet->hashtags; hashAux != NULL; hashAux = hashAux->top) {
			Hashtag* hashtag = (Hashtag*)hashAux->data;

			Stack* found = StackFind(*stackAssociatedHashtags, hashtag, comapareHashtagsText);

			if (!found)
				*stackAssociatedHashtags = StackPush(*stackAssociatedHashtags, hashtag);
			else
				hashtag = (Hashtag*)found->data;

			for (Stack* hashAuxAssociated = tweet->hashtags; hashAuxAssociated != NULL; hashAuxAssociated = hashAuxAssociated->top) {
				Hashtag* associatedHashtag = (Hashtag*)hashAuxAssociated->data;

				if (strcmp(hashtag->hashtag, associatedHashtag->hashtag) == 0)
					continue;

				Stack* found = StackFind(hashtag->associated, associatedHashtag, comapareHashtagAssociated);

				if (!found) {
					AssociatedHashtag* associated = malloc(sizeof(AssociatedHashtag));

					strcpy(associated->hashtag, associatedHashtag->hashtag);
					associated->count = 1;

					hashtag->associated = StackPush(hashtag->associated, associated);
				}
				else {
					AssociatedHashtag* associated = (AssociatedHashtag*)found->data;
					associated->count++;
				}
			}
		}
	}

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