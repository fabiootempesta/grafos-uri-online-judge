#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Aresta{
private:
    int v1,v2,p;

public:
    Aresta(int ve1, int ve2, int pe){
        this->v1=ve1;
        this->v2=ve2;
        this->p=pe;
    }
    int getV1(){
        return this->v1;
    }

    int getV2(){
        return this->v2;
    }

    int getP(){
        return this->p;
    }

    bool operator<(const Aresta &a) const{
        return p<a.p;
    }
};

class Grafo{
private:
    int numV;
    vector<Aresta> arestas;

public:
    Grafo(){
        this->numV=0;
    }

    Grafo(int V){
        this->numV=V;
    }

    void setV(int V){
        this->numV=V;
    }

    void setAresta(int v1, int v2, int p){
        Aresta ar(v1,v2,p);
        arestas.push_back(ar);
    }

    void limpaGrafo(){
        numV=0;
        arestas.clear();
    }

    int buscar(int subset[], int v){
        if(subset[v]==-1){
            return v;
        }else{
            return buscar(subset,subset[v]);
        }
    }

    bool unir(int subset[], int v1, int v2){
        int v1Busca=buscar(subset,v1), v2Busca=buscar(subset,v2);
        if (v1Busca!=v2Busca){
            subset[v1Busca]=v2Busca;
            return true;
        }else{
            return false;
        }
    }
    int custoTotal(){
        int custo=0;
        for(int i = 0; i <arestas.size(); i++){
            custo+=arestas[i].getP() ;
        }
        return custo;
    }
    int custoKruskal(){
        sort(arestas.begin(), arestas.end());

        int *subset = new int[numV];
        for(int i=0;i<numV;i++)
            subset[i]=-1;

        int custo=0;
        for(int i=0; i<arestas.size();i++){
            if(unir(subset,arestas[i].getV1(),arestas[i].getV2()))
                custo+=arestas[i].getP();
        }
        return custo;
    }
};

int main()
{
    int numV=1, numArestas=1, v1, v2, p;
    Grafo g;

    while(numV!=0 && numArestas!=0){
        cin>>numV>>numArestas;
        g.setV(numV);
        if(numV!=0 && numArestas!=0){
            for(int i=0;i<numArestas;i++){
                cin>>v1>>v2>>p;
                g.setAresta(v1, v2, p);
            }
            cout<<g.custoTotal()-g.custoKruskal()<<endl;
            g.limpaGrafo();
        }
    }

    return 0;
}
