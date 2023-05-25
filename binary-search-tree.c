/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //노드 구조체 정의
	int key; //노드에 입력할 값 변수
	struct node *left; //왼쪽 자식 노드로 이동할 포인터
	struct node *right; //오른쪽 자식 노드로 이동할 포인터
} Node;


int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //명령어를 입력 받을 변수
	int key; //값을 입력 받을 변수
	Node* head = NULL; //헤드 노드를 선언하고 NULL 값으로 초기화
	Node* ptr = NULL;	/* temp */

	printf("[----- [Jeong Hanul] [2020039076] -----]\n\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어를 입력받아 command에 저장

		switch(command) {
		case 'z': case 'Z': //z or Z 입력 시
			initializeBST(&head);
			break;
		case 'q': case 'Q': //q or Q 입력 시
			freeBST(head);
			break;
		case 'n': case 'N': //n or N 입력 시
			printf("Your Key = ");
			scanf("%d", &key); //노드에 넣을 key 값 입력
			insert(head, key);	
			break;
		case 'd': case 'D': //d or D 입력 시
			printf("Your Key = ");
			scanf("%d", &key); //노드에서 삭제할 key 값 입력
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F': //f or F 입력 시
			printf("Your Key = ");
			scanf("%d", &key); //탐색할 key 값 입력
			ptr = searchIterative(head, key);
			if(ptr != NULL) //ptr이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //찾은 노드 값과 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //찾는 노드 값이 없음을 출력
			break;
		case 's': case 'S': //s or S 입력 시
			printf("Your Key = ");
			scanf("%d", &key); //탐색할 key 값 입력
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL) //ptr이 NULL이 아니면
				printf("\n node [%d] found at %p\n", ptr->key, ptr); //찾은 노드 값과 주소 출력
			else
				printf("\n Cannot find the node [%d]\n", key); //찾는 노드 값이 없음을 출력
			break;

		case 'i': case 'I': //i or I 입력 시
			inorderTraversal(head->left);
			break;
		case 'p': case 'P': //p or P 입력 시
			preorderTraversal(head->left);
			break;
		case 't': case 'T': //t or T 입력 시
			postorderTraversal(head->left);
			break;
		default: //이외 입력 시
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) { //이진 트리를 초기화하는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //매개변수로 받은 헤드 노드 h에 Node 사이즈만큼 동적 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //오른쪽 포인터를 자기 자신으로 초기화
	(*h)->key = -9999; //key 값을 -9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr) //inorder 방식으로 트리를 출력하는 함수
{
	if(ptr) { //ptr이 참이면 (NULL이 아님)
		inorderTraversal(ptr->left); //왼쪽 포인터를 매개변수로 하여 함수 재호출 
		printf(" [%d] ", ptr->key); //노드 값 출력
		inorderTraversal(ptr->right); //오른쪽 포인터를 매개변수로 하여 함수 재호출 
	}
}

void preorderTraversal(Node* ptr) //preorder 방식으로 트리를 출력하는 함수
{
	if(ptr) { //ptr이 참이면 (NULL이 아님)
		printf(" [%d] ", ptr->key); //노드 값 출력
		preorderTraversal(ptr->left); //왼쪽 포인터를 매개변수로 하여 함수 재호출
		preorderTraversal(ptr->right); //오른쪽 포인터를 매개변수로 하여 함수 재호출 
	}
}

void postorderTraversal(Node* ptr) //postorder 방식으로 트리를 출력하는 함수
{
	if(ptr) { //ptr이 참이면 (NULL이 아님)
		postorderTraversal(ptr->left); //왼쪽 포인터를 매개변수로 하여 함수 재호출
		postorderTraversal(ptr->right); //오른쪽 포인터를 매개변수로 하여 함수 재호출 
		printf(" [%d] ", ptr->key); //노드 값 출력
	}
}


int insert(Node* head, int key) //노드에 값을 입력하고 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //노드 포인터 newNode를 선언하고 동적 할당
	newNode->key = key; //newNode의 key 값에 입력 받은 key 대입
	newNode->left = NULL; //newNode의 왼쪽 포인터를 NULL로 초기화
	newNode->right = NULL; //newNode의 오른쪽 포인터를 NULL로 초기화

	if (head->left == NULL) { //헤드 노드의 왼쪽 포인터가 NULL이면
		head->left = newNode; //헤드 노드의 왼쪽 포인터에 newNode 대입
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //노드 포인터 newNode를 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	Node* parentNode = NULL; //노드 포인터 parentNode 선언하고 NULL로 초기화
	while(ptr != NULL) { //ptr이 NULL이 아닌 동안

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //ptr의 key 값과 입력 받은 key 값이 같은 경우 1 반환

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //parentNode에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key 값이 입력 받은 key 값보다 작은 경우
			ptr = ptr->right; //ptr에 오른쪽 포인터 대입
		else //ptr의 key 값이 입력 받은 key 값보다 큰 경우
			ptr = ptr->left; //ptr에 왼쪽 포인터 대입
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //parentNode의 key 값이 입력 받은 key 값보다 큰 경우
		parentNode->left = newNode; //parentNode의 왼쪽 포인터에 newNode 대입
	else //parentNode의 key 값이 입력 받은 key 값보다 작은 경우
		parentNode->right = newNode; //parentNode의 오른쪽 포인터에 newNode 대입
	return 1;
}

int deleteLeafNode(Node* head, int key) //해당하는 key 값인 리프 노드를 제거하는 함수
{
	if (head == NULL) { //헤드 노드가 NULL인 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //헤드 노드의 왼쪽 포인터가 NULL인 경우
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //노드 포인터 ptr를 선언하고 헤드 노드의 왼쪽 포인터로 초기화


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //노드 포인터 parentNode를 선언하고 헤드 노드로 초기화

	while(ptr != NULL) { //ptr이 NULL이 아닌 동안

		if(ptr->key == key) { //ptr의 key 값과 입력 받은 key 값이 같은 경우
			if(ptr->left == NULL && ptr->right == NULL) { //ptr의 왼쪽 포인터와 오른쪽 포인터가 NULL인 경우

				/* root node case */
				if(parentNode == head) //parentNode가 헤드 노드인 경우
					head->left = NULL; //헤드 노드의 왼쪽 포인터에 NULL 대입

				/* left node case or right case*/
				if(parentNode->left == ptr) //parentNode의 왼쪽 포인터가 ptr인 경우
					parentNode->left = NULL; //parentNode의 왼쪽 포인터에 NULL 대입
				else
					parentNode->right = NULL; //parentNode의 오른쪽 포인터에 NULL 대입

				free(ptr); //ptr 메모리 해제
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key); //key 값에 해당 하는 노드는 리프 노드가 아님을 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr; //parentNode에 ptr 대입

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //ptr의 key 값이 입력 받은 key 값보다 작은 경우
			ptr = ptr->right; //ptr에 ptr의 오른쪽 포인터 대입
		else //ptr의 key 값이 입력 받은 key 값보다 큰 경우
			ptr = ptr->left; //ptr에 ptr의 왼쪽 포인터 대입


	}

	printf("Cannot find the node for key [%d]\n ", key); //key 값에 해당 하는 노드가 없음을 출력

	return 1;
}

Node* searchRecursive(Node* ptr, int key) //Recursive 방식으로 노드를 탐색하는 함수
{
	if(ptr == NULL) //ptr이 NULL일 경우
		return NULL; //NULL 반환

	if(ptr->key < key) //ptr의 key 값이 입력 받은 key 값보다 작을 경우
		ptr = searchRecursive(ptr->right, key); //ptr에 ptr의 오른쪽 포인터, key 값을 매개변수로 하는 함수 재호출하여 대입
	else if(ptr->key > key) //ptr의 key 값이 입력 받은 key 값보다 클 경우
		ptr = searchRecursive(ptr->left, key); //ptr에 ptr의 왼쪽 포인터, key 값을 매개변수로 하는 함수 재호출하여 대입

	/* if ptr->key == key */
	return ptr; //ptr 반환

}
Node* searchIterative(Node* head, int key) //Iterative 방식으로 노드를 탐색하는 함수
{
	/* root node */
	Node* ptr = head->left; //노드 포인터 ptr 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	while(ptr != NULL) //ptr이 NULL이 아닌 동안
	{
		if(ptr->key == key) //ptr의 key 값이 입력 받은 key 값일 경우
			return ptr; //ptr 반환

		if(ptr->key < key) ptr = ptr->right; //ptr의 key 값이 입력 받은 key 값보다 작을 경우 ptr에 ptr의 오른쪽 포인터 대입
		else//ptr의 key 값이 입력 받은 key 값보다 클 경우 ptr에 ptr의 왼쪽 포인터 대입
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr) //노드 메모리 해제하는 함수
{
	if(ptr) { //ptr이 참이면 (NULL이 아님)
		freeNode(ptr->left); //ptr의 왼쪽 포인터를 매개변수로 하는 함수 재호출
		freeNode(ptr->right); //ptr의 오른쪽 포인터를 매개변수로 하는 함수 재호출
		free(ptr); //ptr 메모리 해제
	}
}

int freeBST(Node* head) //이진 트리의 모든 노드 메모리 해제하는 함수
{

	if(head->left == head) //헤드 노드의 왼쪽 포인터가 헤드 노드인 경우
	{
		free(head); //헤드 노드 메모리 해제
		return 1;
	}

	Node* p = head->left;//노드 포인터 p 선언하고 헤드 노드의 왼쪽 포인터로 초기화

	freeNode(p); //p를 매개변수로 하는 freeNode 함수 호출

	free(head); //헤드 노드 메모리 해제
	return 1;
}