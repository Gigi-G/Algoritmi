#include <iostream>
#include <fstream>

using namespace std;

int K = 0;

int findMin(int *A, int n) {
	int min = A[0];
	for(int i = 1; i<n; i++) min = min>A[i]?A[i]:min; 
	return min;
}

int findMax(int *A, int n) {
	int max = A[0];
	for(int i=1; i<n; i++) max = max<A[i]?A[i]:max;
	return max;
}

/*int* CountingSort(int *A, int *B, int n) { //implementazione non stabile
	int min = findMin(A, n);
	int max = findMax(A, n);
	int k = max - min + 1;
	int *C = new int[k];
    K = k;
	for(int i=0; i<k; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i] - min]++;
	int j = 0;
	for(int i=0; i<k; i++){
		while(C[i]>0) {
			B[j++] = i + min;
			C[i]--;
		}	
	}
    return C;
}*/

int* CountingSortS(int *A, int *B, int n) { //implementazione stabile
	int min = findMin(A, n);
	int max = findMax(A, n);
	int k = max - min + 1;
	int* C = new int[k];
    K = k;
	for(int i=0; i<k; i++) C[i] = 0;
	for(int i=0; i<n; i++) C[A[i] - min]++;
	for(int i=1; i<k; i++) C[i] += C[i-1];
	for(int i=n-1; i>-1; i--) {
		B[C[A[i]-min]-1] = A[i];
		C[A[i]-min]--;
	}
    return C;
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string t = "";
    int N = 0;
    for(int i=0; i<100; i++){
        in >> t >> N;
        int count[N];
        int B[N];
        if(t=="char"){
            char x = ' ';
            for(int j=0; j<N; j++){
                in >> x;
                count[j] = (int)x;
            }
            int* C = CountingSortS(count,B,N);
            for(int j=0; j<K; j++){
                out << C[j] << " ";
            }
            for(int j=0; j<N; j++){
                out << (char)B[j] << " ";
            }
            out << endl;
        }
        else if(t=="double"){
            double x = 0;
            for(int j=0; j<N; j++){
                in >> x;
                count[j] = (int)(x*10);
            }
            int* C = CountingSortS(count,B,N);
            for(int j=0; j<K; j++){
                out << C[j] << " ";
            }
            for(int j=0; j<N; j++){
                out << (double)(B[j]/10.0) << " ";
            }
            out << endl;
        }
        else{
            int x = 0;
            for(int j=0; j<N; j++){
                in >> x;
                count[j] = x;
            }
            int* C = CountingSortS(count,B,N);
            for(int j=0; j<K; j++){
                out << C[j] << " ";
            }
            for(int j=0; j<N; j++){
                out << B[j] << " ";
            }
            out << endl;
        }
    }
    in.close();
    out.close();
    return 0;
}