//person.h
#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <iostream>
using namespace std;

class Person
{
private:
	string firstname;
	string lastname;
public:
	Person() :firstname("None"), lastname("None") {}
	Person(const string& fn, const string& ln)
		:firstname(fn), lastname(ln) {}
	virtual ~Person() = 0;
	virtual void Show() const = 0;
};

class Gunslinger :virtual public Person
{
private:
	double time;
	int nick;
public:
	Gunslinger(double t = 0, int n = 0)
		:Person(), time(t), nick(n) {}
	Gunslinger(const string& fn, const string& ln, double t = 0, int n = 0)
		:Person(fn, ln), time(t), nick(n) {}
	Gunslinger(const Person& p, double t = 0, int n = 0)
		:Person(p), time(t), nick(n) {}
	double Draw() const;
	void Show() const;
};

class PokerPlayer :virtual public Person
{
public:
	PokerPlayer() :Person() {}
	PokerPlayer(const string& fn, const string& ln)
		:Person(fn, ln) {}
	PokerPlayer(const Person& p) :Person(p) {}
	int Draw() const;
	void Show() const;
};

class BadDude :public Gunslinger, public PokerPlayer
{
public:
	BadDude() {}
	BadDude(const string& fn, const string& ln, double t = 0, int n = 0)
		:Person(fn, ln), Gunslinger(fn, ln, t, n), PokerPlayer(fn, ln) {}
	BadDude(const Person& p, double t = 0, int n = 0)
		:Person(p), Gunslinger(p, t, n), PokerPlayer(p) {}
	BadDude(const Gunslinger& g)
		:Person(g), Gunslinger(g), PokerPlayer(g) {}
	BadDude(const PokerPlayer& p, double t = 0, int n = 0)
		:Person(p), Gunslinger(p, t, n), PokerPlayer(p) {}
	double Gdraw() const;
	int Cdraw() const;
	void Show() const;
};

#endif
