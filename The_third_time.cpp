//第21题
//包含min函数的栈
//定义栈的数据结构，请在该类型中实现一个能够得到栈的最小元素的min函数
//在该栈中，调用min,push及pop的时间复杂度都是O(1)
#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>
class my_stack
{
public:
  my_stack()
      :_data(NULL)
      ,_min(NULL)
      ,_size(0)
      ,_capacity(3)
  {}

  void my_push(T data)
  {
      if(_data == NULL)
      {
          _data = new T[_capacity];
          _min = new T[_capacity];
          _data[_size] = data;
          _min[_size++] = data;
          return;
      }
      
      _CheckCapacity();
      _data[_size] = data;
      if(data < _min[_size-1])
          _min[_size] = data;
      else
          _min[_size] = _min[_size-1];

      ++_size;
  }

  void my_pop()
  {
      if(_data == NULL)
          return;

      --_size;
  }

  T& min()
  {
      if(_data == NULL)
      {
          cout<<"no data..."<<endl;
          exit(0);
      }

      return _min[_size-1];
  }

  ~my_stack()
  {
      if(_data != NULL)
      {
          delete[] _data;
          delete[] _min;
          _data = NULL;
          _min = NULL;
          _size = 0;
      }
  }

  void print_stack()
  {
      if(_data != NULL)
      {
          for(int i = 0; i < _size; ++i)
          {
              cout<<_data[i]<<" ";
          }
          cout<<endl;
      }
  }


private:
  void _CheckCapacity()
  {
      if((_size+1) <= _capacity)
      {
          _capacity *= 2;
          T *tmp_data = new T[_capacity];
          T *tmp_min = new T[_capacity];
          for(int i = 0; i < _size; ++i)
          {
              tmp_data[i] = _data[i];
              tmp_min[i] = _min[i];
          }
          swap(_data, tmp_data);
          swap(_min, tmp_min);

          delete[] tmp_data;
          delete[] tmp_min;
      }
  }

private:
  T *_data;
  T *_min;
  size_t _size;
  size_t _capacity;
};

int main()
{
  my_stack<int> stack;
  stack.my_push(3);
  stack.my_push(5);
  stack.my_push(1);
  stack.my_push(2);
  stack.my_push(0);
  stack.my_push(6);
  stack.print_stack();

  cout<<"min data: "<<stack.min()<<endl;

  stack.my_pop();
  cout<<"min data: "<<stack.min()<<endl;
  stack.my_pop();
  cout<<"min data: "<<stack.min()<<endl;
  stack.my_pop();
  cout<<"min data: "<<stack.min()<<endl;
  stack.my_pop();
  cout<<"min data: "<<stack.min()<<endl;

  return 0;
}



//第20题
//顺时针打印矩阵
//输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字
//
#include <iostream>
#include <assert.h>
using namespace std;
  
void ClockwisePrintArr(int arr[][5], size_t row, size_t col)
{
  assert(arr && row && col);

  int (*tmp)[5] = arr;

  int start_row = 0;
  int start_col = 0;
  int end_row = row;
  int end_col = col;
  while((start_row < end_row) && (start_col < end_col))
  {
      for(int i = start_col; i < end_col; ++i)
      {
          cout<<tmp[start_row][i]<<" ";
      }
      
      for(int i = start_row+1; i < end_row; ++i)
      {
          cout<<tmp[i][end_col-1]<<" ";
      }

      for(int i = end_col-2; i >= start_col; --i)
      {
          cout<<tmp[end_row-1][i]<<" ";
      }

      for(int i = end_row-2; i > start_row; --i)
      {
          cout<<tmp[i][start_col]<<" ";
      }

      ++start_row;
      ++start_col;
      --end_row;
      --end_col;
  }
  cout<<endl;
}

