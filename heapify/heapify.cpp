#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

template<class T> class Heap{
	private:
		int len;
		int i;
		T *h;
		int count;
	
		int Parent(int j){
			if(j==0 || floor(j/2)<1) return -1;
			return floor(j/2);
		}

		int Left(int j){
			if(j==0 || j*2>i-1) return -1;
			return j*2;
		}

		int Right(int j){
			if(j==0 || j*2+1>i-1) return -1;
			return j*2+1;
		}
		
		void MaxHeapify(int j){
			count++;
			int l = j << 1;
			int r = (j << 1) | 1;
			int max;
			if(l<=i-1 && h[l] > h[j]) max = l;
			else max = j;
			if(r<=i-1 && h[r] > h[max]) max = r;
			if(max != j){
				T tmp = h[j];
				h[j] = h[max];
				h[max] = tmp;
				MaxHeapify(max);
			}
		}
		
	public:
		Heap(int n){
			i = 1;
			len = n;
			h = new T[n+1];
			count = 0;
		}

		Heap* maxEnqueue(T k){
			if(i>len) return this;
			int j = i;
			while(j>1 && h[Parent(j)]<k){
				h[j] = h[Parent(j)];
				j = Parent(j);
			}
			h[j] = k;
			i++;
			return this;
		}
		
		Heap* insert(T k){
			h[i++] = k;
			return this;
		}
		
		T* extractMax() {
			if(len) {
				T* el = h+1;
				h[1] = h[len--];
				i--;
				if(len) {
					MaxHeapify(1);
					return el;
				}
			}
			return NULL;
		}

		void BuildMaxHeap(){
			for(int j = floor((i-1)/2); j>=1; j--) {MaxHeapify(j);}
		}
		
		T* getElement(int j) const { 
			if(j==0 || j>=len || j>i) return NULL;
			return h+j;
		}
		
		int getSize() const {return i;}
		
		int getCountHeapify() const {return count;}
};

template<class T> ostream& operator << (ostream& os, const Heap<T>& h){
	int len = h.getSize();
	for(int i = 1; i<len; i++) os << *h.getElement(i) << " ";
	os << endl;
	return os;
}

int main(){
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	string t = "";
	int N = 0;
	for(int i=0; i<100; i++){
		in >> t;
		if(t == "char") {
			in >> N;
			Heap<char>* h = new Heap<char>(N);
			char  x = ' ';
			for(int i=0; i<N; i++){
				in >> x;
				h->insert(x);
			}
			h->BuildMaxHeap();
			for(int i=0; i<N; i++) {
				h->extractMax();
			}
			out << h->getCountHeapify() << endl;
		}
		else {
			in >> N;
			Heap<double>* h = new Heap<double>(N);
			double  x = 0;
			for(int i=0; i<N; i++){
				in >> x;
				h->insert(x);
			}
			h->BuildMaxHeap();
			for(int i=0; i<N; i++) {
				h->extractMax();
			}
			out << h->getCountHeapify() << endl;
		}
	}
	in.close();
	out.close();
	return 0;
}
