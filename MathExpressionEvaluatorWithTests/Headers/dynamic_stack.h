#pragma once

#include <iostream>
#include <algorithm>

template <class T>
class TDynamicStack {

private:

	T* data;
	size_t dataSize;
	int topIndex;

public:

	TDynamicStack(size_t initialCapacity = 10) : data(new T[initialCapacity]), dataSize(initialCapacity), topIndex(-1) {}
	~TDynamicStack();

	size_t Size() const;
	bool IsEmpty() const;
	bool IsFull() const;

	T Pop();
	void Push(const T& element);

	TDynamicStack(const TDynamicStack& stack);
	TDynamicStack<T>& operator=(const TDynamicStack& stack);

private:

	void EnsureData(double multiplier);

};


template<class T>
inline TDynamicStack<T>::~TDynamicStack()
{
	delete[] data;
}

template<class T>
inline size_t TDynamicStack<T>::Size() const
{
	return topIndex + 1;
}

template<class T>
inline bool TDynamicStack<T>::IsEmpty() const
{
	return topIndex == -1;
}

template<class T>
inline bool TDynamicStack<T>::IsFull() const
{
	return Size() == dataSize;
}

template<class T>
inline T TDynamicStack<T>::Pop()
{

	if (IsEmpty()) {
		throw "Stack Is Empty";
	}

	return data[topIndex--];
}

template<class T>
inline void TDynamicStack<T>::Push(const T& element)
{
	if (IsFull()) {
		EnsureData(2);
	}

	data[++topIndex] = element;

}

template<class T>
inline TDynamicStack<T>::TDynamicStack(const TDynamicStack& stack)
{
	this->data = new T[stack.dataSize];
	std::copy(stack.data, stack.data + stack.dataSize, this->data);

	this->topIndex = stack.topIndex;
	this->dataSize = stack.dataSize;
}

template<class T>
inline TDynamicStack<T>& TDynamicStack<T>::operator=(const TDynamicStack& stack)
{

	if (this == &stack) {
		return *this;
	}

	if (dataSize < stack.dataSize) {
		T* tempData = new T[stack.dataSize];

		delete[] this->data;

		this->data = tempData;
	}

	std::copy(stack.data, stack.data + stack.dataSize, this->data);

	this->topIndex = stack.topIndex;
	this->dataSize = stack.dataSize;

	return *this;
}



template<class T>
inline void TDynamicStack<T>::EnsureData(double multiplier)
{
	size_t ensuredDataSize = static_cast<size_t>(dataSize * multiplier);
	
	T* ensuredData = new T[ensuredDataSize];
	std::copy(data, data + Size(), ensuredData);
	delete[] data;

	dataSize = ensuredDataSize;
	data = ensuredData;
}
