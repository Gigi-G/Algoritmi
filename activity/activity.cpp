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
    int getSize() const {return b-a;}
};

ostream& operator <<(ostream& out, const Coppie& c){
    return out << "(" << c.getA() << "," << c.getB() << ")";
}

int operator <(const Coppie c1, const Coppie c2){
    return ((c1.getB()<c2.getB()));
}

int operator >(const Coppie c1, const Coppie c2){
    return ((c1.getB()>c2.getB()));
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

void CountingSort(Coppie** A, Coppie** B, int n){
    Coppie* min = findMin(A,n);
    Coppie* max = findMax(A,n);
    int mi = min->getB();
    int ma = max->getB();
    int k = ma - mi + 1;
    int* C = new int[k];
    for(int i=0; i<k; i++) C[i] = 0;
    for(int i=0; i<n; i++) C[(A[i])->getB()-mi]++;
    for(int i=1; i<k; i++) C[i] += C[i-1];
    for(int i=n-1;i>-1;i--){
        B[C[(A[i])->getB() - mi]-1] = A[i];
        C[(A[i])->getB() - mi]--;
    }
}

int max(int a, int b){
    return a>b?a:b;
}

int lastactivity(Coppie** A, int i){
    int k = i;
    for(int j = i-1; j>=0; j--){
        if(A[j]->getB()<=A[k]->getA()) return j;
    }
    return -1;
}

int activity(Coppie** A, int n){
    int B[n];
    B[0] = A[0]->getSize();
    for(int i=1; i<n; i++){
        int inclAct = A[i]->getSize();
        int l = lastactivity(A,i);
        if(l != -1){
            inclAct += B[l];
        }
        B[i] = max(inclAct, B[i-1]);
    }
    return B[n-1];
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    int N = 0;
    int x = 0, y = 0;
    char put = ' ';
    for(int i=0; i<100; i++){
        in >> N;
        Coppie** A = new Coppie*[N];
        Coppie** B = new Coppie*[N];
        for(int j = 0; j<N; j++){
            in >> put >> x >> y >> put;
            A[j] = new Coppie(x,y);
        }
        CountingSort(A,B,N);
        out << activity(B,N) << endl;
    }
    in.close();
    out.close();
    return 0;
}