//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树
//假设输入的前序遍历和和中序遍历的结果中都不含重复的数字

#include <iostream>
#include <assert.h>
#include <stdlib.h>
using namespace std;

typedef int data_type;

struct BinaryTreeNode
{
    data_type _data;
    BinaryTreeNode* _Lnode;
    BinaryTreeNode* _Rnode;

    BinaryTreeNode(data_type data)
        :_data(data)
        ,_Lnode(NULL)
        ,_Rnode(NULL)
    {}  
};

BinaryTreeNode* RebuildBinaryTree(const data_type* prevlist, const data_type *inlist, const size_t num, size_t head, size_t tail)
{
    assert(prevlist && inlist && num);

    BinaryTreeNode *root = new BinaryTreeNode(*prevlist);

    size_t root_index;
    for(root_index = 0; root_index < num; ++root_index)
    {   
        if(inlist[root_index] == *prevlist)
            break;
    }   
    if(inlist[root_index] != *prevlist)
    {   
        cout<<"Invalid parameter..."<<endl;
		exit(0);
    }

    size_t left_node_num = root_index - head;
    if(left_node_num > 0)
        root->_Lnode = RebuildBinaryTree(prevlist+1, inlist, num, head, root_index-1);

    size_t right_node_num = tail - root_index;
    if(right_node_num > 0)
        root->_Rnode = RebuildBinaryTree(prevlist+left_node_num+1, inlist, num, root_index+1, tail);

    return root;
}

void PreOrder(BinaryTreeNode *root)
{
    if(root != NULL)
    {
        cout<<root->_data<<"->";
        PreOrder(root->_Lnode);
        PreOrder(root->_Rnode);
    }
}

int main()
{
    data_type PrevOrderList[] = {1, 2, 4, 7, 3, 5, 6, 8};
    data_type InOrderList[] = {4, 7, 2, 1, 5, 3, 8, 6};

    size_t node_num = sizeof(PrevOrderList)/sizeof(PrevOrderList[0]);
    size_t head = 0;
    size_t tail = node_num-1;
    BinaryTreeNode* root = RebuildBinaryTree(PrevOrderList, InOrderList, node_num, head, tail);

    cout<<"the root data: "<<root->_data<<endl;
    PreOrder(root);
	cout<<"NULL"<<endl;
    return 0;
}




//用两个栈实现一个队列
//实现它的两个函数appendTail和deleteHead,分别完成在队列尾部插入结点和在队列头部删除结点的功能

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class Queue
{
public:
  Queue()
  {}

  void appendTail(T data)
  {
      _stack1.push_back(data);
  }

  void deleteHead()
  {
      if(!_stack2.empty())
      {
          _stack2.pop_back();
      }
      else
      {
          while(!_stack1.empty())
          {
              _stack2.push_back(_stack1.back());
              _stack1.pop_back();
          }
          if(!_stack2.empty())
              _stack2.pop_back();
          else
          {
              cout<<"the queue is empty..."<<endl;
              return;
          }
      }
      cout<<"the new head is "<<_stack2.back()<<endl;
  }

  void print_queue()
  {
      vector<T> tmp1(_stack1);
      vector<T> tmp2(_stack2);

      cout<<"head ";
      if(tmp2.empty())
      {
          while(!tmp1.empty())
          {
              tmp2.push_back(tmp1.back());
              tmp1.pop_back();
          }
          while(!tmp2.empty())
          {
              cout<<tmp2.back()<<" ";
              tmp2.pop_back();
          }
      }
      else
      {
          while(!tmp2.empty())
          {
              cout<<tmp2.back()<<" ";
              tmp2.pop_back();
              if(tmp2.empty())
              {
                  while(!tmp1.empty())
                  {
                      tmp2.push_back(tmp1.back());
                      tmp1.pop_back();
                  }
              }
          }
      }
      cout<<"tail"<<endl;
  }
  

private:
  vector<T> _stack1;
  vector<T> _stack2;
};

