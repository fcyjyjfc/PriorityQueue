#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <vector>
#include <utility>

template <typename T>
bool compare(const T& lhs, const T& rhs)
{
	return lhs < rhs;
}

template <typename T>
class PriorityQueue
{
public:
	// 类型别名
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

	// 构造函数
	PriorityQueue() noexcept : que(1), sz(0) {}

	template <typename Iter>
	PriorityQueue(Iter beg, Iter end);

	// 从初始值列表构造，委托给别的构造函数完成
	template <typename T2>
	PriorityQueue(std::initializer_list<T2> list) : PriorityQueue(list.begin(), list.end()) {}

	// 返回队列的大小、判断是否为空
	size_type size() noexcept { return sz; }
	bool empty() noexcept { return sz == 0; }

	// 插入和删除操作
	void Insert(T val);
	T Delete();

private:
	std::vector<T> que; // 保存优先队列的数据
	size_type sz; // 队列大小

	// 执行下滤操作构造堆
	void PercolateDown(size_type cur);
};


// PriorityQueue的构造函数
// 从迭代器beg和end表示的范围内构造优先队列
template <typename T>
template <typename Iter>
PriorityQueue<T>::PriorityQueue(Iter beg, Iter end)
	: que(end - beg + 1), sz(0)
{
	size_type i = 1; // 将下标0处留空，方便计算
	for (Iter it = beg; it != end; ++it)
		que.at(i++) = *it;
	sz = end - beg; // 队列的大小

	for (i = sz / 2; i > 0; i--)
		PercolateDown(i); // 执行下滤
}


template <typename T>
void PriorityQueue<T>::PercolateDown(size_type cur)
{
	using std::swap; // 将标准库swap作用域扩展至此函数

	for (size_type child; cur * 2 <= sz; cur = child)
	{
		child = cur * 2;
		if (child + 1 <= sz && que[child + 1] < que[child])
			child += 1; // 选择2个孩子中较小的一个

		if (que[cur] > que[child]) // 父节点大于子节点
			swap(que[cur], que[child]); // 交换
	}
}


template <typename T>
void PriorityQueue<T>::Insert(T val)
{
	que.push_back(val); // 先放在尾部，使size加1

	size_type cur = sz + 1;
	for (; que[cur / 2] > val && cur > 1; cur /= 2)
		que[cur] = que[cur / 2];

	que[cur] = val;
	++sz; // 元素个数加1
}


template <typename T>
T PriorityQueue<T>::Delete()
{
	const T ret = que[1]; // 保存第一个元素
	const T last = que[sz--]; // 保存最后一个元素

	size_type cur = 1, child;
	for (; cur * 2 <= sz; cur = child)
	{
		child = cur * 2;
		if (child + 1 <= sz && que[child + 1] < que[child])
			child += 1; // 找出较小的孩子

		if (que[child] < last)
			que[cur] = que[child]; // 较小的孩子赋值给父节点
		else
			break; // 最后一个元素比cur的2个孩子都小
	}
	que[cur] = last;

	return ret;
}

#endif