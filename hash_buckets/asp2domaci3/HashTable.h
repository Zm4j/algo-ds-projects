#pragma once

#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

struct struktura {
	unsigned int indeks=1e9;
	string imeprezime;
	vector<string> listapredmeta;
};

class apstraktna {
private:
public:
	virtual int getadres(int pp1, int i, int c, int pp) = 0;
};

class izvedena: public apstraktna {
private:
public:
	virtual int getadres(int pp1, int i, int c, int pp) {
		return ((pp1 + i * i * c) % pp + pp) % pp;
	}
};

class HashTable{
private:

	int k, p;
	int keycounter = 0;
	struktura** tabela;

public:

	friend class apstraktna;

	HashTable(int k1,int p1) {
		k = k1; p = p1;
		int g = pow(2, p1);
		tabela = new struktura* [g];
		for (int i = 0; i < g; i++) tabela[i] = new struktura [k];
	}

	struktura* findkey(unsigned int k);
	bool insertkey(unsigned int k, struktura s);
	bool deletekey(unsigned int k);
	void clear();
	int keycount();
	int tablesize();
	double fillratuio();
	void dodajispit(unsigned int k1,string str);
	void brisiispit(unsigned int k1,string str);
	friend ostream& operator<<(ostream& os, HashTable& h);
};

