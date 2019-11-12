#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

template<class T> class Heap{
	private:
		int len;
		int i;
		T *h;
	
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
		
		void MinHeapify(int j){
			int l = Left(j);
			int r = Right(j);
			int min;
			if(l!=-1 && h[l] < h[j]) min = l;
			else min = j;
			if(r!=-1 && h[r] < h[min]) min = r;
			if(min != j){
				T tmp = h[j];
				h[j] = h[min];
				h[min] = tmp;
				MinHeapify(min);
			}
		}
		
	public:
		Heap(int n){
			i = 1;
			len = n+1;
			h = new T[n+1];
		}

		Heap* insert(T k){
			if(i>len) return this;
			h[i++] = k;
			return this;
		}

		void BuildMinHeap(){
			for(int j = floor(i/2); j>=1; j--) MinHeapify(j);
		}
		
		T* getElement(int j) const { 
			if(j==0 || j>=len || j>i) return NULL;
			return h+j;
		}
		
		int getSize() const {return i;}
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
			h->BuildMinHeap();
			out << *h;
		}
		else {
			in >> N;
			Heap<double>* h = new Heap<double>(N);
			double  x = 0;
			for(int i=0; i<N; i++){
				in >> x;
				h->insert(x);
			}
			h->BuildMinHeap();
			out << *h;
		}
	}
	in.close();
	out.close();
	return 0;
}