int main()
{
  Queue<char> queue;
  queue.appendTail('a');
  queue.appendTail('b');
  queue.appendTail('c');
  queue.appendTail('d');
  queue.appendTail('e');
  queue.print_queue();

  queue.deleteHead();
  queue.deleteHead();
  queue.print_queue();

  queue.appendTail('f');
  queue.appendTail('g');
  queue.appendTail('h');
  queue.print_queue();

  return 0;
}




//输入一个链表的头结点，从尾到头反过来打印出每个结点的值

#include <iostream>
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
void ReversePrintList(ListNode<T>* head)
{
  if(head != NULL)
  {
      ReversePrintList(head->_next);
      cout<<head->_data<<"->";
  }
  else
      cout<<"NULL->";
}

int main()
{
  ListNode<int>* list = NULL;
  push_node(list, 1);
  push_node(list, 2);
  push_node(list, 3);
  push_node(list, 4);
  push_node(list, 5);
  push_node(list, 6);
  push_node(list, 7);
  push_node(list, 8);
  push_node(list, 9);

  cout<<"print list: ";
  print_list(list);
  cout<<"reverse print list: ";
  ReversePrintList(list);
  cout<<endl;

  destroy_list(list);
  return 0;
}




#include <iostream>
#include <vector>
using namespace std;

template <class T>
struct ListNode
{
  T _data;
  ListNode<T>* _next;

  ListNode(T data)
      :_data(data)
      ,_next(NULL)
  {}
};
template <class T>
class List
{
public:
  List()
      :_head(NULL)
  {}

  List(T data)
      :_head(new ListNode<T>(data))
  {}

  ~List()
  {
      if(_head != NULL)
      {
          ListNode<T>* tmp = _head;
          ListNode<T>* cur = _head;
          while(cur != NULL)
          {
              tmp = cur;
              cur = cur->_next;
              delete tmp;
          }
          _head = NULL;
      }
  }

  void _push(T data)
  {
      if(_head == NULL)
      {
          _head = new ListNode<T>(data);
          return;
      }
      ListNode<T>* tmp = _head;
      while(tmp->_next != NULL)
          tmp = tmp->_next;

      tmp->_next = new ListNode<T>(data);
  }

  void print_list()
  {
      cout<<"print list: ";
      ListNode<T>* tmp = _head;
      while(tmp != NULL)
      {
          cout<<tmp->_data<<"->";
          tmp = tmp->_next;
      }
      cout<<"NULL"<<endl;
  }

  void ReversePrintList()
  {
      vector<T> list;
      ListNode<T>* tmp = _head;
      while(tmp != NULL)
      {
          list.push_back(tmp->_data);
          tmp = tmp->_next;
      }
      cout<<"reverse print list:"<<endl;
      while(!list.empty())
      {
          cout<<list.back()<<"->";
          list.pop_back();
      }
      cout<<"NULL"<<endl;
  }

private:
  ListNode<T>* _head;
};

int main()
{
  List<int> list(1);
  list._push(2);
  list._push(3);
  list._push(4);
  list._push(5);
  list._push(6);
  list._push(7);
  list._push(8);
  list._push(9);

  list.print_list();
  list.ReversePrintList();

  return 0;
}


//实现一个函数，把字符串中的每个空格都替换成““%20”

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <assert.h>
using namespace std;

void ReplaceSpace(char*& dst, const char* src)
{
  assert(dst && src);
  char* tmp = dst;
  size_t s_count = 0;
  while(*tmp != '\0')
  {
      if(*(tmp++) == ' ')
          ++s_count;
  }

  size_t dst_len = strlen(dst);
  size_t src_len = strlen(src);

  char *tail = dst+dst_len;
  char *right_place = tail+s_count*(src_len-1);

  while(tail >= dst)
  {
      if(*tail != ' ')
      {
          *right_place = *tail;
      }
      else
      {
          right_place -= (src_len-1);
          strncpy(right_place, src, src_len);
      }
      --tail;
      --right_place;
  }
}