int main()
{
  int arr[5][5] = {{ 0,  1,  2,  3,  4},
                   { 5,  6,  7,  8,  9},
                   {10, 11, 12, 13, 14},
                   {15, 16, 17, 18, 19},
                   {20, 21, 22, 23, 24}};

  ClockwisePrintArr(arr, sizeof(arr)/sizeof(arr[0]), sizeof(arr[0])/sizeof(arr[0][0]));

  return 0;
}



//第19题
//二叉数的镜像
//完成一个函数，输入一个二叉数，该函数输出它的镜像
//
#include <iostream>
#include <assert.h>
using namespace std;

struct BinaryTreeNode
{
  int _val;
  BinaryTreeNode* _Lchild;
  BinaryTreeNode* _Rchild;

  BinaryTreeNode(int val)
      :_val(val)
      ,_Lchild(NULL)
      ,_Rchild(NULL)
  {}
};

BinaryTreeNode* _CreatTree(const int *arr, size_t& index, size_t size)
{
  if((arr[index] != '#') && (index < size))
  {
      BinaryTreeNode *root = new BinaryTreeNode(arr[index]);
      root->_Lchild = _CreatTree(arr, ++index, size);
      root->_Rchild = _CreatTree(arr, ++index, size);
      return root;
  }
  else
      return NULL;
};

BinaryTreeNode* CreatTree(const int *arr, size_t size)
{
  assert(arr && size);

  size_t index = 0;
  return _CreatTree(arr, index, size);
}

void PrevOrder(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      cout<<root->_val<<"->";
      PrevOrder(root->_Lchild);
      PrevOrder(root->_Rchild);
  }
}

void DestoryTree(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      delete root;
      DestoryTree(root->_Lchild);
      DestoryTree(root->_Rchild);
  }
}

//方法一：
//void ImageTree(BinaryTreeNode *root)
//{
//    if(root == NULL)
//        return;
//    BinaryTreeNode* tmp = root->_Lchild;
//    root->_Lchild = root->_Rchild;
//    root->_Rchild = tmp;
//
//    ImageTree(root->_Lchild);
//    ImageTree(root->_Rchild);
//}

//方法二：
void ImageTree(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      cout<<root->_val<<"->";
      ImageTree(root->_Rchild);
      ImageTree(root->_Lchild);
  }
}


int main()
{
  int arr[] = {1,2,4,'#','#',5,'#','#',3,6,'#','#',7,'#','#'};

  BinaryTreeNode *root = CreatTree(arr, sizeof(arr)/sizeof(arr[0]));

  cout<<"BinaryTree: ";
  PrevOrder(root);
  cout<<"NULL"<<endl;
  
  cout<<"ImageBinaryTree: ";
  ImageTree(root);

  //PrevOrder(root);
  cout<<"NULL"<<endl;

  DestoryTree(root);

  return 0;
}



//第18题
//树的子结构
//输入两棵二叉数A和B，判断B是不是A的子结构
//
#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

struct BinaryTreeNode
{
  int _val;
  BinaryTreeNode* _Lchild;
  BinaryTreeNode* _Rchild;

  BinaryTreeNode(int val)
      :_val(val)
      ,_Lchild(NULL)
      ,_Rchild(NULL)
  {}
};

BinaryTreeNode* _CreatTree(const int *arr, size_t& index, size_t size)
{
  if((arr[index] != '#') && (index < size))
  {
      BinaryTreeNode *root = new BinaryTreeNode(arr[index]);
      root->_Lchild = _CreatTree(arr, ++index, size);
      root->_Rchild = _CreatTree(arr, ++index, size);
      return root;
  }
  else
      return NULL;
};

BinaryTreeNode* CreatTree(const int *arr, size_t size)
{
  assert(arr && size);

  size_t index = 0;
  return _CreatTree(arr, index, size);
}

bool Judge(BinaryTreeNode* father, BinaryTreeNode* child)
{
  if((father == NULL) && (child == NULL))
      return true;
  else if((father != NULL) && (child != NULL))
  {
      if(father->_val != child->_val)
          return false;
  }
  else
      return false;

  bool ret = Judge(father->_Lchild, child->_Lchild) && Judge(father->_Rchild, child->_Rchild);

  return ret;
}

