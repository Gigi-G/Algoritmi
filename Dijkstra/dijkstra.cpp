#include <iostream>
#include <fstream>
#define INF 2000

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

    G nodevalue(int i){
        return nodeset->getKey(i);
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

template<class H> class Coppie{
    public:
    H v;
    int d;

    Coppie(){
        v = INF;
        d = INF;
    }
};

template<class H> class Heap{
    private:
    Coppie<H>* c;
    int n;
    int p;

    int _getRight(int node) {return (node<<1) | 1;}

    int _getLeft(int node) {return node<<1;}

    int _getParent(int node) {return node>>1;}

    void Heapify(int i){
        int r = _getRight(i);
        int l = _getLeft(i);
        int min = i;
        if(l<p && c[l].d<c[min].d) min = l;
        if(r<p && c[r].d<c[min].d) min = r;
        if(min != i){
            Coppie<H> tmp = c[i];
            c[i] = c[min];
            c[min] = tmp;
            Heapify(min);
        }
    }

    public:
    Heap(int n){
        this->n=n+1;
        c = new Coppie<H>[n+1];
        p = 1;
    }

    Heap<H>* Insert(H key){
        if(p>=n) return this;
        c[p].d = INF;
        c[p++].v = key;
        return this;
    }

    void print(){
        for(int i=1; i<p; i++) cout << c[i].v << " " << c[i].d << "; ";
        cout << endl;
    }

    void HeapDecrease(H key, int dist){
        int i = -1;
        for(int j=1; j<p; j++){
            if(c[j].v == key) i = j;
        }
        if(i == -1) return;
        if(dist>c[i].d) return;
        c[i].d = dist;
        while(i>1 && c[_getParent(i)].d>c[i].d){
            Coppie<H> tmp = c[i];
            c[i] = c[_getParent(i)];
            c[_getParent(i)] = tmp;
            i = _getParent(i);
        }
    }

    Coppie<H>* ExtractMin(){
        Coppie<H>* cc = NULL;
        if(p<1) return cc;
        cc = new Coppie<H>();
        cc->d = c[1].d;
        cc->v = c[1].v;
        p = p-1;
        c[1] = c[p];
        Heapify(1);
        return cc;
    }

    int getSize() const{return p-1;}
};

template<class H> int Dijkstra(Graph<H> *g, H s, H dest, Coppie<H>* d, int V){
    int dist = 0;
    Heap<H> *h = new Heap<H>(V);
    for(int i=0; i<V; i++) h->Insert(g->nodevalue(i));
    int i = 0;
    h->HeapDecrease(s,0);
    while(h->getSize()>0){
        Coppie<H>* c = h->ExtractMin();
        d[i].d = c->d;
        d[i].v = c->v;
        dist = d[i].d;
        if(c->d == INF || d[i].v == dest) break;
        for(int j = 0; j<V; j++){
            dist = g->existEdge(c->v,j);
            h->HeapDecrease(g->nodevalue(j),d[i].d+dist);
        }
        i++;
    }
    return dist;
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
        Coppie<double>* c = new Coppie<double>[V];
        out << Dijkstra(g,s,dest,c,V) << endl;
    }
    in.close();
    out.close();
    return 0;
}