#ifndef _MY_LIST_
#define _MY_LIST_

#include <stdio.h>
/// \@单链表，带头节点实现
typedef int elem_type;

typedef struct node{
	elem_type val;
	struct node *next;
}node_t, *node_ptr, **node_pptr;

#define _TRUE_  1
#define _FALSE_ 0

////////////////////////////////////////基本实现//////////////////////////////////////
int list_init( node_pptr phead);
int is_empty(node_ptr head);
int push_front(node_ptr head, elem_type _val);
int pop_front(node_ptr head);
int push_back(node_ptr head, elem_type _val);
int pop_back(node_ptr head);
int clear(node_ptr head);
int insert(node_ptr head, node_ptr pos, elem_type _val);//节点之后插入
int size(node_ptr head);
int get_elem(node_ptr head, int i, elem_type *_val);
int find(node_ptr head, elem_type _val, node_pptr _node/*output*/);
int erase(node_ptr head, node_ptr _erase_node);
int remove_val(node_ptr head, elem_type _val);
void show_list(node_ptr head);

////////////////////////////////////////相关面试题/////////////////////////////////////
/// \@1. 删除单链表的一个非尾节点
int del_non_tail_node(node_ptr head);

/// \@2. 在当前节点前插入一个数据X
int insert_front_node(node_ptr _n, elem_type x);

/// \@3. 约瑟夫环（约瑟夫问题）是一个数学的应用问题：已知n个人
/// \@ （以编号1，2，3...n分别表示）围坐在一张圆桌周围。
/// \@ 从编号为k的人开始报数，数到m的那个人出列；他的下一
/// \@ 个人又从1开始报数，数到m的那个人又出列；依此规律
/// \@ 重复下去，直到圆桌周围的人全部出列。
node_ptr JosephCycle();

/// \@4. 逆置单链表
int reverse(node_ptr head);

/// \@5. 对单链表进行排序（冒泡升序）
int bubble_sort(node_ptr head);

/// \@6. 排序优化->快速排序
void quick_sort();

/// \@7. 合并有序链表，合并后链表依旧有序
node_ptr merge_order(node_ptr head1, node_ptr head2);

/// \@8. 递归实现链表合并
node_ptr merge_recursive(node_ptr head1, node_ptr head2);

/// \@[快慢指针问题]
/// \@9. 查找单链表的中间节点
int find_mid_node(node_ptr head, node_pptr _n/*output*/);

/// \@10. 删除单链表的倒数第k个节点（k > 1 && k < 链表总长度）
/// \@    时间复杂度O（N）
void del_tailn_node(node_ptr head, int _tail_n);

/// \@[链表带环问题]
/// \@11. 判断链表是否带环，若链表带环则求链表的长度和相遇节点， 不带环则返回－1
int check_cycle(node_ptr head, node_pptr _meet_node/*output*/, int *out_cycle_len)

/// \@12. 获取环入口
/// \@

/// \@[链表相交问题]
/// \@13. 判断两个链表是否相交，假设两个链表都不带环。
/// \@    求环的交点，长链表先走n步（n为两链表的长度差），
/// \@    然后再一起走，第一个相遇点则为交点。(未实现)
/// \@    这里还需要考虑链表带环时，链表的相交问题。
int check_cross(node_ptr head1, node_ptr head2);

/// \@[复杂链表的复制]
/// \@14. 一个链表的每个节点，有一个指向next指针指向下一个节点，
/// \@    还有一个random指针指向这个链表中的一个随机节点或者NULL，
/// \@    现在要求实现复制这个链表，返回复制后的新链表。
typedef struct complex_node
{
	elem_type _data;				// 数据
	struct complex_node* _next;		// 指向下一个节点的指针
	struct complex_node* _random;	// 指向随机节点
}complex_node;

#endif

