#include <iostream>
#include <fstream>

using namespace std;

class Terne{
    private:
    int a, b, c;

    public:
    Terne(int a, int b, int c){
        this->a = a;
        this->b = b;
        this->c = c;
    }

    int getA() const {return a;}
    int getB() const {return b;}
    int getC() const {return c;}
};

ostream& operator <<(ostream& out, const Terne c){
    return out << "(" << (double)(c.getA()/10.0) << "," << (double)(c.getB()/10.0) << "," << (double)(c.getC()/10.0) << ")";
}

int operator <(const Terne c1, const Terne c2){
    return ((c1.getA()<c2.getA()));
}

int operator >(const Terne c1, const Terne c2){
    return ((c1.getA()>c2.getA()));
}

int operator ==(const Terne c1, const Terne c2){
    return !(c1<c2 || c1>c2);
}

Terne* findMax(Terne** A, int n){
    Terne* m = *A;
    for(int i=1; i<n; i++) m = *m<*(A[i])?A[i]:m;
    return m;
}

Terne* findMin(Terne** A, int n){
    Terne* m = *A;
    for(int i=1; i<n; i++) m = *m>*(A[i])?A[i]:m;
    return m;
}

int K = 0;

int* CountingSort(Terne** A, Terne** B, int n){
    Terne* min = findMin(A,n);
    Terne* max = findMax(A,n);
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
    double x = 0, y = 0, z = 0;
    char put = ' ';
    for(int i=0; i<100; i++){
        in >> N;
        Terne** A = new Terne*[N];
        Terne** B = new Terne*[N];
        for(int j = 0; j<N; j++){
            in >> put >> x >> y >> z >> put; 
            A[j] = new Terne((int)(x*10),(int)(y*10),(int)(z*10));
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