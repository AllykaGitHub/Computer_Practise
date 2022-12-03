#include <iostream>
using namespace std;

// Структура, описывающая один элемент (узел)
template <class T>
struct Element
{
	T data; // данные
	Element<T>* next; // адрес следующего элемента в списке
	Element<T>* prev; // адрес предыдущего элемента в списке
};

// Клас, реализующий двусвязный список
template <class T>
class List
{
private:
	Element<T>* begin; // указатель на первый элемент списка
	Element<T>* end; // указатель на последний элемент списка
	int count; // количество элементов в списке

	// Метод, возвращающий элемент в заданной позиции,
	// считается что позиция корректна.
	Element<T>* Move(int index);

	// Метод, копирующий список
	void Copy(const List<T>& obj);

	// Метод, проверяющий корректность позиии (индекса) в списке
	bool CorrectIndex(int index);

public:
	// Конструктор
	List();

	// Конструктор копирования
	List(const List& obj);

	// Оператор копирования
	List<T>& operator=(const List& obj);

	// Деструктор
	~List();

	// ---------- Методы доступа к отдельным элементам списка --------
	// Получить элемент списка по индексу
	T GetElement(int index);

	// Изменить значение элемента в заданной позиции
	void SetElement(T _data, int index);

	// ---------- Методы изменения размера списка ------------
	// Добавить элемент в конец списка
	void AddEnd(T _data);

	// Добавить элемент в начало списка
	void AddBegin(T _data);

	// Вставка элемента в заданную позицию списка
	void Insert(T _data, int index);

	// Удалить элемент в заданной позиции,
	// позиция нумеруется с 0
	void Del(int index);

	// Очистка списка
	void Clear();

	// Реверсирование списка
	void Reverse();

	// Вывод списка
	void Print(string msg);

	// Получить количество элементов списка
	int Count();

	// ------------------------------------------
	// Перегрузка операторов
	// Операция + - конкатенация списков
	List<T>& operator+(const List<T>& obj);

	// Операция сравнения списков на равенство
	bool operator==(const List& obj);

	// Операция сравнения списков на неравенство
	bool operator!=(const List& obj);

	// Операция >=
	bool operator>=(const List& obj);

	// Операция <=
	bool operator<=(const List& obj);

	// Операция >
	bool operator>(const List& obj);

	// Операция <
	bool operator<(const List& obj);
};

