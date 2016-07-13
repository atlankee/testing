//1515987 ������ �����ͱ��� �� ������Ʈ #7��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//5�� Ż���-2
//���� ���� ���� ����Ʈ

#define MNLength 10 //����� max name length

typedef struct ListNode //���� ����Ʈ ����ü ListNode��
{
	struct ListNode *pre; //����� ��ũ�� ����Ű�� �����Ͱ� �ִ�. pre�� ���� ��ũ�� ����Ų��.
	int num;
	char person[MNLength]; //���(�̸�����) �ϳ��� ������->people ���� ����Ų��
	struct ListNode *next; //����� ��ũ�� ����Ű�� �����Ͱ� �ִ�. next�� ���� ��ũ�� ����Ű��
} ListNode; //�̸��� ListNode��� �Ѵ�

//���� ����Ʈ ���� �Լ�
void insert_node_double(ListNode **phead, ListNode *p, ListNode *new_node)
{
	//phead: ��� �������� ������, p:���� ���, new_node: ������ ���
	if (*phead == NULL)
	{	new_node->pre = new_node->next = new_node; *phead = new_node;} //����Ʈ�� ������� �� ������ ��尡 ù ��尡 �ȴ�
	//�� �� ���� ���Ե� ���� �ڱ� �ڽ��� (���������) ����Ű���� �Ѵ�.
	else
	{
		new_node->pre = p; new_node->next = p->next;
		p->next->pre = new_node; p->next = new_node;
	} //�� ���� ��쿡�� ���� ��� ������ ��带 �����Ѵ�. �� �� new_node�� �߰��� �տ� p�� ����ų �� �ְ� �ȴ� 
}

//���� ��� ���� �Լ�
void remove_node(ListNode **phead, ListNode *p, ListNode *remove_node)
{
	//���� ���(����/�����ϰ� ���� ��� ���� ���) (�̶� p->next�� remove_node, remove_node->pre�� p)
	
	//printf("%d�� %s�� Ż��\n",remove_node->num,remove_node->person); Ż���� ����� ��ȣ�� �̸��� ����Ѵ�
	remove_node->pre->next = remove_node->next;
	remove_node->next->pre = remove_node->pre; //�����ϰ� ���� ����� �յڸ�ũ���� ��������� ���� ����� �յڸ�ũ�鿡 ����(�ڸ� �̾��ְԵ�)
	free(remove_node); //�� ��尡 �Ҵ��ߴ� �޸𸮸� �����ش�
}

//���� ���� ��� ���� �Լ�
ListNode * set_nodes_double(int num,char person[MNLength],ListNode *next) //��� ���� �޸� �Ҵ� �Լ� ����
{
	//�̹� ��� ���� �������ֱ� ������ node�� ������ ��ŭ ������� ������ �ִ´�.
	ListNode * new_node; //new_node�� linkedlist�� ����� ������ ���� ���̴�
	new_node = (ListNode*)malloc(sizeof(ListNode)); //new_node�� ListNode�� ũ�⸸ŭ ���� �Ҵ�ȴ�

	if(new_node == NULL)
	{	fprintf(stderr,"�޸𸮸� �Ҵ��� �� �����ϴ�.\n");
		//���� new_node�� ����Ű�� ���� ������(�ּ� NULL) �޸� �Ҵ� ������
		exit(1); //���α׷��� ��ٷ� �����Ѵ�.
	}
	new_node->num = num;
	strcpy(new_node->person, person);
	new_node->pre = new_node->next = new_node;

	return new_node;
	//�׷��� ������ new_node�� ���� ���ڷ� �� num, person�� �����ϰ� �ּҴ� ���ڷ� �� link�� �����ϰ� new_node�� �����Ѵ�.
}

//���� ����Ʈ ���� ���ϴ� �Լ�
int listlength(ListNode* node)
{
	ListNode * temp = node; //�ϴ� node�� �ӽ÷� �����ص� temp�� �����ϰ�
	int count = 0;
	
	if (node) //��� ���� ������
	{
		count++; temp = temp->next; //���� count�� 1 ������Ű�� temp�� ���� ��ũ�� �̵�
		while(temp != node)
		{
			count++; temp = temp->next;
			//temp�� ���� ��ũ�� �̵��ϸ鼭 �ʹݿ� ���ڷ� �־��� node�� ���������� count�� ������Ų��.
		}
	}
	return count; //���� count�� ��������ŭ�� ���� ����Ʈ�� ����
}

//���� ����Ʈ ��� �Լ�
void display(ListNode * linkedlist) //���� ����� �ؾߵ� �� ���Ƽ� �Լ��� ���� �Ű� ���Ҵ�..
{
	for(int i=0;i<listlength(linkedlist);i++)
	{
		printf("%d: ",linkedlist->num);
		printf("%s->",linkedlist->person); //�Լ��� ȣ�� �Ͽ� ���ĵ� ���� ����Ʈ�� ������ ����Ѵ�
		linkedlist = linkedlist->next; //��ũ�� ����Ű�� ������ �̵��ϱ� ���� ���� ��ũ�� �̵�
	}
	printf("\n\n");
}
void display_reversed(ListNode * linkedlist) //�������� ���ƾߵǴ� ����
{
	for(int i=0;i<listlength(linkedlist);i++)
	{
		printf("%d: ",linkedlist->num);
		printf("%s->",linkedlist->person); //�Լ��� ȣ�� �Ͽ� ���ĵ� ���� ����Ʈ�� ������ ����Ѵ�
		linkedlist = linkedlist->pre; //��ũ�� ����Ű�� ������ �̵��ϱ� ���� ���� ��ũ�� �̵�
	}
	printf("\n\n");
}

