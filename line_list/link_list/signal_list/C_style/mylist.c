#include "mylist.h"
#include <unistd.h>
#include <stdlib.h>

////////////////////////////////////////基本实现//////////////////////////////////////
//购买节点,静态函数, 无需暴露
static node_ptr buy_node(elem_type _val)
{
	node_ptr tmp = (node_ptr)malloc(sizeof(node_t));
	if( NULL == tmp ){
		perror("malloc");
		return NULL;
	}
	tmp->val = _val;
	tmp->next = NULL;
	return tmp;
}

//摧毁节点
static void delete_node(node_ptr _node)
{
	if( _node ){
		free(_node);
		_node = NULL;
	}
}

//初始化头节点
int list_init(node_pptr phead)
{
	if( NULL == (*phead = buy_node(0)) ){
		return _FALSE_;
	}
	return _TRUE_;
}

//判断list是否为空
int is_empty(node_ptr head)
{
	if( head && (head->next == NULL) ){
		return _TRUE_;
	}
	return _FALSE_;
}

//list头部插入
int push_front(node_ptr head, elem_type _val)
{
	node_ptr tmp = NULL;
	if( NULL == (tmp = buy_node(_val))){
		return _FALSE_;
	}
	tmp->next = head->next;
	head->next = tmp;
	return _TRUE_;
}

//list头部清理
int pop_front(node_ptr head)
{
	if( is_empty(head) ){
		return _FALSE_;
	}
	node_ptr tmp = head->next;
	head->next = tmp->next;
	tmp->next = NULL;
	delete_node(tmp);
	return _TRUE_;
}

//list尾部插入
int push_back(node_ptr head, elem_type _val)
{
	while(head->next != NULL){
		head = head->next;
	}
	node_ptr tmp = NULL;
	if( NULL == (tmp = buy_node(_val))){
		return _FALSE_;
	}
	head->next = tmp;
	tmp->next  = NULL;
	return _TRUE_;
}

//list尾部清理
int pop_back(node_ptr head)
{
	if(is_empty(head)){
		return _FALSE_;
	}
	node_ptr pre = head;
	head = head->next; //指向有效节点
	while( head && head->next ){
		pre = head;
		head = head->next;
	}
	pre->next = NULL;
	delete_node(head);
	return _TRUE_;
}

//清除整个链表
int clear(node_ptr head)
{
	while( _TRUE_ == pop_front(head) );
	return _TRUE_;
}

//节点之后插入
int insert(node_ptr head, node_ptr pos, elem_type _val)
{
	while(head){
		if( head == pos ){
	        node_ptr tmp = NULL;
	        if( NULL == (tmp = buy_node(_val))){
	        	return _FALSE_;
	        }
	        tmp->next = pos->next;
	        pos->next = tmp;
	        return _TRUE_;
		}
		head = head->next;
	}
	return _FALSE_;
}

//求list长度
int size(node_ptr head)
{
	int count = 0;
	while(head->next != NULL){
		count++;
		head = head->next;
	}
	return count;
}

//获取链表指定位置的元素
int get_elem(node_ptr head, int i, elem_type *_val)
{
	head = head->next;
	int j = 1;
	int ret = _FALSE_;
	while( head && j < i ){
		head = head->next;
		j++;
	}
	if( head && j == i ){
		*_val = head->val;
		ret = _TRUE_;
	}
	return ret;
}

//查找链表中指定元素
int find(node_ptr head, elem_type _val, node_pptr _node)
{
	node_ptr begin = head->next;//指向第一个有效节点
	while(begin){
		if( begin->val == _val ){
			*_node = begin;
			return _TRUE_;
		}
		begin = begin->next;
	}
	return _FALSE_;
}

//删除指定链表的指定节点
int erase(node_ptr head, node_ptr _erase_node)
{
	if( !is_empty(head) ){
		while( head && head->next ){
			if(head->next == _erase_node){//存在该节点，删除
				head->next = head->next->next;
				_erase_node->next = NULL;
				delete_node(_erase_node);
				return _TRUE_;
			}
			head = head->next;
		}
	}
	return _FALSE_;
}

//移除链表指定元素
int remove_val(node_ptr head, elem_type _val)
{
	if( !is_empty(head) ){
		node_ptr pre = head;
		head = head->next;//指向第一个有效元素
		while(head){
			if( head->val == _val ){
				pre->next = head->next;
				head->next = NULL;
				delete_node(head);
				return _TRUE_;
			}
			pre = head;
			head = head->next;
		}
	}
	return _FALSE_;
}

//顺序输出链表
void show_list(node_ptr head)
{
	if( !is_empty(head) ){
    	head = head->next;
    	while(head){
    		printf("%d ", head->val);
    		head = head->next;
    	}
    	printf("\n");
	}
}

