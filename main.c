#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
typedef struct pereche{
    int u, v, nr;
    float *transoane;
} *Pereche;

float max(float a, float b){
    if (a>b)
        return a;
    return b;
}
int min(int a, int b){
    if(a<b)
        return a;
    return b;
}
int main(int argc, char *argv[]){
    char **orase = malloc(100 * sizeof(char*));
    for(int i =0;i<100;++i){
        orase[i] = malloc(100 * sizeof(char));
    }
    int cnt = 0;
    if(strcmp(argv[1],"1")==0){
        Pereche perechi = (Pereche) malloc(100 * sizeof(struct pereche));
        for(int i=0;i<100;++i)
            perechi[i].transoane = malloc(100 * sizeof(float));
        Graph g = initGraph(100, 1);
        int nrRute, nrAni;
        float uzuraMaxima;
        char *a = malloc(100 * sizeof(char));
        char *b = malloc(100 * sizeof(char));
        int nrTransoane;
        float *transoane = malloc(100 * sizeof(float));
        scanf("%d%d%f", &nrRute, &nrAni, &uzuraMaxima);
        for(int i=0;i<nrRute;++i){
            scanf("%s%s%d", a, b, &nrTransoane);
            int u = -1, v = -1;
            for(int l=0;l<cnt && u==-1;++l){
                if(strcmp(a, orase[l])==0)
                    u = l;
            }
            if(u == -1){
                u = cnt;
                strcpy(orase[cnt++], a);
            }
            for(int l=0;l<cnt && v == -1;++l){
                if(strcmp(b, orase[l])==0)
                    v = l;
            }
            if(v == -1){
                v = cnt;
                strcpy(orase[cnt++], b);
            }
            for(int j=0;j<nrTransoane;++j)
                scanf("%f", &transoane[j]);
            perechi[i].u = u;
            perechi[i].v = v;
            perechi[i].nr = nrTransoane;
            for(int j=0;j<nrTransoane;++j)
                perechi[i].transoane[j] = transoane[j];
            insertEdge(g, u, v, 0);
        }
        for(int ii=0;ii<nrAni;++ii){
            for(int i=0;i<nrRute;++i){
                for(int j=0;j<perechi[i].nr;++j){
                    perechi[i].transoane[j] *= 2;
                    if(perechi[i].transoane[j]>100)
                        perechi[i].transoane[j] = 100;
                }
            }

            for(int i=0;i<nrRute;++i){
                for(int j=1;j<perechi[i].nr-1;++j){
                    if(perechi[i].transoane[j] == 0)
                        perechi[i].transoane[j] = max(perechi[i].transoane[j-1],perechi[i].transoane[j+1])/4;
                }
            }
            float *maxi = calloc(nrRute, sizeof(float));
            for(int i=0;i<nrRute;++i){
                if(perechi[i].transoane[0] == 0){
                    maxi[i] = perechi[i].transoane[1];
                    for(int j=0;j<nrRute;++j){
                        if(isArc(g, perechi[j].u, perechi[i].u)){
                            if(maxi[i] < perechi[j].transoane[perechi[j].nr-1])
                                maxi[i] = perechi[j].transoane[perechi[j].nr-1];
                        }
                    }
                }
            }

            float *maxf = calloc(nrRute, sizeof(float));
            for(int i=0;i<nrRute;++i){
                if(perechi[i].transoane[perechi[i].nr-1] == 0){
                    maxf[i] = perechi[i].transoane[perechi[i].nr-2];
                    for(int j=0;j<nrRute;++j){
                        if(isArc(g, perechi[i].u, perechi[j].u)){
                            if(maxf[i]< perechi[j].transoane[0])
                                maxf[i] = perechi[j].transoane[0];
                        }
                    }
                }
            }
            for(int i=0;i<nrRute;++i){
                if(perechi[i].transoane[0] == 0)
                    perechi[i].transoane[0] = maxi[i]/4;
                if(perechi[i].transoane[perechi[i].nr-1] == 0)
                    perechi[i].transoane[perechi[i].nr-1] = maxf[i]/4;
            }
            free(maxi);
            free(maxf);
        }
        int cntSol = 0;
        int *solutie = calloc(nrRute, sizeof(int));
        for(int i=0;i<nrRute;++i){
            printf("%s %s %d ", orase[perechi[i].u], orase[perechi[i].v], perechi[i].nr);
            float medie = 0;
            for(int j=0;j<perechi[i].nr;++j){
                printf("%.2f ", perechi[i].transoane[j]);
                medie += perechi[i].transoane[j];
            }
            medie /= perechi[i].nr;
            if(medie<uzuraMaxima)
                solutie[cntSol++] = i+1;
            printf("\n");
        }
        for(int i=0;i<cntSol;++i)
            printf("%d ", solutie[i]);
        free(solutie);
        free(transoane);
        free(a);
        free(b);
        freeGraph(g);
        for(int i=0;i<100;++i)
            free(perechi[i].transoane);
        free(perechi);
    }
    if(strcmp(argv[1], "2")==0){
        Graph g = initGraph(100, 0);
        char *a = malloc(100 * sizeof(char));
        char *b = malloc(100 * sizeof(char));
        Pereche perechi = (Pereche) malloc(100 * sizeof(struct pereche));
        int muchiiMax;
        int muchii;
        int cnt =0;
        int cost;
        scanf("%s%d%d", a, &muchiiMax, &muchii);
        strcpy(orase[cnt++],a);
        for(int i=0;i<muchii;++i){
            scanf("%s%s%d",a,b,&cost);
            int u = -1, v = -1;
            for(int l=0;l<cnt && u==-1;++l){
                if(strcmp(a, orase[l])==0)
                    u = l;
            }
            if(u == -1){
                u = cnt;
                strcpy(orase[cnt++], a);
            }
            for(int l=0;l<cnt && v == -1;++l){
                if(strcmp(b, orase[l])==0)
                    v = l;
            }
            if(v == -1){
                v = cnt;
                strcpy(orase[cnt++], b);
            }
            perechi[i].u = u;
            perechi[i].v = v;
            perechi[i].nr = cost;
            insertEdge(g, u, v, cost);
        }   
        List result = Prim(g, 0);
        List sol = result;
        int minim = min(muchiiMax, cnt-1);
        for(int i=0;i<minim-1;++i){
            sol = sol->next;
        }
        sol->next = NULL;
        sol = result;
        printf("%d\n", minim);
        for(int i=0;i<muchii;++i){
            sol = result;
            while(sol){
                if(sol->data.u == perechi[i].u && sol->data.v == perechi[i].v)
                    printf("%s %s\n", orase[perechi[i].u], orase[perechi[i].v]);
                if(sol->data.u == perechi[i].v && sol->data.v == perechi[i].u)
                    printf("%s %s\n", orase[perechi[i].u], orase[perechi[i].v]);
                sol = sol->next;
            }
        }
        int counter = 0;
        freeList(result);
        free(perechi);
        free(a);
        free(b);
        freeGraph(g);
    }
    for(int i=0;i<100;++i){
        free(orase[i]);
    }
    free(orase);
}