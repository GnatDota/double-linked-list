#pragma once

template<class T>
class DLList
{
public:
	DLList();

	void Create(int size);
	void Add(T data);
	void AddFront(T data);
	void AddTo(int index, T data);

	void Clear();
	void Remove();
	void RemoveFront();
	void RemoveAt(int index);


	T& operator[](const int index);
	inline int GetSize() { return size; }

	~DLList();
private:
	template<class T>
	class Node
	{
	public:
		Node<T> *pNext;
		Node<T> *pPrev;
		T data;

		Node<T>(T data = T(), Node<T> *pPrev = nullptr, Node<T> *pNext = nullptr)
		{
			this->pNext = pNext;
			this->pPrev = pPrev;
			this->data = data;
		}
	};

	Node<T>* GetIndexPtr(int index)
	{
		if (GetCenter() > index)
		{
			int counter = 0;
			Node<T> *current = this->head;

			while (current != nullptr)
			{
				if (counter == index)
				{
					return current;
				}
				current = current->pNext;
				counter++;
			}
		}
		else if (GetCenter() < index)
		{
			int counter = size - 1;
			Node<T> *current = this->tail;

			while (current != nullptr)
			{
				if (counter == index)
				{
					return current;
				}
				current = current->pPrev;
				counter--;
			}
		}
		else
		{
			int counter = 0;
			Node<T> *current = this->head;

			while (current != nullptr)
			{
				if (counter == index)
				{
					return current;
				}
				current = current->pNext;
				counter++;
			}
		}
	}
	inline int GetCenter() { return size / 2; }
	int size;
	Node<T> *head;
	Node<T> *tail;
};

template<class T>
DLList<T>::DLList()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template<class T>
T& DLList<T>::operator[](const int index)
{
	if (GetCenter() > index)
	{
		int counter = 0;
		Node<T> *current = this->head;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else if (GetCenter() < index)
	{
		int counter = size - 1;
		Node<T> *current = this->tail;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pPrev;
			counter--;
		}
	}
	else
	{
		int counter = 0;
		Node<T> *current = this->head;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
}

template<class T>
void DLList<T>::Create(int size)
{
	for (size_t i = 0; i < size; i++)
	{
		Add(T());
	}
}

template<class T>
void DLList<T>::Add(T data)
{
	Node<T> *tmp = new Node<T>(data);

	if (head == nullptr)
	{
		head = tail = tmp;
	}
	else
	{
		tmp->pPrev = tail;
		tail->pNext = tmp;
		tail = tmp;
	}

	size++;
}

template<class T>
void DLList<T>::AddFront(T data)
{
	Node<T> *tmp = new Node<T>(data);

	if (head == nullptr)
	{
		head = tail = tmp;
	}
	else
	{
		tmp->pNext = head;
		head->pPrev = tmp;
		head = tmp;
	}

	size++;
}

template<class T>
void DLList<T>::AddTo(int index, T data)
{
	Node<T> *tmp = new Node<T>(GetIndexPtr(index)->data);
	Node<T> *tmpNext = GetIndexPtr(index)->pNext;

	if (head == nullptr)
	{
		head = tail = tmp;
	}
	else
	{
		GetIndexPtr(index)->data = data;
		GetIndexPtr(index)->pNext = tmp;
		tmp->pNext = tmpNext;
		tmp->pPrev = GetIndexPtr(index);
	}

	size++;
}


template<class T>
void DLList<T>::Clear()
{
	int tmp = size;

	if (size != 0)
	{
		for (size_t i = 0; i < tmp; i++)
		{
			Remove();
		}
	}
	else { return; }
}

template<class T>
void DLList<T>::Remove()
{
	if (head == tail)
	{
		delete head;
		head = nullptr;
		size--;
	}
	else if (head != nullptr)
	{
		Node<T>* tmpTail = tail;
		tail = tmpTail->pPrev;
		tail->pNext == nullptr;
		delete tmpTail;
		tmpTail = nullptr;
		size--;
	}
	else { return; }
}

template<class T>
void DLList<T>::RemoveFront()
{
	if (size != 0)
	{
		Node<T>* tmp = head;
		Node<T>* tmpNext = head->pNext;
		head = tmpNext;
		head->pPrev = nullptr;
		delete tmp;
		tmp = nullptr;
		size--;
	}
	else if (head == tail)
	{
		delete head;
		head = nullptr;
		size--;
	}
	else { return; }
}

template<class T>
void DLList<T>::RemoveAt(int index)
{
	if (head == nullptr) { return; }
	if (index >= size || index < 0) { return; }
	
	if (index == 0)
	{
		RemoveFront();
	}
	else if (index == size - 1)
	{
		Remove();
	}
	else
	{
		Node<T>* tmp = GetIndexPtr(index);
		Node<T>* tmpPrev = GetIndexPtr(index - 1);
		Node<T>* tmpNext = GetIndexPtr(index + 1);
		tmpPrev->pNext = tmpNext;
		tmpNext->pPrev = tmpPrev;
		delete tmp;
		tmp = nullptr;
		size--;
	}
}

template<class T>
DLList<T>::~DLList()
{
	Clear();
}