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
	listInit(&booklist);	// ��ũ�帮��Ʈ �ʱ⼳��

	readFromFile(&booklist);	// ���Ϸκ��� ������ �о���̱�

	int menu, exit = FALSE;

	while (exit == FALSE) {

		system("cls");
		menu = dispMenu(listCount(&booklist));	// �޴� ���
		system("cls");

		if (menu == 1) listInsert(&booklist);	// ���� �߰�
		else if (menu == 2) deleteMenu(&booklist);	// ���� ����
		else if (menu == 3) sortMenu(&booklist);	// ���� ����
		else if (menu == 4) listSearch(&booklist);	// ���� �˻�
		else if (menu == 5) listPrint(&booklist);	// ���� ���
		else if (menu == 6) {	// ����
			writeToFile(&booklist);	// ���Ͽ� ���
			exit = TRUE;	// ���� Ż��
			freeAllNode(&booklist);	// ��� ��� �޸� �Ҵ� ����
		}
#ifdef DEBUG
		else if (menu == 7)	testAdd(&booklist); // �׽�Ʈ�� ���� �߰�
		else if (menu == 8) delLastNode(&booklist);	// �׽�Ʈ�� ���� ����
#endif
		else {
			rewind(stdin);	// �ٸ� ���ڳ� ����(��)�� ������ �� �Է¹��� ���
		}
	}
#ifdef DEBUG
	_CrtDumpMemoryLeaks();	// ����׿� memory leaks Ž��
#endif
	return 0;
}