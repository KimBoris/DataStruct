#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"


//배열리스트를 생성하는 함수
//(maxElementCount = 최대 원소 수)
ArrayList* createArrayList(int maxElementCount) {
	ArrayList *pReturn = NULL;
	int i = 0;

	if (maxElementCount > 0) {
		pReturn = (ArrayList *)malloc(sizeof(ArrayList));//malloc이 실패하는 경우 NULL값이 실행되게 된다. 

		if (pReturn != NULL) { //따라서, malloc이후에는 메모리 할당조건을 꼭 달아준다. 
			pReturn->maxElementCount = maxElementCount;
			pReturn->currentElementCount = 0;
			pReturn->pElement = NULL;
		}
		else {//메모리 할당된 값이 NULL이라면 오류
			printf("오류, 메모리할당 createArrayList()\n");
			return NULL;
		}
	}
	else {//Array를 생성할 수 없는 경우 = 0
		printf("오류, 최대 원소 개수는 0이상이어야 합니다\n");
		return NULL;
	}

	pReturn->pElement = (ArrayListNode *)malloc(sizeof(ArrayListNode) * maxElementCount);//실제로 배열 리스트를 만드는 함수
	if (pReturn->pElement == NULL) {//메모리 할당했는지 점검
		printf("오류, 2번째 메모리할당 createArrayList()\n");
		free(pReturn); return NULL;//중간에 실패하게 되면 pReturn에 대해 free를 해준다는점 주의
	}
	memset(pReturn->pElement, 0, sizeof(ArrayListNode) * maxElementCount);//성공했다면 메모리를 0으로 초기화
	//가비지 값이 많은 버그를 양산할 수 있기 때문에 0 으로 초기화해주는 아름다운 습관을 권장.

	return pReturn;
}

int addALElement(ArrayList* pList, int position, ArrayListNode element) { //AL을 추가
					//주소, 위치, 원소
	int ret = FALSE;
	int i=0;


	//아름다운 습관 : 포인터가 전달되었을때는 반드시 NULL체크를 하는 아름다운 습관을 가져야한다. 
	if (pList != NULL) { //리스트가 NULL인지 체크 
		if (isArrayListFull(pList) != TRUE) {//가득차지 않았으면
			if (position >= 0//위치가 0보다 커야하고
				&& position <= pList->currentElementCount)//currentElement 까지 저장을 할 수 있다. ( 0 base이기 때문에 )
			{
				for(i = pList->currentElementCount-1; i >= position; i--) {//(currentElementCount) = 시작 >  (position) =  현재 저장되어있는 가장 오른쪽에서 우리가 추가하려는 위치까지 (i--) = 왼쪽 방향으로 진행
					pList->pElement[i+1] = pList->pElement[i]; //한칸씩 다 옮겨준다.
				}
				pList->pElement[position] = element;//내가 원하는 위치에 대입
				pList->currentElementCount++;//현재 원소의 갯수를 1 올려준다.
				
				ret = TRUE;
			}
			else {//범위 오류
				printf("오류, 위치 인덱스-[%d] 범위 초과, addALElement()\n",
						position);
			}
		}
		else {//현재 가득 찼다.
			printf("오류, 리스트 용량 초과-[%d]/[%d]\n", 
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
			printf("오류, 위치 인덱스-[%d] 범위 초과, removeALElement()\n",
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
			printf("오류, 위치 인덱스-[%d] 범위 초과, getALElement()\n", position);
		}
	}

	return pReturn;
}

void displayArrayList(ArrayList* pList) {
	int i = 0;
	if (pList != NULL) {
		printf("최대 원소 개수: %d\n", pList->maxElementCount);
		printf("현재 원소 개수: %d\n", pList->currentElementCount);

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