///////////////////////////////////////相关面试题/////////////////////////////////////

/// \@1. 删除单链表的一个非尾节点(没有指明链表首地址)
int del_non_tail_node(node_ptr _n)
{
	if(_n && _n->next ){//保证不是尾节点
		node_ptr tmp = _n->next;
		_n->val = tmp->val;
		_n->next = tmp->next;
		free(tmp);
		tmp = NULL;
		return _TRUE_;
	}
	return _FALSE_;
}

/// \@2. 在当前节点前插入一个数据X
int insert_front_node(node_ptr _n, elem_type _x)
{
	int res = _FALSE_;
	if(_n){
		node_ptr tmp = NULL;
		if(NULL != (tmp = buy_node(_x))){//购买新的节点
			//插入新节点到当前节点之后
			tmp->next = _n->next;
			_n->next  = tmp;
			//交换节点数据内容，达到目的
			elem_type val_tmp = tmp->val;
			tmp->val = _n->val;
			_n->val = val_tmp;
			res = _TRUE_;
		}
	}
	return res;
}

/// \@3. 约瑟夫环（约瑟夫问题）是一个数学的应用问题：已知n个人
/// \@ （以编号1，2，3...n分别表示）围坐在一张圆桌周围。
/// \@ 从编号为k的人开始报数，数到m的那个人出列；他的下一
/// \@ 个人又从1开始报数，数到m的那个人又出列；依此规律
/// \@ 重复下去，直到圆桌周围的人全部出列。
node_ptr JosephCycle()
{
	return NULL;
}

/// \@4. 逆置单链表
int reverse(node_ptr head)
{
	int res = _FALSE_;
	if( !is_empty(head) ){
		//至少有一个节点，至少有两个节点才需要逆置操作
		node_ptr insert_front = head->next;//指向第一个有效节点
		node_ptr insert_after = head->next->next; //指向第二个有效节点
		while( insert_after ){
			insert_front->next = insert_after->next;
			insert_after->next = head->next;
			head->next = insert_after;
			insert_after = insert_front->next;
		}
		res = _TRUE_;
	}
	return res;
}

static void swap( elem_type *val1, elem_type *val2)
{
	elem_type tmp = *val1;
	*val1 = *val2;
	*val2 = tmp;
}

/// \@5. 对单链表进行排序（冒泡升序）
int bubble_sort(node_ptr head)
{
	int res = _FALSE_;
	if( !is_empty(head) && size(head) > 1 ){//使用已经存在的接口，这里存在潜在性能问题
		node_ptr prev = NULL;
		node_ptr next = NULL;      
		node_ptr tail = NULL;

		//end指针回退， 等于第一个节点退出
		while(tail != head->next){
			prev = head->next;
			next = prev->next;
			while(next != tail){ //bug？
				if(prev->val < next->val){
					swap(&(prev->val), &(next->val));
				}
				prev = next;
				next = next->next;
			}
			tail = prev;
		}
		res = _TRUE_;
	}
	return res;
}

/// \@6. 排序优化->快速排序
void quick_sort()
{
}

/// \@7. 合并有序链表，合并后链表依旧有序(按照由小到大顺序)
node_ptr merge_order(node_ptr head1, node_ptr head2)
{
	//若两张链表相同，则直接返回
	if(head1 == head2){
		return head1;
	}
	//若其中一个链表为空，则返回另外一张链表
	if( is_empty(head1) ){
		return head2;
	}
	if( is_empty(head2) ){
		return head1;
	}

	//开始合并
	node_ptr start1 = head1->next;//指向链表1的第一个有效节点
	node_ptr start2 = head2->next;//指向链表2的第一个有效节点
	node_ptr new_head = NULL;
	if( start1->val < start2->val ){
		new_head = start1;
		start1 = start1->next;
		delete_node(head2);//清除多余的头节点
	}else{
		new_head = start2;
		start2 = start2->next;
		delete_node(head1);
	}

	//始终指向新链表的尾节点，方便新链表尾插生成
	node_ptr new_tail = new_head->next;

	while( start1 && start2 ){
		if( start1->val < start2->val ){
			new_tail->next = start1;
			start1 = start1->next;
			new_tail = new_tail->next;
		}else{
			new_tail->next = start2;
			start2 = start2->next;
			new_tail = new_tail->next;
		}
	}
	//链入最后不为空的剩余链表，剩余链表依旧有序
	if(start1){
		new_tail->next = start1;
	}
	if(start2){
		new_tail->next = start2;
	}
	return new_head;
}

/// \@8. 递归实现链表合并
node_ptr merge_recursive(node_ptr head1, node_ptr head2)
{
	return NULL;
}

