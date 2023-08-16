#include "HashTable.h"

struktura* HashTable::findkey(unsigned int k1){
	int pp = pow(2, p);
	int pp1 = (pp + k1 % pp) % pp;
	int ii = 1;
	int pp2 = pp1;
	while (1) {
		for (int i = 0; i < k; i++) {
			if (tabela[pp1][i].indeks == 1e9) return nullptr;
			if (tabela[pp1][i].indeks == k1) return &tabela[pp1][i];
		}
		//pp1 = (pp1 + 1) % pp;
		//if (pp1 == pp2) return nullptr;
		
		izvedena izv;
		pp1 = izv.getadres(pp2, ii, 1, pp);
		ii++;

	}
	return nullptr;
}

bool HashTable::insertkey(unsigned int k1, struktura s){
	s.indeks = k1;
	int pp = pow(2, p);
	int pp1 = (pp + k1 % pp) % pp;
	int ii=1;
	int pp2 = pp1;
	while (ii<=pp) {
		for (int i = 0; i < k; i++) {
			if (tabela[pp1][i].indeks >= 1e9) {
				tabela[pp1][i] = s;
				keycounter++;
				return true;
			}
			if (tabela[pp1][i].indeks == k1) return false;
		}
		//pp1 = (pp1 + 1) % pp;
		//if (pp1 == pp2) return false;
		
		izvedena izv;
		pp1 = izv.getadres(pp2,ii,1,pp);
		ii++;
		//cout << pp1 << "|\n";
	}
	return false;
}

bool HashTable::deletekey(unsigned int k1){
	int pp = pow(2, p);
	int pp1 = (pp + k1 % pp) % pp;
	int pp2 = pp1;
	int ii = 1;
	struktura *s = new struktura;
	s->indeks = 696969420;
	while (1) {
		for (int i = 0; i < k; i++) {
			if (tabela[pp1][i].indeks >= 1e9) {
				bool h = s->indeks != 696969420;
				s->indeks = 1e9+1;
				if (h) keycounter--;
				return h;
			}
			if (tabela[pp1][i].indeks%pp == k1%pp) {
				if (s->indeks == 696969420) {
					s = &tabela[pp1][i];
				}
				else {
					*s = tabela[pp1][i];
					s = &tabela[pp1][i];
				}
			}
		}
		//pp1 = (pp1 + 1) % pp;
		//if (pp1 == pp2) return false;

		izvedena izv;
		pp1 = izv.getadres(pp2, ii, 1, pp);
		ii++;

	}
	return false;
}

void HashTable::clear(){
	for (int i = 0; i < pow(2, p); i++)
		for (int j = 0; j < k; j++) if(tabela[i][j].indeks != 1e9) tabela[i][j].indeks=1e9+1;
	keycounter = 0;
}

int HashTable::keycount(){
	return keycounter;
}

int HashTable::tablesize(){
	return k*pow(2,p);
}

double HashTable::fillratuio(){
	return (double)((double)keycount() / (double)tablesize());
}

void HashTable::dodajispit(unsigned int k1,string str){
	struktura* s = findkey(k1);
	if (s == nullptr) return;
	//cout << s->indeks;
	s->listapredmeta.push_back(str);
}

void HashTable::brisiispit(unsigned int k1, string str){
	struktura* s = findkey(k1);
	if (s == nullptr) return;
	bool flag = 0;
	for (int i = 0; i < s->listapredmeta.size()-1; i++) {
		if (s->listapredmeta[i] == str) {
			flag = 1;
			string str1 = s->listapredmeta[i];
			s->listapredmeta[i] = s->listapredmeta[i + 1];
			s->listapredmeta[i + 1] = str1;
		}
	}
	if(flag==1 || s->listapredmeta[s->listapredmeta.size()-1]==str) s->listapredmeta.pop_back();
}

ostream& operator<<(ostream& os, HashTable& h){
	int g = pow(2, h.p);
	//cout << g;
	for (int i = 0; i < g; i++) {
		for (int j = 0; j < h.k; j++) {
			//if (h.tabela == nullptr || h.tabela[i] == nullptr) { cout << "DA\n"; continue; }
			unsigned int& pom = h.tabela[i][j].indeks;
			if (pom == 1e9) os << "EMPTY ";
			if (pom == 1e9 + 1) os << "DELETED ";
			
			if (pom < 1e9) {
				os << h.tabela[i][j].indeks << ' ' << h.tabela[i][j].imeprezime << ' ';
				for (int k = 0; k < h.tabela[i][j].listapredmeta.size(); k++) {
					os << h.tabela[i][j].listapredmeta[k] << ' ';
				}
			}
			os << '|';
		}
		os << '\n';
	}
	return os;
}