// Получить элемент в заданной позиции
template <class T>
Element<T>* List<T>::Move(int index)
{
	// 1. Установить указатель на начало списка
	Element<T>* t = begin;

	// 2. Перемотать в позицию index
	for (int i = 0; i < index; i++)
		t = t->next;

	// 3. Вернуть указатель
	return t;
}
// Метод, делающий копию из списка
template <class T>
void List<T>::Copy(const List<T>& obj)
{
	// 1. Очистить список (освободить память)
	Clear();

	// 2. Цикл копирования this <= obj
	Element<T>* t = obj.begin;

	while (t != nullptr)
	{
		AddEnd(t->data);
		t = t->next;
	}
}
// Метод, проверяющий корректность позиции (индекса) в списке
template <class T>
bool List<T>::CorrectIndex(int index)
{
	return (index >= 0) && (index < count);
}
// Конструктор
template <class T>
List<T>::List()
{
	// Создать пустой список
	begin = end = nullptr;
	count = 0;
}
// Конструктор копирования
template <class T>
List<T>::List(const List& obj)
{
	// Сделать копию из списка
	Copy(obj);
}
// Оператор копирования
template <class T>
List<T>& List<T>::operator=(const List& obj)
{
	Copy(obj);
	return *this;
}
// Деструктор
template <class T>
List<T>::~List()
{
	Clear(); // очистить список
}
// Получить элемент списка по индексу
template <class T>
T List<T>::GetElement(int index)
{
	// Проверка, корректен ли индекс,
	// если индекс не корректен, сгенерировать исключение
	if (!CorrectIndex(index))
		throw out_of_range("Incorrect index.");

	// Если индекс корректен, то вернуть элемент
	Element<T>* t = Move(index);
	return t->data;
}
// Изменить значение элемента в указанной позиции
template <class T>
void List<T>::SetElement(T _data, int index)
{
	// Проверка, корректна ли позиция
	if (!CorrectIndex(index))
		return;

	// Получить элемент по позиции и изменить его значение
	Element<T>* t = Move(index);
	t->data = _data;
}
// Добавить элемент в конец списка
template <class T>
void List<T>::AddEnd(T _data)
{
	try
	{
		// 1. Создать новый элемент с данными _data
		Element<T>* t = new Element<T>;
		t->next = nullptr; // следующего элемента нет
		t->prev = end; // установить предыдущий элемент
		t->data = _data; // записать данные

		// 2. Заполнить поле next пока что последнего элемента
		if (end != nullptr)
			end->next = t;

		// 3. Проверка, есть ли в списке элементы
		if (count == 0)
		{
			// если элементов нет,
			// то это одновременно и начало и конец списка
			begin = end = t;
		}
		else
		{
			// если элементы в списке есть, то это конец списка
			end = t;
		}

		// 3. Увеличить общее количество элементов
		count++;
	}
	catch (bad_alloc e)
	{
		// Если память не выделена, то вывести системное сообщение
		cout << e.what() << endl;
	}
}
// Добавить элемент в начало списка
template <class T>
void List<T>::AddBegin(T _data)
{
	try
	{
		// 1. Создать новый элемент (новую ячейку памяти)
		// и заполнить его данными
		Element<T>* t = new Element<T>;
		t->data = _data; // данные
		t->prev = nullptr; // предыдущего элемента нет

		// следующий элемент указывает на предыдущий первый
		t->next = begin;

		// 2. Есть ли элементы в списке?
		if (count > 0)
		{
			// если есть, то перенаправить предыдущее начало списка
			begin->prev = t;
			begin = t;
		}
		else
		{
			// если элементов нет, то начало и конец есть тем самым элементом
			begin = end = t;
		}

		// 3. Увеличить общее количество элементов
		count++;
	}
	catch (bad_alloc e)
	{
		// если память не выделена, то обработать ошибку
		cout << e.what() << endl;
	}
}
// Вставка элемента в заданную позицию списка
template <class T>
void List<T>::Insert(T _data, int index)
{
	// 1. Проверка, корректна ли позиция
	if (!CorrectIndex(index))
		return;

	// 2. Проверка, вставка ли в конец списка (по указателю end)
	if (index == count)
	{
		// Добавить данные по указателю end
		AddEnd(_data);
		return;
	}

	// 3. Проверка, вставка ли в начало списка (перед begin)
	if (index == 0)
	{
		AddBegin(_data);
		return;
	}

	try
	{
		// 4. Получить элемент перед позицией вставки
		Element<T>* itemPrev = Move(index - 1);

		// 5. Получить элемент в позиции вставки
		Element<T>* item = Move(index);

		// 6. Создать новый элемент и вставить его в список
		Element<T>* t = new Element<T>;
		t->data = _data;
		t->next = item;
		t->prev = itemPrev;
		itemPrev->next = t;
		item->prev = t;

		// 7. Увеличить количество элементов
		count++;
	}
	catch (bad_alloc e)
	{
		// Если память не выделена, то вывести системное сообщение
		cout << e.what() << endl;
	}
}
// Удалить элемент в заданной позиции,
// позиция нумеруется с 0
template <class T>
void List<T>::Del(int index)
{
	// 1. Проверка, есть ли элементы в списке
	if (count == 0) return;

	// 2. Игнор, если позиция указана неправильно
	if (!CorrectIndex(index))
		return;

	// 3. Перейти к удаляемому элементу
	Element<T>* item = Move(index);

	// 4. Получить предыдущий элемент
	Element<T>* itemPrev = item->prev;

	// 5. Получить следующий элемент
	Element<T>* itemNext = item->next;

	// 6. Проверка, удаляется ли не первый элемент списка
	if ((count > 1) && (itemPrev != nullptr))
		itemPrev->next = itemNext; // обойти элемент item

	  // 7. Проверка, удаляется ли не последний элемент списка
	if ((itemNext != nullptr) && (count > 1))
		itemNext->prev = itemPrev;

	// 8. Если удаляется первый элемент
	if (index == 0)
		begin = itemNext;

	// 9. Если удаляется последний элемент
	if (index == count - 1)
		end = itemPrev;

	// 10. Удалить элемент item
	delete item;

	// 11. Уменьшить общее количество элементов
	count--;
}
// Очистка списка
template <class T>
void List<T>::Clear()
{
	// Нужно count раз удалить первый элемент списка
	int n = count; // сделать копию из count - важно!
	for (int i = 0; i < n; i++)
		Del(0);
}
// Реверсирование списка
template <class T>
void List<T>::Reverse()
{
	List<T> L;
	Element<T>* t = begin;

	// цикл формирования списка,
	// элемент добавляется в начало списка
	while (t != nullptr)
	{
		L.AddBegin(t->data);
		t = t->next;
	}
	*this = L;
}
// Вывод списка
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
// Получить количество элементов списка
template <class T>
int List<T>::Count()
{
	return count;
}
// Операция + - конкатенация списков
template <class T>
List<T>& List<T>::operator+(const List<T>& obj)
{
	// 1. Получить доступ к списку obj
	Element<T>* t = obj.begin;

	// 2. Добавить к временному списку элементы t
	while (t != nullptr)
	{
		AddEnd(t->data);
		t = t->next;
	}

	// 3. Вернуть объединенный список
	return *this;
}
// Операция сравнения списков на равенство
template <class T>
bool List<T>::operator==(const List<T>& obj)
{
	// 1. Сначала сравнить размеры списков
	if (count != obj.count)
		return false;

	// 2. Если размеры одинаковы, то сравнить поэлементно
	Element<T>* t1 = begin;
	Element<T>* t2 = obj.begin;

	while (t1 != nullptr)
	{
		// Как только найдено хотя бы одно несовпадение, то выход с кодом false
		if (t1->data != t2->data)
			return false;

		t1 = t1->next;
		t2 = t2->next;
	}

	return true;
}
// Операция сравнения списков на неравенство
template <class T>
bool List<T>::operator!=(const List<T>& obj)
{
	// Использовать оператор сравнения ==
	return !(*this == obj);
}

