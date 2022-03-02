#include "PriorityQueue.h"
#include <vector>
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::vector;

int main()
{
	// 
	vector<int> ivec{ 0,1,2,3,4,5,6,7,8,9,10 };
	vector<double> dvec{ 3567.34,5,547.34,43.25 };
	PriorityQueue<int> Pq(ivec.begin(), ivec.end());
	PriorityQueue<double> pd(dvec.begin(), dvec.end());
	PriorityQueue<int> pq2{ 1.3,2.1,3.0,4.2,5.4,6.3,7.0,.8 };

	vector<string> strvec{ "C++", "Apue", "Pointers" };
	PriorityQueue<string> str_pq(strvec.begin(), strvec.end());
	str_pq.Insert("Tcp/ip");
	str_pq.Insert(string("Const"));
	str_pq.Insert("String");
	str_pq.Insert("double");
	str_pq.Insert("reference");
	str_pq.Insert("type-id");

	while (!str_pq.empty())
		cout << str_pq.Delete() << endl;

	return 0;
}