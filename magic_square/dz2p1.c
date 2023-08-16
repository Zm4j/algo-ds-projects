#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int *mat;
    int brojnula;
    struct Node **child;
} Node;

Node *newNode(int *key,int n)
{
    Node *temp = (Node*)calloc(1, sizeof(Node));
    temp->mat = key;
    temp->brojnula = n;
    temp->child = (Node**)calloc(n,sizeof(Node*));
    return temp;
}

void stampaj_matricu(int n, int *a){
    printf("\n");
    for(int i=0;i<n*n;i++){
        if(i%n==0 && i) printf("\n");
        printf("%d ",*(a+i));
    }
    printf("\n");
}

int proverakvadrata(int n,int *a,int srv){
    int matrica[n][n];
    for(int i=0;i<n*n;i++) matrica[i/n][i%n]=*(a+i);

    for(int i=0;i<n;i++){
        int u=0, v=0;
        for(int j=0;j<n;j++){
            u+=matrica[i][j];
            v+=matrica[j][i];
        }
        if(u!=srv/n || v!=srv/n) return 0;
    }
    int u=0,v=0;
    for(int i=0;i<n;i++)
    {u+=matrica[i][i];v+=matrica[i][n-1-i];}
    if(u!=srv/n || v!=srv/n) return 0;
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int proverakvadrata1(int n,int *a,int srv){
    int matrica[n][n];
    for(int i=0;i<n*n;i++) matrica[i/n][i%n]=*(a+i);

    for(int i=0;i<n;i++){
        int u=0, v=0,flag1=0,flag2=0;
        for(int j=0;j<n;j++){
            u+=matrica[i][j];
            v+=matrica[j][i];
            if(matrica[i][j]==0) flag1=1;
            if(matrica[j][i]==0) flag2=1;
        }
        if(flag1 && u>=srv/n) return 0;
        if(!flag1 && u!=srv/n) return 0;
        if(flag2 && v>=srv/n) return 0;
        if(!flag2 && v!=srv/n) return 0;
    }
    int u=0,v=0,flag1=0,flag2=0;
    for(int i=0;i<n;i++){
        u+=matrica[i][i];
        v+=matrica[i][n-1-i];
        if(matrica[i][i]==0) flag1=1;
        if(matrica[i][n-1-i]==0) flag2=1;

    }
        if(flag1 && u>=srv/n) return 0;
        if(!flag1 && u!=srv/n) return 0;
        if(flag2 && v>=srv/n) return 0;
        if(!flag2 && v!=srv/n) return 0;
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int proverasuperkvadrata(int n,int *a,int srv){
    int matrica[n][n];
    for(int i=0;i<n*n;i++) matrica[i/n][i%n]=*(a+i);

    for(int i=1;i<n;i++){
        int u=0, v=0;
        for(int j=0;j<n;j++){
            u+=matrica[j][(i+j)%n];
            v+=matrica[j][((n-1-i-j)%n+n)%n];
        }
        if(u!=srv/n || v!=srv/n) return 0;
    }
    return 1;
}

int *f(int *a,int n){
    int *b;
    b = (int*)calloc(n*n, sizeof(int));
    for(int i=0;i<n*n;i++) *(b+i)=*(a+i);
    return b;
}

//da li seu nizu a nalazi element m?
int provera(int *a,int n,int m){
    for(int i=0;i<n;i++)
        if(*(a+i)==m) return 1;
    return 0;
}

void resimagicnikvadrat(int n,int brnula1,int *b,Node **stek,int stv){

    int brojac=1;
    int pozicija=0;
    int *h = (int*)calloc(n*n, sizeof(int));

    while(pozicija<brojac){ // ?????
        h=f((*(stek+pozicija))->mat,n);

        int ii=0;
        while(*(h+ii)) ii++; //h pokazuje na lokaciju gde je prazno polje trenutno u matrici.

        int brnula=(*(stek+pozicija))->brojnula;
        int j=0;
        for(int i=0;i<brnula;i++){
            while(j<brnula1 && provera(h,n*n,*(b+j))) j++; // provera da li se u matrici vec nalazi neki broj koji je u nizu ostalih brojeva koje treba dodati u matricu.
            if(i==brnula) continue; //ovo se nikada ne desava ali ok.
            *(h+ii)=*(b+j);

            if(!proverakvadrata1(n,h,stv)) continue;

            (*((*(stek+pozicija))->child+i)) = newNode(f(h,n),brnula-1);

            (*(stek+brojac))=(*((*(stek+pozicija))->child+i));
            brojac++;
        }
        *(h+ii)=0;
        pozicija++;
    }

}

int pomoc(int brnula){
    int sum=1;
    for(int i=1;i<=brnula;i++){
        sum=1+i*sum;
    }
    return sum;
}

void ispisstabla1(Node **root,int h,int brnula,int n,int srv){
    int j=-1;
    int k=0;
    for(int i=1;i<=h;i++){
        if(j!=(*(root+i-1))->brojnula){
            j=(*(root+i-1))->brojnula;
            printf ("\n-----------------  NIVO %d  ----------------------\n",k++);
        }
        stampaj_matricu(n,(*(root+i-1))->mat);
        /*if(k-1==brnula){
            if(proverasuperkvadrata(n,(*(root+i-1))->mat,srv))
                printf("\nJESTE SUPER KVADRAT\n");
            else
                printf("\nNIJE SUPER KVADRAT\n");
        }*/
    }
}

void resavanjemagicnogkvadratazadomacizadatakizalgoritmaistrukturapodatakadomaci2(int n,Node **root,int srv,int brnula){
    for(int i=0;i<pomoc(brnula);i++){
        if(proverakvadrata(n,(*(root+i))->mat,srv)){
            stampaj_matricu(n,(*(root+i))->mat);
            if(proverasuperkvadrata(n,(*(root+i))->mat,srv))
                printf("\nJESTE SUPER KVADRAT\n");
            else
                printf("\nNIJE SUPER KVADRAT\n");
        }
    }
}

int main()
{

    Node **root = (Node**)calloc(pomoc(12),sizeof(Node*));
    int *b; b = (int*)calloc(pomoc(12), sizeof(int));
    int srv0;
    int n0;
    int brnula0;
    while(1){
        int flp;
        printf("MENI\n1.Unesi kvadrat\n2.Ispis Stabla\n3.Ispisi Resenja stabla\n4.Ispis karakteristicnog zbira\n5.Formiranje stabla\n6.Proveri da li je popunjen kvadrat magican\n7.Proveri da li je popunjen  kvadrat super magican\n");
        scanf("%d",&flp);

        if(flp==1){
            int *a;
            int n;
            printf("unesit broj n: ");
            scanf("%d",&n);

            a = (int*)calloc(n*n, sizeof(int));

            printf("Uneti matricu pocetnog kvadrata:\n");

            int srv=0; // vrednost karakteristicnog zbira *n
            int brnula=0;

            for(int i=0;i<n*n;i++) {
                scanf("%d",&(*(a+i)));
                if(*(a+i)) srv+=*(a+i);
                else brnula++;
            }

            printf("uneti ostale vrednosti magicnog kvadrata:\n");
            for(int i=0;i<brnula;i++){
                scanf("%d",&(*(b+i)));
                srv+=*(b+i);
            }

            *root = newNode(a,brnula);

            srv0=srv;
            n0=n;
            brnula0=brnula;

            //resimagicnikvadrat(n,brnula,b,root,srv);
            //ispisstabla1(root,pomoc(brnula0),brnula0,n0,srv0);
        }

        if(flp==2){
            ispisstabla1(root,pomoc(brnula0),brnula0,n0,srv0);
        }

        if(flp==3){
            resavanjemagicnogkvadratazadomacizadatakizalgoritmaistrukturapodatakadomaci2(n0,root,srv0,brnula0); //ispisuje magicnekvadrate i dal je super ili ne.
        }
        if(flp==4){
            printf("Karakteristicna suma kvadrata: %d\n",srv0/n0);
        }
        if(flp==5){
            resimagicnikvadrat(n0,brnula0,b,root,srv0);
        }
        if(flp==6){
            int *a;
            int n;
            printf("unesit broj n: ");
            scanf("%d",&n);

            a = (int*)calloc(n*n, sizeof(int));

            printf("Uneti matricu pocetnog kvadrata:\n");

            int srv=0; // vrednost karakteristicnog zbira *n

            for(int i=0;i<n*n;i++){
                scanf("%d",&(*(a+i)));
                if(*(a+i)) srv+=*(a+i);
            }
            if(proverakvadrata(n,a,srv)) printf("Jeste magican\n");
            else printf("Nije magican\n");
        }
        if(flp==7){
            int *a;
            int n;
            printf("unesit broj n: ");
            scanf("%d",&n);

            a = (int*)calloc(n*n, sizeof(int));

            printf("Uneti matricu pocetnog kvadrata:\n");

            int srv=0; // vrednost karakteristicnog zbira *n

            for(int i=0;i<n*n;i++){
                scanf("%d",&(*(a+i)));
                if(*(a+i)) srv+=*(a+i);
            }
            if(proverakvadrata(n,a,srv) && proverasuperkvadrata(n,a,srv)) printf("Jeste super magican\n");
            else printf("Nije super magican\n");
        }
        if(flp>7 || flp<1) break;
    }
    printf("kraj programa\n");
    return 0;
}
//4 1 14 4 15 8 11 5 10 13 2 16 3 12 7 9 6
//4 1 14 4 15 8 11 5 10 13 2 16 3 0 0 0 0 6 7 9 12
//4 0 0 0 0 0 0 0 0 0 0 0 3 12 7 9 6 13 10 5 11 8 15 4 14 1 2 16
//3 0 0 0 0 0 0 0 0 0 1 2 3 4 5 6 7 8 9
//3 4 9 2 3 5 0 0 0 0 7 8 1 6