void main(void)
{
	printf("1515987 ������ Project#7\n");

	ListNode *linkedlist = NULL; //���� ����Ʈ�� �����Ѵ�. ó���� ������ NULL

	//������� ����(�̸�)�� ��� �迭�� �����Ѵ�..
	char people[27][MNLength]={"�����","�̸���","������","������","�ٴٴ�","����","������","�ٹٹ�","����","�ƾƾ�",
				"����","������","����","������","������","������","������","īīī","������","ŸŸŸ",
				"������","ȣȣȣ","������","������","������","������","�ڵ���"};

	char (*personp)[MNLength];	//person pointer. people �迭�� �̸� �ϳ�(person)�� ����Ų�� (*personp)[�̸�ũ��]
	/*for(int i=0;i<27;i++){	
		personp = &people[i];		//personp �� ������� �ִ� person�� �ּҸ� ������ person�� ���� ����ų���̴�.
		printf("%s ",*(personp));	//personp�� ����Ű�� people[i]�� �ּ��� ��(�׳� �� �ε��� ��)�� ����Ѵ�.
	}*/

	for(int i=27;i>0;i--)
	{
		personp = &people[i-1];		//personp �� ������� �ִ� person�� �ּҸ� ������ person�� ���� ����ų���̴�.
		insert_node_double(&linkedlist,linkedlist,set_nodes_double(i,*(personp),linkedlist)); //i: ������� ���� ��ȣ�� ǥ��
		//personp�� ����Ű�� people �ε����� ���ڿ��� ��������
		//������ ������ linkedlist�� ���ο� ��尡 ��������鼭 ���� ����Ʈ�� ���ʴ�� ���Եȴ�.
		//�� �� ���ο� ��尡 ���ԵǸ鼭 �� ���� NULL��� ������ ���Ե� ��� �� ��ó���� �����ߴ� ��带 ����Ű�� �ȴ�.
	}
	printf("���ε��� 5�ν� �谡 ��Ÿ�����ϴ�..!\n����̱⸦ ���� ������ 27�� �� 5���� ���ε��� Ż���ϰ� �ɰ��Դϴ�.\n");
	printf("\n���ε��� ������ �����:\n");
	display(linkedlist);
	display_reversed(linkedlist); //���� ���ε��� ������ ����� ���(�����)

	srand((unsigned int)time(NULL)); //���� ���� �Լ��� �̿��� ������ ������ ��ȣ�� �����Ѵ�.
	int fate = rand() % 27 +1; //fate: ����. ����̱�� ���ε��� ���� ����� �ɷ�����..
	printf("����� ����: %d\n",fate);

	while(linkedlist)
	{
		if(linkedlist->num == fate) //���� ���ڰ� fate�� ����� �߰ߵǸ�
		{
			while(listlength(linkedlist) != 5) //5���� ����������
			{
				remove_node(&linkedlist,linkedlist->next->next->next->next,linkedlist->next->next->next->next->next);
				//���� ���� 5���� �Ѿ�� �� �ڿ� ����� Ż���Ѵ�(���ε��� ����)
				display(linkedlist); //���� ���ε��� ������ ����� ��� ������
				linkedlist = linkedlist->next->next->next->next->next;
				//����� Ż�� �� �� 5���� �Ѿ��(�� ���� ����� Ż�� ������ ��) ���� ���� �ݺ�.
				//5���� �Ѿ�� ���� ��������� ���鼭 Ż����Ű�� ������ Ż���� ��� ������ ����� �������� �����

				//�̷� �߰��������� while ������ ���� �߿� �����ο����� 5���� ������ �ľ��ؾ��Ѵ�..
				if(listlength(linkedlist) == 6) //�׷��� �ϴ� 6���� ���� �Ǹ� ������ ����������
					break;
				else
				{
					remove_node(&linkedlist,linkedlist->pre->pre->pre->pre->pre->pre->pre,linkedlist->pre->pre->pre->pre->pre->pre);
					//�� ���� ��쿡�� �̾ �ݴ� �������� 6���� �Ѿ�� �� ���� ����� Ż���Ѵ�
					display_reversed(linkedlist); //���� ���ε��� ������ ����� ��� ������
					linkedlist = linkedlist->pre->pre->pre->pre->pre->pre; //����� Ż�� �� �� 6���� �Ѿ�� ���� ���� �ݺ�
				}
			}
			linkedlist = linkedlist->pre; //������ ��� ��尡 �������ϴ� ��Ȳ..�̾ �ϴ� ������ ����� ���� ���� ���� �̵��� ��
			remove_node(&linkedlist,linkedlist->pre->pre->pre->pre->pre->pre,linkedlist->pre->pre->pre->pre->pre);
			//��Ģ��� �ݴ�� �̵��� �� 6���� �Ѿ�� 7��° ���(���� ������ �Ǿ��� ���)�� Ż����Ų��.
			//�̹� �ѹ� pre�� �̵��߱� ������ remove_node�� pre�� while���� ���� ���������� �̵��� �ϳ� �ٿ���
			display_reversed(linkedlist); //���� ���ε��� ������ ����� ��� ������
			break;
		}
		linkedlist = linkedlist->next; //���� ���ڰ� fate�� ����� ���ö� ���� ��ũ�� ���󰣴�.
	}
	printf("���� 5���� ���ε��� Ż���Ͽ����ϴ�.(¦¦¦)\n\n");
	
}