// Trie.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Trie.h"
#include "string.h"
#include "stdlib.h"

int _tmain(int argc, _TCHAR* argv[])
{
	pTrieNode pMyTrie = (pTrieNode)malloc(sizeof(TrieNode));
	initTrieNode(pMyTrie);
	
	//读取单词文本
	FILE *fWords = fopen("words.txt","r");
	if(fWords == NULL) return 0;
	char szBuf[MAX_WORD_LEN] = {0};
	while(fgets(szBuf,MAX_WORD_LEN,fWords) != NULL) //会读入换行符。。。
	{
		szBuf[strlen(szBuf)-1] = '\0';
		addWord(pMyTrie,szBuf);
		memset(szBuf,0,MAX_WORD_LEN);
	}
	fclose(fWords);

	//查找
	findWord(pMyTrie,"gram",true);
    
	return 0;
}


int initTrieNode(pTrieNode pNode,char cNum)
{
	pNode->bIsWord = false;
	pNode->count = 0;
	pNode->cData = cNum;
	for(int i = 0; i < MAX_CHAR_NUM; i++)
	{
		pNode->next[i] = NULL;
	}

	return 0;
}


int addWord(pTrieNode pHead,const char *szWord)
{
	pTrieNode pCur = pHead;
	int nWordLen = strlen(szWord);

	for(int i = 0; i < nWordLen; i++)
	{
		//字母匹配
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//字母不匹配，则添加一个字母节点
		else
		{
			pTrieNode pNode = (pTrieNode)malloc(sizeof(TrieNode));   //新建一个节点
			initTrieNode(pNode,szWord[i]);         //赋值
			pCur->next[szWord[i]-'a'] = pNode;
			pCur = pNode;
		}
	}
	
	pCur->bIsWord = true;
	pCur->count++;

	return 0;
}


int delWord(pTrieNode pHead,const char *szWord)
{
	pTrieNode pCur = pHead;
	int nWordLen = strlen(szWord);

	for(int i = 0; i < nWordLen; i++)
	{
		//字母匹配
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//字母不匹配，不存在这个单词
		else
		{
			return 0;
		}
	}
	
	//到字符串的末尾,树中至少存在这个字符串,直接将标识位重置
	pCur->bIsWord = false;
	pCur->count = 0;

	return 0;
}


bool findWord(pTrieNode pHead,const char *szWord, bool bAll)
{
	pTrieNode pCur = pHead;
	int       nWordLen = strlen(szWord);
	bool      bRet = false;
	for(int i = 0; i < nWordLen; i++)
	{
		//字母匹配
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//字母不匹配，不存在这个单词
		else
		{
			return false;
		}
	}

	//查找到单词末尾,如果单词标记为true,则找到
	bRet = pCur->bIsWord;
	if(bRet == true) printf("%s\n",szWord);

	char szPrefix[MAX_CHAR_NUM] = {0};
	strcpy(szPrefix,szWord);
	if(bAll)
	{
		for(int i = 0; i < MAX_CHAR_NUM; i++)
		{
			if(pCur->next[i] != NULL)
			{
				//printf("%s",szPrefix);
				showAll(pCur->next[i],szPrefix);
			}
		}
		//showAll(pCur,szPrefix);
	}

	return bRet;
}

int showAll(pTrieNode pNode,char *szPrefix)
{
	//printf("%s",szPrefix);
	//printf("%c",pNode->cData);
	char szCurPrefix[MAX_WORD_LEN] = {0};
	strcpy(szCurPrefix,szPrefix);
	szCurPrefix[strlen(szPrefix)] = pNode->cData;
	if(pNode->bIsWord == true)
	{
		//printf("\n");
		printf("%s\n",szCurPrefix);
	}
	for(int i = 0; i < MAX_CHAR_NUM; i++)
	{
		if(pNode->next[i] != NULL)
		{
			//printf("%s",szPrefix);
			showAll(pNode->next[i],szCurPrefix);
		}
	}

	return 0;
}