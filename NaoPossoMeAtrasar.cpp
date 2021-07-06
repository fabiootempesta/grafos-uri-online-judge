#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Vertice{
private:
    int id;
    string nome;
    bool open;
    int dijkstraD; //menor distância encontrada
    int dijkstraP; //pai


public:

    int getId(){return id;}

    void setId(int n){id=n;}

    bool getOpen(){return open;}

    void setOpen(bool n){open=n;}

    void setD(int v){dijkstraD=v;}

    int getD() const{return dijkstraD;}

    void setP(int v){dijkstraP=v;}

    int getP(){return dijkstraP;}

    string getNome(){return nome;}

    void setNome(string n){nome=n;}

    bool operator<(const Vertice &other) const {return this->dijkstraD < other.getD();}

};

struct compDistancia
{
    bool operator()(Vertice  *v1, Vertice *v2){
        return v1->getD()>v2->getD();
    }
};

class Adjacencia{
private:
    int v2;
    int peso;

public:
    void setV2(int v){v2=v;}
    void setPeso(int p){peso=p;}
    int getV2(){return v2;}
    int getPeso(){return peso;}
};

class Grafo{
private:
    int numV;
	vector<Vertice> Vertices;
    vector<list<Adjacencia>> listaAdjacencia;


public:
    void inicializa(){
        numV=0;
        listaAdjacencia.clear();
        Vertices.resize(0);
        listaAdjacencia.resize(0);
    }

    void limpa(){
        numV=0;
        Vertices.clear();
        listaAdjacencia.clear();
    }

    int getNV(){return numV;}

    void addVertice(string nome, int &i){
        Vertice v;
        v.setNome(nome);
        v.setD(INT_MAX);
        v.setP(-1);
        v.setId(numV);
        v.setOpen(false);
        Vertices.push_back(v);
        numV++;
        listaAdjacencia.resize(numV);
        i=v.getId();

    }

    void addAresta(int v1, int v2, int peso){

        Adjacencia a;
        a.setPeso(peso);
        a.setV2(v2);
        listaAdjacencia[v1].push_back(a);
    }

    int nome2id(string n){
        int x=-1;
        for(int i=0;i<numV;i++){
            if(Vertices[i].getNome()==n){
                x=Vertices[i].getId();
                break;
            }
        }
        return x;
    }

    void dijkstra(Vertice &origem){
        //não convém implementar o conjunto de vértices finalizados (S) para esta aplicação!
        origem.setD(0);
        Vertice *u;
        vector<Vertice*> Q;
        for(int i=0;i<numV;i++)
            Q.push_back(&Vertices[i]);

        sort(Q.rbegin(),Q.rend());

        while(!Q.empty()){
            //imprime();

            u=Q.back();


            Q.pop_back();


            list<Adjacencia>::iterator it;

            for(it = listaAdjacencia[u->getId()].begin(); it != listaAdjacencia[u->getId()].end(); it++){
                if(Vertices[it->getV2()].getD()>(u->getD()+it->getPeso()) && u->getD()!=INT_MAX){
                    Vertices[it->getV2()].setP(u->getId());
                    Vertices[it->getV2()].setD(u->getD()+it->getPeso());
                    sort(Q.rbegin(),Q.rend());
                }
            }


        }
    }

    string formatarResposta(int minutosOnibus, int minutosPonto){
        string respostaFormatada="";
        int horas=17;
        if(minutosPonto<=30)
            minutosOnibus+=30;
        else
            minutosOnibus+=50;
        while(minutosOnibus>=60){
            horas++;
            minutosOnibus-=60;
        }
        if(minutosOnibus<10)
            respostaFormatada=to_string(horas)+":0"+to_string(minutosOnibus)+"\n";
        else
            respostaFormatada=to_string(horas)+":"+to_string(minutosOnibus)+"\n";

        if(horas>17 && minutosOnibus>0)
            respostaFormatada+="Ira se atrasar";
        else
            respostaFormatada+="Nao ira se atrasar";

        return respostaFormatada;





    }

    string respostaFinal(int X){
        dijkstra(Vertices[nome2id("varzea")]);
        string r=formatarResposta(Vertices[nome2id("alto")].getD(),X);

        return r;

    }


};

int main(int argc, char *argv[])
{
    int X,N,V,T,v1,v2;
    string r="", O,D;
    Grafo g;
    g.inicializa();
    cin>>X>>N>>V;
    if(X!=0 && N!=0 && V!=0){
        while(!(X==0 && N==0 && V==0)){
            for(int i=0;i<N;i++){
                cin>>O>>D>>T;
                v1=g.nome2id(O);
                v2=g.nome2id(D);
                if(v1==-1)
                    g.addVertice(O,v1);
                if(v2==-1){
                    g.addVertice(D,v2);
                }
                g.addAresta(v1,v2,T);
                //g.imprime();
            }
            cout<<g.respostaFinal(X)<<endl;
            g.limpa();
            cin>>X>>N>>V;
        }

    }
    return 0;
}
