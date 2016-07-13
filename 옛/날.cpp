//1515987 박정윤 데이터구조 텀 프로젝트 #7번
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//5인 탈출기-2
//이중 원형 연결 리스트

#define MNLength 10 //사람의 max name length

typedef struct ListNode //연결 리스트 구조체 ListNode는
{
	struct ListNode *pre; //연결된 링크를 가리키는 포인터가 있다. pre는 이전 링크를 가리킨다.
	int num;
	char person[MNLength]; //사람(이름길이) 하나의 데이터->people 값을 가리킨다
	struct ListNode *next; //연결된 링크를 가리키는 포인터가 있다. next는 다음 링크를 가리키고
} ListNode; //이름도 ListNode라고 한다

//연결 리스트 삽입 함수
void insert_node_double(ListNode **phead, ListNode *p, ListNode *new_node)
{
	//phead: 헤드 포인터의 포인터, p:선행 노드, new_node: 삽입할 노드
	if (*phead == NULL)
	{	new_node->pre = new_node->next = new_node; *phead = new_node;} //리스트가 비어있을 때 삽입할 노드가 첫 노드가 된다
	//이 때 새로 삽입될 노드는 자기 자신을 (양방향으로) 가리키도록 한다.
	else
	{
		new_node->pre = p; new_node->next = p->next;
		p->next->pre = new_node; p->next = new_node;
	} //그 외의 경우에는 선행 노드 다음에 노드를 삽입한다. 이 때 new_node는 추가로 앞에 p를 가리킬 수 있게 된다 
}

//연결 노드 삭제 함수
void remove_node(ListNode **phead, ListNode *p, ListNode *remove_node)
{
	//선행 노드(삭제/삽입하고 싶은 노드 앞의 노드) (이때 p->next는 remove_node, remove_node->pre는 p)
	
	//printf("%d번 %s님 탈락\n",remove_node->num,remove_node->person); 탈락한 사람의 번호와 이름을 출력한다
	remove_node->pre->next = remove_node->next;
	remove_node->next->pre = remove_node->pre; //삭제하고 싶은 노드의 앞뒤링크들을 삭제노드의 선행 노드의 앞뒤링크들에 대입(뒤를 이어주게됨)
	free(remove_node); //뺄 노드가 할당했던 메모리를 돌려준다
}

//이중 연결 노드 세팅 함수
ListNode * set_nodes_double(int num,char person[MNLength],ListNode *next) //노드 동적 메모리 할당 함수 정의
{
	//이미 사람 수가 정해져있기 떄문에 node에 정해진 만큼 사람들의 정보를 넣는다.
	ListNode * new_node; //new_node는 linkedlist에 사람의 정보를 담을 것이다
	new_node = (ListNode*)malloc(sizeof(ListNode)); //new_node는 ListNode의 크기만큼 동적 할당된다

	if(new_node == NULL)
	{	fprintf(stderr,"메모리를 할당할 수 없습니다.\n");
		//만약 new_node가 가리키는 것이 없으면(주소 NULL) 메모리 할당 에러로
		exit(1); //프로그램을 곧바로 종료한다.
	}
	new_node->num = num;
	strcpy(new_node->person, person);
	new_node->pre = new_node->next = new_node;

	return new_node;
	//그렇지 않으면 new_node의 값에 인자로 준 num, person을 대입하고 주소는 인자로 준 link를 대입하고서 new_node를 리턴한다.
}

//연결 리스트 길이 구하는 함수
int listlength(ListNode* node)
{
	ListNode * temp = node; //일단 node를 임시로 저장해둘 temp를 정의하고
	int count = 0;
	
	if (node) //노드 값이 있으면
	{
		count++; temp = temp->next; //먼저 count를 1 증가시키고 temp는 다음 링크로 이동
		while(temp != node)
		{
			count++; temp = temp->next;
			//temp는 다음 링크로 이동하면서 초반에 인자로 넣어준 node를 만날때까지 count를 증가시킨다.
		}
	}
	return count; //따라서 count가 세어진만큼이 연결 리스트의 길이
}

//연결 리스트 출력 함수
void display(ListNode * linkedlist) //자주 출력을 해야될 거 같아서 함수로 따로 옮겨 놓았다..
{
	for(int i=0;i<listlength(linkedlist);i++)
	{
		printf("%d: ",linkedlist->num);
		printf("%s->",linkedlist->person); //함수를 호출 하여 정렬된 연결 리스트의 수들을 출력한다
		linkedlist = linkedlist->next; //링크가 가리키는 값으로 이동하기 위해 다음 링크로 이동
	}
	printf("\n\n");
}
void display_reversed(ListNode * linkedlist) //역순으로 돌아야되는 버전
{
	for(int i=0;i<listlength(linkedlist);i++)
	{
		printf("%d: ",linkedlist->num);
		printf("%s->",linkedlist->person); //함수를 호출 하여 정렬된 연결 리스트의 수들을 출력한다
		linkedlist = linkedlist->pre; //링크가 가리키는 값으로 이동하기 위해 다음 링크로 이동
	}
	printf("\n\n");
}

