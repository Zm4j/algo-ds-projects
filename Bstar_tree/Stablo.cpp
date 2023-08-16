#include "stablo.h"

void Stablo::brisi(){
	queue <struktura*> niz1;
	if (koren!=nullptr) niz1.push(koren);
	while (niz1.size()>0) {
		Stablo::struktura* temp1 = niz1.front();
		niz1.pop();
		for (int i = 0; i < temp1->vektor.size(); i++) {
			if (temp1->vektor[i] != nullptr) niz1.push(temp1->vektor[i]);
		}
		free(temp1);
	}
	koren = nullptr;
}

bool Stablo::pretrazi(string x){
	Stablo::struktura* temp = koren;
	Stablo::struktura* naslismo = nullptr;
	bool flg = 0;
	while (temp != nullptr) {
		flg = 0;
		for (int j = 0; j < temp->cvor.size(); j++) {
			if (temp->cvor[j] == x) return true;
			if (temp->cvor[j] > x) {
				temp = temp->vektor[j];
				flg = 1;
				break;
			}
		}
		if(flg==0) temp = temp->vektor[temp->vektor.size() - 1];
	}
	return false;
}

bool Stablo::dodaj(string x){

	vector <int> stek;
	int brojukorenu=2*((2*m-2)/3);

	if (koren == nullptr) {
		Stablo::struktura *kik = new (struktura);
		kik->otac = nullptr;
		kik->vektor.push_back(nullptr);
		kik->vektor.push_back(nullptr);
		kik->vektor1.push_back(0);
		kik->vektor1.push_back(0);
		kik->cvor.push_back(x);

		koren = kik;
		return true;
	}

	Stablo::struktura* temp = koren;
	Stablo::struktura* naslismo = nullptr;
	int indeks = 0;
	int pozicija = 0;
	bool flg = 0;

	while (temp != nullptr) {
		flg = 0;
		indeks = pozicija;
		for (int j = 0; j < temp->cvor.size(); j++) {
			if (temp->cvor[j] == x) return false;
			if (temp->cvor[j] > x) {
				stek.push_back(j);
				if (temp->vektor[j] == nullptr) {
					naslismo = temp;
				}
				else {
					//temp->vektor1[j]++;
				}
				pozicija = j;
				temp = temp->vektor[j];
				flg = 1;
				break;
			}
		}
		if (flg==0) {
			stek.push_back(temp->vektor.size() - 1);
			if (temp->vektor[temp->vektor.size() - 1] == nullptr) {
				naslismo = temp;
			}
			else {
				//temp->vektor1[temp->vektor.size() - 1]++;
			}
			pozicija = temp->vektor.size() - 1;
			temp = temp->vektor[temp->vektor.size() - 1];
		}
	}

	stek.pop_back();

	if (naslismo->cvor.size() < m-1 || (naslismo->otac==nullptr && naslismo->cvor.size() < brojukorenu)) {

		string y;
		for (int i = pozicija; i < naslismo->cvor.size(); i++) {
			y = naslismo->cvor[i];
			naslismo->cvor[i] = x;
			x = y;
		}
		naslismo->cvor.push_back(x);
		naslismo->vektor.push_back(nullptr);
		naslismo->vektor1.push_back(0);
		
		return true;
	}

	if (naslismo->otac != nullptr && indeks < naslismo->otac->cvor.size() && ( naslismo->otac->vektor[indeks + 1]->cvor.size() < m - 1)) {
		string y=x;

		for (int i = pozicija; i < naslismo->cvor.size(); i++) {
			y = naslismo->cvor[i];
			naslismo->cvor[i] = x;
			x = y;
		}
		
		//jos jedna rotacija

		y = naslismo->otac->cvor[indeks];
		naslismo->otac->cvor[indeks] = x;
		x = y;

		naslismo = naslismo->otac->vektor[indeks + 1];
		naslismo->cvor.push_back("");
		for (int i = 0; i < naslismo->cvor.size(); i++) {
			y = naslismo->cvor[i];
			naslismo->cvor[i] = x;
			x = y;
		}
		naslismo->vektor.push_back(nullptr);
		naslismo->vektor1.push_back(0);

		naslismo->otac->vektor1[indeks + 1]++;
		naslismo->otac->vektor1[indeks]--;

		return true;
	}
	
	if (naslismo->otac != nullptr && indeks > 0 && ( naslismo->otac->vektor[indeks - 1]->cvor.size() < m - 1)) {
		
		string y=x;
		if (pozicija) y = naslismo->cvor[0];

		for (int i = 0; i < pozicija; i++) {
			if (i < naslismo->cvor.size() - 1) {
				if (naslismo->cvor[i+1] < x) naslismo->cvor[i] = naslismo->cvor[i + 1];
				else {
					naslismo->cvor[i] = x;
					break;
				}
			}
			else {
				naslismo->cvor[i] = x;
			}
		}

		x = naslismo->otac->cvor[indeks-1];
		naslismo->otac->cvor[indeks-1] = y;

		naslismo = naslismo->otac->vektor[indeks - 1];
		naslismo->cvor.push_back(x);
		naslismo->vektor.push_back(nullptr);
		naslismo->vektor1.push_back(0);

		naslismo->otac->vektor1[indeks - 1]++;
		naslismo->otac->vektor1[indeks]--;

		return true;
	}

	{
		string y;
		for (int i = pozicija; i < naslismo->cvor.size(); i++) {
			y = naslismo->cvor[i];
			naslismo->cvor[i] = x;
			x = y;
		}
		naslismo->cvor.push_back(x);
		naslismo->vektor.push_back(nullptr);
		naslismo->vektor1.push_back(0);
	}

	while (naslismo != nullptr && naslismo->cvor.size() > m - 1) {
		
		if (naslismo->otac == nullptr) {
			if (naslismo->cvor.size() <= brojukorenu) return true;
			Stablo::struktura* kik1 = new (struktura);
			Stablo::struktura* kik3 = new (struktura);
			
			vector <string> vek;
			vector <struktura*> vek1;
			vector <int> vek2;
			
			vek2.push_back(0);
			vek2.push_back(0);

			kik1->otac = naslismo;
			kik3->otac = naslismo;

			for (int i = 0; i < naslismo->cvor.size(); i++) {
				if (i < (brojukorenu) / 2) {
					vek2[0]++;
					kik1->cvor.push_back(naslismo->cvor[i]);
					if (kik1->cvor.size() == 1) {
						vek2[0] += naslismo->vektor1[0];
						kik1->vektor.push_back(naslismo->vektor[0]);
						kik1->vektor1.push_back(naslismo->vektor1[0]);
						if(naslismo->vektor[0])naslismo->vektor[0]->otac = kik1;
					}
					vek2[0] += naslismo->vektor1[i + 1];
					kik1->vektor.push_back(naslismo->vektor[i + 1]);
					kik1->vektor1.push_back(naslismo->vektor1[i + 1]);
					if (naslismo->vektor[i + 1])naslismo->vektor[i + 1]->otac = kik1;
				}
				if (i == (brojukorenu) / 2) {
					
					vek.push_back(naslismo->cvor[i]);

					vek1.push_back(kik1);
					vek1.push_back(kik3);
				}
				if(i > (brojukorenu) / 2) {
					vek2[1]++;
					kik3->cvor.push_back(naslismo->cvor[i]);
					if (kik3->cvor.size() == 1) {
						vek2[1] += naslismo->vektor1[i];
						kik3->vektor.push_back(naslismo->vektor[i]);
						kik3->vektor1.push_back(naslismo->vektor1[i]);
						if (naslismo->vektor[i])naslismo->vektor[i]->otac = kik3;
					}
					vek2[1] += naslismo->vektor1[i + 1];
					kik3->vektor.push_back(naslismo->vektor[i + 1]);
					kik3->vektor1.push_back(naslismo->vektor1[i + 1]);
					if (naslismo->vektor[i + 1])naslismo->vektor[i + 1]->otac = kik3;
				}
			}

			koren->vektor = vek1;
			koren->cvor = vek;
			koren->vektor1 = vek2;
			//return false;
			return true;
		}

		else {
			Stablo::struktura* idemo = new (Stablo::struktura);
			idemo->otac = naslismo->otac;
			idemo->cvor.push_back("");
			naslismo->otac->vektor.push_back(idemo);
			naslismo->otac->vektor1.push_back(0);

			vector <string> pomocni;
			indeks = stek[stek.size() - 1];
			stek.pop_back();

			vector <string> svi;
			vector <struktura*> svi2;
			vector <int> svi3;

			int k1 = indeks;
			bool flag2 = 0;
			if (indeks == naslismo->otac->cvor.size()) {
				k1--;
				flag2 = 1;
			}

			for (int i = 0; i < k1; i++) {
				pomocni.push_back(naslismo->otac->cvor[i]);
			}


			for (int i = 0; i < naslismo->otac->vektor[k1]->cvor.size(); i++) {
				svi.push_back(naslismo->otac->vektor[k1]->cvor[i]);
				//cout << naslismo->otac->vektor[k1]->cvor[i] << ' ';
				svi2.push_back(naslismo->otac->vektor[k1]->vektor[i]);
				svi3.push_back(naslismo->otac->vektor[k1]->vektor1[i]);
				if (i == naslismo->otac->vektor[k1]->cvor.size() - 1) {
					svi2.push_back(naslismo->otac->vektor[k1]->vektor[i + 1]);
					svi3.push_back(naslismo->otac->vektor[k1]->vektor1[i + 1]);
				}
			}
			svi.push_back(naslismo->otac->cvor[k1]);
			for (int i = 0; i < naslismo->otac->vektor[k1+1]->cvor.size(); i++) {
				svi.push_back(naslismo->otac->vektor[k1+1]->cvor[i]);
				svi2.push_back(naslismo->otac->vektor[k1 + 1]->vektor[i]);
				svi3.push_back(naslismo->otac->vektor[k1 + 1]->vektor1[i]);
				if (i == naslismo->otac->vektor[k1 + 1]->cvor.size() - 1) {
					svi2.push_back(naslismo->otac->vektor[k1 + 1]->vektor[i + 1]);
					svi3.push_back(naslismo->otac->vektor[k1 + 1]->vektor1[i + 1]);
				}
			}
			if (flag2 == 0) {
				Stablo::struktura* tempo = naslismo->otac->vektor[naslismo->otac->vektor.size() - 1];
				for (int i = naslismo->otac->vektor.size() - 1; i > indeks + 1; i--) {
					naslismo->otac->vektor[i] = naslismo->otac->vektor[i - 1];
				}
				naslismo->otac->vektor[indeks + 1] = tempo;
			}
			
			int j = 0;
			int j1 = 3;
			int j2 = svi.size() - 2;
			int k = 0;

			for (int i = 0; i < svi.size(); i++) {
				vector <string> tren1;
				vector <struktura*> tren2;
				vector <int> tren3;
				j = 0;
				int brojanje = 0;
				while (j1 && j2 && i < svi.size() && j < (j2 / j1)) {
					tren1.push_back(svi[i]);
					tren2.push_back(svi2[i]);
					tren3.push_back(svi3[i]);
					brojanje += svi3[i] + 1;
					if(svi2[i]) svi2[i]->otac = naslismo->otac->vektor[k+k1];
					j++;
					i++;
				}
				
				j1--;
				j2 -= j; 
				//cout << i;
				tren2.push_back(svi2[i]);
				tren3.push_back(svi3[i]);
				brojanje += svi3[i];
				//cout << '\\';
				if (svi2[i]) svi2[i]->otac = naslismo->otac->vektor[k+k1];
				naslismo->otac->vektor1[k + k1] = brojanje; //  ????
				naslismo->otac->vektor[k + k1]->cvor = tren1;
				naslismo->otac->vektor[k + k1]->vektor = tren2;
				naslismo->otac->vektor[k + k1]->vektor1 = tren3;
				k++;
				if (i < svi.size())pomocni.push_back(svi[i]);
			}
			for (int i = k1 + 1; i < naslismo->otac->cvor.size(); i++) {
				pomocni.push_back(naslismo->otac->cvor[i]);
			}

			//cout << '\n';
			naslismo->otac->cvor = pomocni;
			
			naslismo = naslismo->otac;
			
		}
		//return false;
	}
	
	return true;
}

