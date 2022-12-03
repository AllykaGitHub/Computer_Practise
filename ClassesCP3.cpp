//main.cpp
#include "personCP3.h"
#include <iostream>
#include <cstring>
using namespace std;
const int SIZE = 4;


Person::~Person()
{
}
void Person::Show() const
{
	cout << "Firstname: " << firstname << endl;
	cout << "Lastname: " << lastname << endl;
}

double Gunslinger::Draw() const
{
	return time;
}
void Gunslinger::Show() const
{
	cout << "Category: Gunslinger\n";
	Person::Show();
	cout << "Gun out time: " << time << endl;
	cout << "Nicks: " << nick << endl;
}

int PokerPlayer::Draw() const
{
	return (rand() % 52);
}
void PokerPlayer::Show() const
{
	cout << "Category: PokerPlayer\n";
	Person::Show();
}

double BadDude::Gdraw() const
{
	return Gunslinger::Draw();
}
int BadDude::Cdraw() const
{
	return PokerPlayer::Draw();
}
void BadDude::Show() const
{
	cout << "Category: BadDude\n";
	Gunslinger::Show();
	cout << "Next card: " << PokerPlayer::Draw() << endl;
}
int main()
{
	Person* p[SIZE];
	int ct;
	for (ct = 0; ct < SIZE; ct++)
	{
		char choice;
		cout << "Enter the person category:\n"
			<< "g: Gunslinger p: PokerPlayer "
			<< "b: BadDude q: quit\n";
		cin >> choice;
		cin.get();
		while (strchr("gpbq", choice) == NULL)
		{
			cout << "Please enter a g,p,b or q: ";
			cin >> choice;
			cin.get();
		}
		if (choice == 'q')
			break;
		string fn, ln;
		double t = 0;
		int n = 0;
		cout << "Enter the first name: ";
		getline(cin, fn);
		cout << "Enter the last name: ";
		getline(cin, ln);
		switch (choice)
		{
		case 'g':
			cout << "Enter the Gun out time: ";
			cin >> t;
			cout << "Enter the nicks: ";
			cin >> n;
			p[ct] = new Gunslinger(fn, ln, t, n);
			break;
		case 'p':
			p[ct] = new PokerPlayer(fn, ln);
			break;
		case 'b':
			cout << "Enter the Gun out time: ";
			cin >> t;
			cout << "Enter the nicks: ";
			cin >> n;
			p[ct] = new BadDude(fn, ln, t, n);
			break;
		}
	}
	cout << "\nHere is your person:\n";
	int i;
	for (i = 0; i < ct; i++)
	{
		cout << endl;
		p[i]->Show();
	}
	for (i = 0; i < ct; i++)
	{
		delete p[i];
	}
	cout << "Bye.\n";
	return 0;
}
