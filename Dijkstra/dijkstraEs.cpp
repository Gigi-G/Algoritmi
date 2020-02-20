#include <iostream>
#include <fstream>
#define INF 999999

using namespace std;

template<class H> class Nodeset{
    private:
    H* node;
    int n, count;

    public:
    Nodeset(int n){
        count = 0;
        this->n = n;
        node = new H[n];
    }

    void InsertNode(H k){
        if(count>=n) return;
        node[count++] = k;
    }

    H getValue(int i){
        return node[i%count];
    }

    int getIndex(H key){
        for(int i=0; i<count; i++){
            if(node[i] == key) return i;
        }
        return INF;
    }

    int getSize() const {return n;}
};

template<class H> class Graph{
    private:
    Nodeset<H> *g;
    int n;
    int **m;

    public:
    Graph(int n){
        this->n = n;
        m = new int*[n];
        for(int i=0; i<n; i++){
            m[i] = new int[n];
            for(int j=0; j<n; j++) m[i][j] = INF;
        }
        g = new Nodeset<H>(n);
    }

    void InsertVertex(H key){
        g->InsertNode(key);
    }

    H getVertex(int i){
        return g->getValue(i);
    }

    int getIndex(H key){
        return g->getIndex(key);
    }

    void InsertEdge(H x, H y, int w){
        int i = g->getIndex(x);
        int j = g->getIndex(y);
        if(i == INF || j == INF) return;
        m[i][j] = w;
    }

    int getEdgeByIndex(int i, int j){
        return m[i][j];
    }

    int getEdgeByValue(H x, H y){
        int i = g->getIndex(x);
        int j = g->getIndex(y);
        if(i == INF || j == INF) return -1;
        return m[i][j];
    }

    void print(){
        for(int i=0; i<g->getSize(); i++){
            cout << g->getValue(i) << "|-> ";
            for(int j=0; j<g->getSize(); j++){
                if(m[i][j]!=INF) cout << g->getValue(j) << " ";
            }
            cout << endl;
        }
    }

    int getSize() const {return n;}

};

int Conv(int *c, int n){
    for(int i=0; i<n; i++){
        if(c[i] == 0) return 1;
    }
    return 0;
}

template<class H> void Dijkstra(Graph<H>& g, double s, double dest, ostream& out){
    int n = g.getSize();
    int d[n];
    int c[n];
    for(int i=0; i<n; i++){
        d[i] = INF;
        c[i] = 0;
    }
    d[g.getIndex(s)] = 0;
    int min = 0, min_val = INF;
    while(Conv(c,n)){
        min = 0;
        min_val = INF;
        for(int i=0; i<n; i++){
            if(d[i]<min_val && c[i]==0){
                min = i;
                min_val = d[i];
            }
        }
        c[min] = 1;
        if(dest == g.getVertex(min)) {
            out << d[min] << endl;
            return;
        }
        else if(d[min] == INF) break;
        for(int i=0; i<n; i++){
            if(!c[i] && g.getEdgeByIndex(min,i)!=INF && d[i]>d[min]+g.getEdgeByIndex(min,i)){
                d[i] = d[min] + g.getEdgeByIndex(min,i);
            }
        }
    }
    out << "inf" << endl;
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    int V = 0, E = 0;
    double x, y, w, S, D;
    string t = "";
    Graph<double> *g;
    char p = ' ';
    for(int k=0; k<100; k++){
        in >> V >> E >> t;
        g = new Graph<double>(V);
        for(int i = 0; i<V; i++){
            in >> x;
            g->InsertVertex(x);
        }
        for(int i = 0; i<E; i++){
            in >> p >> x >> y >> w >> p;
            g->InsertEdge(x,y,w);
        }
        in >> S >> D;
        Dijkstra(*g, S, D, out);
    }
    in.close();
    out.close();
    return 0;
}