#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
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
	printf("----- [민선홍] [2018038028] -----");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

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
		fflush(stdout);
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			fflush(stdout);
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) // 재귀함수를 이용하여, 중위 순회 출력
{
	if(ptr == NULL) // 가리키는게 NULL 이라면 반환
	{
		return ;
	}

	if(ptr -> key == -9999) // ptr -> key의 값이 -9999 라면, ptr -> left의 값을 넣어 이동하여 재귀함수 호출
	{
		inorderTraversal(ptr -> left);
	}
	else // 다른 경우에는
	{
		inorderTraversal(ptr -> left); // 중위 순회 함수에 ptr -> left의 값을 넣어 이동하여 함수 호출
		printf("[%d]", ptr -> key); // ptr -> key의 값 출력
		inorderTraversal(ptr -> right); // 중위 순회 함수에 ptr -> right의 값을 넣어 이동하여 함수 호출
	}
}

void preorderTraversal(Node* ptr) // 재귀함수를 이용하여, 전위 순회 출력
{
	if(ptr == NULL) // 가리키는게 NULL 이라면 반환
	{
		return ;
	}

	if(ptr -> key == -9999) // ptr -> key의 값이 -9999 라면, ptr -> left의 값을 넣어 이동하여 재귀함수 호출
	{
		preorderTraversal(ptr -> left);
	}
	else // 다른 경우에는
	{
		printf("[%d]", ptr -> key); // ptr -> key의 값 출력
		preorderTraversal(ptr -> left); // 전위 순회 함수에 ptr -> left의 값을 넣어 이동하여 함수 호출
		preorderTraversal(ptr -> right); // 전위 순회 함수에 ptr -> right의 값을 넣어 이동하여 함수 호출
	}
}

void postorderTraversal(Node* ptr) // 재귀함수를 이용하여, 후위 순회 출력
{
	if(ptr == NULL) // 가리키는게 NULL 이라면 반환
		{
			return ;
		}

		if(ptr -> key == -9999) // ptr -> key의 값이 -9999 라면, ptr -> left의 값을 넣어 이동하여 재귀함수 호출
		{
			postorderTraversal(ptr -> left);
		}
		else
		{
			postorderTraversal(ptr -> left); // 후위 순회 함수에 ptr -> left의 값을 넣어 이동하여 함수 호출
			postorderTraversal(ptr -> right); // 후위 순회 함수에 ptr -> right의 값을 넣어 이동하여 함수 호출
			printf("[%d]", ptr -> key); // ptr -> key의 값 출력
		}
}


int insert(Node* head, int key) // 노드에 key의 값을 삽입하는 함수
{
	 Node* parent; // Node의 포인터 변수 parent 생성
	   Node* node = (Node*)malloc(sizeof(Node)); // Node의 포인터 변수 node를 생성하여 메모리 할당
	   Node* temp = head -> left; // Node의 포인터 변수 temp 생성한 뒤, 헤더포인터가 가리키는 left 값 대입
	   node -> key = key; // node -> key에 key의 값 대입
	   node -> left = NULL; // node -> left 값은 NULL
	   node -> right = NULL; // node -> right 값은 NULL


	   if(head->left == NULL) // head -> left의 값이 NULL이면
	   {
	      head -> left = node; // head -> left 값에 node의 값 대입
	      return 0;
	   }

	   while(temp != NULL) // temp의 값이 NULL이 될 때 까지
	   {
	      parent = temp; // parent 값에 head -> left의 값이 들어가있는 temp 대입
	      if (key == parent -> key) // 만약 key의 값이 parent -> key의 값과 같다면, 프린트문 출력
	      {
	         printf("키의값이 이미 존재합니다.\n");
	         return 1;
	      }
	      if(key < parent -> key) // key의 값이 parent -> key의 값보다 작다면,
	      {
	         temp = parent -> left; // temp 에 parent -> left의 값 대입 하여 왼쪽 노드로 이동
	      }
	      else // 그게 아니라면,
	      {
	         temp = parent -> right; // temp 에 parent -> right 값 대입 하여 오른쪽 노드로 이동
	      }
	   }
	      if(key < parent -> key) // key의 값이 parent -> key의 값보다 작다면,
	      {
	         parent -> left = node; // parent -> left에 node의 값 대입 하여 새로운 노드 생성
	      }
	      else // 그게 아니라면
	      {
	         parent -> right = node; // parent -> right에 node의 값 대입 하여 새로운 노드 생성
	      }
	   return 0;

}

