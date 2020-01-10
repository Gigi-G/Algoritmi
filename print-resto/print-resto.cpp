#include <iostream>
#include <fstream>
#define INF 20000
#define SU 1
#define SX 2

using namespace std;

int findMin(int a, int b){
    if(a <= b)
        return a;
    else
        return b;
}

int findMinCoins(int coins[], int sum, int size){
    int** arr = new int*[size + 1];
    for(int i = 0; i < size + 1; i++)
        arr[i] = new int[sum + 1];
    
    for(int i = 0; i < size + 1; i++)
        arr[i][0] = 0;
    
    for(int j = 1; j < sum + 1; j++)
        arr[0][j] = INF;

    for(int i = 1; i < size + 1; i++){
        for(int j = 1; j < sum + 1; j++){
            if(coins[i - 1] > j)
                arr[i][j] = arr[i - 1][j];
            else
                arr[i][j] = findMin(1 + arr[i][j - coins[i - 1]], arr[i - 1][j]);
        }
    }
    
    int answer = arr[size][sum];
    
    for(int i = 0; i < size + 1; i++)
        delete[] arr[i];
    delete[] arr;
    
    return answer;
}

int** MatrixMinCoins(int coins[], int sum, int size){
    int** A = new int*[size+1];
    for(int i=0; i<size+1; A[i++] = new int[sum+1]);
    int** arr = new int*[size + 1];
    for(int i = 0; i < size + 1; i++)
        arr[i] = new int[sum + 1];
    
    for(int i = 0; i < size + 1; i++)
        arr[i][0] = A[i][0] = 0;
    
    for(int j = 1; j < sum + 1; j++)
        arr[0][j] = A[0][j] = INF;

    for(int i = 1; i < size + 1; i++){
        for(int j = 1; j < sum + 1; j++){
            if(coins[i - 1] > j){
                arr[i][j] = arr[i - 1][j];
                A[i][j] = SU;
            }
            else{
                arr[i][j] = findMin(1 + arr[i][j - coins[i - 1]], arr[i - 1][j]);
                if(1 + arr[i][j - coins[i - 1]]<=arr[i - 1][j]){
                    A[i][j] = SX;
                }
                else A[i][j] = SU;
            }
        }
    }
    
    return A;
}

void printChange(int** A, int r, int i, int* M, ostream& out){
    if(A[i][r] <= 0) return;
    if(A[i][r] == SX){
        printChange(A,r-M[i-1],i,M,out);
        out << M[i-1] << " ";
    }
    else{
        printChange(A,r,i-1,M,out);
    }
}

void sort(int *A, int n){
    for(int i=1; i<n; i++){
        int j = i;
        while(j>0 && A[j-1]>A[j]){
            int tmp = A[j];
            A[j] = A[j-1];
            A[j-1] = tmp;
            j--;
        }
    }
}

int main(){
	ifstream in;
	ofstream out;
	in.open("input.txt");
	out.open("output.txt");
	int N=0, R=0;
    for(int g=0;g<100;g++){
    	in >> R >> N;
    	int coins[N];
    	for(int i=0;i<N;i++){
    		in >> coins[i];
    	}
    	out << findMinCoins(coins, R, N) << " ";
        sort(coins,N);
        int **A = MatrixMinCoins(coins,R,N);
        printChange(A,R,N,coins,out);
        out << endl;
    }
    in.close();
    out.close();
    return 0;
}
