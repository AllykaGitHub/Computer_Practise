#include <iostream>
using namespace std;

// ���������, ����������� ���� ������� (����)
template <class T>
struct Element
{
	T data; // ������
	Element<T>* next; // ����� ���������� �������� � ������
	Element<T>* prev; // ����� ����������� �������� � ������
};

// ����, ����������� ���������� ������
template <class T>
class List
{
private:
	Element<T>* begin; // ��������� �� ������ ������� ������
	Element<T>* end; // ��������� �� ��������� ������� ������
	int count; // ���������� ��������� � ������

	// �����, ������������ ������� � �������� �������,
	// ��������� ��� ������� ���������.
	Element<T>* Move(int index);

	// �����, ���������� ������
	void Copy(const List<T>& obj);

	// �����, ����������� ������������ ������ (�������) � ������
	bool CorrectIndex(int index);

public:
	// �����������
	List();

	// ����������� �����������
	List(const List& obj);

	// �������� �����������
	List<T>& operator=(const List& obj);

	// ����������
	~List();

	// ---------- ������ ������� � ��������� ��������� ������ --------
	// �������� ������� ������ �� �������
	T GetElement(int index);

	// �������� �������� �������� � �������� �������
	void SetElement(T _data, int index);

	// ---------- ������ ��������� ������� ������ ------------
	// �������� ������� � ����� ������
	void AddEnd(T _data);

	// �������� ������� � ������ ������
	void AddBegin(T _data);

	// ������� �������� � �������� ������� ������
	void Insert(T _data, int index);

	// ������� ������� � �������� �������,
	// ������� ���������� � 0
	void Del(int index);

	// ������� ������
	void Clear();

	// �������������� ������
	void Reverse();

	// ����� ������
	void Print(string msg);

	// �������� ���������� ��������� ������
	int Count();

	// ------------------------------------------
	// ���������� ����������
	// �������� + - ������������ �������
	List<T>& operator+(const List<T>& obj);

	// �������� ��������� ������� �� ���������
	bool operator==(const List& obj);

	// �������� ��������� ������� �� �����������
	bool operator!=(const List& obj);

	// �������� >=
	bool operator>=(const List& obj);

	// �������� <=
	bool operator<=(const List& obj);

	// �������� >
	bool operator>(const List& obj);

	// �������� <
	bool operator<(const List& obj);
};

