#pragma once

#include "Stack.h"
#include "TweetProcessor.h"
#include "avl.h"
#include "compareFunctions.h"

void loadTweetsOnStructures(Stack* tweets, AVLNode** treeHashtags, AVLNode** treeUsers, AVLNode** treeRetweets, AVLNode** treeMentions);