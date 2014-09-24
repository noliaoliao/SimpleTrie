// Trie.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Trie.h"
#include "string.h"
#include "stdlib.h"

int _tmain(int argc, _TCHAR* argv[])
{
	pTrieNode pMyTrie = (pTrieNode)malloc(sizeof(TrieNode));
	initTrieNode(pMyTrie);
	
	//��ȡ�����ı�
	FILE *fWords = fopen("words.txt","r");
	if(fWords == NULL) return 0;
	char szBuf[MAX_WORD_LEN] = {0};
	while(fgets(szBuf,MAX_WORD_LEN,fWords) != NULL) //����뻻�з�������
	{
		szBuf[strlen(szBuf)-1] = '\0';
		addWord(pMyTrie,szBuf);
		memset(szBuf,0,MAX_WORD_LEN);
	}
	fclose(fWords);

	//����
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
		//��ĸƥ��
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//��ĸ��ƥ�䣬�����һ����ĸ�ڵ�
		else
		{
			pTrieNode pNode = (pTrieNode)malloc(sizeof(TrieNode));   //�½�һ���ڵ�
			initTrieNode(pNode,szWord[i]);         //��ֵ
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
		//��ĸƥ��
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//��ĸ��ƥ�䣬�������������
		else
		{
			return 0;
		}
	}
	
	//���ַ�����ĩβ,�������ٴ�������ַ���,ֱ�ӽ���ʶλ����
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
		//��ĸƥ��
		if(pCur->next[szWord[i]-'a'] != NULL && pCur->next[szWord[i]-'a']->cData == szWord[i])
		{
			pCur = pCur->next[szWord[i]-'a'];
			continue;
		}
		//��ĸ��ƥ�䣬�������������
		else
		{
			return false;
		}
	}

	//���ҵ�����ĩβ,������ʱ��Ϊtrue,���ҵ�
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