#include <iostream>
#include <fstream>

#define INPUT   "input.txt"
#define OUTPUT  "output.txt"

using namespace std; 

template <class T> class MaxHeap {

    int arraySize; 
    int heapSize; 
    T * array; 

    // only for ex. purpouse
    int heapifyTimes; 

    int _parent (int node)   { return node >> 1; }
    int _right  (int node)   { return (node << 1) | 1; }
    int _left   (int node)   { return node << 1; }

    int lastNodeWithSon() 
    {
        return this->heapSize / 2; 
    }

    void _swap(int i, int j) 
    {
        T tmp = this->array[i]; 
        this->array[i] = this->array[j]; 
        this->array[j] = tmp; 
    }

    void heapify(int node)
    {
        heapifyTimes ++; 
        int l = _left(node); 
        int r = _right(node); 
        int max = node; 
        if ( l <= heapSize-1 && array[l] > array[max]) {
            max = l; 
        }
        if ( r <= heapSize-1 && array[r] > array[max]) {
            max = r; 
        }
        if (max != node) {
            _swap(max, node);
            heapify(max);  
        }
    }

    public: 

    MaxHeap(int size)
    {
        this->arraySize = size + 1; 
        this->heapSize  = 1; 
        this->array = new T[arraySize]; 
        this->heapifyTimes = 0;  
    }

    void enqueue(T key)
    {
        if (heapSize >arraySize ) return; 
        int tmp = this->heapSize;
        while (tmp > 1 && array[_parent(tmp)] < key) {
            array[tmp] = array[_parent(tmp)];
            tmp = _parent(tmp); 
        }
	array[tmp] = key;
	this->heapSize++;
    }

    T* extractMax()
    {
        if (heapSize-1) {  
		T max = array[1]; 
		array[1] = array[heapSize-1]; 
		heapSize--;
		if(heapSize-1) {
			heapify(1);
			return new T(max); 
		}
	}
	return NULL;
    }

    void analyzeContent()
    {
        for (int i = 1; i < this->heapSize; i++) {
            cout << this->array[i] << " "; 
        }
        cout << endl; 
    }

    void printSolution(fstream& out)
    {
        out << heapifyTimes << " "; 
        for (int i = 1; i < this->heapSize; i++) 
            out << this->array[i] << " "; 
        out << endl;
    }

}; 

template <class T> void process(int size, fstream &in, fstream &out) 
{
    char ch;
    string outfill; 
    MaxHeap<T> mh(size); 

    for (int i = 0; i < size; i++) {
        in >> ch >> ch;
        if (ch == 'x') {
            mh.extractMax(); 
            in >> outfill; 
        }
        else {
            T key; 
            in >> key; 
            mh.enqueue(key); 
        }
    }

    mh.printSolution(out); 
}

int main()
{
    fstream infile, outfile; 
    infile.open(INPUT, fstream::in);
    outfile.open(OUTPUT, fstream::out);

    string type; 
    int inputSize;

    while(!infile.eof()) {

        infile >> type >> inputSize; 
        if (!infile.eof()) {

            if (type == "int")      process<int>    (inputSize, infile, outfile); 
            if (type == "char")     process<char>   (inputSize, infile, outfile); 
            if (type == "bool")     process<bool>   (inputSize, infile, outfile); 
            if (type == "double")   process<double> (inputSize, infile, outfile); 

        }
    }

    infile.close(); 
    outfile.close(); 
}