#pragma once

#include "Stack.h"
#include "TweetProcessor.h"
#include "avl.h"
#include "compareFunctions.h"

void loadTweetsOnStructures(Stack* tweets, AVLNode** treeHashtags, AVLNode** treeUsers, AVLNode** treeRetweets, AVLNode** treeMentions, AVLNode** treeInfluencers, AVLNode** treeEngagement, Stack** stackAssociatedHashtags);

void operationA(FILE* destination, AVLNode* hashtags, int quantity);

void operationB(FILE* destination, AVLNode* users, int quantity);

void operationC(FILE* destination, AVLNode* retweets, int quantity);

void operationD(FILE* destination, AVLNode* mentions, int quantity);

void operationE(FILE* destination, AVLNode* influencers, int quantity);

void operationF(FILE* destination, AVLNode* engagements, int quantity);

void operationG(FILE* destination, Stack* engagements, Hashtag* hashtag);