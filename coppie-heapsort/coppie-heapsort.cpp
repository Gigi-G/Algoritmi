#include <iostream>
#include <fstream>

using namespace std;

template<class T> class Coppie{
    private:
    T e1, e2;

    public:
    Coppie(T a, T b){
        e1 = a;
        e2 = b;
    }

    T getE1() const {return e1;}
    T getE2() const {return e2;}
};

template<class T> ostream& operator <<(ostream& os, const Coppie<T>& c){
    return os << "(" << c.getE1() << "," << c.getE2() << ")";
}

template<class T> int operator >(const Coppie<T> a, const Coppie<T> b) {
    if(!((a.getE1()<b.getE1()) || (a.getE1()==b.getE1() && a.getE2()<=b.getE2()))) return 1;
    return 0;
}

template<class H> class Heap{
    private:
    int heapsize, len, count;
    H** heap;

    void heapify(int i){
        count++;
        int l = i << 1;
        int r = (i << 1) | 1;
        int max = i;
        if(l<=heapsize && *heap[l] > *heap[max]) max = l;
        if(r<=heapsize && *heap[r] > *heap[max]) max = r;
        if(max!=i){
            H* tmp = *(heap+i);
            *(heap+i) = *(heap+max);
            *(heap+max) = tmp;
            heapify(max);
        }
    }

    public:
    Heap(int n){
        len = n+1;
        heap = new H*[len];
        count = 0;
        heapsize = 0;
    }

    void BuildMaxHeap() {
        for(int i = (heapsize>>1); i>=1; i--) heapify(i);
    }

    void HeapSort(){
        BuildMaxHeap();
        int hs = heapsize;
        for(int i=heapsize; i>=2; i--) {
            H* tmp = *(heap+i);
            *(heap+i) = *(heap+1);
            *(heap+1) = tmp;
            heapsize--;
            heapify(1);
        }
        heapsize = hs;
    }

    void insertElement(H k){
        if(heapsize+1>=len) return;
        heapsize++;
        *(heap+heapsize) = new H(k);
    }

    H* getElement(int i) const {
        if(i<=0 || i>heapsize) return NULL;
        return *(heap+i);
    }

    int getHeapSize() const {return heapsize;}

    int getHeapifyCount() const {return count;}
    
};

template<class H> ostream& operator <<(ostream& os, const Heap<H>& heap){
    int size = heap.getHeapSize();
    for(int i=1; i<=size; i++) os << *heap.getElement(i) << " ";
    return os;
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    int N = 0;
    string t = "";
    for(int i=0; i<100; i++){
        in >> t >> N;
        if(t=="char"){
            Heap<Coppie<char>>* heap = new Heap<Coppie<char>>(N);
            char x = ' ', y = ' ';
            char put = ' ';
            for(int j=0; j<N; j++){
                in >> put >> x >> y >> put;
                heap->insertElement(Coppie<char>(x,y));
            }
            heap->HeapSort();
            out << heap->getHeapifyCount() << " " << *heap << endl;
        }
        else {
            Heap<Coppie<double>>* heap = new Heap<Coppie<double>>(N);
            double x = 0, y = 0;
            char put = ' ';
            for(int j=0; j<N; j++){
                in >> put >> x >> y >> put;
                heap->insertElement(Coppie<double>(x,y));
            }
            heap->HeapSort();
            out << heap->getHeapifyCount() << " " << *heap << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}