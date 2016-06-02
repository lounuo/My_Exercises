//��28��
//�ַ���������
//����һ���ַ�������ӡ�����ַ������ַ��������������
//
#include <iostream>
using namespace std;

void PrintAllArray(char* str, char *p_start)
{
    if(str != NULL)
    {   
        if(*p_start == '\0')
        {
            cout<<str<<endl;
            return;
        }

        for(char *tmp = p_start; *tmp != '\0'; ++tmp)
        {
            swap(*tmp, *p_start);
            PrintAllArray(str, p_start+1);
            swap(*tmp, *p_start);
        }
    }   
}

int main()
{
    char str[] = "abcd";
    char* p_tmp = str;
    PrintAllArray(str, p_tmp);
    return 0;
}





//��27��
//������������˫������
//����һ�ö��������������ö���������ת����һ�������˫������
//Ҫ���ܴ����κ��µĽ�㣬ֻ�ܵ������н��ָ���ָ��
//
#include <iostream>
#include <assert.h>
using namespace std;

struct BinaryTreeNode
{
  int _val;
  BinaryTreeNode *_Lnode;
  BinaryTreeNode *_Rnode;

  BinaryTreeNode(int val)
      :_val(val)
       ,_Lnode(NULL)
       ,_Rnode(NULL)
  {}
};

BinaryTreeNode* _Create(const int *arr, size_t& index, size_t size)
{
  if((index < size) && (arr[index] != '#'))
  {
      BinaryTreeNode* root = new BinaryTreeNode(arr[index]);
      root->_Lnode = _Create(arr, ++index, size);
      root->_Rnode = _Create(arr, ++index, size);
      return root;
  }
  else
      return NULL;
}

BinaryTreeNode* CreateBinaryTree(const int *arr, size_t size)
{
  assert(arr && size);

  size_t index = 0;
  return _Create(arr, index, size);
}

void DestoryBinaryTree(BinaryTreeNode* ListNode)
{
  BinaryTreeNode* tmp = ListNode;
  while(ListNode != NULL)
  {
      tmp = ListNode;
      ListNode = ListNode->_Lnode;
      delete tmp;
  }
}

void PrevOrder(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      cout<<root->_val<<" ";
      PrevOrder(root->_Lnode);
      PrevOrder(root->_Rnode);
  }
}

void BSTToList(BinaryTreeNode* root, BinaryTreeNode** lastnode)
{
  if(root != NULL)
  {
      BSTToList(root->_Lnode, lastnode);
      root->_Lnode = *lastnode;

      if(*lastnode != NULL)
          (*lastnode)->_Rnode = root;

      *lastnode = root;
      BSTToList(root->_Rnode, lastnode);
  }
}

void PrintList(BinaryTreeNode* ListNode)
{
  assert(ListNode);

  BinaryTreeNode* tmp = ListNode;
  cout<<"ListHead:"<<tmp->_val<<endl;
  cout<<"�����ӡ����";
  while(tmp->_Rnode != NULL)
  {
      cout<<tmp->_val<<"->";
      tmp = tmp->_Rnode;
  }
  cout<<tmp->_val<<"->NULL"<<endl;

  cout<<"ListTail:"<<tmp->_val<<endl;
  cout<<"�����ӡ����";
  while(tmp->_Lnode != NULL)
  {
      cout<<tmp->_val<<"->";
      tmp = tmp->_Lnode;
  }
  cout<<tmp->_val<<"->NULL"<<endl;
}

int main()
{
  int arr[] = {8,6,5,'#','#',7,'#','#',10,9,'#','#',11,'#','#'};

  BinaryTreeNode* root = CreateBinaryTree(arr, sizeof(arr)/sizeof(arr[0]));
  cout<<"PrevOrder: ";
  PrevOrder(root);
  cout<<endl;
  
  BinaryTreeNode* lastnode = NULL;
  BSTToList(root, &lastnode);
  
  BinaryTreeNode* ListNode = root;
  while(ListNode->_Lnode != NULL)
      ListNode = ListNode->_Lnode;

  PrintList(ListNode);

  DestoryBinaryTree(ListNode);
  return 0;
}








