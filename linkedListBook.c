#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListBook.h"
#include <Windows.h>
#define DEBUG

void listInit(LIST* ptrlist)
{
	ptrlist->head = (NODE*)malloc(sizeof(NODE));	// �����̳�� ����

	if (ptrlist->head != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

		ptrlist->tail = (NODE*)malloc(sizeof(NODE));	// ���ϴ��̳�� ����

		if (ptrlist->tail != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

			ptrlist->head->prev = NULL;	// �����̳���� prev�� NULL
			ptrlist->head->next = ptrlist->tail;	// �����̳���� next�� ���ϴ��̳��
			ptrlist->tail->prev = ptrlist->head;	// ���ϴ��̳���� prev�� �����̳��
			ptrlist->tail->next = NULL;	// ���ϴ��̳���� next�� NULL
			ptrlist->numOfData = 0;	// �����Ͱ��� 0
		}
		else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
	}
	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
}

int listCount(LIST* ptrlist)
{
	return ptrlist->numOfData;
}

int dispMenu(int numOfData) {
	int menu;

	printf("------------------------------------------------------------------------------\n");
#ifdef DEBUG
	printf("| ~ �׽�Ʈ�� �����߰���ư : 7, ����������ư : 8 ~                            |\n");
	printf("|                                                                            |\n");
#endif // DEBUG
	printf("|                           ���� �˻� ���α׷�                               |\n");
	printf("|                                                  (���� ������ ���� : %3d)  |\n", numOfData);
	printf("|                                                                            |\n");
	printf("|-----------------------------------MENU-------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  1. ���� �߰�                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  2. ���� ����                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  3. ���� ����                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. ���� �˻�                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. ���� Ȯ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  6. ����                                                                   |\n");
	printf("|                                                                            |\n");
	printf("------------------------------------------------------------------------------\n\n");
	printf("   ���ϴ� �޴��� �Է��ϼ��� [ ]\b\b");
	scanf_s("%d", &menu);
	return menu;
}

void addNode(LIST* ptrlist, NODE* tempBook) {
	NODE* newNode = (NODE*)malloc(sizeof(NODE));	// �� ��� ����, �ӽ� �������� newNode�� �ּҰ� ����
	if (newNode != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

		// ���� ������ ���� �������
		newNode->price = tempBook->price;
		newNode->page = tempBook->page;
		newNode->date.year = tempBook->date.year;
		newNode->date.month = tempBook->date.month;
		newNode->date.day = tempBook->date.day;
		strcpy_s(newNode->title, sizeof(newNode->title), tempBook->title);
		strcpy_s(newNode->author, sizeof(newNode->author), tempBook->author);
		// ���� ������ ���� �������

		// ���� �߰� ���
		newNode->prev = ptrlist->tail->prev;	// �� ����� prev�� ���� ������ ���(ù �߰��� ��� �����̳��)�� ����Ŵ
		ptrlist->tail->prev->next = newNode;	// ���� ������ ���(ù �߰��� ��� �����̳��)�� next�� �� ��带 ����Ŵ

		newNode->next = ptrlist->tail;	// �� ����� next�� ���ϴ��̳�带 ����Ŵ
		ptrlist->tail->prev = newNode;	// ���ϴ��̳���� prev�� ����带 ����Ŵ

		(ptrlist->numOfData)++;	// ������ ���� ����

	}
	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
}

