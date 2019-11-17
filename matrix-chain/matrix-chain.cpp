#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

int matrixChain(int *p, int n){
	int m[n][n];
	for(int i=0; i<n; i++){
		m[i][i] = 0;
	}
	int j = 0;
	for(int l=2; l<n; l++){
		for(int i=1; i<n-l+1; i++){
			j = i+l-1;
			m[i][j] = INT_MAX;
			int q = 0;
			for(int k=i; k<j; k++){
				q = m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(q<m[i][j]) m[i][j]=q;
			}
		}
	}
	/*for(int i =0; i<n; i++){
		for(int j = 0; j<n; j++) cout << m[i][j] << " ";
		cout << endl;
	}
	cout << endl;*/
	return m[1][n-1];
}

int main(){
	ifstream in;
	in.open("input.txt");
	ofstream out;
	out.open("output.txt");
	int N = 0;
	int pi = 0, pj = 0;
	char put = ' ';
	for(int i=0; i<100; i++){
		in >> N;
		int p[N+1];
		for(int j=0; j<N; j++){
			in >> put >> pi >> put >> pj >> put;
			p[j] = pi;
		}
		p[N] = pj;
		/*for(int j=0; j<N+1; j++){
			cout << p[j] << " ";
		}
		cout << endl;*/
		out << matrixChain(p,N+1) << endl;
	}
	in.close();
	out.close();
	return 0;
}