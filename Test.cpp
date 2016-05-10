//调整数组顺序使奇数位于偶数前面
//输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有奇数位于数组的前半部分，
//所有的偶数位于数组的后半部分

#include <iostream>
#include <assert.h>
using namespace std;

void AdjustArr(int *parr, size_t size)
{
  assert(parr && size);

  int *start = parr;
  int *end = parr+size-1;

  while(start < end)
  {
      while((*start % 2) != 0)
          ++start;
      while((*end % 2) == 0)
          --end;
      if(start < end)
      {   swap(*start, *end);
          ++start;
          --end;
      }
      else
          return;
  }
}

void PrintArr(int *parr, size_t size)
{
  assert(parr && size);

  for(size_t i = 0; i < size; ++i)
  {
      cout<<parr[i]<<" ";
  }
  cout<<endl;
}

int main()
{
  int arr[] = {1,5,2,4,6,11,3,8,0,7};
  size_t size = sizeof(arr)/sizeof(arr[0]);

  PrintArr(arr, size);
  AdjustArr(arr, size);
  PrintArr(arr, size);

  return 0;
}







//在O(1)时间删除链表结点
//给定单向链表的头指针和一个结点指针，定义一个函数在O(1)时间删除该结点。
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

template <class T>
ListNode<T>* GetNode(ListNode<T>* pHead, size_t n)
{
  assert(pHead);
  ListNode<T>* tmp = pHead;
  while(((--n) != 0) && (tmp != NULL))
  {
      tmp = tmp->_next;
  }
  if(tmp == NULL)
      return NULL;
  else
      return tmp;
}

template <class T>
void DeleteNode(ListNode<T>* pHead, ListNode<T>* dNode)
{
  assert(pHead && dNode);

  if(dNode->_next == NULL)
  {
      delete dNode;
      dNode = NULL;
      return;
  }

  ListNode<T>* tmp = dNode->_next;
  swap(dNode->_data, tmp->_data);
  dNode->_next = tmp->_next;
  delete tmp;
  tmp = NULL;
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
  cout<<"delete Node later: ";
  ListNode<int>* dNode = GetNode(list, 4);
  DeleteNode(list, dNode);
  print_list(list);

  destroy_list(list);
  return 0;
}





//打印1到最大的n位数
//输入数字n，按顺序打印出从1到最大的n位十进制数
//
#include <iostream>
#include <string.h>
using namespace std;

void PrintMaxNNum(size_t n)
{
    char *num = new char[n+1];

    char* tmp = num;
    while(tmp < num+n)
    {
        *tmp = '0';
        ++tmp;
    }

    *(tmp--) = '\0';

    char *cur = tmp;

    while(cur >= num)
    {
        while(*tmp < '9')
        {
            ++(*tmp);
            cout<<cur<<" ";
        }
        *tmp = '0';

        for(int i = 1; cur >= num; ++i)
        {
            if((tmp-i) < cur)
                --cur;
            if(cur >= num)
            {
                ++(*(tmp-i));
                if(*(tmp-i) <= '9')
                {
                    cout<<cur<<" ";
                    break;
                }
                else
                {
                    *(tmp-i) = '0';
                    continue;
                }
            }
        }
    }
    cout<<endl;
    delete[] num;
}


int main()
{
    size_t n = 3;
    PrintMaxNNum(n);
    return 0;
}






//数值的整数次方
//实现函数double Power(double base, int exponent),求base的exponent次方，不得使用
//库函数，同时不需要考虑大数问题

#include <iostream>
#include <math.h>
using namespace std;

//实现方法2：递归获取pow值
double GetPow(double base, int exp)
{
  double ret = 1;
  if(exp != 0)
  {
      ret = GetPow(base, exp>>1);
      if((exp & 0x1) == 0)
      {
          ret *= ret;
      }
      else
      {
          ret *= (ret * base);
      }
  }
  return ret;
}