/// \@[快慢指针问题]
/// \@9. 查找单链表的中间节点
int find_mid_node(node_ptr head, node_pptr _n/*output*/)
{
	if( is_empty(head) ){
		return _FALSE_;
	}
	//快慢指针，快指针一次走两步，慢指针一次走一步
	node_ptr slow = head->next;
	node_ptr fast = head->next;
	while(fast && fast->next){//有bug，当有2个节点的时候，有问题
		slow = slow->next;
		fast = fast->next->next;
	}
	//fast 指针为空， 节点个数为偶数
	//fast->next为空，节点个数为奇数
	*_n = slow;
	return _TRUE_;
}

/// \@10. 删除单链表的倒数第k个节点（k > 1 && k < 链表总长度）
/// \@    时间复杂度O（N）
void del_tailn_node(node_ptr head, int _tail_n)
{
	if( !is_empty(head) ){
		node_ptr fast = head->next;
		node_ptr slow = head->next;

		while(fast && _tail_n){
			fast = fast->next;
			_tail_n--;
		}
		node_ptr pre = head;
		while(fast){
			pre = slow;
			slow = slow->next;
			fast = fast->next;
		}
		pre->next = slow->next;
		delete_node(slow);
	}
}

/// \@[链表带环问题]
/// \@11. 判断链表是否带环，若链表带环则求环的长度和相遇节点， 不带环则返回－1
int check_cycle(node_ptr head, node_pptr _meet_node/*output*/, int *out_cycle_len/*output*/)
{
	if( !is_empty(head) ){
		node_ptr slow = head;
		node_ptr fast = head->next;
		while(fast && fast->next){
			if(slow == fast){
				int cycle_len = 0;
				*_meet_node = fast;
				do{
					slow = slow->next;
					cycle_len++;
				}while(slow == fast);
				*out_cycle_len = cycle_len;
				return _TRUE_;
			}
			slow = slow->next; //慢指针一次走一步
			fast = fast->next->next; //快指针一次走两步
		}
	}
	return _FALSE_;
}

/// \@12. 获取环入口
/// \@ 在已知相遇节点（不一定是环的入口）的情况下，求环入口.
node_ptr get_cycle_entry_node(node_ptr head, node_ptr _meet_node)
{
	if(!is_empty()){
    	int length1 = 0;
    	int length2 = 0;
    	int interval = 0;
    	node_ptr start1 = head->next;//指向第一个有效节点
		node_ptr start2 = _meet_node->next;//指向相遇节点的下一个节点，此时，相遇节点可以认为是start1和start2两张链表的尾节点

		//1.模拟从相遇节点断开环，则转换为两单链表相交，求交点的问题。
		while(start1 != _meet_node){
			length1++; //统计start1链表的长度
			start1 = start1->next;
		}
		while(start2 != _meet_node){
			length2++; //统计start2链表的长度
			start2 = start2->next;
		}

		//2：先计算两个链表的长度，长的链表先走interval（两链表长度的差值）步。
		//重置链表起点
		start1 = head->next;
		start2 = _meet_node->next;
		if(length1 > length2){ //start1链表较长, 则先让start1指针先走
			interval = length1 - length2;
			while(interval-){
				start1 = start1->next;
			}
		}else{
			interval = length2 - length1;
			while(interval){
				start2 = start2->next;
			}
		}

		// 3. 同步向后递推， 则第一次相遇的节点为环的入口点, 最后一个节点是start1和start2的_meet_node
		while(start1 != start2){
			start1 = start1->next;
			start2 = start2->next;
		}
		return start1;
	}
}

/// \@[链表相交问题]
/// \@13. 判断两个链表是否相交，假设两个链表都不带环。
/// \@    求环的交点，长链表先走n步（n为两链表的长度差），
/// \@    然后再一起走，第一个相遇点则为交点。(未实现)
/// \@    这里还需要考虑链表带环时，链表的相交问题。
int check_cross(node_ptr head1, node_ptr head2)
{
	int res = _FALSE_;
	if( !is_empty(head1) && !is_empty(head2) ){
    	while(head1->next && head2->next){
			head1 = head1->next;
			head2 = head2->next;
    	}
		while(head1->next){
			head1 = head1->next;
		}
		while(head1->next){
			head2 = head2->next;
		}
		if( head1 == head2 ){
			res = _TRUE_;
		}
	}
	return res;
}

/// \@[复杂链表的复制]
/// \@14. 一个链表的每个节点，有一个指向next指针指向下一个节点，
/// \@    还有一个random指针指向这个链表中的一个随机节点或者NULL，
/// \@    现在要求实现复制这个链表，返回复制后的新链表。
