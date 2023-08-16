#include <bits/stdc++.h>

using namespace std;

typedef struct cvor{
    string key;
    string prevod;
    int counter;
    struct cvor *levo;
    struct cvor *desno;
    struct cvor *gore;
}cvor;

cvor *dodajcvor(cvor *root, cvor *novi){
    //cvor *root = *roott;
    if(root==NULL){
        root=novi;
        //cout << root->key;
        return root;
    }
    //root->levo=novi;
    //return root;
    cvor *p = root;
    while(1){
        if(p->key>novi->key){
            if(p->levo == NULL) break;
            p=p->levo;
        }
        else{
            if(p->key==novi->key) novi->counter=max(novi->counter,p->counter+1);
            if(p->desno == NULL) break;
            p=p->desno;
        }
    }

    if(p->key>novi->key)
        p->levo=novi;
    else{
        if(p->key==novi->key) novi->counter=p->counter+1;
        p->desno=novi;
    }
    novi->gore=p;
    return root;
}

cvor *unesicvor1(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    //...
    {cvor *novi= new cvor;
    novi->counter=1;
    novi->key=s1;
    novi->prevod=s2;
    novi->levo=NULL;
    novi->desno=NULL;
    novi->gore=NULL;
    return novi;}
}

cvor *unesicvor2(cvor* root, int nn){
    ifstream in("ime.txt");
    string s1,s2;

    for(int i=0;i<nn;i++){
        getline(in, s1);
        getline(in, s2);

        //cout << s1 << ' ' << s2 << '\n';

        cvor *novi = new cvor;
        novi->counter=1;
        novi->key=s1;
        novi->prevod=s2;
        novi->levo=NULL;
        novi->desno=NULL;
        novi->gore=NULL;

        root=dodajcvor(root,novi);
    }

    return root;
}

vector<string> trazenjecvora(cvor *root, string key){
    cvor *p = root;
    vector <string> v;
    while(p!=NULL){
        if(p->key>key)
            p=p->levo;
        else{
            if(p->key==key) {
                v.push_back(p->prevod);
            }
            p=p->desno;
        }
    }
    return v;
}

void ispis(cvor *root){
    if(root==NULL) return;
    queue <cvor*> que;
    que.push(root);
    vector <string> v;
    v.push_back(root->key);
    int visina=0;
    string c="/";
    string c1="\\";
    while(1){
        visina++;
        vector <cvor*> pomoc;
        while(que.size()){

            if(que.front()==NULL){
                v.push_back(c);
                v.push_back(c1);
                pomoc.push_back(NULL);
                pomoc.push_back(NULL);
                que.pop();
                continue;
            }

            if(que.front()->levo!=NULL){
                pomoc.push_back(que.front()->levo);
                v.push_back(que.front()->levo->key);
            }
            else{
                pomoc.push_back(NULL);
                v.push_back(c);
            }
            if(que.front()->desno!=NULL){
                pomoc.push_back(que.front()->desno);
                v.push_back(que.front()->desno->key);
            }
            else{
                pomoc.push_back(NULL);
                v.push_back(c1);
            }
            que.pop();
        }

        if(pomoc.size()==0) break;

        bool flag=true;
        for(int i=0;i<pomoc.size();i++){
            que.push(pomoc[i]);
            if(pomoc[i]!=NULL) flag=false;
        }

        if(flag) break;
    }
    //cout << visina;
    cout << '\n';
    for(int i=1;i<(v.size()+1)/2;i*=2){
        int k=pow(2,visina-1)-1;
        string razmak;
        for(int i=0;i<k;i++){
            razmak+=' ';
        }
        cout << razmak;
        string razmak2;
        k=pow(2,visina)-1;
        for(int i=0;i<k;i++){
            razmak2+=' ';
        }
        for(int j=i;j<i*2;j++){
            cout << v[j-1] << razmak2;
        }
        cout << '\n';
        visina--;
    }

}

void desetpoena(cvor *root){
    int brponavljanja=-1;
    string s1; //kljuc
    string s2; //prevod

    vector <cvor*> v;
    v.push_back(root);
    for(int i=0;i<v.size();i++){
        if(v[i]->counter>brponavljanja){
            brponavljanja=v[i]->counter;
            s1=v[i]->key;
            s2=v[i]->prevod;
        }
        if(v[i]->levo!=NULL) v.push_back(v[i]->levo);
        if(v[i]->desno!=NULL) v.push_back(v[i]->desno);
    }

    cout << s1 << ' ' << s2 << '\n' << "broj ponavljanja: " << brponavljanja << '\n';
}