// �������� ������� � �������� �������
template <class T>
Element<T>* List<T>::Move(int index)
{
	// 1. ���������� ��������� �� ������ ������
	Element<T>* t = begin;

	// 2. ���������� � ������� index
	for (int i = 0; i < index; i++)
		t = t->next;

	// 3. ������� ���������
	return t;
}
// �����, �������� ����� �� ������
template <class T>
void List<T>::Copy(const List<T>& obj)
{
	// 1. �������� ������ (���������� ������)
	Clear();

	// 2. ���� ����������� this <= obj
	Element<T>* t = obj.begin;

	while (t != nullptr)
	{
		AddEnd(t->data);
		t = t->next;
	}
}
// �����, ����������� ������������ ������� (�������) � ������
template <class T>
bool List<T>::CorrectIndex(int index)
{
	return (index >= 0) && (index < count);
}
// �����������
template <class T>
List<T>::List()
{
	// ������� ������ ������
	begin = end = nullptr;
	count = 0;
}
// ����������� �����������
template <class T>
List<T>::List(const List& obj)
{
	// ������� ����� �� ������
	Copy(obj);
}
// �������� �����������
template <class T>
List<T>& List<T>::operator=(const List& obj)
{
	Copy(obj);
	return *this;
}
// ����������
template <class T>
List<T>::~List()
{
	Clear(); // �������� ������
}
// �������� ������� ������ �� �������
template <class T>
T List<T>::GetElement(int index)
{
	// ��������, ��������� �� ������,
	// ���� ������ �� ���������, ������������� ����������
	if (!CorrectIndex(index))
		throw out_of_range("Incorrect index.");

	// ���� ������ ���������, �� ������� �������
	Element<T>* t = Move(index);
	return t->data;
}
// �������� �������� �������� � ��������� �������
template <class T>
void List<T>::SetElement(T _data, int index)
{
	// ��������, ��������� �� �������
	if (!CorrectIndex(index))
		return;

	// �������� ������� �� ������� � �������� ��� ��������
	Element<T>* t = Move(index);
	t->data = _data;
}
// �������� ������� � ����� ������
template <class T>
void List<T>::AddEnd(T _data)
{
	try
	{
		// 1. ������� ����� ������� � ������� _data
		Element<T>* t = new Element<T>;
		t->next = nullptr; // ���������� �������� ���
		t->prev = end; // ���������� ���������� �������
		t->data = _data; // �������� ������

		// 2. ��������� ���� next ���� ��� ���������� ��������
		if (end != nullptr)
			end->next = t;

		// 3. ��������, ���� �� � ������ ��������
		if (count == 0)
		{
			// ���� ��������� ���,
			// �� ��� ������������ � ������ � ����� ������
			begin = end = t;
		}
		else
		{
			// ���� �������� � ������ ����, �� ��� ����� ������
			end = t;
		}

		// 3. ��������� ����� ���������� ���������
		count++;
	}
	catch (bad_alloc e)
	{
		// ���� ������ �� ��������, �� ������� ��������� ���������
		cout << e.what() << endl;
	}
}
// �������� ������� � ������ ������
template <class T>
void List<T>::AddBegin(T _data)
{
	try
	{
		// 1. ������� ����� ������� (����� ������ ������)
		// � ��������� ��� �������
		Element<T>* t = new Element<T>;
		t->data = _data; // ������
		t->prev = nullptr; // ����������� �������� ���

		// ��������� ������� ��������� �� ���������� ������
		t->next = begin;

		// 2. ���� �� �������� � ������?
		if (count > 0)
		{
			// ���� ����, �� ������������� ���������� ������ ������
			begin->prev = t;
			begin = t;
		}
		else
		{
			// ���� ��������� ���, �� ������ � ����� ���� ��� ����� ���������
			begin = end = t;
		}

		// 3. ��������� ����� ���������� ���������
		count++;
	}
	catch (bad_alloc e)
	{
		// ���� ������ �� ��������, �� ���������� ������
		cout << e.what() << endl;
	}
}
// ������� �������� � �������� ������� ������
template <class T>
void List<T>::Insert(T _data, int index)
{
	// 1. ��������, ��������� �� �������
	if (!CorrectIndex(index))
		return;

	// 2. ��������, ������� �� � ����� ������ (�� ��������� end)
	if (index == count)
	{
		// �������� ������ �� ��������� end
		AddEnd(_data);
		return;
	}

	// 3. ��������, ������� �� � ������ ������ (����� begin)
	if (index == 0)
	{
		AddBegin(_data);
		return;
	}

	try
	{
		// 4. �������� ������� ����� �������� �������
		Element<T>* itemPrev = Move(index - 1);

		// 5. �������� ������� � ������� �������
		Element<T>* item = Move(index);

		// 6. ������� ����� ������� � �������� ��� � ������
		Element<T>* t = new Element<T>;
		t->data = _data;
		t->next = item;
		t->prev = itemPrev;
		itemPrev->next = t;
		item->prev = t;

		// 7. ��������� ���������� ���������
		count++;
	}
	catch (bad_alloc e)
	{
		// ���� ������ �� ��������, �� ������� ��������� ���������
		cout << e.what() << endl;
	}
}
// ������� ������� � �������� �������,
// ������� ���������� � 0
template <class T>
void List<T>::Del(int index)
{
	// 1. ��������, ���� �� �������� � ������
	if (count == 0) return;

	// 2. �����, ���� ������� ������� �����������
	if (!CorrectIndex(index))
		return;

	// 3. ������� � ���������� ��������
	Element<T>* item = Move(index);

	// 4. �������� ���������� �������
	Element<T>* itemPrev = item->prev;

	// 5. �������� ��������� �������
	Element<T>* itemNext = item->next;

	// 6. ��������, ��������� �� �� ������ ������� ������
	if ((count > 1) && (itemPrev != nullptr))
		itemPrev->next = itemNext; // ������ ������� item

	  // 7. ��������, ��������� �� �� ��������� ������� ������
	if ((itemNext != nullptr) && (count > 1))
		itemNext->prev = itemPrev;

	// 8. ���� ��������� ������ �������
	if (index == 0)
		begin = itemNext;

	// 9. ���� ��������� ��������� �������
	if (index == count - 1)
		end = itemPrev;

	// 10. ������� ������� item
	delete item;

	// 11. ��������� ����� ���������� ���������
	count--;
}
// ������� ������
template <class T>
void List<T>::Clear()
{
	// ����� count ��� ������� ������ ������� ������
	int n = count; // ������� ����� �� count - �����!
	for (int i = 0; i < n; i++)
		Del(0);
}
// �������������� ������
template <class T>
void List<T>::Reverse()
{
	List<T> L;
	Element<T>* t = begin;

	// ���� ������������ ������,
	// ������� ����������� � ������ ������
	while (t != nullptr)
	{
		L.AddBegin(t->data);
		t = t->next;
	}
	*this = L;
}
// ����� ������
template <class T>
void List<T>::Print(string msg)
{
	cout << msg << " => ";

	Element<T>* t = begin;
	for (int i = 0; i < count; i++)
	{
		cout << t->data << " ";
		t = t->next;
	}
	cout << endl;
}
// �������� ���������� ��������� ������
template <class T>
int List<T>::Count()
{
	return count;
}
// �������� + - ������������ �������
template <class T>
List<T>& List<T>::operator+(const List<T>& obj)
{
	// 1. �������� ������ � ������ obj
	Element<T>* t = obj.begin;

	// 2. �������� � ���������� ������ �������� t
	while (t != nullptr)
	{
		AddEnd(t->data);
		t = t->next;
	}

	// 3. ������� ������������ ������
	return *this;
}
// �������� ��������� ������� �� ���������
template <class T>
bool List<T>::operator==(const List<T>& obj)
{
	// 1. ������� �������� ������� �������
	if (count != obj.count)
		return false;

	// 2. ���� ������� ���������, �� �������� �����������
	Element<T>* t1 = begin;
	Element<T>* t2 = obj.begin;

	while (t1 != nullptr)
	{
		// ��� ������ ������� ���� �� ���� ������������, �� ����� � ����� false
		if (t1->data != t2->data)
			return false;

		t1 = t1->next;
		t2 = t2->next;
	}

	return true;
}
// �������� ��������� ������� �� �����������
template <class T>
bool List<T>::operator!=(const List<T>& obj)
{
	// ������������ �������� ��������� ==
	return !(*this == obj);
}

