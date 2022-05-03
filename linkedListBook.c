#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListBook.h"
#include <Windows.h>
#define DEBUG

void listInit(LIST* ptrlist)
{
	ptrlist->head = (NODE*)malloc(sizeof(NODE));	// 헤드더미노드 생성

	if (ptrlist->head != NULL) {	// malloc 반환이 NULL인 경우 예외처리

		ptrlist->tail = (NODE*)malloc(sizeof(NODE));	// 테일더미노드 생성

		if (ptrlist->tail != NULL) {	// malloc 반환이 NULL인 경우 예외처리

			ptrlist->head->prev = NULL;	// 헤드더미노드의 prev는 NULL
			ptrlist->head->next = ptrlist->tail;	// 헤드더미노드의 next는 테일더미노드
			ptrlist->tail->prev = ptrlist->head;	// 테일더미노드의 prev는 헤드더미노드
			ptrlist->tail->next = NULL;	// 테일더미노드의 next는 NULL
			ptrlist->numOfData = 0;	// 데이터개수 0
		}
		else printf("메모리 할당에 실패하였습니다.");
	}
	else printf("메모리 할당에 실패하였습니다.");
}

int listCount(LIST* ptrlist)
{
	return ptrlist->numOfData;
}

int dispMenu(int numOfData) {
	int menu;

	printf("------------------------------------------------------------------------------\n");
#ifdef DEBUG
	printf("| ~ 테스트용 도서추가버튼 : 7, 도서삭제버튼 : 8 ~                            |\n");
	printf("|                                                                            |\n");
#endif // DEBUG
	printf("|                           도서 검색 프로그램                               |\n");
	printf("|                                                  (현재 데이터 개수 : %3d)  |\n", numOfData);
	printf("|                                                                            |\n");
	printf("|-----------------------------------MENU-------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  1. 도서 추가                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  2. 도서 삭제                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  3. 도서 정렬                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. 도서 검색                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. 도서 확인                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  6. 종료                                                                   |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   원하는 메뉴를 입력하세요 [ ]\b\b");
	scanf_s("%d", &menu);
	return menu;
}

void addNode(LIST* ptrlist, NODE* tempBook) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));	// 새 노드 생성, 임시 포인터인 newNode에 주소값 대입
	if (newNode != NULL) {	// malloc 반환이 NULL인 경우 예외처리

		// 도서 데이터 저장 여기부터
		newNode->price = tempBook->price;
		newNode->page = tempBook->page;
		newNode->date.year = tempBook->date.year;
		newNode->date.month = tempBook->date.month;
		newNode->date.day = tempBook->date.day;
		strcpy_s(newNode->title, sizeof(newNode->title), tempBook->title);
		strcpy_s(newNode->author, sizeof(newNode->author), tempBook->author);
		// 도서 데이터 저장 여기까지

		// 꼬리 추가 방식
		newNode->prev = ptrlist->tail->prev;	// 새 노드의 prev가 직전 마지막 노드(첫 추가인 경우 헤드더미노드)를 가리킴
		ptrlist->tail->prev->next = newNode;	// 직전 마지막 노드(첫 추가인 경우 헤드더미노드)의 next가 새 노드를 가리킴

		newNode->next = ptrlist->tail;	// 새 노드의 next가 테일더미노드를 가리킴
		ptrlist->tail->prev = newNode;	// 테일더미노드의 prev가 새노드를 가리킴

		(ptrlist->numOfData)++;	// 데이터 개수 증가

	}
	else printf("메모리 할당에 실패하였습니다.");
}