void main(void)
{
	printf("1515987 박정윤 Project#7\n");

	ListNode *linkedlist = NULL; //연결 리스트를 선언한다. 처음은 여전히 NULL

	//사람들의 정보(이름)를 담는 배열을 선언한다..
	char people[27][MNLength]={"김수동","이명자","가가가","나나나","다다다","라라라","마마마","바바바","사사사","아아아",
				"어어어","오오오","우우우","으으으","이이이","자자자","차차차","카카카","파파파","타타타",
				"하하하","호호호","후후후","헤헤헤","흐흐흐","히히히","박두주"};

	char (*personp)[MNLength];	//person pointer. people 배열의 이름 하나(person)를 가리킨다 (*personp)[이름크기]
	/*for(int i=0;i<27;i++){	
		personp = &people[i];		//personp 는 순서대로 있는 person의 주소를 담으면 person의 값도 가리킬것이다.
		printf("%s ",*(personp));	//personp가 가리키는 people[i]의 주소의 값(그냥 그 인덱스 값)을 출력한다.
	}*/

	for(int i=27;i>0;i--)
	{
		personp = &people[i-1];		//personp 는 순서대로 있는 person의 주소를 담으면 person의 값도 가리킬것이다.
		insert_node_double(&linkedlist,linkedlist,set_nodes_double(i,*(personp),linkedlist)); //i: 사람들의 고유 번호를 표현
		//personp가 가리키는 people 인덱스의 문자열을 가져오고
		//가져올 때마다 linkedlist에 새로운 노드가 만들어지면서 연결 리스트에 차례대로 삽입된다.
		//이 때 새로운 노드가 삽입되면서 그 노드는 NULL대신 이전에 삽입된 노드 중 맨처음에 삽입했던 노드를 가리키게 된다.
	}
	printf("무인도에 5인승 배가 나타났습니다..!\n제비뽑기를 통해 남겨진 27명 중 5명만이 무인도를 탈출하게 될것입니다.\n");
	printf("\n무인도에 남겨진 사람들:\n");
	display(linkedlist);
	display_reversed(linkedlist); //현재 무인도에 남겨진 사람들 출력(양방향)

	srand((unsigned int)time(NULL)); //난수 생성 함수를 이용해 제비의 임의의 번호를 지정한다.
	int fate = rand() % 27 +1; //fate: 제비. 제비뽑기로 무인도에 남을 사람을 걸러낸다..
	printf("운명의 제비: %d\n",fate);

	while(linkedlist)
	{
		if(linkedlist->num == fate) //고유 숫자가 fate인 사람이 발견되면
		{
			while(listlength(linkedlist) != 5) //5명이 남을때까지
			{
				remove_node(&linkedlist,linkedlist->next->next->next->next,linkedlist->next->next->next->next->next);
				//제비 포함 5명을 넘어가고 그 뒤에 사람이 탈락한다(무인도에 남음)
				display(linkedlist); //현재 무인도에 남겨진 사람들 출력 정방향
				linkedlist = linkedlist->next->next->next->next->next;
				//사람이 탈락 한 후 5명을 넘어가서(그 다음 사람이 탈락 기준이 됨) 위의 과정 반복.
				//5명을 넘어가는 것은 양방향으로 돌면서 탈락시키기 때문에 탈락한 사람 이후의 사람을 기준으로 해줬다

				//이런 중간시점에서 while 루프를 도는 중에 남은인원수가 5명이 될지를 파악해야한다..
				if(listlength(linkedlist) == 6) //그래서 일단 6명이 남게 되면 루프를 빠져나오고
					break;
				else
				{
					remove_node(&linkedlist,linkedlist->pre->pre->pre->pre->pre->pre->pre,linkedlist->pre->pre->pre->pre->pre->pre);
					//그 외의 경우에는 이어서 반대 방향으로 6명을 넘어가고 그 앞의 사람이 탈락한다
					display_reversed(linkedlist); //현재 무인도에 남겨진 사람들 출력 역방향
					linkedlist = linkedlist->pre->pre->pre->pre->pre->pre; //사람이 탈락 한 후 6명을 넘어가서 위의 과정 반복
				}
			}
			linkedlist = linkedlist->pre; //기준이 됬던 노드가 빠져야하는 상황..이어서 일단 삭제할 노드의 앞의 노드로 먼저 이동한 후
			remove_node(&linkedlist,linkedlist->pre->pre->pre->pre->pre->pre,linkedlist->pre->pre->pre->pre->pre);
			//규칙대로 반대로 이동할 때 6명을 넘어가고 7번째 사람(본래 기준이 되었던 사람)을 탈락시킨다.
			//이미 한번 pre로 이동했기 때문에 remove_node에 pre는 while루프 안의 과정때보다 이동을 하나 줄였다
			display_reversed(linkedlist); //현재 무인도에 남겨진 사람들 출력 역방향
			break;
		}
		linkedlist = linkedlist->next; //고유 숫자가 fate인 사람이 나올때 까지 링크를 따라간다.
	}
	printf("위의 5명이 무인도를 탈출하였습니다.(짝짝짝)\n\n");
	
}