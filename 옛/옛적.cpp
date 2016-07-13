//1515987 ������ �����ͱ��� �� ������Ʈ #6��
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//5�� Ż���
//���� ���� ����Ʈ

#define MNLength 10 //����� max name length

typedef struct ListNode //���� ����Ʈ ����ü ListNode��
{
	int num;
	char person[MNLength]; //���(�̸�����) �ϳ��� ������->people ���� ����Ų��
	struct ListNode *link; //����� ��ũ�� ����Ű�� �����Ͱ� �ִ�
} ListNode; //�̸��� ListNode��� �Ѵ�

//���� ��� ���� �Լ�
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	//phead: ��� �������� ������, p:���� ���, new_node: ������ ���

	if (*phead == NULL)
	{	new_node->link = new_node; *phead = new_node;} //����Ʈ�� ������� �� ������ ��尡 ù ��尡 �ȴ�
	//�� �� ���� ���Ե� ���� �ڱ� �ڽ��� ����Ű���� �Ѵ�.
	else
	{	new_node->link = p->link; p->link = new_node;} //�� ���� ��쿡�� ���� ��� ������ ��带 �����Ѵ�
}

//���� ��� ���� �Լ�
void remove_node(ListNode **phead, ListNode *p, ListNode *remove_node)
{
	//���� ���(����/�����ϰ� ���� ��� ���� ���)
	printf("%d�� %s�� Ż��\n",remove_node->num,remove_node->person); //Ż���� ����� ��ȣ�� �̸��� ����Ѵ�
	p->link = remove_node->link; // p -> �� ��� -> �� ��� �� 
	free(remove_node); //�� ��尡 �Ҵ��ߴ� �޸𸮸� �����ش�
}

//���� ��� ���� �Լ� (��ǻ� ���� �����鿡 ��� ���� ��� ���� �ռ��� ����..
ListNode * set_nodes(int num,char person[MNLength],ListNode *link) //��� ���� �޸� �Ҵ� �Լ� ����
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
	strcpy(new_node->person, person); //person�� String���̱� ������ strcpy�� �̿��ؼ� new_node�� person���� ����
	new_node->link = link;

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
		count++; temp = temp->link; //���� count�� 1 ������Ű�� temp�� ���� ��ũ�� �̵�
		while(temp != node)
		{
			count++; temp = temp->link;
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
		linkedlist = linkedlist->link; //��ũ�� ����Ű�� ������ �̵��ϱ� ���� ���� ��ũ�� �̵�
	}
	printf("\n\n");
}


void main(void)
{
	printf("1515987 ������ Project#6\n");

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
		insert_node(&linkedlist,linkedlist,set_nodes(i,*(personp),linkedlist)); //i: ������� ���� ��ȣ�� ǥ��
		//personp�� ����Ű�� people �ε����� ���ڿ��� ��������
		//������ ������ linkedlist�� ���ο� ��尡 ��������鼭 ���� ����Ʈ�� ���ʴ�� ���Եȴ�.
		//�� �� ���ο� ��尡 ���ԵǸ鼭 �� ���� NULL��� ������ ���Ե� ��� �� ��ó���� �����ߴ� ��带 ����Ű�� �ȴ�.
	}
	printf("���ε��� 5�ν� �谡 ��Ÿ�����ϴ�..!\n����̱⸦ ���� ������ 27�� �� 5���� ���ε��� Ż���ϰ� �ɰ��Դϴ�.\n");
	printf("\n���ε��� ������ �����:\n");
	display(linkedlist); //���� ���ε��� ������ ����� ���

	srand((unsigned int)time(NULL)); //���� ���� �Լ��� �̿��� ������ ������ ��ȣ�� �����Ѵ�.
	int fate = rand() % 27; //fate: ����. ����̱�� ���ε��� ���� ����� �ɷ�����..
	printf("����� ����: %d\n",fate);

	while(linkedlist)
	{
		if(linkedlist->num == fate) //���� ���ڰ� fate�� ����� �߰ߵǸ�
		{
			while(listlength(linkedlist) != 5) //5���� ����������
			{
				remove_node(&linkedlist,linkedlist->link->link->link->link,linkedlist->link->link->link->link->link);
				//���� ���� 5���� �Ѿ�� �� �ڿ� ����� Ż���Ѵ�(���ε��� ����)
				display(linkedlist); //���� ���ε��� ������ ����� ���
				linkedlist = linkedlist->link->link->link->link; //����� Ż�� �� �� 4���� �Ѿ��(�� ���� ����� Ż�� ������ ��) ���� ���� �ݺ�
				//link�� ���� 4�� �̵��ϰ� �� ������ remove�� ���� ������ Ż�� ������ �� ó���� ����ϴ� ���� ���� �� ���Ƽ� �̷��� �ߴ�..
			}
			break;
		}
		linkedlist = linkedlist->link; //���� ���ڰ� fate�� ����� ���ö� ���� ��ũ�� ���󰣴�.
	}
	printf("���� 5���� ���ε��� Ż���Ͽ����ϴ�.(¦¦¦)\n\n");
	
}
