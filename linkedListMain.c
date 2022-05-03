#include <stdio.h>
#include "linkedListBook.h"
#include <Windows.h>
#define DEBUG

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

int main(void) {
	//_CrtSetBreakAlloc();

	LIST booklist;
	listInit(&booklist);	// 링크드리스트 초기설정

	readFromFile(&booklist);	// 파일로부터 데이터 읽어들이기

	int menu, exit = FALSE;

	while (exit == FALSE) {

		system("cls");
		menu = dispMenu(listCount(&booklist));	// 메뉴 출력
		system("cls");

		if (menu == 1) listInsert(&booklist);	// 도서 추가
		else if (menu == 2) deleteMenu(&booklist);	// 도서 삭제
		else if (menu == 3) sortMenu(&booklist);	// 도서 정렬
		else if (menu == 4) listSearch(&booklist);	// 도서 검색
		else if (menu == 5) listPrint(&booklist);	// 도서 출력
		else if (menu == 6) {	// 종료
			writeToFile(&booklist);	// 파일에 출력
			exit = TRUE;	// 루프 탈출
			freeAllNode(&booklist);	// 모든 노드 메모리 할당 해제
		}
#ifdef DEBUG
		else if (menu == 7)	testAdd(&booklist); // 테스트용 도서 추가
		else if (menu == 8) delLastNode(&booklist);	// 테스트용 도서 삭제
#endif
		else {
			rewind(stdin);	// 다른 숫자나 문자(열)이 들어왔을 땐 입력버퍼 비움
		}
	}
#ifdef DEBUG
	_CrtDumpMemoryLeaks();	// 디버그용 memory leaks 탐지
#endif
	return 0;
}