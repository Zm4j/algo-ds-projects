#include "stablo.h"
#include <algorithm>
#include <random>
#include <fstream>

int main() {
	srand(unsigned(time(NULL)));
	/*
	int n;
	cin >> n;
	Stablo s(4);
	vector <string> v;
	for (int i = 1; i <= 17; i++) {
		if (i == 1) v.push_back("01");
		if (i == 2) v.push_back("02");
		if (i == 3) v.push_back("03");
		if (i == 4) v.push_back("04");
		if (i == 5) v.push_back("05");
		if (i == 6) v.push_back("06");
		if (i == 7) v.push_back("07");
		if (i == 8) v.push_back("08");
		if (i == 9) v.push_back("09");
		if(i>=10) v.push_back(to_string(i));
	}
	//random_shuffle(v.begin(), v.end());
	for (auto i : v) {

		if (s.dodaj(i) == false) break;

		//cout << s << "\n";

		//s.proba(); cout  << "\n\n";
		
		//else{ cout << '\n' << s << '\n'; }
		//cout << s;
	}
	//s.dodaj("18");
	//s.dodaj("19");

	s.brisi("09");
	s.brisi("04");
	s.brisi("06");

	cout << '\n';
	cout << s;
	cout << '\n';

	cout << "brojeva manjih od 0 ima: " << s.sestizadatak("00"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 1 ima: " << s.sestizadatak("01"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 2 ima: " << s.sestizadatak("02"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 3 ima: " << s.sestizadatak("03"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 4 ima: " << s.sestizadatak("04"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 5 ima: " << s.sestizadatak("05"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 6 ima: " << s.sestizadatak("06"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 7 ima: " << s.sestizadatak("07"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 8 ima: " << s.sestizadatak("08"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 9 ima: " << s.sestizadatak("09"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 10 ima: " << s.sestizadatak("10"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 11 ima: " << s.sestizadatak("11"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 12 ima: " << s.sestizadatak("12"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 13 ima: " << s.sestizadatak("13"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 14 ima: " << s.sestizadatak("14"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 15 ima: " << s.sestizadatak("15"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 16 ima: " << s.sestizadatak("16"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 17 ima: " << s.sestizadatak("17"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 18 ima: " << s.sestizadatak("18"); cout << ' '; cout << "\n";
	cout << "brojeva manjih od 19 ima: " << s.sestizadatak("19"); cout << ' '; cout << "\n";
	cout << '\n';
	cout << '\n';

	cout << s << '\n';

	//cout << "asd";

	s.brisi();
	cout << "jeste";
	return 0;
	*/

	Stablo stablo1;
	while (1) {
		int meni;
		{	
			cout << "unesite stavku menija: \n";
			cout << "1. kreiranje stabla reda m\n";
			cout << "2. pronalazenje kljuca u stablu\n";
			cout << "3. ispisivanje stabla\n";
			cout << "4. umetanje kljuca u stablo\n";
			cout << "5. brisanje kljuca iz stabla\n";
			cout << "6. sesti zadatak\n";
			cout << "7. brisanje stabla\n";
			cout << "8. unos random primera\n";
			cout << "9. unos iz datoteke\n";
			cout << "0. za izlazak\n";
			cin >> meni;
			system("CLS");
		}
		if (meni == 1) {
			int m;
			cout << "uneti red stabla m: ";
			cin >> m;
			stablo1.red_stabla(m);
		}
		if (meni == 2) {
			string str;
			cout << "uneti kljuc za pretragu: ";
			cin >> str;
			stablo1.pretrazi(str) ? (cout << "Kljuc se nalazi u stablu") : (cout << "Kljuc se ne nalazi u stablu");
		}
		if (meni == 3) {
			cout << stablo1;
			cout << '\n';
		}
		if (meni == 4) {
			string str;
			cout << "uneti kljuc za unos: ";
			cin >> str;
			stablo1.dodaj(str) ? (cout << "Kljuc je unet") : (cout << "Kljuc nije unet");
		}
		if (meni == 5) {
			string str;
			cout << "uneti kljuc za brisanje";
			cin >> str;
			stablo1.brisi(str) ? (cout << "Kljuc je uklonjen") : (cout << "Kljuc nije uklonjen");
		}
		if (meni == 6) {
			string str;
			cout << "uneti kljuc za sestizadatak: ";
			cin >> str;
			cout << "Broj cvorova manjih od " << str << " je: " << stablo1.sestizadatak(str) << "\n";
		}
		if (meni == 7) {
			stablo1.brisi();
			cout << "Stablo je obrisano";
		}
		if (meni == 8) {
			int n,l,h;
			cout << "uneti red [3,10]: ";
			cin >> n;
			cout << "uneti raspon brojeva [1,99]: ";
			cin >> l >> h;
			Stablo s(n);
			vector <string> v;
			for (int i = l; i <= h; i++) {
				if (i == 1) v.push_back("01");
				if (i == 2) v.push_back("02");
				if (i == 3) v.push_back("03");
				if (i == 4) v.push_back("04");
				if (i == 5) v.push_back("05");
				if (i == 6) v.push_back("06");
				if (i == 7) v.push_back("07");
				if (i == 8) v.push_back("08");
				if (i == 9) v.push_back("09");
				if (i >= 10) v.push_back(to_string(i));
			}
			random_shuffle(v.begin(), v.end());
			for (auto i : v) {
				s.dodaj(i);
			}
			cout << s;
		}
		if (meni == 9) {
			ifstream in("ime.txt");
			string s1;

			while (getline(in,s1)) {
				stablo1.dodaj(s1);
			}
		}
		if (meni == 0) break;
		cout << "\n\n";
	}
	cout << "kod je uspesno zavrsen\n";

	return 0;
}