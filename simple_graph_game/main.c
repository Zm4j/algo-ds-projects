#include <stdio.h>
#include <stdlib.h>

int proveragrane(int *niz1, int *niz2,int g1,int g2){
    for(int i=niz2[g1]; i <niz2[g1+1];i++) if(niz1[i]==g2) return 1;
    return 0;
}

void dodavanjecvora(int *niz2,int *duzina2){
    niz2[*duzina2+1]=niz2[*duzina2];
    *duzina2+=1;
}

void dodavanjegrane(int *niz1, int *niz2,int *duzin2,int *duzin1){
    int g1,g2;
    scanf("%d",&g1);
    scanf("%d",&g2);
    int duzina1=*duzin1;
    int duzina2=*duzin2;
    if(g1>duzina2 || g2>duzina2 ){return;}
    if(proveragrane(niz1,niz2,g1,g2) || proveragrane(niz1,niz2,g2,g1) ) return;
    if(g2<g1){int c=g2;g2=g1;g1=c;}

    duzina1+=2;

    int x1=niz2[duzina2]-niz2[g1+1];
    int x2=niz2[duzina2]-niz2[g2+1];

    for(int i=0;i<x1+1;i++) niz1[duzina1-i-1]=niz1[duzina1-i-2-(i<x2 && g1!=g2)];

    for(int i=g1+1;i<=duzina2+1;i++) niz2[i]+=1+(i>=g2+1 && g1!=g2);

    //printf("\\\\\\\\ %d %d \\\\\\\\\\n",x1,x2);

    niz1[niz2[g1+1]-1]=g2;
    niz1[niz2[g2+1]-1]=g1;

    *duzin1+=1 + (g1!=g2);
}

void dodavanjegrane1(int *niz1, int *niz2,int *duzin2,int *duzin1){
    int g1,g2;
    scanf("%d",&g1);
    scanf("%d",&g2);
    int duzina1=*duzin1;
    int duzina2=*duzin2;
    if(g1>duzina2 || g2>duzina2 ){return;}
    if(proveragrane(niz1,niz2,g1,g2)) return;
    //if(g2<g1){int c=g2;g2=g1;g1=c;}

    duzina1+=1;

    int x1=niz2[duzina2]-niz2[g1+1];
    //int x2=niz2[duzina2]-niz2[g2+1];

    for(int i=0;i<x1+1;i++) niz1[duzina1-i-1]=niz1[duzina1-i-2];

    for(int i=g1+1;i<=duzina2+1;i++) niz2[i]+=1;

    //printf("\\\\\\\\ %d %d \\\\\\\\\\n",x1,x2);

    niz1[niz2[g1+1]-1]=g2;

    *duzin1+=1;
}

void brisanjegrane(int *niz1, int *niz2,int *duzin2,int *duzin1,int g1,int g2){
    int duzina1=*duzin1;
    int duzina2=*duzin2;
    if(g1>duzina2 || g2>duzina2){return;}
    if(!proveragrane(niz1,niz2,g1,g2) || !proveragrane(niz1,niz2,g2,g1) ) return;

    if(g2<g1){int c=g2;g2=g1;g1=c;}

    int indeks1,indeks2;
    for(int i=niz2[g1]; i <niz2[g1+1];i++) if(niz1[i]==g2) indeks1=i;
    for(int i=niz2[g2]; i <niz2[g2+1];i++) if(niz1[i]==g1) indeks2=i;

    for(int i=indeks1;i<duzina1-1-(g1!=g2);i++) niz1[i]=niz1[i+1+(i>=indeks2-1 && g1!=g2)];
    for(int i=g1+1;i<duzina2+1;i++) niz2[i]-=1+(i>=g2+1 && g1!=g2);

    *duzin1-=1+(g1!=g2);
}