//��26��
//��������ĸ���
//ʵ�ֺ���ComplexListNode* Clone(ComplexListNode* pHead),����һ����������
//�ڸ��������У�ÿ����������һ��_next��ָ��ָ����һ�����֮�⣬����һ��_sib��ָ��ָ���������������NULL
//
#include <iostream>
#include <assert.h>
using namespace std;

int list_num = 0;

struct ComplexListNode//�������������ݽṹ
{
  int _val;
  ComplexListNode* _next;
  ComplexListNode* _sib;

  ComplexListNode(int val)//���캯��
      :_val(val)
       ,_next(NULL)
       ,_sib(NULL)
  {}
};

ComplexListNode* Buy_Node(int val)//��������������
{
  ComplexListNode* node = new ComplexListNode(val);
  return node;
}

//������
void Push_Node(ComplexListNode** phead, int val)
{
  if((*phead) == NULL)
      (*phead) = Buy_Node(val);
  else
  {
      ComplexListNode* tmp = (*phead);
      while(tmp->_next != NULL)
          tmp = tmp->_next;

      tmp->_next = Buy_Node(val);
  }

  ++list_num;
}

//�������ɽ���ָ��
void SetSibPointer(ComplexListNode* head, int* positions)
{
  assert(head && positions);

  ComplexListNode* tmp = head;
  ComplexListNode *p[list_num];
  for(size_t i = 0; i < list_num; ++i)
  {
      p[i] = tmp;
      tmp = tmp->_next;
  }

  tmp = head;
  for(size_t i = 0; i < list_num; ++i)
  {
      if(positions[i] != 0)
          tmp->_sib = p[positions[i]];

      tmp = tmp->_next;
  }
}

//��������
void DestoryList(ComplexListNode* head)
{
  if(head != NULL)
  {
      ComplexListNode* tmp = head;
      while(head != NULL)
      {
          head = head->_next;
          delete tmp;
          tmp = NULL;
          tmp = head;
      }
  }
}

//��ӡ����
void PrintList(ComplexListNode* head)
{
  if(head != NULL)
  {
      ComplexListNode *tmp = head;
      while(tmp != NULL)
      {
          cout<<tmp->_val<<"->";
          tmp = tmp->_next;
      }
      cout<<"NULL"<<endl;

      tmp = head;
      while(tmp != NULL)
      {
          cout<<tmp->_val<<" sibling is ->";
          if(tmp->_sib != NULL)
              cout<<tmp->_sib->_val<<endl;
          else
              cout<<"NULL"<<endl;

          tmp = tmp->_next;
      }
  }
}

//���Ƹ�������
ComplexListNode* Clone(ComplexListNode* head)
{
  if(head != NULL)
  {
      ComplexListNode *tmp = head;
      ComplexListNode *newnode = NULL;
      
      //����ÿ����㲢���뵱ǰ���ĺ���
      while(tmp != NULL)
      {
          newnode = Buy_Node(tmp->_val);
          newnode->_next = tmp->_next;
          tmp->_next = newnode;
          tmp = newnode->_next;
      }

      //�����´����������sibָ���ָ��
      tmp = head;
      newnode = tmp->_next;
      while(tmp != NULL)
      {
          if(tmp->_sib != NULL)
              newnode->_sib = tmp->_sib->_next;
          tmp = newnode->_next;
          if(tmp != NULL)
              newnode = tmp->_next;
      }

      //�����������
      tmp = head;
      ComplexListNode* NewHead = tmp->_next;
      newnode = tmp->_next;
      while(tmp != NULL)
      {
          tmp->_next = newnode->_next;
          tmp = tmp->_next;
          if(tmp != NULL)
          {
              newnode->_next = tmp->_next;
              newnode = newnode->_next;
          }
      }

      return NewHead;
  }
}

int main()
{
  ComplexListNode* head = NULL;
  Push_Node(&head, 7);
  Push_Node(&head, 5);
  Push_Node(&head, 8);
  Push_Node(&head, 2);
  Push_Node(&head, 6);
  Push_Node(&head, 9);
  Push_Node(&head, 3);

  int positions[7] = {2,5,0,4,0,0,4};
  SetSibPointer(head, positions);
  cout<<"Complex List: ";
  PrintList(head);

  ComplexListNode* NewComplexListHead = Clone(head);
  cout<<"New Complex List: ";
  PrintList(NewComplexListHead);
  cout<<"Complex List: ";
  PrintList(head);

  DestoryList(head);
  DestoryList(NewComplexListHead);
  return 0;
}




