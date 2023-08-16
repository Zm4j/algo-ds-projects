#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <sstream>
/*
using namespace std;

struct struktura {
	unsigned int indeks=1e9;
	string imeprezime;
	vector <string> listapredmeta;
};

struct baket {
	int dubina = 1;
	vector <struktura> strukt;
};

void ispis(vector <baket*> tabela,int k) {
	for (int i = 0; i < tabela.size(); i++) {
		cout << i << ". ";
		for (int j = 0; j < tabela[i]->strukt.size(); j++) {
			cout << tabela[i]->strukt[j].indeks;
			cout << ' ' << tabela[i]->strukt[j].imeprezime << ": ";
			for (int k = 0; k < tabela[i]->strukt[j].listapredmeta.size(); k++) {
				cout << tabela[i]->strukt[j].listapredmeta[k] << ' ';
			}
			cout << "| ";
		}
		cout << '(' << tabela[i]->dubina << ')';
		cout << '\n';
	}
}

struktura unos() {
	cout << "uneti u jednom redu odvojeno spejsom\n";
	struktura str;
	//cin >> str.indeks;
	string s;
	
	getline(cin, s);
	stringstream test(s);
	int i = 0;
	while (getline(test, s, ' ')) {
		if (i == 0) str.indeks = stoi(s);
		if (i == 1) str.imeprezime = s;
		if (i == 2) str.imeprezime += " " + s;
		if (i > 2) str.listapredmeta.push_back(s);
		i++;
	}
	
	return str;
}

int main(){
	int k;
	int b;
	cout << "k, b: ";
	cin >> k >> b; cin.ignore();

	vector <baket*> tabela;
	for (int i = 0; i < pow(2, b); i++) {
		baket* b = new baket;
		tabela.push_back(b);
	}

	while (1) {
		struktura str=unos();

		int pp = str.indeks % ((int)pow(2, b));
		tabela[pp]->strukt.push_back(str);

		if (tabela[pp]->strukt.size() <= k) { ispis(tabela, k); continue;}

		// dodavanje i punjenje novog baketa
		vector <struktura> vektor = tabela[pp]->strukt;
		tabela[pp]->strukt.clear();
		tabela[pp]->dubina++;
		baket* bak = new baket;
		bak->dubina = tabela[pp]->dubina;
		for (auto i:vektor) {
			if (i.indeks % (int)pow(2, tabela[pp]->dubina) == i.indeks % (int)pow(2, tabela[pp]->dubina - 1)) tabela[pp]->strukt.push_back(i);
			else bak->strukt.push_back(i);
		}

		

		// dodela baketa nekom kurcu
		if (tabela[pp]->dubina > b) {
			//cout << "IZLAZ";
			b = tabela[pp]->dubina;
			int h = tabela.size();
			for (int i = 0; i < h; i++) {
				if (i == pp) tabela.push_back(bak);
				else tabela.push_back(tabela[i]);
			}
		}
		
		else {
			//cout << "IZLAZ1";
			//indeks%pow(2,dubina-1) && not 
			for (int i = 0; i < tabela.size(); i++) {
				if (i % (int)pow(2, tabela[pp]->dubina - 1) != str.indeks % (int)pow(2, tabela[pp]->dubina - 1)) continue;
				if ((i / ((int)pow(2, tabela[pp]->dubina - 1))) % 2) tabela[i] = bak;
			}
		}

		ispis(tabela, k);

	}
}
*/
//3 1 16 4 6 22 24 10 31 7 9 20 26 11