void listInsert(LIST* ptrlist)
{	

	NODE* tempBook = (NODE*)calloc(1, sizeof(NODE));

	if (tempBook != NULL) {	// calloc ��ȯ�� NULL�� ��� ����ó��

		while (1) {

			char temp[100] = { 0, };

			printf("------------------------------------------------------------------------------\n\n");
			printf("   ���� ������ �Է��ϼ���: ");
			scanf_s(" %99[^\n]", temp, (int)sizeof(temp));
			if (strlen(temp) > sizeof(tempBook->title) - 1) {	// temp�� ���� �Է¹��� �� ���ڿ��� ���� �˻�
				printf("   �ʹ� �� ���ڿ��� �Է��ϼ̽��ϴ�. ó������ �ٽ� �Է��� �ּ���.\n   ");
				system("pause");
				system("cls");
				continue;
			}
			strcpy_s(tempBook->title, sizeof(tempBook->title), temp);

			printf("\n   ���� ������ �Է��ϼ���: ");
			scanf_s("%d", &tempBook->price);
			rewind(stdin);

			printf("\n   ���� ���ڸ� �Է��ϼ���: ");
			scanf_s(" %99[^\n]", temp, (int)sizeof(temp));
			if (strlen(temp) > sizeof(tempBook->author) - 1) {	// temp�� ���� �Է¹��� �� ���ڿ��� ���� �˻�
				printf("   �ʹ� �� ���ڿ��� �Է��ϼ̽��ϴ�. ó������ �ٽ� �Է��� �ּ���.\n   ");
				system("pause");
				system("cls");
				continue;
			}
			strcpy_s(tempBook->author, sizeof(tempBook->author), temp);

			printf("\n   ���� �������� �Է��ϼ���: ");
			scanf_s("%d", &tempBook->page);
			rewind(stdin);

			printf("\n   ���� ���࿬���� �Է��ϼ���(yy mm dd) : __ __ __\b\b\b\b\b\b\b\b");
			scanf_s("%02hhd %02hhd %02hhd", &tempBook->date.year, &tempBook->date.month, &tempBook->date.day); // 0���� �Է¹���
			rewind(stdin);

			addNode(ptrlist, tempBook);	// ��� �߰� �Լ� ȣ��

			printf("\n------------------------------------------------------------------------------\n");
			printf("\n   ��� �Է��Ϸ���[1] �޴��� ���ư�����[0]�� �Է��ϼ��� [ ]\b\b");
			char chk;
			scanf_s("%hhd", &chk);
			if (chk != 1) {
				free(tempBook);	// tempBook �޸� �Ҵ� ����
				break;
			}
			system("cls");
		}
	}
	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�");
}