int main()
{
  char *str = new char[200];
  cout<<"please input string:";
  gets(str);
  ReplaceSpace(str, "20%");
  cout<<"The string after replace: "<<str<<endl;
  delete[] str;
  return 0;
}



//在一个二维数组中，每一行都按照从左到右递增的顺序排列，每一列都按照从上到下递增的顺序排列
//完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数

#include <iostream>
#include <assert.h>
using namespace std;

bool SearchNum(int (*parr)[5], size_t row, size_t col, int num)
{
  assert(parr);
  size_t tmp_row = 0;
  size_t tmp_col = col-1;

  while((tmp_row < row) && (tmp_col >= 0))
  {
      if(parr[tmp_row][tmp_col] == num)
          return true;
      else if(parr[tmp_row][tmp_col] > num)
          --tmp_col;
      else
          ++tmp_row;
  }
  return false;
}

int main()
{
  int arr[5][5] = {{0,  1,  2,  3,  4},

                   {5,  9, 10, 11, 12},

                   {6, 13, 16, 17, 18},

                   {7, 14, 19, 21, 24},

                   {8, 15, 22, 23, 25}};

  bool ret = SearchNum(arr, 5, 5, 17);  //success return true, failed return false
  if(ret)
      cout<<"the num is exist..."<<endl;
  else
      cout<<"the num is not exist..."<<endl;
  return 0;
}





//设计一个类，我们只能生成该类的一个实例

#include <iostream>
using namespace std;

class Singleton
{
private:
  Singleton()
  {}
  Singleton(Singleton& s);
  Singleton& operator=(Singleton& s);

public:
  static Singleton*& GetInstance()
  {
      //if(_instance == NULL)
      //{
      //  _instance = new Singleton();
      //}
      return _instance;
  }

private:
  static Singleton *_instance;
};
//Singleton* Singleton::_instance = NULL;
Singleton* Singleton::_instance = new Singleton();

int main()
{
  Singleton *s1 = Singleton::GetInstance();
  Singleton *s2 = Singleton::GetInstance();
  if(s1 == s2)
      cout<<"s1 == s2"<<endl;
  else
      cout<<"Singleton instance error..."<<endl;

  return 0;
}




//自我实现一个字符串类

#include <iostream>
#include <string.h>
using namespace std;

class CMyString
{
public:
    CMyString(const char* str);
    CMyString(const CMyString& s);
    //CMyString& operator=(CMyString s);
    CMyString& operator=(const CMyString& s);
    ~CMyString();

    void print_string();

private:
    char* _str;
};

CMyString::CMyString(const char* str)
    :_str(NULL)
{
    _str = new char[strlen(str)+1];
    strcpy(_str, str);
}

CMyString::CMyString(const CMyString& s)
    :_str(NULL)
{
    CMyString tmp(s._str);
    swap(_str, tmp._str);
}

//CMyString& CMyString::operator=(CMyString s)
//{
//  if(strcmp(s._str, _str) != 0)
//      swap(_str, s._str);
//  return *this;
//}

CMyString& CMyString::operator=(const CMyString& s)
{
  if(this != &s)
  {
      char* tmp = new char[strlen(s._str)+1];
      if(tmp != NULL)
      {
          delete[] _str;
          _str = tmp;
          strcpy(_str, s._str);
      }
  }
  return *this;
}

CMyString::~CMyString()
{
  if(_str != NULL)
  {
      delete[] _str;
      _str = NULL;
  }
}

void CMyString::print_string()
{
  cout<<_str<<endl;
}

int main()
{
  CMyString s1("this is my string...");
  s1.print_string();
  CMyString s2("hello world...");
  s2.print_string();
  CMyString s3(s2);
  s3.print_string();
  s3 = s1;
  s3.print_string();

  return 0;
}