int deleteLeafNode(Node* head, int key) // leaf Node만 지우는 함수
{
   Node* parent = NULL; // Node의 포인터 변수형 parent를 생성하고 NULL로 초기화
   Node* del = head->left; // Node의 포인터 변수형 del를 생성하고 헤더포인터가 가리키는 left의 값 대입

   if (del == NULL) // 만약 헤더포인터가 가리키는 left의 값이 들어가있는 del이 NULL이면, 프린트문 출력
   {
      printf("삭제할 key의 노드가 없습니다.\n");
      return 0;
   }
   while (del != NULL) // del 값이 NULL이 될 때까지 반복문 실행
   {
      if (key < del -> key) // key의 값이 del -> key의 값보다 작다면
      {
         parent = del; // parent에 del의 값을 대입
         del = del->left; // del에 del -> left의 값을 대입 후 왼쪽으로 이동
      }
      else if (key > del -> key) // key의 값이 del -> key의 값보다 크면
      {
         parent = del; //  parent에 del의 값 대입
         del = del->right; // del에 del -> right의 값을 대입 후 오른쪽으로 이동
      }
      else // 그 외에
      {
         if (del->right == NULL && del->left == NULL) // del이 가리키는 right 값과 del이 가리키는 left 값이 둘다 NULL이라면
         {
            if (del == head->left) // 이중 if문을 이용하여, del의 값과 헤더포인터가 가리키는 left의 값이 같다면
            {
               free(del); // del 메모리 해제
               break;
            }
            else if (del == parent -> left) // del의 값과
                       {
                          parent->left = NULL;
                          free(del);
                          break;
                       }
            else if(del == parent -> right) // del의 값과 parent -> right의 값이 같다면
            {
               parent->right = NULL; // parent가 가리키는 right의 값을 NULL로 초기화
               free(del); // del 메모리 해제
               break;
            }
            break;
         }
         break;
      }
   }
   return 0;
}


Node* searchRecursive(Node* ptr, int key) // 재귀함수를 이용하여, 검색하는 함수
{
	if (ptr == NULL) // 노드가 존재하지 않을경우 프린트문 출력
	{
		printf("key값이 들어간 노드가 없습니다.\n");
		return 0;
	}
	if (ptr -> key == -9999) // ptr -> key 값이 -9999와 같을 경우, 재귀함수(searchRecursive) 호출
	{
		searchRecursive(ptr -> left, key);
	}
	else if (key == ptr -> key) // key의 값이 ptr -> key의 값과 같을 경우, ptr 반환
	{
		return ptr;
	}
	else if (key < ptr -> key) // key의 값이 ptr -> key의 값보다 작을경우, ptr -> left, key의 값을 넣어 이동하여 재귀함수 실행
	{
		searchRecursive(ptr -> left, key);
	}
	else
	{
		searchRecursive(ptr -> right, key); // 그게 아닐경우, ptr -> right 값과 key의 값을 넣어 이동하여 재귀함수 실행
	}
}

Node* searchIterative(Node* head, int key) // 재귀함수를 이용하지않고 검색하는 함수
{
	Node* root = head -> left; // Node의 포인터 변수 root 를 생성하고 head -> left의 값 대입 이동

	if(root == NULL) // head -> left의 값이 들어가있는 root가 NULL이라면, 프린트문 출력
	{
		printf("key값이 들어간 노드가 없습니다\n");
		return 0;
	}
	while(root != NULL) // root가 NULL이 될 때 까지 반복문 실행
	{
		if (key == root -> key) // key의 값과 root -> key의 값이 같을경우
		{
			return root; // root를 반환
		}
		else if (key < root -> key) // key의 값이 root -> key 값보다 작으면,
		{
			root = root -> left; // root에 root -> left 값 대입하여 이동
		}
		else // 다른 경우엔
			root = root -> right; // root에 root -> right 값 대입하여 이동
	}
	printf("key값이 들어간 노드가 없습니다\n");
	return 0;
}


int freeBST(Node* head) // 노드의 메모리들을 해제하는 함수
{
	if (head == NULL) // 헤드포인터의 값이 NULL이면, 1반환하고 종료
	{
		return 1;
	}

	if (head -> key == -9999) // head -> key의 값이  -9999라면,
	{
		freeBST(head -> left); // 재귀함수를 이용하여, head -> left값을 넣어 이동하여 메모리 해제
	}

	else if (head != NULL) // 헤드포인터의 값이 NULL이 아니라면,
	{
		freeBST(head -> left); // 재귀함수를 이용하여 head -> left 값을 넣어 이동하여 메모리 해제
		freeBST(head -> right); // 재귀함수를 이용하여 head -> right의 값을 넣어 이동하여 메모리 해제
		free(head); // 헤드포인터의 메모리 해제
		head = NULL; // 헤드포인터에 NULL 값 대입
	}
	return 1;
}





