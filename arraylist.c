#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"


//�迭����Ʈ�� �����ϴ� �Լ�
//(maxElementCount = �ִ� ���� ��)
ArrayList* createArrayList(int maxElementCount) {
	ArrayList *pReturn = NULL;
	int i = 0;

	if (maxElementCount > 0) {
		pReturn = (ArrayList *)malloc(sizeof(ArrayList));//malloc�� �����ϴ� ��� NULL���� ����ǰ� �ȴ�. 

		if (pReturn != NULL) { //����, malloc���Ŀ��� �޸� �Ҵ������� �� �޾��ش�. 
			pReturn->maxElementCount = maxElementCount;
			pReturn->currentElementCount = 0;
			pReturn->pElement = NULL;
		}
		else {//�޸� �Ҵ�� ���� NULL�̶�� ����
			printf("����, �޸��Ҵ� createArrayList()\n");
			return NULL;
		}
	}
	else {//Array�� ������ �� ���� ��� = 0
		printf("����, �ִ� ���� ������ 0�̻��̾�� �մϴ�\n");
		return NULL;
	}

	pReturn->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * maxElementCount);//������ �迭 ����Ʈ�� ����� �Լ�
	if (pReturn->pElement == NULL) {//�޸� �Ҵ��ߴ��� ����
		printf("����, 2��° �޸��Ҵ� createArrayList()\n");
		free(pReturn); return NULL;//�߰��� �����ϰ� �Ǹ� pReturn�� ���� free�� ���شٴ��� ����
	}
	memset(pReturn->pElement, 0, sizeof(ArrayListNode) * maxElementCount);//�����ߴٸ� �޸𸮸� 0���� �ʱ�ȭ
	//������ ���� ���� ���׸� ����� �� �ֱ� ������ 0 ���� �ʱ�ȭ���ִ� �Ƹ��ٿ� ������ ����.

	return pReturn;
}

int addALElement(ArrayList* pList, int position, ArrayListNode element) { //AL�� �߰�
					//�ּ�, ��ġ, ����
	int ret = FALSE;
	int i=0;


	//�Ƹ��ٿ� ���� : �����Ͱ� ���޵Ǿ������� �ݵ�� NULLüũ�� �ϴ� �Ƹ��ٿ� ������ �������Ѵ�. 
	if (pList != NULL) { //����Ʈ�� NULL���� üũ 
		if (isArrayListFull(pList) != TRUE) {//�������� �ʾ�����
			if (position >= 0//��ġ�� 0���� Ŀ���ϰ�
				&& position <= pList->currentElementCount)//currentElement ���� ������ �� �� �ִ�. ( 0 base�̱� ������ )
			{
				for(i = pList->currentElementCount-1; i >= position; i--) {//(currentElementCount) = ���� >  (position) =  ���� ����Ǿ��ִ� ���� �����ʿ��� �츮�� �߰��Ϸ��� ��ġ���� (i--) = ���� �������� ����
					pList->pElement[i+1] = pList->pElement[i]; //��ĭ�� �� �Ű��ش�.
				}
				pList->pElement[position] = element;//���� ���ϴ� ��ġ�� ����
				pList->currentElementCount++;//���� ������ ������ 1 �÷��ش�.
				
				ret = TRUE;
			}
			else {//���� ����
				printf("����, ��ġ �ε���-[%d] ���� �ʰ�, addALElement()\n",
						position);
			}
		}
		else {//���� ���� á��.
			printf("����, ����Ʈ �뷮 �ʰ�-[%d]/[%d]\n", 
					position, pList->maxElementCount);
		}
	}
	return ret;
}

int removeALElement(ArrayList* pList, int position) {
	int ret = FALSE;
	int i=0;

	if (pList != NULL) {
		if (position >= 0 
				&& position < pList->currentElementCount) {
			for(i = position; i < pList->currentElementCount-1; i++) {
				pList->pElement[i] = pList->pElement[i+1];
			}
			pList->currentElementCount--;
			ret = TRUE;
		}
		else {
			printf("����, ��ġ �ε���-[%d] ���� �ʰ�, removeALElement()\n",
					position);
		}
	}

	return ret;
}

ArrayListNode* getALElement(ArrayList* pList, int position) {
	ArrayListNode* pReturn = NULL;
	if (pList != NULL) {
		if (position >=0 && position < getArrayListLength(pList)) {
			pReturn = &(pList->pElement[position]);
		}
		else {
			printf("����, ��ġ �ε���-[%d] ���� �ʰ�, getALElement()\n", position);
		}
	}

	return pReturn;
}

void displayArrayList(ArrayList* pList) {
	int i = 0;
	if (pList != NULL) {
		printf("�ִ� ���� ����: %d\n", pList->maxElementCount);
		printf("���� ���� ����: %d\n", pList->currentElementCount);

		for(i = 0; i < pList->currentElementCount; i++) {
			printf("[%d],%d\n", i, getALElement(pList, i)->data);
		}
		
		i = pList->currentElementCount;
		for(; i < pList->maxElementCount; i++) {
			printf("[%d],Empty\n", i);
		}
	}
	else {
		printf("ArryList is NULL");
	}
}

int isArrayListFull(ArrayList* pList) {
	int ret = FALSE;

	if (pList != NULL) {
		if (pList->currentElementCount == pList->maxElementCount) {
			ret = TRUE;
		}
	}

	return ret;
}

int getArrayListLength(ArrayList* pList) {
	int ret = 0;

	if (pList != NULL) {
		ret = pList->currentElementCount;
	}

	return ret;
}

void deleteArrayList(ArrayList* pList)
{
	int i = 0;
	if (pList != NULL) {
		free(pList->pElement);
		free(pList);
	}
}