bool JudgeChildTree(BinaryTreeNode* father, BinaryTreeNode* child)
{
  bool ret = false;
  if((father == NULL) || (child == NULL))
      return ret;
  if(father->_val == child->_val)
      ret = Judge(father, child);

  if(!ret)
      ret = JudgeChildTree(father->_Lchild, child);
  if(!ret)
      ret = JudgeChildTree(father->_Rchild, child);

  return ret;
}

void PrevOrder(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      cout<<root->_val<<"->";
      PrevOrder(root->_Lchild);
      PrevOrder(root->_Rchild);
  }
}

void DestoryTree(BinaryTreeNode *root)
{
  if(root != NULL)
  {
      delete root;
      DestoryTree(root->_Lchild);
      DestoryTree(root->_Rchild);
  }
}

int main()
{
  int arr1[] = {1,2,4,'#','#',5,8,'#','#','#',3,6,'#','#',7,'#',9,'#','#'};
  int arr2[] = {3,6,'#','#',7,'#',9,'#','#'};
  int arr3[] = {2,4,'#','#',5,'#','#'};

  BinaryTreeNode *father = CreatTree(arr1, sizeof(arr1)/sizeof(arr1[0]));
  BinaryTreeNode *child1 = CreatTree(arr2, sizeof(arr2)/sizeof(arr2[0]));
  BinaryTreeNode *child2 = CreatTree(arr3, sizeof(arr3)/sizeof(arr3[0]));
  
  PrevOrder(father);
  cout<<"NULL"<<endl;
  PrevOrder(child1);
  cout<<"NULL"<<endl;
  PrevOrder(child2);
  cout<<"NULL"<<endl;

  bool ret = JudgeChildTree(father, child1);
  cout<<ret<<endl;
  ret = JudgeChildTree(father, child2);
  cout<<ret<<endl;
  
  DestoryTree(father);
  DestoryTree(child1);
  DestoryTree(child2);

  return 0;
}






#include <iostream>
#include <assert.h>
using namespace std;

template <class T>
struct ListNode
{
  T _data;
  ListNode<T>* _next;
};

template <class T>
ListNode<T>* buy_node(T data)
{
  ListNode<T>* tmp = new ListNode<T>;
  tmp->_data = data;
  tmp->_next = NULL;
  return tmp;
}

template <class T>
void init_list(ListNode<T>** node, T data)
{
  *node = buy_node(data);
}

template <class T>
void push_node(ListNode<T>*& head, T data)
{
  if(head == NULL)
  {
      init_list(&head, data);
      return;
  }
  ListNode<T>* tmp = head;
  while(tmp->_next != NULL)
  {
      tmp = tmp->_next;
  }
  tmp->_next = buy_node(data);
}

template <class T>
void print_list(ListNode<T>* head)
{
  while(head != NULL)
  {
      cout<<head->_data<<"->";
      head = head->_next;
  }
  cout<<"NULL"<<endl;
}

