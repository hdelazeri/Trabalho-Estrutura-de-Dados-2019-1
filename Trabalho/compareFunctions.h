#pragma once

#include <string.h>

#include "TweetProcessor.h"

int comapareHashtagsText(void* a, void* b);

int comapareHashtagsMentions(void* a, void* b);

int comapareUsersName(void* a, void* b);

int comapareTweetsRetweets(void* a, void* b);

int comapareUsersMentions(void* a, void* b);
