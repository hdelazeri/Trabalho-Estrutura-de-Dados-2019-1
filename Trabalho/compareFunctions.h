#pragma once

#include <ctype.h>
#include <string.h>

#include "TweetProcessor.h"

int comapareHashtagsText(void* a, void* b);

int comapareHashtagsMentions(void* a, void* b);

int comapareUsersName(void* a, void* b);

int comapareTweetsRetweets(void* a, void* b);

int comapareUsersMentions(void* a, void* b);

int comapareUsersTweets(void* a, void* b);

int comapareUsersRetweets(void* a, void* b);

int comapareUsersEngagement(void* a, void* b);

int comapareHashtagAssociated(void* a, void* b);
