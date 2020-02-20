#include <iostream>
#include <fstream>

using namespace std;

template<class H> class Heap{
    private:
    int heapsize, len, count;
    H* heap;

    void heapify(int i){
        count++;
        int l = i << 1;
        int r = (i << 1) | 1;
        int m = i;
        if(l<=heapsize && heap[l] < heap[m]) m = l;
        if(r<=heapsize && heap[r] < heap[m]) m = r;
        if(m!=i){
            H tmp = heap[m];
            heap[m] = heap[i];
            heap[i] = tmp;
            heapify(m);
        } 
    }
    

    public:
    Heap(int n){
        this->len = n+1;
        heapsize = 0;
        count = 0;
        heap = new H[n+1];
    }

    void insert(H k){
        if(heapsize+1>=len) return;
        heap[++heapsize] =  k;
    }

    void BuildMinHeap(){
        for(int i = (heapsize>>1); i>0; i--) heapify(i);
    }

    void HeapSort(){
        BuildMinHeap();
        int hsize = heapsize;
        for(int i = hsize; i>1; i--){
            H tmp = heap[1];
            heap[1] = heap[i];
            heap[i] = tmp;
            heapsize--;
            heapify(1); 
        }
        heapsize = hsize;
    }

    H* extraxrMax(){
        if(heapsize){
            H* tmp = heap + 1;
            heap[1] = heap[heapsize--];
            if(heapsize){
                heapify(1);
                return tmp;
            }
        }
        return NULL;
    }

    H* getElement(int i) const {
        if(i<=0 || i>heapsize) return NULL;
        return heap+i;
    }

    int getSize() const {return heapsize;}

    int getHeapifyCount() const {return count;}

};

template<class H> ostream& operator <<(ostream& os, const Heap<H>& heap){
    int heapsize = heap.getSize();
    for(int i=1; i<=heapsize; i++) os << *(heap.getElement(i)) << " ";
    return os;
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string type="";
    int N = 0;
    for(int i=0; i<100; i++){
        in >> type;
        if(type == "char"){
            in >> N;
            Heap<char>* heap = new Heap<char>(N);
            char x = ' ';
            for(int j=0; j<N; j++){
                in >> x;
                heap->insert(x);
            }
            heap->HeapSort();
            out << heap->getHeapifyCount() << " " << *heap << endl;
        }
        else{
            in >> N;
            Heap<double>* heap = new Heap<double>(N);
            double x = 0;
            for(int j=0; j<N; j++){
                in >> x;
                heap->insert(x);
            }
            heap->HeapSort();
            out << heap->getHeapifyCount() << " " << *heap << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}