#pragma once

template <typename T>
class Container
{
	T** list;
	int size, capacity;

	void copy(const Container<T>&);
	void free();
	void resize();

public:
	Container();
	Container(const Container<T>&);
	Container& operator=(const Container&);
	~Container();

	void add(const T*);
	bool deleteAt(int);

};

template <typename T>
void Container<T>::copy(const Container<T>& other)
{
	capacity = other.capacity;
	size = other.size;

	list = new T * [capacity];

	for (size_t i = 0; i < size; i++)
		list[i] = other.list[i]->clone();
}

template <typename T>
void Container<T>::free()
{
	for (size_t i = 0; i < size; i++)
		delete list[i];

	delete[] list;

	capacity = size = 0;
}

template <typename T>
void Container<T>::resize()
{
	T** temp = new T * [capacity *= 2];
	for (size_t i = 0; i < size; i++)
		temp[i] = list[i];

	delete[] list;
	list = temp;
}

template <typename T>
Container<T>::Container()
{
	size = 0;
	capacity = 2;
	list = new T * [capacity];
}

template <typename T>
Container<T>::Container(const Container<T>& other)
{
	copy(other);
}

template <typename T>
Container<T>& Container<T>::operator=(const Container& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}

	return *this;
}

template <typename T>
Container<T>::~Container()
{
	free();
}

template <typename T>
void Container<T>::add(const T* item)
{
	if (size >= capacity)
		resize();

	list[size++] = item->clone();
}

template <typename T>
bool Container<T>::deleteAt(int index)
{
	if (index < 0 || index >= size)
		return false;

	delete list[index];

	for (int i = index; i < size - 1; i++)
		list[i] = list[i + 1];

	list[size - 1] = nullptr;
	size--;

	return true;
}