// �������� >=
template <class T>
bool List<T>::operator>=(const List<T>& obj)
{
	// 1. �������� ���������� ���������
	if (count > obj.count)
		return true;

	// 2. �������� �� ����������
	if (*this == obj)
		return true;

	return false;
}
// �������� <=
template <class T>
bool List<T>::operator<=(const List<T>& obj)
{
	// 1. ��������� �� ���������� ��������� � ������
	if (count < obj.count)
		return true;

	// 2. ��������� �� ����������
	if (*this == obj)
		return true;

	return false;
}


int main()
{
	// ����
	List<double> L1; // ������� ������

	// �������� �������� � ������
	L1.AddBegin(2.0);
	L1.AddBegin(1.0);
	L1.AddEnd(3.0);
	L1.AddEnd(4.0);
	L1.Print("L1: ");

	// �������� ������� � �������� �������
	L1.Insert(-2.5, 2);
	L1.Print("L1.Insert: ");

	// ����������� �����������
	List<double> L2 = L1;
	L2.Print("L2: ");

	// �������� �����������
	List<double> L3;
	L3 = L2;
	L3.Print("L3: ");

	// �������� �������
	double x = L1.GetElement(3);
	cout << "x = " << x << endl;

	// ���������� ����� �������
	L3.SetElement(100.55, 0);
	L3.Print("L3: ");

	// �������� ��� ������
	if (L1 == L3)
		cout << "L1==L2" << endl;
	else
		cout << "L1!=L2" << endl;

	// �������������� ������
	L1.Reverse();
	L1.Reverse();
	L1.Print("L1: ");
	return 0;
}