#include <iostream>
#include <fstream>
#define INPUT "input.txt"
#define OUTPUT "output.txt"
#define INF 999999
#define UNDF 888888

using namespace std;

template<class H> class NodeSet{
    private:
    H* node;
    int n, c;

    public:
    NodeSet(int n){
        c = 0;
        this->n = n;
        node = new H[n];
    }

    void InsertKey(H key){
        if(c>=n) return;
        node[c++] = key;
    }

    H GetKey(int i){
        return node[i%c];
    }

    int GetIndex(H key){
        for(int i=0; i<c; i++){
            if(node[i] == key) return i;
        }
        return -1;
    }

    int GetN() const {return c;}
};

template<class H> class Graph{
    private:
    H** m;
    NodeSet<H>* g;
    int n;

    public:
    Graph(int n){
        this->n = n;
        g = new NodeSet<H>(n);
        m = new H*[n];
        for(int i=0; i<n; i++){
            m[i] = new H[n];
            for(int j=0; j<n; j++) m[i][j] = INF;
        }
    }

    void InsertVertex(H key){
        g->InsertKey(key);
    }

    void InsertEdge(H x, H y, H w){
        int i = g->GetIndex(x);
        int j = g->GetIndex(y);
        if(i == -1 || j == -1) return;
        m[i][j] = w;
    }

    H GetVertexValue(int i) const{
        return g->GetKey(i);
    }

    int GetVertexIndex(H key){
        int i = g->GetIndex(key);
        return i;
    }

    int EdgeByIndex(int i, int j) const{
        return m[i][j];
    }

    int EdgeByValue(H x, H y) const{
        int i = g->GetIndex(x);
        int j = g->GetIndex(y);
        if(i == -1 || j == -1) return INF;
        return m[i][j];
    }

    int GetLength() const {return g->GetN();}
};

template<class H> ostream& operator<<(ostream& out, const Graph<H>& g){
    int n = g.GetLength();
    for(int i=0; i<n; i++){
        out << g.GetVertexValue(i) << "|->[ ";
        for(int j=0; j<n; j++){
            if(g.EdgeByIndex(i,j)!=INF) out << g.GetVertexValue(j)<<" ";
        }
        out << "]" << endl;
    }
    return out;
}

template<class H> double bellman_ford(Graph<H>* G, double S, double D){
    double* d = new double[G->GetLength()];
    for(int i=0; i<G->GetLength(); i++){
        d[i] = INF;
    }
    d[G->GetVertexIndex(S)] = 0;
    for(int i=0; i<G->GetLength(); i++){
        for(int x=0; x<G->GetLength(); x++){
            for(int y=0; y<G->GetLength(); y++){
                if(d[y]>d[x]+G->EdgeByIndex(x,y)){
                    d[y] = d[x]+G->EdgeByIndex(x,y);
                }
            }
        }
    }
    for(int x=0; x<G->GetLength(); x++){
        for(int y=0; y<G->GetLength(); y++){
            if(d[y]>d[x]+G->EdgeByIndex(x,y) && d[y]!=INF){
                return UNDF;
            }
        }
    }
    return d[G->GetVertexIndex(D)];
}

int main(){
    ifstream in;
    ofstream out;
    in.open(INPUT);
    out.open(OUTPUT);
    int V, E;
    double S, D;
    double k = 0, s = 0, d = 0, w = 0;
    string type = "";
    char put = ' ';
    Graph<double> *G; 
    for(int g=0; g<100; g++){
        in >> V >> E >> type;
        G = new Graph<double>(V);
        for(int i=0; i<V; i++){
            in >> k;
            G->InsertVertex(k);
        }
        for(int i=0; i<E; i++){
            //in >> put >> s >> put >> d >> put >> w >> put;
            in >> put >> s >> d >> w >> put;
            G->InsertEdge(s,d,w);
        }
        in >> S >> D;
        d = bellman_ford(G,S,D);
        if(d == INF) out << "inf." << endl;
        else if(d == UNDF) out << "undef." << endl;
        else out << d << endl;
    }
    in.close();
    out.close();
    return 0;
}