void listInsert(LIST* ptrlist)
{	

	NODE* tempBook = (NODE*)calloc(1, sizeof(NODE));

	if (tempBook != NULL) {	// calloc 반환이 NULL인 경우 예외처리

		while (1) {

			char temp[100] = { 0, };

			printf("------------------------------------------------------------------------------\n\n");
			printf("   도서 제목을 입력하세요: ");
			scanf_s(" %99[^\n]", temp, (int)sizeof(temp));
			if (strlen(temp) > sizeof(tempBook->title) - 1) {	// temp에 먼저 입력받은 후 문자열의 길이 검사
				printf("   너무 긴 문자열을 입력하셨습니다. 처음부터 다시 입력해 주세요.\n   ");
				system("pause");
				system("cls");
				continue;
			}
			strcpy_s(tempBook->title, sizeof(tempBook->title), temp);

			printf("\n   도서 가격을 입력하세요: ");
			scanf_s("%d", &tempBook->price);
			rewind(stdin);

			printf("\n   도서 저자를 입력하세요: ");
			scanf_s(" %99[^\n]", temp, (int)sizeof(temp));
			if (strlen(temp) > sizeof(tempBook->author) - 1) {	// temp에 먼저 입력받은 후 문자열의 길이 검사
				printf("   너무 긴 문자열을 입력하셨습니다. 처음부터 다시 입력해 주세요.\n   ");
				system("pause");
				system("cls");
				continue;
			}
			strcpy_s(tempBook->author, sizeof(tempBook->author), temp);

			printf("\n   도서 페이지를 입력하세요: ");
			scanf_s("%d", &tempBook->page);
			rewind(stdin);

			printf("\n   도서 발행연도를 입력하세요(yy mm dd) : __ __ __\b\b\b\b\b\b\b\b");
			scanf_s("%02hhd %02hhd %02hhd", &tempBook->date.year, &tempBook->date.month, &tempBook->date.day); // 0포함 입력받음
			rewind(stdin);

			addNode(ptrlist, tempBook);	// 노드 추가 함수 호출

			printf("\n------------------------------------------------------------------------------\n");
			printf("\n   계속 입력하려면[1] 메뉴로 돌아가려면[0]를 입력하세요 [ ]\b\b");
			char chk;
			scanf_s("%hhd", &chk);
			if (chk != 1) {
				free(tempBook);	// tempBook 메모리 할당 해제
				break;
			}
			system("cls");
		}
	}
	else printf("메모리 할당에 실패하였습니다");
}