//��25��
//�������к�Ϊĳһֵ��·��
//����һ����������һ����������ӡ���������н��ֵ�ĺ�Ϊ��������������·��
//�����ĸ���㿪ʼ����һֱ��Ҷ����������Ľ���γ�һ��·��
//
#include <iostream>
#include <assert.h>
#include <vector>
using namespace std;

struct BinaryTreeNode
{
  int _val;
  BinaryTreeNode *_Lnode;
  BinaryTreeNode *_Rnode;

  BinaryTreeNode(int val)
      :_val(val)
       ,_Lnode(NULL)
       ,_Rnode(NULL)
  {}
};

BinaryTreeNode* _Create(int *arr, size_t& index, size_t size)
{
  if((index < size) && (arr[index] != '#'))
  {
      BinaryTreeNode *root = new BinaryTreeNode(arr[index]);
      root->_Lnode = _Create(arr, ++index, size);
      root->_Rnode = _Create(arr, ++index, size);
      return root;
  }
  else
      return NULL;
}

BinaryTreeNode* CreateBinaryTree(int *arr, size_t size)
{
  assert(arr && size);

  size_t index = 0;
  return _Create(arr, index, size);
}

void DestoryBinaryTree(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      DestoryBinaryTree(root->_Lnode);
      DestoryBinaryTree(root->_Rnode);
      delete root;
  }
}

void PrevOrder(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      cout<<root->_val<<" ";
      PrevOrder(root->_Lnode);
      PrevOrder(root->_Rnode);
  }
}

void _Count(BinaryTreeNode* root, vector<int> *pv, int& count, int num)
{
  if(root != NULL)
  {
      count += root->_val;
      (*pv).push_back(root->_val);

      _Count(root->_Lnode, pv, count, num);
      _Count(root->_Rnode, pv, count, num);

      if(count == num)
      {
          cout<<"A Path Is : ";
          for(size_t i = 0; i < (*pv).size(); ++i)
              cout<<(*pv)[i]<<"->";
          cout<<"NULL"<<endl;
      }

      count -= (*pv).back();
      (*pv).pop_back();
  }
}

void PrintPathOfNumInBT(BinaryTreeNode *root, int num)
{
  assert(root);

  vector<int> v;
  int count = 0;
  _Count(root, &v, count, num);
}

int main()
{
  int arr[] = {1,2,6,'#','#',4,5,'#','#','#',3,7,'#','#',8,'#','#'};
  int num = 12;

  BinaryTreeNode *root = CreateBinaryTree(arr, sizeof(arr)/sizeof(arr[0]));
  cout<<"PrevOrder:";
  PrevOrder(root);
  cout<<endl;
  
  PrintPathOfNumInBT(root, num);

  DestoryBinaryTree(root);
  return 0;
}







//��24��
//�����������ĺ����������
//����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�������Ľ��
//������򷵻�true�����򷵻�false��������������������������ֶ�������ͬ
//
#include <iostream>
using namespace std;

bool JudgeIsPostOrderOfBST(int *arr, size_t start, size_t end)
{
  bool ret = false;
  if((arr != NULL) && (start < end))
  {
      size_t i = 0;
      for(; i < end; ++i)
      {
          if(arr[i] > arr[end])
              break;
      }

      size_t j = i;
      for(; j < end; ++j)
      {
          if(arr[j] < arr[end])
              return ret;
      }
      if(j == end)
          ret = true;
      
      if(start < i-1)
          ret = JudgeIsPostOrderOfBST(arr, start, i-1);
      if(i < end-1)
          ret = JudgeIsPostOrderOfBST(arr, i, end-1);
  }
  return ret;
}

int main()
{
  int arr1[] = {5,7,6,9,11,10,8};
  int arr2[] = {4,5,2,6,7,3,1};

  cout<<JudgeIsPostOrderOfBST(arr1, 0, sizeof(arr1)/sizeof(arr1[0]-1))<<endl;
  cout<<JudgeIsPostOrderOfBST(arr2, 0, sizeof(arr2)/sizeof(arr2[0]-1))<<endl;
  return 0;
}






