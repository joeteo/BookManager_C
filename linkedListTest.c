#define DEBUG

#ifdef DEBUG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedListBook.h"
#include <time.h>

void testAdd(LIST* ptrlist) {	// 테스트용 도서 추가



	NODE* tempBook = (NODE*)malloc(sizeof(NODE));
	if (tempBook != NULL) {	// malloc 반환이 NULL인 경우 예외처리

		// 테스트용 데이터
		char buf[30];	// 정수->문자열 변환 위한 임시 buffer
		sprintf_s(buf, sizeof(buf), "%d번째 책(test)", listCount(ptrlist) + 1);	// 정수를 문자열로 변환해 버퍼에 저장해주는 함수
		strcpy_s(tempBook->title, sizeof(tempBook->title), buf);

		char name[][3] = {"이","조","한","정","강","윤","장","수","현","상","연","고","우","민","준","서","훈","아","원","지"};		
		strcpy_s(buf, sizeof(buf), name[rand() % 20]);
		strcat_s(buf, sizeof(buf), name[rand() % 20]);
		strcat_s(buf, sizeof(buf), name[rand() % 20]);
		strcpy_s(tempBook->author, sizeof(tempBook->author), buf);

		tempBook->price = rand()%50*1000;
		tempBook->page = rand()%1000;
		tempBook->date.year = rand() % 12 + 1;
		tempBook->date.month = rand() % 12 + 1;
		tempBook->date.day = rand() % 30 + 1;
		// 테스트용 데이터

		addNode(ptrlist, tempBook);	// 노드 추가 함수 호출

		free(tempBook);	// tempBook 메모리 할당 해제	

	}
	else printf("메모리 할당에 실패하였습니다");
}

#endif // DEBUG