#include <iostream>
#include <fstream>

using namespace std;

class Coppie{
    private:
    int a, b;

    public:
    Coppie(int a, int b){
        this->a = a;
        this->b = b;
    }

    int getA() const {return a;}
    int getB() const {return b;}
};

ostream& operator <<(ostream& out, const Coppie c){
    return out << "(" << (double)(c.getA()/10.0) << "," << (double)(c.getB()/10.0) << ")";
}

int operator <(const Coppie c1, const Coppie c2){
    return ((c1.getA()<c2.getA()));
}

int operator >(const Coppie c1, const Coppie c2){
    return ((c1.getA()>c2.getA()));
}

int operator ==(const Coppie c1, const Coppie c2){
    return !(c1<c2 || c1>c2);
}

Coppie* findMax(Coppie** A, int n){
    Coppie* m = *A;
    for(int i=1; i<n; i++) m = *m<*(A[i])?A[i]:m;
    return m;
}

Coppie* findMin(Coppie** A, int n){
    Coppie* m = *A;
    for(int i=1; i<n; i++) m = *m>*(A[i])?A[i]:m;
    return m;
}

int K = 0;

int* CountingSort(Coppie** A, Coppie** B, int n){
    Coppie* min = findMin(A,n);
    Coppie* max = findMax(A,n);
    int mi = min->getA();
    int ma = max->getA();
    int k = ma - mi + 1;
    K = k;
    int* C = new int[k];
    for(int i=0; i<k; i++) C[i] = 0;
    for(int i=0; i<n; i++) C[(A[i])->getA()-mi]++;
    for(int i=1; i<k; i++) C[i] += C[i-1];
    for(int i=n-1;i>-1;i--){
        B[C[(A[i])->getA() - mi]-1] = A[i];
        C[(A[i])->getA() - mi]--;
    }
    return C;
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    int N = 0;
    double x = 0, y = 0;
    char put = ' ';
    for(int i=0; i<100; i++){
        in >> N;
        Coppie** A = new Coppie*[N];
        Coppie** B = new Coppie*[N];
        for(int j = 0; j<N; j++){
            in >> put >> x  >> y >> put;
            A[j] = new Coppie((int)(x*10),(int)(y*10));
        }
        int * C = CountingSort(A,B,N);
        for(int j = 0; j<K; j++) out << C[j] << " ";
        for(int j = 0; j<N; j++) out << *(B[j])<< " ";
        out << endl;
    }
    in.close();
    out.close();
    return 0;
}