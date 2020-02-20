#include <iostream>
#include <fstream>
#define INF 2000
#define CONV 99999
#define UN -2000

using namespace std;

template<class H> class NodeSet{
    private:
    H* set;
    int n;
    int i;

    public:
    NodeSet(int n){
        set = new H[n];
        this->n = n;
        i = 0;
    }

    void insert(H key){
        if(i>=n) return;
        set[i++] = key;
    }

    H getKey(int j){
        return set[j%n];
    }

    int getIndex(H key){
        for(int j=0; j<i; j++){
            if(set[j]==key) return j;
        }
        return -1;
    }
};

template<class G> class Graph{
    private:
    int** m;
    NodeSet<G>* nodeset;
    int n; 

    public:
    Graph(int n){
        this->n = n;
        m = new int*[n];
        for(int i=0; i<n; i++){
            m[i] = new int[n];
            for(int j=0; j<n; j++) m[i][j] = INF;
        }
        nodeset = new NodeSet<G>(n);
    }

    int GetLength() const {return n;}

    Graph* insertNode(G key){
        nodeset->insert(key);
        return this;
    }

    void insertEdge(G x, G y, int p){
        int i = nodeset->getIndex(x);
        int j = nodeset->getIndex(y);
        if(i == -1 || j == -1) return;
        m[i][j] = p;
    }

    int existEdge(G x, int i){
        int j = nodeset->getIndex(x);
        return m[j][i];
    }

    int existEdge2(int i, int j){
        return m[i][j];
    }

    G nodevalue(int i){
        return nodeset->getKey(i);
    }

    int IndexNode(G key){
        return nodeset->getIndex(key);
    }

    void print(){
        for(int i=0; i<n; i++){
            cout << nodeset->getKey(i) << "|-> ";
            for(int j=0; j<n; j++){
                if(m[i][j]!=INF) cout << nodeset->getKey(j) << " ";
            }
            cout << endl;
        }
    }
};

int Conv(int *c, int n){
    for(int i=0; i<n; i++){
        if(c[i] == 0) return 1;
    }
}

template<class H> void Dijkstra(Graph<H>& g, double s, double dest, ostream& out){
    int *d = new int[g.GetLength()];
    int *c = new int[g.GetLength()];
    for(int i=0; i<g.GetLength(); i++) {
        d[i] = INF;
        c[i] = 0;
    }
    d[g.IndexNode(s)] = 0;
    while(Conv(c,g.GetLength())){
        int min = 0;
        int min_index = INF;
        for(int i=0; i<g.GetLength(); i++){
            if(min_index>d[i] && c[i]==0) {
                min_index = d[i];
                min = i;
            }
        }
        c[min] = 1;
        if(g.nodevalue(min) == dest) {
            out << d[min] << endl;
            return;
        }
        for(int j=0; j<g.GetLength(); j++){
            if(!c[j] && g.existEdge2(min,j)!=INF && d[j]>d[min]+g.existEdge2(min,j)){
                d[j]=d[min]+g.existEdge2(min,j);
            }
        }
    }
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    int V = 0, E = 0;
    string t = "";
    for(int k=0; k<100; k++){
        in >> V >> E >> t;
        Graph<double>* g = new Graph<double>(V);
        double v1 = 0, v2 = 0, d= 0;
        for(int i = 0; i<V; i++){
            in >> v1;
            g->insertNode(v1);
        }
        char p =' ';
        for(int i=0; i<E; i++){
            //in >> p >> v1 >> p >> v2 >> p >> d >> p;
            in >> p >> v1 >> v2 >> d >> p;
            g->insertEdge(v1,v2,d);
        }
        double s = 0, dest = 0;
        in >> s >> dest;
        Dijkstra(*g,s,dest,out);
    }
    in.close();
    out.close();
    return 0;
}