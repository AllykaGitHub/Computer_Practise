#include <iostream>
using namespace std;
class Time

{

	int min, sec;

public:

	Time() { min = 0; sec = 0; } //����������� ��� ����������

	Time(int a) { min = a; sec = 0; } //����������� � ����� ���������� ���� int

	Time(int a, int b) { min = a; sec = b; } //����������� � ����� ���������� ���� int

	Time(Time& time1) { min = time1.min; sec = time1.sec; } //����������� � ���������� ���� Time

	~Time() {} //����������

	int getmin() { return min; } //��������� ���������� �����

	int getsec() { return sec; } //��������� ���������� ������

	void setmin(int a) { min = a; } //��������� ���������� �����

	void setsec(int a) { sec = a; } //��������� ���������� ������

	Time& operator = (Time&); //���������� ��������� ������������

	Time operator - (int sec1); //���������� ��������� "-"

	int operator ==(Time time1); //���������� ��������� "�����"

	int operator !=(Time time1); //���������� ��������� "�� �����"

	friend istream& operator>>(istream& in, Time& time1); //������������� ������� �������� �����

	friend ostream& operator<<(ostream& out, Time time1); //������������� ������� �������� ������

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

	Time a; //����������� �� ���������

	Time b(2); //����������� � ����� ���������� ���� int

	Time c(5, 10); //����������� � ����� ����������� ���� int

	Time d(c); //����������� � ����� ���������� ���� Time

	cout << a << endl << b << endl << c << endl << d << endl; //����� ��������� ����������

	cout << (c == d) << " " << (a == b) << " " << (c != b) << endl;

	//�������� ������� c ����� d; a ����� b; c �� ����� b

	cin >> a; //���� ���������� a

	cin >> b; //���� ���������� b

	c = d ; // ����������� ������������ 

	cout << a << endl << b << endl << c << endl << d << endl; //����� �����������

	m = a.getmin(); //��������� ���������� ����� �� ���������� a

	s = a.getsec(); //��������� ���������� ������ �� ���������� a

	cout << m << " " << s << endl; //����� �����������

	b.setmin(4); //��������� ���������� ����� � ���������� b

	b.setsec(32); //��������� ���������� ������ � ���������� b

	cout << b << endl;

	cin >> ch;

}

