#include <stdio.h>
#include <Windows.h>
#include "linkedListBook.h"


void readFromFile(LIST* ptrlist) {

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "booklist.bin", "rb");	// ����س��� ����Ʈ ����Ϸ��� booklist_backup.bin

	if (err == 0) {

		fseek(fp, 0, SEEK_END);    // ���� �����͸� ������ ������ �̵���Ŵ
		size_t fileSize = ftell(fp);          // ���� �������� ���� ��ġ�� ����
		rewind(fp);		// ���� �������� ��ġ�� �ٽ� �Ǿ����� ����

		int numberOfNode = (int) fileSize / sizeof(NODE);	// ���Ͽ� ����� ����� ����

		NODE* tempBook = (NODE*)malloc(sizeof(NODE));
		if (tempBook != NULL) {	// malloc ��ȯ�� NULL�� ��� ����ó��

			for (int i = 0; i < numberOfNode; i++) {	// numberOfNode ��ŭ �ݺ��ϸ�
				fread(tempBook, sizeof(NODE), 1, fp); // ���� �о� ���̱�
				addNode(ptrlist, tempBook);
			}

			free(tempBook);	// tempBook �޸� �Ҵ� ����

		} else printf("�޸� �Ҵ翡 �����Ͽ����ϴ�.");

		fclose(fp);	// ���� ��Ʈ�� �ݱ�

	}
	else {
		printf("���Ͽ��� ����\n");
		printf("�����ڵ� : %d\n", err);
		system("pause");
	}
}


void writeToFile(LIST* ptrlist) {

	FILE* fp = NULL;
	errno_t err = fopen_s(&fp, "booklist.bin", "wb");	// ���� ��½�Ʈ�� ����

	if (err == 0) {

		ptrlist->curr = ptrlist->head->next;	// �����̳���� next ���� curr �����Ϳ� ����

		while (ptrlist->curr != ptrlist->tail) {	//	curr�� ���ϴ��̳�带 ����Ű�� �� ������ �ݺ�
			fwrite(ptrlist->curr, sizeof(NODE), 1, fp); // ���� ���
			ptrlist->curr = ptrlist->curr->next;	// curr�� next�ּҰ� ����
		}
		fclose(fp);	// ���� ��Ʈ�� �ݱ�
	}
	else {
		printf("�������� ����\n");
		printf("�����ڵ� : %d\n", err);
		system("pause");
	}
}