//��23��
//�������´�ӡ������
//�������´�ӡ����������ÿ����㣬ͬһ��Ľ�㰴�մ����ҵ�˳���ӡ
//
#include <iostream>
#include <assert.h>
#include <queue>
using namespace std;

struct BinaryTreeNode
{
  int _val;
  BinaryTreeNode *_Lnode;
  BinaryTreeNode *_Rnode;

  BinaryTreeNode(int val)
      :_val(val)
       ,_Lnode(NULL)
       ,_Rnode(NULL)
  {}
};

BinaryTreeNode* _Create(int *arr, size_t& index, size_t size)
{
  if((index < size) && (arr[index] != '#'))
  {
      BinaryTreeNode *root = new BinaryTreeNode(arr[index]);
      root->_Lnode = _Create(arr, ++index, size);
      root->_Rnode = _Create(arr, ++index, size);
      return root;
  }
  else
      return NULL;
}

BinaryTreeNode* CreateBinaryTree(int *arr, size_t size)
{
  assert(arr && size);

  size_t index = 0;
  return _Create(arr, index, size);
}

void DestoryBinaryTree(BinaryTreeNode* root)
{
  if(root != NULL)
  {
      DestoryBinaryTree(root->_Lnode);
      DestoryBinaryTree(root->_Rnode);
      delete root;
      root = NULL;
  }
}

void LevelOrderBinaryTree(BinaryTreeNode *root)
{
  assert(root);
  queue<BinaryTreeNode*> q;

  q.push(root);
  while(!q.empty())
  {
      if(q.front()->_Lnode != NULL)
          q.push(q.front()->_Lnode);
      if(q.front()->_Rnode != NULL)
          q.push(q.front()->_Rnode);

      cout<<q.front()->_val<<" ";
      q.pop();
  }
  cout<<endl;
}

void PrevOrder(BinaryTreeNode* root)
{
  if(root != NULL)
  {
      cout<<root->_val<<" ";
      PrevOrder(root->_Lnode);
      PrevOrder(root->_Rnode);
  }
}

int main()
{
  int arr[] = {1,2,4,'#','#',5,8,'#','#','#',3,6,'#','#',7,'#',9,'#','#'};
  BinaryTreeNode *root = CreateBinaryTree(arr, sizeof(arr)/sizeof(arr[0]));
  cout<<"PrevOrder: ";
  PrevOrder(root);
  cout<<endl;

  cout<<"LevelOrder: ";
  LevelOrderBinaryTree(root);
  DestoryBinaryTree(root);
  return 0;
}






//��22��
//ջ��ѹ�롢��������
//���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�Ϊ��ջ�ĵ���˳��
//����ѹ��ջ���������о������
//
#include <iostream>
#include <stack>
#include <assert.h>
using namespace std;

bool IsPopSeq(int *push_arr, int *pop_arr, size_t size)
{
  assert(push_arr && pop_arr && size);
  stack<int> s;

  size_t push_index = 0;
  size_t pop_index = 0;
  while(pop_index < size)
  {
      while(push_index < size)
      {
          s.push(push_arr[push_index]);
          ++push_index;
          if(s.top() == pop_arr[pop_index])
              break;
      }
      if((!s.empty()) && (s.top() != pop_arr[pop_index])) 
          return false;

      while((!s.empty()) && (pop_arr[pop_index] == s.top()))
      {
          s.pop();
          ++pop_index;
      }
  }
  if((push_index == size) && (pop_index == size) && s.empty())
      return true;
  else
      return false;
}

int main()
{
  int push_arr[] = {1, 2, 3, 4, 5};
  
  int pop_arr1[] = {4, 5, 3, 2, 1};
  int pop_arr2[] = {4, 3, 5, 1, 2};
  int pop_arr3[] = {2, 5, 3, 4, 1};

  size_t size = sizeof(push_arr)/sizeof(push_arr[0]);

  bool ret = IsPopSeq(push_arr, pop_arr1, size);
  cout<<ret<<endl;
  ret = IsPopSeq(push_arr, pop_arr2, size);
  cout<<ret<<endl;
  ret = IsPopSeq(push_arr, pop_arr3, size);
  cout<<ret<<endl;

  return 0;
}