// Операция >=
template <class T>
bool List<T>::operator>=(const List<T>& obj)
{
	// 1. Сравнить количество элементов
	if (count > obj.count)
		return true;

	// 2. Сравнить по содержанию
	if (*this == obj)
		return true;

	return false;
}
// Операция <=
template <class T>
bool List<T>::operator<=(const List<T>& obj)
{
	// 1. Сравнение по количеству элементов в списке
	if (count < obj.count)
		return true;

	// 2. Сравнение по содержанию
	if (*this == obj)
		return true;

	return false;
}


int main()
{
	// Тест
	List<double> L1; // Создать список

	// Добавить элементы в список
	L1.AddBegin(2.0);
	L1.AddBegin(1.0);
	L1.AddEnd(3.0);
	L1.AddEnd(4.0);
	L1.Print("L1: ");

	// Вставить элемент в заданную позицию
	L1.Insert(-2.5, 2);
	L1.Print("L1.Insert: ");

	// Конструктор копирования
	List<double> L2 = L1;
	L2.Print("L2: ");

	// Оператор копирования
	List<double> L3;
	L3 = L2;
	L3.Print("L3: ");

	// Получить элемент
	double x = L1.GetElement(3);
	cout << "x = " << x << endl;

	// Установить новый элемент
	L3.SetElement(100.55, 0);
	L3.Print("L3: ");

	// Сравнить два списка
	if (L1 == L3)
		cout << "L1==L2" << endl;
	else
		cout << "L1!=L2" << endl;

	// Реверсирование списка
	L1.Reverse();
	L1.Reverse();
	L1.Print("L1: ");
	return 0;
}