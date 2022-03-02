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
	// ���ͱ���
	typedef T value_type;
	typedef typename std::vector<T>::size_type size_type;

	// ���캯��
	PriorityQueue() noexcept : que(1), sz(0) {}

	template <typename Iter>
	PriorityQueue(Iter beg, Iter end);

	// �ӳ�ʼֵ�б��죬ί�и���Ĺ��캯�����
	template <typename T2>
	PriorityQueue(std::initializer_list<T2> list) : PriorityQueue(list.begin(), list.end()) {}

	// ���ض��еĴ�С���ж��Ƿ�Ϊ��
	size_type size() noexcept { return sz; }
	bool empty() noexcept { return sz == 0; }

	// �����ɾ������
	void Insert(T val);
	T Delete();

private:
	std::vector<T> que; // �������ȶ��е�����
	size_type sz; // ���д�С

	// ִ�����˲��������
	void PercolateDown(size_type cur);
};


// PriorityQueue�Ĺ��캯��
// �ӵ�����beg��end��ʾ�ķ�Χ�ڹ������ȶ���
template <typename T>
template <typename Iter>
PriorityQueue<T>::PriorityQueue(Iter beg, Iter end)
	: que(end - beg + 1), sz(0)
{
	size_type i = 1; // ���±�0�����գ��������
	for (Iter it = beg; it != end; ++it)
		que.at(i++) = *it;
	sz = end - beg; // ���еĴ�С

	for (i = sz / 2; i > 0; i--)
		PercolateDown(i); // ִ������
}


template <typename T>
void PriorityQueue<T>::PercolateDown(size_type cur)
{
	using std::swap; // ����׼��swap��������չ���˺���

	for (size_type child; cur * 2 <= sz; cur = child)
	{
		child = cur * 2;
		if (child + 1 <= sz && que[child + 1] < que[child])
			child += 1; // ѡ��2�������н�С��һ��

		if (que[cur] > que[child]) // ���ڵ�����ӽڵ�
			swap(que[cur], que[child]); // ����
	}
}


template <typename T>
void PriorityQueue<T>::Insert(T val)
{
	que.push_back(val); // �ȷ���β����ʹsize��1

	size_type cur = sz + 1;
	for (; que[cur / 2] > val && cur > 1; cur /= 2)
		que[cur] = que[cur / 2];

	que[cur] = val;
	++sz; // Ԫ�ظ�����1
}


template <typename T>
T PriorityQueue<T>::Delete()
{
	const T ret = que[1]; // �����һ��Ԫ��
	const T last = que[sz--]; // �������һ��Ԫ��

	size_type cur = 1, child;
	for (; cur * 2 <= sz; cur = child)
	{
		child = cur * 2;
		if (child + 1 <= sz && que[child + 1] < que[child])
			child += 1; // �ҳ���С�ĺ���

		if (que[child] < last)
			que[cur] = que[child]; // ��С�ĺ��Ӹ�ֵ�����ڵ�
		else
			break; // ���һ��Ԫ�ر�cur��2�����Ӷ�С
	}
	que[cur] = last;

	return ret;
}

#endif