void listPrint(LIST* ptrlist) {

	printf("------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;	// �����̳���� next ���� curr �����Ϳ� ����

	if (ptrlist->curr == ptrlist->tail) {	// curr �����Ͱ� ���ϴ��̳�带 ����Ű�� ���
		printf("   ����� �����Ͱ� �����ϴ�...\n\n   ");
		system("pause");
		return;
	} else {	// �����Ͱ� �ִ� ���
		while (ptrlist->curr!= ptrlist->tail) {	// ��� next �ּҷ� ��带 ��ȸ�ϸ鼭 curr�� ���ϴ��̳�带 ����ų ������ �ݺ� ���
			printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
				ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
			ptrlist->curr = ptrlist->curr->next;	// curr�� next�ּҰ� ����
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
	printf("   �˻�� �Է��ϼ���.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %99[^\n]", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;

	if (ptrlist->curr == ptrlist->tail) {	// curr �����Ͱ� ���ϴ��̳�带 ����Ű�� ���
		printf("   ����� �����Ͱ� �����ϴ�...\n\n");
	}
	else {
		while (ptrlist->curr != ptrlist->tail) { // curr�� ��ȸ�ϸ� ���ϴ��̳�带 ����ų ������ �ݺ� ���
			if (strstr(ptrlist->curr->title, keyword) != NULL) {	// str1 ���ڿ��� str2 ���ڿ��� �����ϰ� ������ char * ��ȯ
				printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
					ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
				chk++;	// �˻� ����� ���� ���� chk++
			}
			ptrlist->curr = ptrlist->curr->next;
			i++;	// å��ȣ ������� �˻������ ������� i++
		}
		if (chk == 0) printf("   �˻� ����� �����ϴ�.\n\n");
	}
	printf("------------------------------------------------------------------------------\n   ");
	system("pause");
}


void deleteMenu(LIST* ptrlist) {
	char chk = 0;
	int numToDelete = 0;

	if (listCount(ptrlist) > 0) {
		printf("------------------------------------------------------------------------------\n");
		printf("   �����ϰ��� �ϴ� ������ �˻��ϼ���\n\n");

		int* searchedNum = (int*)calloc(listCount(ptrlist), sizeof(int));	// �˻������ȣ ���� �������� ����������ŭ int �޸� �Ҵ�
		if (searchedNum != NULL) {	// calloc ��ȯ�� 0�� ��� ����ó��

			listSearchForDel(ptrlist, searchedNum);	// ������ �˻� �Լ�

			if (searchedNum[0] == 0) {	// �˻� ����� ���� ��
				printf("\n   �޴��� ���ư��ϴ�......");
				system("pause");
			}
			else if (searchedNum[1] == 0 || listCount(ptrlist) == 1) {	// �˻� ����� 1���� �� || �˻������ �����鼭 ���� ������ 1���� ��
				printf("\n   ���� �����Ͻðڽ��ϱ�? Yes [1] / No [0] ... [ ]\b\b");
				scanf_s("%hhd", &chk);
				if (chk == 1 ) {
					deleteNode(ptrlist, searchedNum[0]);	// ��� ���� �Լ� ȣ��
					printf("\n   ������ �Ϸ�Ǿ����ϴ�...");
					system("pause");
				}			
				else {
					printf("\n   �������� �ʰ� �޴��� ���ư��ϴ�...");
					system("pause");
				}
			}
			else {	// �˻� ����� ������ �� ��
				printf("   ��� �����Ϸ��� [1] ������ ������ �����Ϸ��� [0]�� �����ּ��� ... [ ]\b\b");
				scanf_s("%hhd", &chk);
				if (chk == 1) {
					int i = 0;
					while (searchedNum[i] != 0 && listCount(ptrlist) > 0) {	// ���� ������ ���� ���� �ݺ��ϸ鼭 �˻� ��� ������ŭ
						deleteNode(ptrlist, searchedNum[i] - i);	// �˻� ��� ��� ����(���ﶧ���� ������ȣ-1)
						i++;
					}
					printf("\n   ������ �Ϸ�Ǿ����ϴ�...");
					system("pause");
					return;
				}
				else if (chk != 0) {
					printf("\n   �������� �ʰ� �޴��� ���ư��ϴ�...");
					system("pause");
					return;
				}
				printf("\n   ������ ���� ��ȣ�� �Է����ּ��� ... [   ]\b\b\b\b");
				scanf_s("%d", &numToDelete);
				for (int i = 0; i < listCount(ptrlist); i++) {	// �Է��� ��ȣ�� �˻������ �ִ� ��ȣ���� �˻�
					if (searchedNum[i] == numToDelete) {
						chk = 1;
					}
				}
				if (chk == 0 || numToDelete <= 0) {		// 0 �Ǵ� ���� �Ǵ� ����Ʈ�� ���� ��ȣ �Է½� ����ó��
					printf("\n   �߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�...");
					system("pause");
				}
				else {
					printf("\n   ���� �����Ͻðڽ��ϱ�? Yes [1] / No [0] ... [ ]\b\b");
					scanf_s("%hhd", &chk);
					if (chk == 1) {
						deleteNode(ptrlist, numToDelete);	// ��� ���� �Լ� ȣ��
						printf("\n   ������ �Ϸ�Ǿ����ϴ�...");
						system("pause");
					}
					else {
						printf("\n   �������� �ʰ� �޴��� ���ư��ϴ�...");
						system("pause");
					}
				}
			}
			free(searchedNum);	// searchedNum �޸� �Ҵ� ����
		}
	}
	else {
		printf("------------------------------------------------------------------------------\n");
		printf("   ����� �����Ͱ� �����ϴ�. �޴��� ���ư��ϴ�...\n\n   ");
		system("pause");
	}
}


void deleteNode(LIST* ptrlist, int numToDelete) {	// Ư�� ��� ����
	int i = 1;

	ptrlist->curr = ptrlist->head->next;

	while (i!=numToDelete) { // curr�� ������ ���� ��带 ����ų ������ ��ȸ
		ptrlist->curr = ptrlist->curr->next;
		i++;
	}

	ptrlist->curr->prev->next = ptrlist->curr->next;	// �����ҳ���� ���� ����� next�� �����ҳ���� ���� ��带 ����Ű����
	ptrlist->curr->next->prev = ptrlist->curr->prev;	// �����ҳ���� ���� ����� prev�� �����ҳ���� ���� ��带 ����Ű����

	free(ptrlist->curr);	// curr�� ����Ű�� �ִ� ��� �޸� �Ҵ� ����
	(ptrlist->numOfData)--;	// ��� ���� ����
}


void listSearchForDel(LIST* ptrlist, int* searchedNum) {

	char keyword[100] = { 0, };
	char chk = 0;

	printf("------------------------------------------------------------------------------\n");
	printf("   �˻�� �Է��ϼ���.......................[                          ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf_s(" %99[^\n]", keyword, sizeof(keyword));
	printf("\n------------------------------------------------------------------------------\n");
	printf("                ����                 ����      ����     ������    ���࿬��   \n");
	printf("==============================================================================\n");

	int i = 1;
	ptrlist->curr = ptrlist->head->next;

	if (ptrlist->curr == ptrlist->tail) {	// curr �����Ͱ� ���ϴ��̳�带 ����Ű�� ���
	}
	else {
		while (ptrlist->curr != ptrlist->tail) { // curr�� ��ȸ�ϸ� ���ϴ��̳�带 ����ų ������ �ݺ� ���
			if (strstr(ptrlist->curr->title, keyword) != NULL) {	// str1 ���ڿ��� str2 ���ڿ��� �����ϰ� ������ char * ��ȯ
				printf("[%2d] %-30s %-9d %-10s %-8d %02d.%02d.%02d\n\n", i, ptrlist->curr->title, ptrlist->curr->price,
					ptrlist->curr->author, ptrlist->curr->page, ptrlist->curr->date.year, ptrlist->curr->date.month, ptrlist->curr->date.day);
				searchedNum[chk] = i;	// searchedNum�� �˻� ��� ���
				chk++;	// �˻� ����� ���� ���� chk++
			}
			ptrlist->curr = ptrlist->curr->next;
			i++;	// å��ȣ ������� �˻������ ������� i++
		}
		if (chk == 0) printf("   �˻� ����� �����ϴ�.\n\n");
		printf("------------------------------------------------------------------------------\n");
	}
}


void sortMenu(LIST* ptrlist) {

	int select;
	printf("|----------------------------------------------------------------------------|\n");
	printf("|                                                                            |\n");
	printf("|  �������� �����Ͻðڽ��ϱ�?                                                |\n");
	printf("|                                                                            |\n");
	printf("|  1. ���� ��                                                                |\n");
	printf("|                                                                            |\n");
	printf("|  2. ���࿬�� ��                                                            |\n");
	printf("|                                                                            |\n");
	printf("|  3. ������ ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  4. ������ ��                                                              |\n");
	printf("|                                                                            |\n");
	printf("|  5. ���ڸ� ��                                                              |\n");
	printf("------------------------------------------------------------------------------\n\n");
	if (listCount(ptrlist) <= 0) {
		printf("   ����� �����Ͱ� �����ϴ�. �޴��� ���ư��ϴ�...\n\n   ");
		system("pause");
		return;
	}
	printf("   ���ϴ� �޴��� �Է��ϼ��� [ ]\b\b");
	scanf_s("%d", &select);
	
	if (select > 0 && select < 6) {

		LIST tempList;	// �������� �Ѽ����� �ʱ� ���� ���Ŀ� ���纻
		listInit(&tempList);	// ����Ʈ �ʱ⼳��
		copyList(&tempList, ptrlist);	// ����Ʈ ����, listInit �� ���

		if (select == 1) insertionSort(&tempList, (_comp)compare_price);
		else if (select == 2) insertionSort(&tempList, (_comp)compare_date);
		else if (select == 3) insertionSort(&tempList, (_comp)compare_page);
		else if (select == 4) insertionSort(&tempList, (_comp)compare_title);
		else if (select == 5) insertionSort(&tempList, (_comp)compare_author);

		system("cls");
		listPrint(&tempList);	// ���� ������ ���
		freeAllNode(&tempList);	// �ӽø���Ʈ �޸� ��ü �Ҵ� ����

	}
	else {
		rewind(stdin);
		printf("   �߸� �Է��ϼ̽��ϴ�. �޴��� ���ư��ϴ�...");
		system("pause");
	}
}


void copyList(LIST* destination, LIST* source) {	// ����Ʈ ����

	source->curr = source->head->next;	// �ҽ�����Ʈ curr�� 1��° ������ ��带 ����Ű����

	while (source->curr != source->tail) {	// �ҽ�����Ʈ curr�� ������ ����ų������ �ݺ�

		NODE* newDestNode = (NODE*)calloc(1, sizeof(NODE));	// �� ��� ����, �ӽ� �������� newDestNode�� �ּҰ� ����

		if (newDestNode != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

			memcpy(newDestNode, source->curr, sizeof(NODE));	// �޸� ����

			newDestNode->prev = destination->tail->prev;	// ������ ����Ʈ ������ ����� ��� ����
			destination->tail->prev->next = newDestNode;
			newDestNode->next = destination->tail;
			destination->tail->prev = newDestNode;

			(destination->numOfData)++;	// ������ ���� ����

			source->curr = source->curr->next;	// �ҽ�����Ʈ�� curr�� ����ĭ���� �̵�
		}
		else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
	}
}

void putNPushNode(NODE* compNode, NODE* curr) {	// ��� ���ϴ� �ڸ��� ���� �ֱ�

	NODE* temp = (NODE*)malloc(sizeof(NODE));	// ������ ���� ���� �ӽ� ���
	if (temp != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

		memcpy(temp, curr, sizeof(NODE));

		// curr�� compNode �տ� ���� �ְ� ���� curr ���ʰ� ���ʳ�带 ���� ��������
		curr->prev = compNode->prev;
		compNode->prev->next = curr;

		curr->next = compNode;
		compNode->prev = curr;

		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;

		free(temp);	// temp �޸� �Ҵ� ����
	}
	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
}


// �˻� ���� �������
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
// �˻� ���� �������




void insertionSort(LIST* ptrlist, _comp criteria) {		// ��������
	
	NODE* compNode = NULL; // ���Ŀ� �ӽ� ������, curr �� ���� �������� ��ȸ�ϸ� ��Һ�

	ptrlist->curr = ptrlist->head->next->next;	// curr�� 2��° ��� ����Ŵ
	compNode = ptrlist->head->next;	// compNode�� 1��° ��� ����Ŵ

	while (ptrlist->curr != ptrlist->tail) {	// curr�� ���ϴ��� �������� �ݺ�

		if (criteria(ptrlist->curr, compNode) >=0) {	// ������ �̹� ���ĵ� �ڷ�� curr�����Ͱ� �� ũ�ų� ������ �ϰ͵� ����
			ptrlist->curr = ptrlist->curr->next; // ������ �������� �ٷ� curr ��ĭ �ڷ�
		}
		else {
			// curr�����Ͱ� ���� ���� compNode�� �������� �̵��ϴµ� 1��° �����ͳ�������
			while (compNode != ptrlist->head->next && criteria(ptrlist->curr, compNode) < 0) {
				compNode = compNode->prev;
			}
			NODE* temp = ptrlist->curr;	// curr�� ��ġ �����
			putNPushNode(compNode, ptrlist->curr);	// curr ��� �˸��� ��ġ�� ���� �ֱ�
			ptrlist->curr = temp->next;	// ���� �ֱ� ���� �����ص� curr�� ����ĭ���� �ű�
		}
		compNode = ptrlist->curr->prev;	// compNode�� curr���� ��ĭ ��
	}
}


void delLastNode(LIST* ptrlist) {	// ������ ���� ����, freeAllNode������ ���� �׽�Ʈ������ε� ��

	ptrlist->curr = ptrlist->tail->prev;	// ���ϴ��̳���� prev���� curr�� ����

	if (ptrlist->curr == ptrlist->head) {	// curr�� �����̳�带 ����Ű��(=�����Ͱ� ������) �ƹ��͵� ����
	}
	else {
		ptrlist->curr->prev->next = ptrlist->curr->next;	// ������ �����ͳ���� ���� ����� next�� ���ϴ��̳�带 ����Ű����
		ptrlist->curr->next->prev = ptrlist->curr->prev;	// ���ϴ��̳���� prev�� ������ �����ͳ���� ���� ��带 ����Ű����

		free(ptrlist->curr);	// curr�� ����Ű�� ������ �����ͳ�� �޸� �Ҵ� ����

		(ptrlist->numOfData)--;	// ��� ���� ����
	}
}


void freeAllNode(LIST* ptrlist) {	// ����Ʈ�� ��� ��� free

	while (listCount(ptrlist) > 0) {	// ���� ���� ��ŭ ���� (delLastNode�Լ� ���ο��� listCount--��)
		delLastNode(ptrlist);	// ������ ������ �����ϴ� �Լ� ȣ��
	}	
	free(ptrlist->head);	// �����̳�� �޸� �Ҵ� ����
	free(ptrlist->tail);	// ���ϴ��̳�� �޸� �Ҵ� ����

}


//void swapNode(NODE* compNode, NODE* curr) {
//
//	NODE* temp = (NODE*)malloc(sizeof(NODE));	// ������ ���� �ӽ� ���
//	if (temp != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��
//
//		memcpy(temp, curr, sizeof(NODE));
//
//		// ���� prev, next ������ ����
//		curr->prev = compNode->prev;
//		curr->next = compNode->next;
//
//		compNode->prev = temp->prev;
//		compNode->next = temp->next;		
//
//		free(temp);	// temp �޸� �Ҵ� ����
//
//	}
//	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");
//}