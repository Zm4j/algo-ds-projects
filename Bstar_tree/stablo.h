#ifndef _stablo_h_
#define _stablo_h_

#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class Stablo {

	int m;
	int high = 0;
	int nodes = 0;

	struct struktura {
		vector <string> cvor; //sadrzaj cvora
		vector<struktura*> vektor; //niz pokazivaca na sinove
		vector <int> vektor1; //za 6. zadatak
		struktura* otac; //pokazivac na oca
	};

	struktura* koren = nullptr;

	//void kopiraj(const Stablo&);
	//void premesti(Stablo&);

public:

	Stablo(int m=0) : m(m) {};

	//Stablo(const Stablo& s) { kopiraj(s); }
	//Stablo(Stablo&& s) { premesti(s); }
	//Stablo& operator=(const Stablo&);
	//Stablo& operator=(Stablo&&);

	void brisi();
	~Stablo() { brisi(); }

	void red_stabla(int m1) { m = m1; }
	
	bool pretrazi(string x);
	bool dodaj(string x);
	bool brisi(string x);
	void pisi(Stablo &s);
	int sestizadatak(string x);
	void proba();
	//void stampaj() { cout << koren->brk; }
	
	friend ostream& operator<<(ostream&, const Stablo&);
	//6. zadatak, ako se ide
};

#endif // !_stablo_h_