void listPrint(LIST* ptrlist) {

	printf("------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;	// 헤드더미노드의 next 값을 curr 포인터에 대입

	if (ptrlist->curr == ptrlist->tail) {	// curr 포인터가 테일더미노드를 가리키는 경우
		printf("   출력할 데이터가 없습니다...\n\n   ");
		system("pause");
		return;
	} else {	// 데이터가 있는 경우
		while (ptrlist->curr!= ptrlist->tail) {	// 계속 next 주소로 노드를 순회하면서 curr이 테일더미노드를 가리킬 때까지 반복 출력
			printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
				ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
			ptrlist->curr = ptrlist->curr->next;	// curr에 next주소값 대입
			i++;
		}
		printf("------------------------------------------------------------------------------\n");
		system("pause");
	}
}

void listSearch(LIST* ptrlist) {

	char keyword[100] = { 0, };
	char chk = 0;

	printf("------------------------------------------------------------------------------\n");
	printf("   검색어를 입력하세요.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %99[^\n]", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;

	if (ptrlist->curr == ptrlist->tail) {	// curr 포인터가 테일더미노드를 가리키는 경우
		printf("   출력할 데이터가 없습니다...\n\n");
	}
	else {
		while (ptrlist->curr != ptrlist->tail) { // curr이 순회하며 테일더미노드를 가리킬 때까지 반복 출력
			if (strstr(ptrlist->curr->title, keyword) != NULL) {	// str1 문자열이 str2 문자열을 포함하고 있으면 char * 반환
				printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
					ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
				chk++;	// 검색 결과가 나올 때만 chk++
			}
			ptrlist->curr = ptrlist->curr->next;
			i++;	// 책번호 출력위해 검색결과랑 상관없이 i++
		}
		if (chk == 0) printf("   검색 결과가 없습니다.\n\n");
	}
	printf("------------------------------------------------------------------------------\n   ");
	system("pause");
}


void deleteMenu(LIST* ptrlist) {
	char chk = 0;
	int numToDelete = 0;

	if (listCount(ptrlist) > 0) {
		printf("------------------------------------------------------------------------------\n");
		printf("   삭제하고자 하는 도서를 검색하세요\n\n");

		int* searchedNum = (int*)calloc(listCount(ptrlist), sizeof(int));	// 검색결과번호 담을 목적으로 도서개수만큼 int 메모리 할당
		if (searchedNum != NULL) {	// calloc 반환이 0인 경우 예외처리

			listSearchForDel(ptrlist, searchedNum);	// 삭제용 검색 함수

			if (searchedNum[0] == 0) {	// 검색 결과가 없을 때
				printf("\n   메뉴로 돌아갑니다......");
				system("pause");
			}
			else if (searchedNum[1] == 0 || listCount(ptrlist) == 1) {	// 검색 결과가 1개일 때 || 검색결과가 있으면서 도서 데이터 1개일 때
				printf("\n   정말 삭제하시겠습니까? Yes [1] / No [0] ... [ ]\b\b");
				scanf_s("%hhd", &chk);
				if (chk == 1 ) {
					deleteNode(ptrlist, searchedNum[0]);	// 노드 삭제 함수 호출
					printf("\n   삭제가 완료되었습니다...");
					system("pause");
				}			
				else {
					printf("\n   삭제하지 않고 메뉴로 돌아갑니다...");
					system("pause");
				}
			}
			else {	// 검색 결과가 여러개 일 때
				printf("   모두 삭제하려면 [1] 삭제할 도서를 선택하려면 [0]을 눌러주세요 ... [ ]\b\b");
				scanf_s("%hhd", &chk);
				if (chk == 1) {
					int i = 0;
					while (searchedNum[i] != 0 && listCount(ptrlist) > 0) {	// 도서 데이터 개수 이하 반복하면서 검색 결과 갯수만큼
						deleteNode(ptrlist, searchedNum[i] - i);	// 검색 결과 모두 삭제(지울때마다 도서번호-1)
						i++;
					}
					printf("\n   삭제가 완료되었습니다...");
					system("pause");
					return;
				}
				else if (chk != 0) {
					printf("\n   삭제하지 않고 메뉴로 돌아갑니다...");
					system("pause");
					return;
				}
				printf("\n   삭제할 도서 번호를 입력해주세요 ... [   ]\b\b\b\b");
				scanf_s("%d", &numToDelete);
				for (int i = 0; i < listCount(ptrlist); i++) {	// 입력한 번호가 검색결과에 있는 번호인지 검사
					if (searchedNum[i] == numToDelete) {
						chk = 1;
					}
				}
				if (chk == 0 || numToDelete <= 0) {		// 0 또는 음수 또는 리스트에 없는 번호 입력시 예외처리
					printf("\n   잘못 입력하셨습니다. 메뉴로 돌아갑니다...");
					system("pause");
				}
				else {
					printf("\n   정말 삭제하시겠습니까? Yes [1] / No [0] ... [ ]\b\b");
					scanf_s("%hhd", &chk);
					if (chk == 1) {
						deleteNode(ptrlist, numToDelete);	// 노드 삭제 함수 호출
						printf("\n   삭제가 완료되었습니다...");
						system("pause");
					}
					else {
						printf("\n   삭제하지 않고 메뉴로 돌아갑니다...");
						system("pause");
					}
				}
			}
			free(searchedNum);	// searchedNum 메모리 할당 해제
		}
	}
	else {
		printf("------------------------------------------------------------------------------\n");
		printf("   출력할 데이터가 없습니다. 메뉴로 돌아갑니다...\n\n   ");
		system("pause");
	}
}


void deleteNode(LIST* ptrlist, int numToDelete) {	// 특정 노드 삭제
	int i = 1;

	ptrlist->curr = ptrlist->head->next;

	while (i!=numToDelete) { // curr이 삭제할 도서 노드를 가리킬 때까지 순회
		ptrlist->curr = ptrlist->curr->next;
		i++;
	}

	ptrlist->curr->prev->next = ptrlist->curr->next;	// 삭제할노드의 직전 노드의 next가 삭제할노드의 다음 노드를 가리키게함
	ptrlist->curr->next->prev = ptrlist->curr->prev;	// 삭제할노드의 다음 노드의 prev가 삭제할노드의 직전 노드를 가리키게함

	free(ptrlist->curr);	// curr이 가리키고 있는 노드 메모리 할당 해제
	(ptrlist->numOfData)--;	// 노드 개수 줄임
}


void listSearchForDel(LIST* ptrlist, int* searchedNum) {

	char keyword[100] = { 0, };
	char chk = 0;

	printf("------------------------------------------------------------------------------\n");
	printf("   검색어를 입력하세요.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %99[^\n]", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                제목                 가격      저자     페이지    발행연도   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;

	if (ptrlist->curr == ptrlist->tail) {	// curr 포인터가 테일더미노드를 가리키는 경우
	}
	else {
		while (ptrlist->curr != ptrlist->tail) { // curr이 순회하며 테일더미노드를 가리킬 때까지 반복 출력
			if (strstr(ptrlist->curr->title, keyword) != NULL) {	// str1 문자열이 str2 문자열을 포함하고 있으면 char * 반환
				printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
					ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
				searchedNum[chk] = i;	// searchedNum에 검색 결과 기록
				chk++;	// 검색 결과가 나올 때만 chk++
			}
			ptrlist->curr = ptrlist->curr->next;
			i++;	// 책번호 출력위해 검색결과랑 상관없이 i++
		}
		if (chk == 0) printf("   검색 결과가 없습니다.\n\n");
		printf("------------------------------------------------------------------------------\n");
	}
}


void sortMenu(LIST* ptrlist) {

	int select;
	printf("|----------------------------------------------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  무엇으로 정렬하시겠습니까?                                                |\n");
	printf("|                                                                            |\n");
	printf("|  1. 가격 순                                                                |\n");
	printf("|                                                                            |\n");
	printf("|  2. 발행연도 순                                                            |\n");
	printf("|                                                                            |\n");
	printf("|  3. 페이지 순                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. 도서명 순                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. 저자명 순                                                              |\n");
	printf("------------------------------------------------------------------------------\n\n");
	if (listCount(ptrlist) <= 0) {
		printf("   출력할 데이터가 없습니다. 메뉴로 돌아갑니다...\n\n   ");
		system("pause");
		return;
	}
	printf("   원하는 메뉴를 입력하세요 [ ]\b\b");
	scanf_s("%d", &select);
	
	if (select > 0 && select < 6) {

		LIST tempList;	// 원본값을 훼손하지 않기 위한 정렬용 복사본
		listInit(&tempList);	// 리스트 초기설정
		copyList(&tempList, ptrlist);	// 리스트 복사, listInit 후 사용

		if (select == 1) insertionSort(&tempList, (_comp)compare_price);
		else if (select == 2) insertionSort(&tempList, (_comp)compare_date);
		else if (select == 3) insertionSort(&tempList, (_comp)compare_page);
		else if (select == 4) insertionSort(&tempList, (_comp)compare_title);
		else if (select == 5) insertionSort(&tempList, (_comp)compare_author);

		system("cls");
		listPrint(&tempList);	// 정렬 데이터 출력
		freeAllNode(&tempList);	// 임시리스트 메모리 전체 할당 해제

	}
	else {
		rewind(stdin);
		printf("   잘못 입력하셨습니다. 메뉴로 돌아갑니다...");
		system("pause");
	}
}


void copyList(LIST* destination, LIST* source) {	// 리스트 복사

	source->curr = source->head->next;	// 소스리스트 curr이 1번째 데이터 노드를 가리키게함

	while (source->curr != source->tail) {	// 소스리스트 curr이 테일을 가리킬때까지 반복

		NODE* newDestNode = (NODE*)calloc(1, sizeof(NODE));	// 새 노드 생성, 임시 포인터인 newDestNode에 주소값 대입

		if (newDestNode != NULL) {	// malloc 반환이 NULL인 경우 예외처리

			memcpy(newDestNode, source->curr, sizeof(NODE));	// 메모리 복사

			newDestNode->prev = destination->tail->prev;	// 목적지 리스트 꼬리에 복사된 노드 연결
			destination->tail->prev->next = newDestNode;
			newDestNode->next = destination->tail;
			destination->tail->prev = newDestNode;

			(destination->numOfData)++;	// 데이터 개수 증가

			source->curr = source->curr->next;	// 소스리스트의 curr을 다음칸으로 이동
		}
		else printf("메모리 할당에 실패하였습니다.");
	}
}

void putNPushNode(NODE* compNode, NODE* curr) {	// 노드 원하는 자리에 끼워 넣기

	NODE* temp = (NODE*)malloc(sizeof(NODE));	// 데이터 보존 위한 임시 노드
	if (temp != NULL) {	// malloc 반환이 NULL인 경우 예외처리

		memcpy(temp, curr, sizeof(NODE));

		// curr을 compNode 앞에 끼워 넣고 원래 curr 앞쪽과 뒤쪽노드를 서로 연결해줌
		curr->prev = compNode->prev;
		compNode->prev->next = curr;

		curr->next = compNode;
		compNode->prev = curr;

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		free(temp);	// temp 메모리 할당 해제
	}
	else printf("메모리 할당에 실패하였습니다.");
}


// 검색 기준 여기부터
int compare_price(const NODE* arg1, const NODE* arg2) {
	if (arg1->price != arg2->price) return (arg1->price - arg2->price);
	else return 0;
}

int compare_page(const NODE* arg1, const NODE* arg2) {
	if (arg1->page != arg2->page) return (arg1->page - arg2->page);
	else return 0;
}

int compare_date(const NODE* arg1, const NODE* arg2) {
	if (arg1->date.year != arg2->date.year) return (arg1->date.year - arg2->date.year);
	else if (arg1->date.month != arg2->date.month) return (arg1->date.month - arg2->date.month);
	else if (arg1->date.day != arg2->date.day) return (arg1->date.day - arg2->date.day);
	else return 0;
}

int compare_title(const NODE* arg1, const NODE* arg2) {
	return strcmp(arg1->title, arg2->title);
}

int compare_author(const NODE* arg1, const NODE* arg2) {
	return strcmp(arg1->author, arg2->author);
}
// 검색 기준 여기까지




void insertionSort(LIST* ptrlist, _comp criteria) {		// 삽입정렬
	
	NODE* compNode = NULL; // 정렬용 임시 포인터, curr 앞 쪽을 역순으로 순회하며 대소비교

	ptrlist->curr = ptrlist->head->next->next;	// curr이 2번째 노드 가리킴
	compNode = ptrlist->head->next;	// compNode가 1번째 노드 가리킴

	while (ptrlist->curr != ptrlist->tail) {	// curr이 테일더미 갈때까지 반복

		if (criteria(ptrlist->curr, compNode) >=0) {	// 앞쪽은 이미 정렬된 자료라서 curr데이터가 더 크거나 같으면 암것도 안함
			ptrlist->curr = ptrlist->curr->next; // 스왑을 안했으면 바로 curr 한칸 뒤로
		}
		else {
			// curr데이터가 작은 동안 compNode가 앞쪽으로 이동하는데 1번째 데이터노드까지만
			while (compNode != ptrlist->head->next && criteria(ptrlist->curr, compNode) < 0) {
				compNode = compNode->prev;
			}
			NODE* temp = ptrlist->curr;	// curr의 위치 저장용
			putNPushNode(compNode, ptrlist->curr);	// curr 노드 알맞은 위치에 끼워 넣기
			ptrlist->curr = temp->next;	// 끼워 넣기 직전 저장해둔 curr의 다음칸으로 옮김
		}
		compNode = ptrlist->curr->prev;	// compNode는 curr보다 한칸 앞
	}
}


void delLastNode(LIST* ptrlist) {	// 마지막 도서 삭제, freeAllNode에서도 쓰고 테스트용삭제로도 씀

	ptrlist->curr = ptrlist->tail->prev;	// 테일더미노드의 prev값을 curr에 대입

	if (ptrlist->curr == ptrlist->head) {	// curr이 헤드더미노드를 가리키면(=데이터가 없으면) 아무것도 안함
	}
	else {
		ptrlist->curr->prev->next = ptrlist->curr->next;	// 마지막 데이터노드의 직전 노드의 next가 테일더미노드를 가리키게함
		ptrlist->curr->next->prev = ptrlist->curr->prev;	// 테일더미노드의 prev가 마지막 데이터노드의 직전 노드를 가리키게함

		free(ptrlist->curr);	// curr이 가리키는 마지막 데이터노드 메모리 할당 해제

		(ptrlist->numOfData)--;	// 노드 개수 줄임
	}
}


void freeAllNode(LIST* ptrlist) {	// 리스트의 모든 노드 free

	while (listCount(ptrlist) > 0) {	// 도서 개수 만큼 삭제 (delLastNode함수 내부에서 listCount--함)
		delLastNode(ptrlist);	// 마지막 도서를 삭제하는 함수 호출
	}	
	free(ptrlist->head);	// 헤드더미노드 메모리 할당 해제
	free(ptrlist->tail);	// 테일더미노드 메모리 할당 해제

}


//void swapNode(NODE* compNode, NODE* curr) {
//
//	NODE* temp = (NODE*)malloc(sizeof(NODE));	// 스왑을 위한 임시 노드
//	if (temp != NULL) {	// malloc 반환이 NULL인 경우 예외처리
//
//		memcpy(temp, curr, sizeof(NODE));
//
//		// 서로 prev, next 포인터 스왑
//		curr->prev = compNode->prev;
//		curr->next = compNode->next;
//
//		compNode->prev = temp->prev;
//		compNode->next = temp->next;		
//
//		free(temp);	// temp 메모리 할당 해제
//
//	}
//	else printf("메모리 할당에 실패하였습니다.");
//}