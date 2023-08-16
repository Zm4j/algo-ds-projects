#include <bits/stdc++.h>

using namespace std;

//indeks fibonacijevog broja prvog veceg, ili broja n ako je on fibonacijev
int fibonacijevindeks(int n){
    long long f1=0,f2=1,f,i=1;
    if(n==0) return 0;
    if(n==1) return 1;
    do{
        f=f1+f2;
        f1=f2;
        f2=f;
        i++;
    }while(f<n);
    //cout << f << endl;
    return i;
}

//vraca niz koji sadrzi prvih n fibonacijevih brojeva
vector <long long> fibonacijevbroj(int n){
    long long f1=0,f2=1,f=-1;
    vector <long long> v;
    v.push_back(0);
    if(n==0) return v;
    v.push_back(1);
    if(n==1) return v;
    while((n--)-1){
        f=f1+f2;
        f1=f2;
        f2=f;
        v.push_back(f);
    }
    return v;
}


int main(){
    double a,b;
    int e;

    int meni;

    while(1){
        cout << "unesi 1 za unos granica i preciznost:\n";
        cout << "unesi 2 za pokretanje igre:\n";
        cout << "unesi 3 da izadjes:\n";

        cin>>meni;
        if(meni==1){
            cout << "unesi granice i tacnost\n";
            cin >> a >> b >> e;
        }
        //pravimo pomocu datog opsega a,b i greske e, prividan opseg od 0 do nekog celog broja n, a n se izracunava, matematicki, kao (b-a) * 10^e
        if(meni==2){
            cout << "unesi '<', '>' ili '=' u zavisnosti od toga da li ste blize ili dalje od zeljenog rezultata\n";
            long long n = (int)((b-a)*pow(10,e));
            int m = fibonacijevindeks(n);
            vector <long long> v = fibonacijevbroj(m);
            for(int i=0;i<v.size();i++){cout << v[i] << ' ';}
            int pre=0;
            //cout << v.size();
            string s;
            long long i;
            int brkoraka=0;
            while(1)
            {
                i=min(n,pre+v[m-1]);
                cout << endl << fixed << setprecision(e) << (double)(i/pow(10,e))+a;
                cin >> s;
                if(s==">"){
                    brkoraka++;
                    pre=i;
                    m--;
                    m--;
                }
                if(s=="<"){
                    brkoraka++;
                    m--;
                }
                if(s=="="){
                    brkoraka++;
                    break;
                }
            }
            cout << brkoraka << endl;
        }
        if(meni==3){
            return 0;
        }
    }
}