void brisanjegrane1(int *niz1, int *niz2,int *duzin2,int *duzin1,int g1,int g2){
    int duzina1=*duzin1;
    int duzina2=*duzin2;
    if(g1>duzina2 || g2>duzina2){return;}
    if(!proveragrane(niz1,niz2,g1,g2)) return;

    //if(g2<g1){int c=g2;g2=g1;g1=c;}

    int indeks1,indeks2;
    for(int i=niz2[g1]; i <niz2[g1+1];i++) if(niz1[i]==g2) {indeks1=i;break;}
    //for(int i=niz2[g2]; i <niz2[g2+1];i++) if(niz1[i]==g1) indeks2=i;

    for(int i=indeks1;i<duzina1-1;i++) niz1[i]=niz1[i+1];
    for(int i=g1+1;i<duzina2+1;i++) niz2[i]-=1;

    *duzin1-=1;
}

void brisanjecvora(int *niz1, int *niz2,int *duzin2,int *duzin1,int g){
    int duzina2=*duzin2;
    if(g>=duzina2) return;
    //int j=niz2[g+1];
    while(niz2[g]!=niz2[g+1]){
        //printf("%d\n",niz2[g+1]);
        //brisanjegrane(niz1,niz2,duzin2,duzin1,niz1[niz2[g]],g);
        brisanjegrane1(niz1,niz2,duzin2,duzin1,niz1[niz2[g]],g);
        brisanjegrane1(niz1,niz2,duzin2,duzin1,g,niz1[niz2[g]]);
    }
    for(int i=g;i<duzina2;i++) niz2[i]=niz2[i+1];
    *duzin2-=1;
    int duzina1=*duzin1;
    for(int i=0;i<duzina1;i++) if(niz1[i]>g) niz1[i]--;
}

void brisanjegrafa(int *niz1,int *niz2, int *duzina2,int *duzina1){
    while(*duzina2)
        brisanjecvora(niz1,niz2,duzina2,duzina1,0);
}

void neljutisecovece(int *niz1,int *niz2, int *duzin2,int *duzin1,int g1,int g2,int **matrica){

    int duzina1=*duzin1;
    int duzina2=*duzin2;
    int velicina=0;
    int duzina=1;
    if(g1>duzina2 || g2>duzina2 || g1==g2){return;}

    for(int i=niz2[g1];i<niz2[g1+1];i++){
        matrica[velicina][0]=niz1[i];
        velicina++;
    }

    int maja=0;
    int sanja=0;
    int maja1=0;
    int sanja1=0;

    for(int ii=0;ii<2*duzina1;ii++){
        //provera
        for(int i=0;i<velicina;i++){
            if(matrica[i][duzina-1]==g2){
                //fmaja();
                if(maja1==0){
                    maja=1;
                    printf("%d->",g1);
                    for(int i1=0;i1<duzina;i1++) {printf("%d",matrica[i][i1]);if(i1<duzina-1) printf("->");}
                    printf("\n");
                    printf("duzina majinog puta je:%d\n",duzina);
                }
                //fsanja();
                if(sanja1==0 && duzina%3==1 || duzina%3==0){
                    sanja=1;
                    int sanjaduzina=0;
                    printf("%d->",g1);
                    for(int i1=0;i1<duzina;i1++) {
                        if(i1%3==1) {printf("(%d->)",matrica[i][i1]);}
                        else {printf("%d",matrica[i][i1]);if(i1<duzina-1) printf("->");sanjaduzina++;}
                    }
                    printf("\n");
                    printf("duzina sanjinog puta je:%d\n",sanjaduzina);
                    return;
                }
                //printf("provera\n");
            }
        }
        if(maja==1) maja1=1;
        if(sanja==1) sanja1=1;
        //dodavanje
        int velicina1=velicina;

        if(sanja && sanja1 && maja && maja1) return;

        for(int j=0;j<velicina;j++){
            int h=matrica[j][duzina-1];
            int viseod1=0;
            //printf("%d- ",h);
            for(int i=niz2[h];i<niz2[h+1];i++){
                if(viseod1==0){
                    viseod1=1;
                    matrica[j][duzina] = niz1[i];
                }

                else{
                    velicina1++;
                    for(int k=0;k<duzina;k++)
                        matrica[velicina1-1][k]=matrica[j][k];
                    matrica[velicina1-1][duzina]=niz1[i];
                }
            }
        }

        velicina=velicina1;
        duzina++;

    }
    for(int i=0;i<velicina;i++){
            if(matrica[i][duzina-1]==g2){
                //fmaja();
                if(maja1==0){
                    maja=1;
                    for(int i1=0;i1<duzina;i1++) printf("%d->",matrica[i][i1]);
                    printf("\n");
                    printf("duzina majinog puta je:%d\n",duzina);
                }
                //fsanja();
                if(sanja1==0 && duzina%3!=2){
                    sanja=1;
                    int sanjaduzina=0;
                    for(int i1=0;i1<duzina;i1++) {
                        if(i1%3==1) {printf("(%d->)",matrica[i][i1]);}
                        else {printf("%d->",matrica[i][i1]);sanjaduzina++;}
                    }
                    printf("\n");
                    printf("duzina sanjinog puta je:%d\n",sanjaduzina);
                }
                //printf("provera\n");
            }
        }


    /*
    for(int i=0;i<velicina;i++){
        for(int j=0;j<duzina;j++){
            printf("%d->",matrica[i][j]);
        }
        printf("\n");
    }
    printf("%d\n",velicina);*/

}

