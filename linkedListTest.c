#define DEBUG

#ifdef DEBUG

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedListBook.h"
#include <time.h>

void testAdd(LIST* ptrlist) {	// �׽�Ʈ�� ���� �߰�



	NODE* tempBook = (NODE*)malloc(sizeof(NODE));
	if (tempBook != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

		// �׽�Ʈ�� ������
		char buf[30];	// ����->���ڿ� ��ȯ ���� �ӽ� buffer
		sprintf_s(buf, sizeof(buf), "%d��° å(test)", listCount(ptrlist) + 1);	// ������ ���ڿ��� ��ȯ�� ���ۿ� �������ִ� �Լ�
		strcpy_s(tempBook->title, sizeof(tempBook->title), buf);

		char name[][3] = {"��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��"};		
		strcpy_s(buf, sizeof(buf), name[rand() % 20]);
		strcat_s(buf, sizeof(buf), name[rand() % 20]);
		strcat_s(buf, sizeof(buf), name[rand() % 20]);
		strcpy_s(tempBook->author, sizeof(tempBook->author), buf);

		tempBook->price = rand()%50*1000;
		tempBook->page = rand()%1000;
		tempBook->date.year = rand() % 12 + 1;
		tempBook->date.month = rand() % 12 + 1;
		tempBook->date.day = rand() % 30 + 1;
		// �׽�Ʈ�� ������

		addNode(ptrlist, tempBook);	// ��� �߰� �Լ� ȣ��

		free(tempBook);	// tempBook �޸� �Ҵ� ����	

	}
	else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�");
}

#endif // DEBUG