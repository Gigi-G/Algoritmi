#include <iostream>
#include <fstream>

#define input "input.txt"
#define output "output.txt"

using namespace std;

int findMin(int *A, int n){
	int min = A[0];
	for(int i=1; i<n; i++) min = min>A[i]?A[i]:min;
       	return min;	
}

int findMax(int *A, int n){
	int max = A[0];
	for(int i=1; i<n; i++) max = max<A[i]?A[i]:max;
	return max;
}

void CountingSort(int *A, int *B, int n, int *D, int k, int min){
	for(int i=0; i<k; i++) D[i] = 0;
	for(int i=0; i<n; i++) {
		D[A[i] - min]++;
	}
	for(int i=1; i<k; i++) D[i] += D[i-1];
	for(int i=n-1; i>-1; i--){
		B[D[A[i] - min] - 1] = A[i];
		D[A[i] - min]--;
	}
}

int main(){
	ifstream in;
	in.open(input);
	ofstream out;
	out.open(output);
	int n=0;
	for(int i=0; i<100; i++){
		in >> n;
		int A[n];
		int B[n];
		for(int i=0; i<n; i++) in >> A[i];
		int min = findMin(A,n);
		int max = findMax(A,n);
		int k = max - min + 1;
		int D[k];
		CountingSort(A,B,n,D,k,min);
		for(int i=0; i<k; i++) out << D[i] << " ";
		for(int i=0; i<n; i++) out << B[i] << " ";
		out << endl;

	}
	in.close();
	out.close();
	return 0;
}
