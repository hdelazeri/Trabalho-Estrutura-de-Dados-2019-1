#include "compareFunctions.h"

int comapareHashtagsText(void* a, void* b) {
	Hashtag hashtag1 = *((Hashtag*)a);
	Hashtag hashtag2 = *((Hashtag*)b);

	return strcmp(hashtag1.hashtag, hashtag2.hashtag);
}

int comapareHashtagsMentions(void* a, void* b) {
	Hashtag hashtag1 = *((Hashtag*)a);
	Hashtag hashtag2 = *((Hashtag*)b);

	return hashtag1.mentions - hashtag2.mentions;
}

int comapareUsersName(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return strcmp(user1.name, user2.name);
}

int comapareUsersMentions(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return user1.mentions - user2.mentions;
}

int comapareTweetsRetweets(void* a, void* b) {
	Tweet tweet1 = *((Tweet*)a);
	Tweet tweet2 = *((Tweet*)b);

	return tweet1.retweets - tweet2.retweets;
}

int comapareUsersTweets(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return user1.tweets - user2.tweets;
}

int comapareUsersRetweets(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return user1.retweets - user2.retweets;
}

int comapareUsersEngagement(void* a, void* b) {
	User user1 = *((User*)a);
	User user2 = *((User*)b);

	return user1.engagement - user2.engagement;
}

int comapareHashtagAssociated(void* a, void* b) {
	AssociatedHashtag  associated = *((AssociatedHashtag*)a);
	Hashtag hashtag = *((Hashtag*)b);

	return strcmp(associated.hashtag, hashtag.hashtag);
}