int main()
{
    int *niz1 = malloc(100*sizeof(int));
    int *niz2 = malloc(100*sizeof(int));
    int *duzina1 = malloc(sizeof(int));
    int *duzina2 = malloc(sizeof(int));
    *duzina1=0;
    *duzina2=0;
    *niz2=0;
    while(1){

        int h;
        printf("unesi 0 za dodavanje cvora\nunesi 1 za dodavanje neusmerene grane\nunesi 2 za dodavanje usmerene grane\nunesi 3 za brisanje neusmerene grane\nunesi 4 za brisanje usmerene grane\nunesi 5 za brisanje cvora\nunesi 6 za brisanje grafa\nunesi 7 za reprezentaciju grafa preko 2 niza\nunesi 8 za izvrsavanje zadatka\nunesi 9 za kraj programa:\n");
        scanf("%d",&h);
        //unos cvora
        if(h==0){
            dodavanjecvora(niz2,duzina2);
        }
        //unos grane
        if(h==1){
            dodavanjegrane(niz1,niz2,duzina2,duzina1);
        }
        if(h==3){
            int g1,g2;
            scanf("%d",&g1);
            scanf("%d",&g2);
            brisanjegrane(niz1,niz2,duzina2,duzina1,g1,g2);
        }
        if(h==5){
            int g;
            scanf("%d",&g);
            brisanjecvora(niz1,niz2,duzina2,duzina1,g);
        }
        if(h==6){
            brisanjegrafa(niz1,niz2,duzina2,duzina1);
        }

        if(h==2){
            dodavanjegrane1(niz1,niz2,duzina2,duzina1);
        }
        if(h==4){
            int g1,g2;
            scanf("%d",&g1);
            scanf("%d",&g2);
            brisanjegrane1(niz1,niz2,duzina2,duzina1,g1,g2);
        }
        if(h==7){
            printf("------------%d\n",*duzina2);
            for(int i=0;i<*duzina1;i++) printf("%d ", niz1[i]);
            printf("\n");
            for(int i=0;i<*duzina2+1;i++) printf("%d ",niz2[i]);
            printf("\n");
        }
        if(h==8){
            int g1,g2;
            scanf("%d",&g1);
            scanf("%d",&g2);
            int **matrica;
            matrica = malloc(1000 * sizeof(int*));
            for (int i=0;i<1000;i++)
                matrica[i]=(int*)malloc(1000*sizeof(int));
            neljutisecovece(niz1,niz2,duzina2,duzina1,g1,g2,matrica);
            for (int i=0;i<1000;i++)
                free(matrica[i]);
            free(matrica);
        }
        if(h==9){
            return 0;
        }

    }
//0 0 0 0 0 0 1 0 3 1 0 4 1 0 5 1 1 4 1 1 5 1 2 3 1 2 4 3 2 4 5 3 7

/*0 0 0 0 0 0 0 0 0 0 0
2 0 1
2 1 2
2 2 4
2 2 5
2 5 3
2 5 6
2 3 2
2 6 7
2 7 8

2 8 9
2 9 10
2 10 0
2 4 5

8 0 10
*/

/*
0 0 0 0 0 0
2 0 1
2 1 2
2 2 3
2 3 4
2 4 5
2 5 2
2 5 0
8 0 3

*/

}
