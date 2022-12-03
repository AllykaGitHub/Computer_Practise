#include <iostream>
using namespace std;
class Time

{

	int min, sec;

public:

	Time() { min = 0; sec = 0; } //конструктор без параметров

	Time(int a) { min = a; sec = 0; } //конструктор с одним параметром типа int

	Time(int a, int b) { min = a; sec = b; } //конструктор с двумя параметром типа int

	Time(Time& time1) { min = time1.min; sec = time1.sec; } //конструктор с параметром типа Time

	~Time() {} //деструктор

	int getmin() { return min; } //получение количества минут

	int getsec() { return sec; } //получение количества секунд

	void setmin(int a) { min = a; } //установка количества минут

	void setsec(int a) { sec = a; } //установка количества секунд

	Time& operator = (Time&); //перегрузка оператора присваивания

	Time operator - (int sec1); //перегрузка оператора "-"

	int operator ==(Time time1); //перегрузка оператора "равно"

	int operator !=(Time time1); //перегрузка оператора "не равно"

	friend istream& operator>>(istream& in, Time& time1); //дружественный внешний оператор ввода

	friend ostream& operator<<(ostream& out, Time time1); //дружественный внешний оператор вывода

};



Time & Time::operator =(Time & time1)

{

	min = time1.min;

	sec = time1.sec;

	return *this;

}

Time Time::operator - (int sec1)

{

	Time time1;

	time1.min = (60 * min + sec - sec1) / 60;

	time1.sec = (60 * min + sec - sec1) % 60;

	return time1;

}

int Time::operator == (Time time1)

{

	return min == time1.min && sec == time1.sec;

}

int Time::operator != (Time time1)

{

	return min != time1.min || sec != time1.sec;

}


istream & operator >>(istream & in, Time & time1)

{

	cout << "input minutes\n";

	in >> time1.min;

	cout << "input seconds\n";

	in >> time1.sec;

	return in;

}

ostream& operator <<(ostream& out, Time time1)

{

	out << time1.min << ":" << time1.sec;

	return out;

}

void main()

{

	char ch;

	int m, s;

	Time a; //конструктор по умолчанию

	Time b(2); //конструктор с одним параметром типа int

	Time c(5, 10); //конструктор с двумя параметрами типа int

	Time d(c); //конструктор с одним параметром типа Time

	cout << a << endl << b << endl << c << endl << d << endl; //вывод созданных переменных

	cout << (c == d) << " " << (a == b) << " " << (c != b) << endl;

	//проверка условий c равно d; a равно b; c не равно b

	cin >> a; //ввод переменной a

	cin >> b; //ввод переменной b

	c = d ; // конструктор присваивания 

	cout << a << endl << b << endl << c << endl << d << endl; //вывод результатов

	m = a.getmin(); //получение количества минут из переменной a

	s = a.getsec(); //получение количества секунд из переменной a

	cout << m << " " << s << endl; //вывод результатов

	b.setmin(4); //установка количества минут в переменную b

	b.setsec(32); //установка количества секунд в переменную b

	cout << b << endl;

	cin >> ch;

}

