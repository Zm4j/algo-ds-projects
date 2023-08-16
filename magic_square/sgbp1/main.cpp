#include <bits/stdc++.h>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int brp,t2,t3,t4;
    cin >> brp >> t2 >> t3 >> t4; cin.ignore();
    vector <string> pice[brp];
    for(int i=0;i<brp;i++){
        string c;
        getline(cin, c);
        stringstream check1(c);
        string str;
        while(getline(check1,str, ' '))
            pice[i].push_back(str);
        cout << pice[i][1] << ' ';
    }

}