double my_pow(double base, int exp)
{ 
  if(exp == 0)
      return 1;
  if((base == 0) || (base == 1))
      return base;

  int flag = 1;
  if(exp < 0)
  {
      flag = 0;
      exp *= (-1);
  }

  double ret = GetPow(base, exp);

  if(flag == 0)
      ret = 1/ret;
  return ret;
}

//实现方法1：循环相乘获取pow值
double my_pow(double base, int exp)
{
  if(exp == 0)
      return 1;
  if((base == 0) || (base == 1))
      return base;

  double ret = 1.0;
  int flag = 1;
  if(exp < 0)
  {   
      flag = 0;
      exp *= (-1);
  }
  while(exp--)
  {
      ret *= base;
  }
  if(flag == 0)
      ret = 1/ret;
  return ret;
}

int main()
{
  double base = 6.123784;
  int exp = 5;
  double ret = my_pow(base, exp);
  cout<<"my_pow ret: "<<ret<<endl;
  cout<<"pow ret: "<<pow(base, exp)<<endl;
  return 0;
}





//二进制中一的个数
//请实现一个函数，输入一个整数，输出该二进制表示中1的个数

#include <iostream>
using namespace std;

//实现方法1
size_t count_one_num(int n)
{
  size_t count = 0;
  while(n != 0)
  {
      ++count;
      n = n & (n-1);
  }
  return count;
}

//实现方法2
size_t count_one_num(int n)
{
  int i = 32;
  size_t count = 0;
  while(--i)
  {
      if((n & 1) == 1)
          ++count;
      n = n>>1;
  }
  return count;
}

//实现方法3
size_t count_one_num(int n)
{
  size_t count = 0;

  while(n != 0)
  {
      if((n % 2) == 1)
          count++;
      n /= 2;
  }
  return count;
}

int main()
{
  int n = 11;
  size_t ret = count_one_num(n);
  cout<<"one number in "<<n<<" are: "<<ret<<endl;

  return 0;
}




//求第n个斐波那契数

#include <iostream>
using namespace std;

//实现方法3：三数轮循
long long Fib(size_t n)
{
  if(n < 2)
      return n;

  long long f0, f1, f2;
  f0 = 0;
  f1 = 1;

  for(size_t i = 2; i <= n; ++i)
  {
      f2 = f0 + f1;
      f0 = f1;
      f1 = f2;
  }
  return f2;
}

//实现方法2：数组存放
long long Fib(size_t n)
{
  if(n < 2)
      return n;

  long long *p = new long long[n+1];
  p[0] = 0;
  p[1] = 1;

  for(size_t i = 2; i <= n; ++i)
  {
      p[i] = p[i-1] + p[i-2];
  }
  long long ret = p[n];
  delete[] p;
  return ret;
}

//实现方法3：递归
long long Fib(size_t n)
{
  if(n < 2)
      return n;
  else
      return Fib(n-1)+Fib(n-2);
}

int main()
{
  size_t n = 58;
  long long ret = Fib(n);
  cout<<"Fibonacci number of "<<n<<" is: "<<ret<<endl;
  return 0;
}




//旋转数组的最小数字
//输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素

#include <iostream>
#include <assert.h>
using namespace std;

int find_min_num(const int *arr, size_t n)
{
  assert(arr && n);

  int left = 0;
  int right = n-1;
  int mid = (right-left)/2;

  while(left < right)
  {
      if((arr[left] <= arr[mid]) && (arr[mid] <= arr[right]))
      {
          break;
      }
      else if((arr[mid-1] > arr[mid]) && (arr[mid+1] > arr[mid]))
      {
          return arr[mid];
      }
      else if((arr[left] <= arr[mid]) && (arr[mid] >= arr[right]))
      {
          left = mid + 1;
      }
      else
      {
          right = mid - 1;
      }

      mid = (right-left)/2 + left;
  }
  return arr[left];
}

int main()
{
  int arr[] = {8, 9, 2, 3, 4, 5, 6, 7};

  int ret = find_min_num(arr, sizeof(arr)/sizeof(arr[0]));
  cout<<"the min number is: "<<ret<<endl;
  return 0;
}
                                                
