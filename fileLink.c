#include <stdio.h>
#include <Windows.h>
#include "linkedListBook.h"


void readFromFile(LIST* ptrlist) {

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "booklist.bin", "rb");	// 백업해놓은 리스트 사용하려면 booklist_backup.bin

	if (err == 0) {

		fseek(fp, 0, SEEK_END);    // 파일 포인터를 파일의 끝으로 이동시킴
		size_t fileSize = ftell(fp);          // 파일 포인터의 현재 위치를 얻음
		rewind(fp);		// 파일 포인터의 위치를 다시 맨앞으로 보냄

		int numberOfNode = (int) fileSize / sizeof(NODE);	// 파일에 저장된 노드의 개수

		NODE* tempBook = (NODE*)malloc(sizeof(NODE));
		if (tempBook != NULL) {	// malloc 반환이 NULL인 경우 예외처리

			for (int i = 0; i < numberOfNode; i++) {	// numberOfNode 만큼 반복하며
				fread(tempBook, sizeof(NODE), 1, fp); // 파일 읽어 들이기
				addNode(ptrlist, tempBook);
			}

			free(tempBook);	// tempBook 메모리 할당 해제

		} else printf("메모리 할당에 실패하였습니다.");

		fclose(fp);	// 파일 스트림 닫기

	}
	else {
		printf("파일오픈 실패\n");
		printf("에러코드 : %d\n", err);
		system("pause");
	}
}


void writeToFile(LIST* ptrlist) {

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "booklist.bin", "wb");	// 파일 출력스트림 개방

	if (err == 0) {

		ptrlist->curr = ptrlist->head->next;	// 헤드더미노드의 next 값을 curr 포인터에 대입

		while (ptrlist->curr != ptrlist->tail) {	//	curr이 테일더미노드를 가리키게 될 때까지 반복
			fwrite(ptrlist->curr, sizeof(NODE), 1, fp); // 파일 출력
			ptrlist->curr = ptrlist->curr->next;	// curr에 next주소값 대입
		}
		fclose(fp);	// 파일 스트림 닫기
	}
	else {
		printf("파일저장 실패\n");
		printf("에러코드 : %d\n", err);
		system("pause");
	}
}

