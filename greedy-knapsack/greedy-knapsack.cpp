#include <iostream>
#include <fstream>

using namespace std;

int findMax(int *A, int n){
    int m = A[0];
    for(int i = 1; i<n; i++) m = A[i]>m?A[i]:m;
    return m;
}

int findMin(int *A, int n){
    int m = A[0];
    for(int i = 1; i<n; i++) m = A[i]<m?A[i]:m;
    return m;
}

void CountingSort(int *A, int *B, int n){
    int min = findMin(A,n);
    int max = findMax(A,n);
    int k = max - min + 1;
    int C[k];
    for(int i = 0; i<k; i++) C[i] = 0;
    for(int i = 0; i<n; i++) C[A[i] - min]++;
    for(int i = 1; i<k; i++) C[i] += C[i-1];
    for(int i=n-1; i>-1; i--){
        B[(C[A[i]-min]--)-1] = A[i];
    }
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    int N = 0, P = 0, x = 0, s = 0, p = 0;
    for(int g=0; g<100; g++){
        s = 0;
        p = 0;
        in >> N >> P;
        int A[N];
        int B[N];
        for(int i = 0; i<N; i++){
            in >> x;
            A[i] = x;
        }
        CountingSort(A,B,N);
        for(int i=N-1; i>-1; i--){
            if(p++<P) s+=B[i];
        }
        out << s << endl;
    }
    in.close();
    out.close();
    return 0;
}