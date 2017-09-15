#ifndef STACK_H//预处理器    
#define STACK_H    

#include <iostream>    
using namespace std;

const int maxlen = 100;//栈的最大存储量    

template <typename elementType>
class stack {
public:
	stack();  
	bool ifempty();
	bool iffull(); 
	bool get_top(elementType &x); 
	bool push(elementType x);
	bool pop();
private:
	int count;//元素的计数器    
	elementType data[maxlen];//顺序存储
};

template <typename elementType>
stack<elementType>::stack() {
	count = 0;
}

template <typename elementType>
bool stack<elementType>::ifempty() {
	if (count == 0)
		return true;
	return false;
}

template <typename elementType>
bool stack<elementType>::iffull() {
	if (count == maxlen)
		return true;
	return false;
}

template <typename elementType>
bool stack<elementType>::get_top(elementType &x) {
	if (!ifempty()) {
		x = data[count - 1];
		return true;
	}
	return false;
}

template <typename elementType>
bool stack<elementType>::push(elementType x) {
	if (!iffull()) {
		data[count++] = x;
		return true;
	}
	return false;
}

template <typename elementType>
bool stack<elementType>::pop() {
	if (!ifempty()) {
		--count;
		return true;
	}
	return false;
}

#endif   