template <class T>
void destroy_list(ListNode<T>*& head)
{
  if(head != NULL)
  {
      ListNode<T>* cur = head;
      ListNode<T>* tmp = head;
      while(cur != NULL)
      {
          tmp = cur;
          cur = cur->_next;
          delete tmp;
      }
      head = NULL;
  }
}
//
//第15题
//链表中倒数第k个结点
//输入一个链表，输出该链表中倒数第k个几点
//为了符合大多数人的习惯，从1开始计数，即链表的尾结点时倒数第1个结点
//
//
//template<class T>
//ListNode<T>* Reciprocal_k_Node(ListNode<T>* head, size_t k)
//{
//    assert(head && k);
//
//    ListNode<T>* first = head;
//    ListNode<T>* second = head;
//
//    while(--k)
//    {
//        if(first->_next != NULL)
//            first = first->_next;
//        else
//            return NULL;
//    }
//
//    while(first->_next != NULL)
//    {
//        first = first->_next;
//        second = second->_next;
//    }
//
//    return second;
//}
//
//
//
//
//
//第16题
//反转单链表
//定义一个函数，输入一个链表的头结点，反转该链表并输出反转后链表的头结点
//
//template <class T>
//ListNode<T>* ReverseList(ListNode<T>* head)
//{
//    if(head == NULL)
//        return head;
//
//    ListNode<T>* newHead = NULL;
//    ListNode<T>* cur = head;
//    ListNode<T>* tmp = head;
//
//    while(cur != NULL)
//    {
//        tmp = cur;
//        cur = cur->_next;
//        tmp->_next = newHead;
//        newHead = tmp;
//    }
//
//    return newHead;
//}





//第17题
//合并两个排序的链表
//输入两个递增排序的链表，合并这两个链表并使新链表中的结点仍然是按照递增排序的

//实现1：循环
template <class T>
ListNode<T>* MergeList(ListNode<T>* list1, ListNode<T>* list2)
{
  if(list1 == NULL)
      return list2;
  else if(list2 == NULL)
      return list1;

  ListNode<T>* newHead = NULL;

  ListNode<T>* tmp1 = NULL;
  ListNode<T>* tmp2 = NULL;

  if(list1->_data <= list2->_data)
  {
      newHead = list1;
      tmp1 = list1->_next;
      tmp2 = list2;
  }
  else
  {
      newHead = list2;
      tmp1 = list1;
      tmp2 = list2->_next;
  }

  ListNode<T>* cur = newHead;

  while((tmp1 != NULL) && (tmp2 != NULL))
  {
      if(tmp1->_data <= tmp2->_data)
      {
          cur->_next = tmp1;
          cur = cur->_next;
          tmp1 = tmp1->_next;
      }
      else
      {
          cur->_next = tmp2;
          cur = cur->_next;
          tmp2 = tmp2->_next;
      }
  }

  if(tmp1 == NULL)
      cur->_next = tmp2;
  else
      cur->_next = tmp1;

  return newHead;
}

//实现2：递归
template <class T>
ListNode<T>* MergeList(ListNode<T>* list1, ListNode<T>* list2)
{
  if(list1 == NULL)
      return list2;
  else if(list2 == NULL)
      return list1;

  ListNode<T>* newHead = NULL;

  if(list1->_data <= list2->_data)
  {
      newHead = list1;
      newHead->_next = MergeList(list1->_next, list2);
  }
  else
  {
      newHead = list2;
      newHead->_next = MergeList(list1, list2->_next);
  }

  return newHead;
}

int main()
{
  ListNode<int>* list1 = NULL;
  push_node(list1, 1);
  push_node(list1, 2);
  push_node(list1, 3);
  push_node(list1, 8);
  push_node(list1, 11);
  push_node(list1, 14);
  
  ListNode<int>* list2 = NULL;
  push_node(list2, 5);
  push_node(list2, 6);
  push_node(list2, 7);
  push_node(list2, 8);
  push_node(list2, 9);

  cout<<"list1: ";
  print_list(list1);
  cout<<"list2: ";
  print_list(list2);
  
  //第15题
  //size_t k = 9;
  //ListNode<int>* ret = Reciprocal_k_Node(list, k);
  //if(ret != NULL)
  //  cout<<"the reciprocal "<<k<<" Node: "<<ret->_data<<endl;
  //else
  //  cout<<"the number "<<k<<" is wrong..."<<endl;
  
  //第16题
  //ListNode<int>* newhead = ReverseList(list);
  //cout<<"reverse list:";
  //print_list(newhead);
  
  //第17题
  ListNode<int>* newhead = MergeList(list1, list2);
  cout<<"merge list:";
  print_list(newhead);

  destroy_list(list1);
  destroy_list(list2);

  return 0;
}