bool Stablo::brisi(string x) {

	vector <int> stek;
	int brojbrisanje = ceil((float)(2 * m - 1) / 3) - 1;

	Stablo::struktura* temp = koren;
	Stablo::struktura* naslismo1 = nullptr;
	Stablo::struktura* naslismo = nullptr;
	int indeks1 = 0;
	int pozicija1 = 0;
	int indeks = 0;
	int pozicija = 0;
	bool flg = 0;
	bool nadjen = 0;

	while (temp != nullptr) {
		flg = 0;
		indeks1 = pozicija1;
		indeks = pozicija;
		for (int j = 0; j < temp->cvor.size(); j++) {
			if (temp->cvor[j] == x) {
				naslismo1 = temp;
				pozicija1 = j;
				nadjen = 1;
			}
			if (flg==0 && temp->cvor[j] > x) {
				stek.push_back(j);
				if (temp->vektor[j] == nullptr) {
					naslismo = temp;
				}
				pozicija = j;
				flg = 1;
			}
		}
		if (flg == 1) { temp = temp->vektor[pozicija]; }
		if (flg == 0) {
			stek.push_back(temp->vektor.size() - 1);
			pozicija = temp->vektor.size() - 1;
			if (temp->vektor[temp->vektor.size() - 1] == nullptr) {
				naslismo = temp;
				pozicija--;
			}
			
			temp = temp->vektor[temp->vektor.size() - 1];
		}
	}

	stek.pop_back();

	if (nadjen == 0) return false;

	if (naslismo != naslismo1) {
		naslismo1->cvor[pozicija1] = naslismo->cvor[pozicija];
	}

	for (int i = pozicija1; i < naslismo->cvor.size() - 1; i++){
		naslismo->cvor[i] = naslismo->cvor[i + 1];
	}

	naslismo->cvor.pop_back();
	naslismo->vektor.pop_back();
	naslismo->vektor1.pop_back();

	if (naslismo->otac == nullptr || naslismo->cvor.size() >= brojbrisanje) {
		naslismo->otac->vektor1[indeks]--;
		return true;
	}

	/*
	if (indeks < naslismo->otac->cvor.size() && (naslismo->otac->vektor[indeks + 1]->cvor.size() > brojbrisanje )) {
		naslismo->cvor.push_back(naslismo->otac->cvor[indeks]);
		naslismo->vektor.push_back(nullptr);

		naslismo->otac->cvor[indeks] = naslismo->otac->vektor[indeks + 1]->cvor[0];
		for (int i = 0; i < naslismo->otac->vektor[indeks + 1]->cvor.size() - 1; i++)
			naslismo->otac->vektor[indeks + 1]->cvor[i] = naslismo->otac->vektor[indeks + 1]->cvor[i + 1];
		naslismo->otac->vektor[indeks + 1]->cvor.pop_back();
		naslismo->otac->vektor[indeks + 1]->vektor.pop_back();
		return true;
	}
	
	if (indeks > 0 && (naslismo->otac->vektor[indeks - 1]->cvor.size() > brojbrisanje )) {
		naslismo->cvor.push_back("");
		naslismo->vektor.push_back(nullptr);
		
		string y = naslismo->otac->cvor[indeks - 1];
		naslismo->otac->cvor[indeks - 1] = naslismo->otac->vektor[indeks - 1]->cvor[naslismo->otac->vektor[indeks - 1]->cvor.size() - 1];
		naslismo->otac->vektor[indeks - 1]->cvor.pop_back();
		for (int i = 0; i < naslismo->cvor.size(); i++) {
			string z = naslismo->cvor[i];
			naslismo->cvor[i] = y;
			y = z;
		}
		return true;
	}
	
	if (indeks < naslismo->otac->cvor.size()-1 && (naslismo->otac->vektor[indeks + 2]->cvor.size() > brojbrisanje )) {
		naslismo->cvor.push_back(naslismo->otac->cvor[indeks]);
		naslismo->vektor.push_back(nullptr);

		naslismo->otac->cvor[indeks] = naslismo->otac->vektor[indeks + 1]->cvor[0];
		for (int i = 0; i < naslismo->otac->vektor[indeks + 1]->cvor.size() - 1; i++)
			naslismo->otac->vektor[indeks + 1]->cvor[i] = naslismo->otac->vektor[indeks + 1]->cvor[i + 1];
		
		naslismo->otac->vektor[indeks + 1]->cvor[naslismo->otac->vektor[indeks + 1]->cvor.size() - 1] = naslismo->otac->cvor[indeks + 1];
		naslismo->otac->cvor[indeks + 1] = naslismo->otac->vektor[indeks + 2]->cvor[0];

		for (int i = 0; i < naslismo->otac->vektor[indeks + 2]->cvor.size() - 1; i++)
			naslismo->otac->vektor[indeks + 2]->cvor[i] = naslismo->otac->vektor[indeks + 2]->cvor[i + 1];
		naslismo->otac->vektor[indeks + 2]->cvor.pop_back();
		naslismo->otac->vektor[indeks + 2]->vektor.pop_back();

		return true;
	}
	
	if (indeks > 1 && (naslismo->otac->vektor[indeks - 2]->cvor.size() > brojbrisanje )) {
		naslismo->cvor.push_back("");
		naslismo->vektor.push_back(nullptr);

		string y = naslismo->otac->cvor[indeks - 2];
		naslismo->otac->cvor[indeks - 2] = naslismo->otac->vektor[indeks - 2]->cvor[naslismo->otac->vektor[indeks - 2]->cvor.size() - 1];
		naslismo->otac->vektor[indeks - 2]->cvor.pop_back();

		for (int i = 0; i < naslismo->otac->vektor[indeks-1]->cvor.size(); i++) {
			string z = naslismo->otac->vektor[indeks-1]->cvor[i];
			naslismo->otac->vektor[indeks-1]->cvor[i] = y;
			y = z;
		}
		string z = y;

		y = naslismo->otac->cvor[indeks - 1];
		naslismo->otac->cvor[indeks - 1] = z;
		//naslismo->otac->vektor[indeks - 1]->cvor.pop_back();

		for (int i = 0; i < naslismo->cvor.size(); i++) {
			string z = naslismo->cvor[i];
			naslismo->cvor[i] = y;
			y = z;
		}
		return true;
	}*/

	while (naslismo->otac!=nullptr) {

		indeks = stek[stek.size() - 1];
		stek.pop_back();

		if (indeks < naslismo->otac->cvor.size() && (naslismo->otac->vektor[indeks + 1]->cvor.size() > brojbrisanje)) {
			naslismo->cvor.push_back(naslismo->otac->cvor[indeks]);
			naslismo->vektor.push_back(naslismo->otac->vektor[indeks+1]->vektor[0]);
			naslismo->vektor1.push_back(naslismo->otac->vektor[indeks + 1]->vektor1[0]);

			if (naslismo->otac->vektor[indeks + 1]->vektor[0]) { naslismo->otac->vektor[indeks + 1]->vektor[0]->otac = naslismo; }

			naslismo->otac->cvor[indeks] = naslismo->otac->vektor[indeks + 1]->cvor[0];
			for (int i = 0; i < naslismo->otac->vektor[indeks + 1]->cvor.size() - 1; i++) {
				naslismo->otac->vektor[indeks + 1]->cvor[i] = naslismo->otac->vektor[indeks + 1]->cvor[i + 1];
				naslismo->otac->vektor[indeks + 1]->vektor[i] = naslismo->otac->vektor[indeks + 1]->vektor[i + 1];
				naslismo->otac->vektor[indeks + 1]->vektor1[i] = naslismo->otac->vektor[indeks + 1]->vektor1[i + 1];
				if (i == naslismo->otac->vektor[indeks + 1]->cvor.size() - 2) {
					naslismo->otac->vektor[indeks + 1]->vektor[i + 1] = naslismo->otac->vektor[indeks + 1]->vektor[i + 2];
					naslismo->otac->vektor[indeks + 1]->vektor1[i + 1] = naslismo->otac->vektor[indeks + 1]->vektor1[i + 2];
				}
			}
			naslismo->otac->vektor[indeks + 1]->cvor.pop_back();
			naslismo->otac->vektor[indeks + 1]->vektor.pop_back();
			naslismo->otac->vektor[indeks + 1]->vektor1.pop_back();

			naslismo->otac->vektor1[indeks]++;
			naslismo->otac->vektor1[indeks + 1]--;

			return true;
		}

		if (indeks > 0 && (naslismo->otac->vektor[indeks - 1]->cvor.size() > brojbrisanje)) {
			naslismo->cvor.push_back("");
			naslismo->vektor.push_back(nullptr);
			naslismo->vektor1.push_back(0);

			string y = naslismo->otac->cvor[indeks - 1];
			struktura* y1 = naslismo->otac->vektor[indeks - 1]->vektor[naslismo->otac->vektor[indeks - 1]->vektor.size()-1];
			int y2= naslismo->otac->vektor[indeks - 1]->vektor1[naslismo->otac->vektor[indeks - 1]->vektor1.size() - 1];

			if(y1) y1->otac = naslismo;
			naslismo->otac->cvor[indeks - 1] = naslismo->otac->vektor[indeks - 1]->cvor[naslismo->otac->vektor[indeks - 1]->cvor.size() - 1];

			naslismo->otac->vektor[indeks - 1]->cvor.pop_back();
			naslismo->otac->vektor[indeks - 1]->vektor.pop_back();
			naslismo->otac->vektor[indeks - 1]->vektor1.pop_back();
			for (int i = 0; i < naslismo->cvor.size(); i++) {
				string z = naslismo->cvor[i];
				struktura* z1 = naslismo->vektor[i];
				int z2 = naslismo->vektor1[i];
				naslismo->cvor[i] = y;
				naslismo->vektor[i] = y1;
				naslismo->vektor1[i] = z2;
				y = z;
				y1 = z1;
				y2 = z2;
			}
			naslismo->vektor[naslismo->vektor.size()] = y1;
			naslismo->vektor1[naslismo->vektor.size()] = y2;

			naslismo->otac->vektor1[indeks - 1]--;
			naslismo->otac->vektor1[indeks]++;

			return true;
		}

		if (indeks < naslismo->otac->cvor.size() - 1 && (naslismo->otac->vektor[indeks + 2]->cvor.size() > brojbrisanje)) {
			naslismo->cvor.push_back(naslismo->otac->cvor[indeks]);
			naslismo->vektor.push_back(naslismo->otac->vektor[indeks + 1]->vektor[0]);
			naslismo->vektor1.push_back(0);

			if (naslismo->otac->vektor[indeks + 1]->vektor[0]) { naslismo->otac->vektor[indeks + 1]->vektor[0]->otac = naslismo; }

			naslismo->otac->cvor[indeks] = naslismo->otac->vektor[indeks + 1]->cvor[0];
			for (int i = 0; i < naslismo->otac->vektor[indeks + 1]->cvor.size() - 1; i++) {
				naslismo->otac->vektor[indeks + 1]->cvor[i] = naslismo->otac->vektor[indeks + 1]->cvor[i + 1];
				naslismo->otac->vektor[indeks + 1]->vektor[i] = naslismo->otac->vektor[indeks + 1]->vektor[i + 1];
				naslismo->otac->vektor[indeks + 1]->vektor1[i] = naslismo->otac->vektor[indeks + 1]->vektor1[i + 1];
				if (i == naslismo->otac->vektor[indeks + 1]->cvor.size() - 2) {
					naslismo->otac->vektor[indeks + 1]->vektor[i + 1] = naslismo->otac->vektor[indeks + 1]->vektor[i + 2];
					naslismo->otac->vektor[indeks + 1]->vektor1[i + 1] = naslismo->otac->vektor[indeks + 1]->vektor1[i + 2];
				}
			}

			naslismo->otac->vektor[indeks + 1]->cvor[naslismo->otac->vektor[indeks + 1]->cvor.size() - 1] = naslismo->otac->cvor[indeks + 1];
			naslismo->otac->cvor[indeks + 1] = naslismo->otac->vektor[indeks + 2]->cvor[0];

			for (int i = 0; i < naslismo->otac->vektor[indeks + 2]->cvor.size() - 1; i++) {
				naslismo->otac->vektor[indeks + 2]->cvor[i] = naslismo->otac->vektor[indeks + 2]->cvor[i + 1];
				naslismo->otac->vektor[indeks + 2]->vektor[i] = naslismo->otac->vektor[indeks + 2]->vektor[i + 1];
				naslismo->otac->vektor[indeks + 2]->vektor1[i] = naslismo->otac->vektor[indeks + 2]->vektor1[i + 1];
				if (i == naslismo->otac->vektor[indeks + 2]->cvor.size() - 2) {
					naslismo->otac->vektor[indeks + 2]->vektor[i + 1] = naslismo->otac->vektor[indeks + 2]->vektor[i + 2];
					naslismo->otac->vektor[indeks + 2]->vektor1[i + 1] = naslismo->otac->vektor[indeks + 2]->vektor1[i + 2];
				}
			}
			naslismo->otac->vektor[indeks + 2]->cvor.pop_back();
			naslismo->otac->vektor[indeks + 2]->vektor.pop_back();
			naslismo->otac->vektor[indeks + 2]->vektor1.pop_back();

			naslismo->otac->vektor1[indeks]++;
			naslismo->otac->vektor1[indeks + 2]--;

			return true;
		}

		if (indeks > 1 && (naslismo->otac->vektor[indeks - 2]->cvor.size() > brojbrisanje)) {
			naslismo->cvor.push_back("");
			naslismo->vektor.push_back(nullptr);
			naslismo->vektor1.push_back(0);

			string y = naslismo->otac->cvor[indeks - 2];
			struktura* y1 = naslismo->otac->vektor[indeks - 2]->vektor[naslismo->otac->vektor[indeks - 2]->vektor.size() - 1];
			int y2 = naslismo->otac->vektor[indeks - 2]->vektor1[naslismo->otac->vektor[indeks - 2]->vektor1.size() - 1];

			if (y1) y1->otac = naslismo->otac->vektor[indeks - 1];

			naslismo->otac->cvor[indeks - 2] = naslismo->otac->vektor[indeks - 2]->cvor[naslismo->otac->vektor[indeks - 2]->cvor.size() - 1];
			
			naslismo->otac->vektor[indeks - 2]->cvor.pop_back();
			naslismo->otac->vektor[indeks - 2]->vektor.pop_back();
			naslismo->otac->vektor[indeks - 2]->vektor1.pop_back();

			for (int i = 0; i < naslismo->otac->vektor[indeks - 1]->cvor.size(); i++) {
				string z = naslismo->otac->vektor[indeks - 1]->cvor[i];
				struktura* z1 = naslismo->otac->vektor[indeks - 1]->vektor[i];
				int z2= naslismo->otac->vektor[indeks - 1]->vektor1[i];

				naslismo->otac->vektor[indeks - 1]->cvor[i] = y;
				naslismo->otac->vektor[indeks - 1]->vektor[i] = y1;
				naslismo->otac->vektor[indeks - 1]->vektor1[i] = y2;

				y = z;
				y1 = z1;
				y2 = z2;
			}
			struktura* z1 = naslismo->otac->vektor[indeks - 1]->vektor[naslismo->otac->vektor[indeks - 1]->vektor.size() - 1];
			naslismo->otac->vektor[indeks - 1]->vektor[naslismo->otac->vektor[indeks - 1]->vektor.size() - 1] = y1;

			int z2= naslismo->otac->vektor[indeks - 1]->vektor1[naslismo->otac->vektor[indeks - 1]->vektor1.size() - 1];
			naslismo->otac->vektor[indeks - 1]->vektor1[naslismo->otac->vektor[indeks - 1]->vektor1.size() - 1] = y2;

			if(z1) z1->otac = naslismo;
			string z = y;

			y = naslismo->otac->cvor[indeks - 1];
			naslismo->otac->cvor[indeks - 1] = z;
			y1 = z1;
			y2 = z2;

			for (int i = 0; i < naslismo->cvor.size(); i++) {
				string z = naslismo->cvor[i];
				struktura* z1 = naslismo->vektor[i];
				int z2 = naslismo->vektor1[i];
				naslismo->cvor[i] = y;
				naslismo->vektor[i] = y1;
				naslismo->vektor1[i] = y2;
				y = z;
				y1 = z1;
				y2 = z2;
			}
			naslismo->vektor[naslismo->vektor.size()] = y1;
			naslismo->vektor1[naslismo->vektor.size()] = y2;

			naslismo->otac->vektor1[indeks]++;
			naslismo->otac->vektor1[indeks - 2]--;

			return true;
		}
		
		if (naslismo->otac->cvor.size() == 1) {
			vector <string> niz1;
			vector <Stablo::struktura*> niz2;
			vector <int> niz3;
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < naslismo->otac->vektor[i]->cvor.size(); j++) {
					niz1.push_back(naslismo->otac->vektor[i]->cvor[j]);
					niz2.push_back(naslismo->otac->vektor[i]->vektor[j]);
					niz3.push_back(naslismo->otac->vektor[i]->vektor1[j]);
					if (j == naslismo->otac->vektor[i]->cvor.size() - 1) {
						niz2.push_back(naslismo->otac->vektor[i]->vektor[j + 1]);
						niz3.push_back(naslismo->otac->vektor[i]->vektor1[j + 1]);
					}
				}
				if (i == 0) niz1.push_back(naslismo->otac->cvor[0]);
			}
			for (int i = 0; i < niz2.size(); i++) if (niz2[i]) niz2[i]->otac = naslismo->otac;
			naslismo->otac->cvor = niz1;
			naslismo->otac->vektor = niz2;
			naslismo->otac->vektor1 = niz3;
			return true;
		}
		//else
		{
			int k1 = indeks - 1;
			if (indeks == naslismo->otac->cvor.size()) k1--;
			if (k1 < 0) k1 = 0;

			vector <string> prim;
			for (int i = 0; i < k1; i++) {
				prim.push_back(naslismo->otac->cvor[i]);
			}

			vector <string> tren1;
			vector <Stablo::struktura*> tren2;
			vector <int> tren3;

			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < naslismo->otac->vektor[k1 + i]->cvor.size(); j++) {
					tren1.push_back(naslismo->otac->vektor[k1 + i]->cvor[j]);
					tren2.push_back(naslismo->otac->vektor[k1 + i]->vektor[j]);
					tren3.push_back(naslismo->otac->vektor[k1 + i]->vektor1[j]);
					if (j == naslismo->otac->vektor[k1 + i]->cvor.size() - 1) {
						tren2.push_back(naslismo->otac->vektor[k1 + i]->vektor[j + 1]);
						tren3.push_back(naslismo->otac->vektor[k1 + i]->vektor1[j + 1]);
					}
				}
				if (i < 2) tren1.push_back(naslismo->otac->cvor[k1 + i]);
			}

			int k = 0;
			for (int i = 0; i < tren1.size(); i++) {
				vector <string> p1;
				vector <Stablo::struktura*> p2;
				vector <int> p3;
				int brojanje = 0;
				int j = 0;
				while (i < tren1.size() && j < tren1.size() / 2) {
					p1.push_back(tren1[i]);
					p2.push_back(tren2[i]);
					if (tren2[i])tren2[i]->otac = naslismo->otac->vektor[k1 + k];
					p3.push_back(tren3[i]);
					brojanje += tren3[i] + 1;
					i++;
					j++;
				}
				p2.push_back(tren2[i]);
				if (tren2[i]) tren2[i]->otac = naslismo->otac->vektor[k1 + k];
				p3.push_back(tren3[i]);
				brojanje += tren3[i];

				if (i < tren1.size())prim.push_back(tren1[i]);
				naslismo->otac->vektor[k1 + k]->cvor = p1;
				naslismo->otac->vektor[k1 + k]->vektor = p2;
				naslismo->otac->vektor[k1 + k]->vektor1 = p3;
				naslismo->otac->vektor1[k1 + k] = brojanje;
				k++;
			}

			for (int i = k1 + k; i < naslismo->otac->vektor.size() - 1; i++) {
				naslismo->otac->vektor[i] = naslismo->otac->vektor[i + 1];
				naslismo->otac->vektor1[i] = naslismo->otac->vektor1[i + 1];
			}

			for (int i = k1+2; i < naslismo->otac->cvor.size(); i++) {
				prim.push_back(naslismo->otac->cvor[i]);
			}

			naslismo->otac->vektor.pop_back();
			naslismo->otac->vektor1.pop_back();

			naslismo->otac->cvor = prim;
			naslismo = naslismo->otac;
			//return true;
		}
	}
	return true;
}