cvor* brisicvor1(cvor *root, string key){
    cvor *p = root;
    while(p!=NULL && p->key!=key){
        if(p->key>key)
            p=p->levo;
        else
            p=p->desno;
    }
    if(p==NULL) return NULL;

    //list
    if(p->levo==NULL && p->desno==NULL){
        if(p->gore==NULL){free(p);return root;}

        if(p->gore->desno==p) p->gore->desno=NULL;
        else p->gore->levo=NULL;
        free(p);
        return root;
    }
    //nije list
    cvor *q;
    if(p->levo!=NULL){
        q=p->levo;
        while(q->desno)
            q=q->desno;
    }
    else{
        q=p->desno;
        while(q->levo)
            q=q->levo;
    }

    string sss1=p->key;
    string sss2=p->prevod;
    int xxx=p->counter;

    p->key=q->key;
    p->prevod=q->prevod;
    p->counter=q->counter;

    q->key=sss1;
    q->prevod=sss2;
    q->counter=xxx;

    if(q->gore->desno==q){
        if(q->desno!=NULL){
            q->gore->desno=q->desno;
            q->desno->gore=q->gore;
        }
        else{
            if(q->levo!=NULL){
                q->gore->desno=q->levo;
                q->levo->gore=q->gore;
            }
            else{
                q->gore->desno=NULL;
            }
        }
    }
    else{
        if(q->desno!=NULL){
            q->gore->levo=q->desno;
            q->desno->gore=q->gore;
        }
        else{
            if(q->levo!=NULL){
                q->gore->levo=q->levo;
                q->levo->gore=q->gore;
            }
            else{
                q->gore->levo=NULL;
            }
        }
    }

    free(q);
    return root;
}

void brisicvor(cvor *root, string key){
    while(brisicvor1(root,key)!=NULL);
}

void brisanjestabla(cvor *root){
    while(!(root->desno==NULL && root->levo==NULL)){
        //cout << root->key << '-';
        brisicvor(root,root->key);
    }
    free(root);
}

int main(){

    int meni;

    cvor *root=NULL;

    while(1){

        cout << "unesi 0 za izlazak iz programa\n";
        cout << "unesi 1 za unos n elemenata u stablo sa standradnog ulaza\n";
        cout << "unesi 2 za unos n elemenata u stablo iz datoteke\n";
        cout << "unesi 3 za unos jednog elementa u stablo sa standradnog ulaza\n";
        cout << "unesi 4 za pretragu svih prevoda u stablu za zadati kljuc\n";
        cout << "unesi 5 za ispis stabla\n";
        cout << "unesi 6 za brisanje svih cvorova sa zadatim kljucem\n";
        cout << "unesi 7 za brisanje celog stabla\n";
        cout << "unesi 8 za 10poena\n";

        cin >> meni; cin.ignore();
        if(meni==0){
            return 0;
        }
        if(meni==1){
            cout << "unesi n elemnata koji se unose za pravljenje stabla\n";
            int t;
            cin >> t; cin.ignore();
            while(t--){
                cvor *novi=unesicvor1();
                root=dodajcvor(root,novi);
            }
        }
        if(meni==2){
            cout << "unesi n elemnata koji se unose za pravljenje stabla\n";
            int t;
            cin >> t; cin.ignore();
            root=unesicvor2(root,t);
        }
        if(meni==3){
            cvor *novi=unesicvor1();
            root=dodajcvor(root,novi);
        }
        if(meni==4){
            cout << "unesite kljuc za koji se traze svi prevodi u stablu\n";
            string s;
            cin >> s; cin.ignore();
            vector <string> v=trazenjecvora(root,s);
            for(int i=0;i<v.size();i++) cout << v[i] << ' ';
            cout << '\n';
        }
        if(meni==5){
            ispis(root);
        }
        if(meni==6){
            cout << "unesite kljuc za koji zelite da izbrisete sve reci u stablu\n";
            string s;
            cin >> s; cin.ignore();
            brisicvor(root,s);
        }
        if(meni==7){
            brisanjestabla(root);
            root=NULL;
        }
        if(meni==8){
            desetpoena(root);
        }
    }
}


/*
7
7
5
5
8
8
1
1
6
6
a
a
3
3
9
9
c
c
2
2
4
4
b
b
*/
