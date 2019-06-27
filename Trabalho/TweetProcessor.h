#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct s_Hashtag {
	int mentions;
	char hashtag[100];
	Stack* associated;
} Hashtag;

typedef struct s_HashtagAssociated {
	char hashtag[100];
	int count;
} AssociatedHashtag;

typedef struct s_User {
	int tweets;
	int mentions;
	int retweets;
	int engagement;
	char name[100];
} User;

typedef struct s_Tweet {
	void* user;
	char text[240];
	int retweets;
	int likes;
	Stack* hashtags;
	Stack* mentions;
} Tweet;

Stack* readAllTweets(FILE* input);
int readTweet(FILE* input, Tweet* tweet);
void printAll(Stack* tweets);