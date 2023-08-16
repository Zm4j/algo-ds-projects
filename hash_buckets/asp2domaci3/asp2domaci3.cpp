#include <iostream>
#include "HashTable.h"
#include <string>
#include <sstream>

struktura unos1() {
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
    /*
   
    HashTable tabela(4,3);
    struktura s;
    s.indeks = 12345678;
    s.imeprezime = "";
    tabela.insertkey(12345678, s);
    tabela.insertkey(12344678, s);
    tabela.insertkey(12343678, s);
    tabela.insertkey(12342678, s);
    tabela.insertkey(12341678, s);
    tabela.insertkey(11345678, s);
    tabela.insertkey(13344678, s);
    tabela.insertkey(14343678, s);
    tabela.insertkey(15342678, s);
    tabela.insertkey(16341678, s);

    //tabela.deletekey(12345678);

    cout << tabela.keycount() << ' ' << tabela.tablesize() << ' ' << tabela.fillratuio() << '\n';
    
    tabela.dodajispit(16341678, "ISPIT0");
    tabela.dodajispit(16341678, "ISPIT1");
    tabela.dodajispit(16341678, "ISPIT2");
    tabela.brisiispit(16341678, "ISPIT1");
    tabela.brisiispit(16341678, "ISPIT1");
    tabela.brisiispit(16341678, "ISPIT2");
    tabela.brisiispit(16341678, "ISPIT0");
    cout << '\n';
    cout << tabela;
    cout << pow(2, 3);
    */
    int k, p;

    cout << "k, p: ";
    cin >> k >> p; cin.ignore();

    HashTable tabela(k,p);
    
    while (1) {
        cout << "MENI:\n"
            "0. izlaz"
            "1. findkey\n"
            "2. insertkey\n"
            "3. deletekey\n"
            "4. clear\n"
            "5. keycount\n"
            "6. tabelasize\n"
            "7. fillratio\n"
            "8. dodajispit\n"
            "9. brisiispit\n"
            "10. cout\n";
        int x;
        cin >> x; cin.ignore();
        if (x == 0) return 0;
        if (x == 1) {
            unsigned int k;
            cin >> k;
            struktura* s = tabela.findkey(k);
        }
        if (x == 2) {
            struktura s = unos1();
            tabela.insertkey(s.indeks, s);
        }
        if (x == 3) {
            unsigned int k;
            cin >> k;
            tabela.deletekey(k);
        }
        if (x == 4) {
            tabela.clear();
        }
        if (x == 5) {
            cout << tabela.keycount();
        }
        if (x == 6) {
            cout << tabela.tablesize();
        }
        if (x == 7) {
            cout << tabela.fillratuio();
        }
        if (x == 8) {
            unsigned int k;
            string stri;
            cin >> k; cin.ignore();
            cin >> stri;
            tabela.dodajispit(k, stri);
        }
        if (x == 9) {
            unsigned int k;
            string stri;
            cin >> k; cin.ignore();
            cin >> stri;
            tabela.brisiispit(k, stri);
        }
        if (x == 10) {
            cout << tabela;
        }
    }
}
