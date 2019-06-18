#include "operations.h"

void loadTweetsOnStructures(Stack* tweets, AVLNode** treeHashtags, AVLNode** treeUsers, AVLNode** treeRetweets, AVLNode** treeMentions)
{
	for (Stack* aux = tweets; aux != NULL; aux = aux->top) {
		Tweet* tweet = (Tweet*)aux->data;
		int i = 0;

		/*------------------- Carrega dados para A --------------------*/
		for (Stack* hashAux = tweet->hashtags; hashAux != NULL; hashAux = hashAux->top) {
			Hashtag* hashtag = (Hashtag*)hashAux->data;

			AVLNode* found = AVLFind(*treeHashtags, hashtag, comapareHashtagsText);

			if (!found)
				*treeHashtags = AVLInsert(*treeHashtags, hashtag, &i, comapareHashtagsMentions);
			else {
				Hashtag* hashFound = (Hashtag*)found->info;
				hashFound->mentions++;
			}
		}

		/*------------------- Carrega dados para B --------------------*/
		User* user = (User*)tweet->user;

		AVLNode* found = AVLFind(*treeUsers, user, comapareUsersName);

		if (!found)
			*treeUsers = AVLInsert(*treeUsers, user, &i, comapareUsersName);
		else {
			User* userFound = (User*)found->info;
			userFound->tweets++;
		}

		/*------------------- Carrega dados para C --------------------*/
		*treeRetweets = AVLInsert(*treeRetweets, tweet, &i, comapareTweetsRetweets);

		/*------------------- Carrega dados para D --------------------*/
		for (Stack* mentionAux = tweet->mentions; mentionAux != NULL; mentionAux = mentionAux->top) {
			User* mention = (User*)mentionAux->data;

			AVLNode* found = AVLFind(*treeMentions, mention, comapareUsersName);

			if (!found)
				*treeMentions = AVLInsert(*treeMentions, mention, &i, comapareUsersMentions);
			else {
				User* userFound = (User*)found->info;
				userFound->mentions++;
			}
		}
	}
}
