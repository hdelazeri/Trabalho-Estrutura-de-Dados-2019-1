#include "compareFunctions.h"

int comapareHashtagsText(void* a, void* b) {
	Hashtag hashtag1 = *((Hashtag*)a);
	Hashtag hashtag2 = *((Hashtag*)b);

	return strcmp(hashtag1.hashtag, hashtag2.hashtag);
}

int comapareHashtagsMentions(void* a, void* b) {
	Hashtag hashtag1 = *((Hashtag*)a);
	Hashtag hashtag2 = *((Hashtag*)b);

	if (hashtag1.mentions == hashtag2.mentions) {
		for (int i = 0; i < strlen(hashtag1.hashtag); i++)
		{
			if (tolower(hashtag1.hashtag[i]) == tolower(hashtag2.hashtag[i]))
				continue;
			else
				return tolower(hashtag2.hashtag[i]) - tolower(hashtag1.hashtag[i]);
		}

		return strlen(hashtag1.hashtag) - strlen(hashtag2.hashtag);
	}
	else {
		return hashtag1.mentions - hashtag2.mentions;
	}
}

int comapareUsersName(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return strcmp(user1.name, user2.name);
}

int comapareUsersMentions(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	if(user1.mentions == user2.mentions) {
		for (int i = 0; i < strlen(user1.name); i++)
		{
			if (tolower(user1.name[i]) == tolower(user2.name[i]))
				continue;
			else
				return tolower(user2.name[i]) - tolower(user1.name[i]);
		}

		return strlen(user1.name) - strlen(user2.name);
	}
	else {
		return user1.mentions - user2.mentions;
	}
}

int comapareTweetsRetweets(void* a, void* b) {
	Tweet tweet1 = *((Tweet*)a);
	Tweet tweet2 = *((Tweet*)b);

	if (tweet1.mentions == tweet2.mentions) {
		for (int i = 0; i < strlen(tweet1.text); i++)
		{
			if (tolower(tweet1.text[i]) == tolower(tweet2.text[i]))
				continue;
			else
				return tolower(tweet2.text[i]) - tolower(tweet1.text[i]);
		}

		return strlen(tweet1.text) - strlen(tweet2.text);
	}
	else {
		return tweet1.mentions - tweet2.mentions;
	}
}

int comapareUsersTweets(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	if (user1.tweets == user2.tweets) {
		for (int i = 0; i < strlen(user1.name); i++)
		{
			if (tolower(user1.name[i]) == tolower(user2.name[i]))
				continue;
			else
				return tolower(user2.name[i]) - tolower(user1.name[i]);
		}

		return strlen(user1.name) - strlen(user2.name);
	}
	else {
		return user1.tweets - user2.tweets;
	}
}

int comapareUsersRetweets(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	if (user1.retweets == user2.retweets) {
		for (int i = 0; i < strlen(user1.name); i++)
		{
			if (tolower(user1.name[i]) == tolower(user2.name[i]))
				continue;
			else
				return tolower(user2.name[i]) - tolower(user1.name[i]);
		}

		return strlen(user1.name) - strlen(user2.name);
	}
	else {
		return user1.retweets - user2.retweets;
	}
}

int comapareUsersEngagement(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return user1.engagement - user2.engagement;

	if (user1.engagement == user2.engagement) {
		for (int i = 0; i < strlen(user1.name); i++)
		{
			if (tolower(user1.name[i]) == tolower(user2.name[i]))
				continue;
			else
				return tolower(user2.name[i]) - tolower(user1.name[i]);
		}

		return strlen(user1.name) - strlen(user2.name);
	}
	else {
		return user1.engagement - user2.engagement;
	}
}

int comapareHashtagAssociated(void* a, void* b) {
	AssociatedHashtag  associated = *((AssociatedHashtag*)a);
	Hashtag hashtag = *((Hashtag*)b);

	return strcmp(associated.hashtag, hashtag.hashtag);
}