void Stablo::pisi(Stablo &s) {
	queue <Stablo::struktura*> niz;
	niz.push(s.koren);
	while (niz.size()) {
		queue <Stablo::struktura*> niz2;
		while (niz.size()) {
			Stablo::struktura* temp = niz.front();
			for (int i = 0; i < temp->vektor.size(); i++) {
				if (temp->vektor[i] != nullptr) niz2.push(temp->vektor[i]);
			}
			cout << temp->cvor.size();
			niz.pop();
			if (niz.size()) cout << " |  ";
		}
		cout << '\n';
		niz = niz2;
	}
}

int Stablo::sestizadatak(string x){
	Stablo::struktura* temp = koren;
	Stablo::struktura* naslismo = nullptr;

	int brojac = 0;

	bool flg = 0;
	while (temp != nullptr) {
		flg = 0;
		for (int j = 0; j < temp->cvor.size(); j++) {
			if (temp->cvor[j] == x) {
				brojac += temp->vektor1[j];
				return brojac;
			}
			if (temp->cvor[j] > x) {
				temp = temp->vektor[j];
				flg = 1;
				break;
			}
			else {
				brojac += temp->vektor1[j] + 1;
			}
		}
		if (flg == 0) temp = temp->vektor[temp->vektor.size() - 1];
	}
	return brojac;
}

void Stablo::proba(){
	//cout << koren->vektor1[0] << " - ";
	//cout << koren->vektor[0]->vektor1[0] << " - ";
	//cout << koren->vektor[0]->vektor[0]->vektor1[0] << " - ";
}

ostream& operator<<(ostream& os, const Stablo& s){
	queue <Stablo::struktura*> niz;
	niz.push(s.koren);
	while (niz.size()) {
		queue <Stablo::struktura*> niz2;
		while (niz.size()) {
			Stablo::struktura* temp = niz.front();
			for (int i = 0; i < temp->vektor.size(); i++) {
				if (temp->vektor[i] != nullptr) niz2.push(temp->vektor[i]);
				if (i<temp->cvor.size()) {
					os << temp->cvor[i] << ' ';
				}
			}
			niz.pop();
			if(niz.size()) os << " |  ";
		}
		os << '\n';
		niz = niz2;
	}
	return os;
}
