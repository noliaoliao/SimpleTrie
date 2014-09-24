#pragma once
#include "stdafx.h"

#define MAX_CHAR_NUM 26
#define MAX_WORD_LEN 15
typedef struct _TrieNode{
	bool bIsWord;     //是否为单词
	int  count;       //单词出现的次数
	char cData;       //节点字母
	struct _TrieNode * next[MAX_CHAR_NUM];  //后继指针
}TrieNode, *pTrieNode;

int initTrieNode(pTrieNode pNode,char cNum = 0);
int addWord(pTrieNode pHead,const char *szWord);
int delWord(pTrieNode pHead,const char *szWord);
bool findWord(pTrieNode pHead,const char *szWord, bool bAll = false);
int  showAll(pTrieNode pNode,char *szPrefix);
//int getIndex(char number);