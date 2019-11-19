#include <iostream>
#include <fstream>
#define F_SUSX 1
#define F_OBL 0
#define F_SU 2
#define F_SX 3

using namespace std;

void LCS(string X, string Y, int** c, int** b){
    int x = X.length() + 1;
    int y = Y.length() + 1;
    for(int i = 0; i<x; i++) {
        c[i][0] = 0;
    }
    for(int i = 0; i<y; i++) {
        c[0][i] = 0;
    }
    for(int i = 1; i<x; i++){
        for(int j = 1; j<y; j++){
            if(X[i-1] == Y[j-1]) {
                c[i][j] = c[i-1][j-1] + 1;
                b[i][j] = F_OBL;
            }
            else{
                if(c[i-1][j] > c[i][j-1]){
                    c[i][j] = c[i-1][j];
                    b[i][j] = F_SU;
                }
                else if(c[i-1][j] < c[i][j-1]){
                    c[i][j] = c[i][j-1];
                    b[i][j] = F_SX;
                }
                else {
                    c[i][j] = c[i-1][j];
                    b[i][j] = F_SUSX;
                }
            }
        }
    }
}

void print(int** c, int n, int m){
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++) cout << c[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

void printLCS(string* out, int** b, string X, int i, int j){
    if(i == 0 || j == 0) return;
    if(b[i][j] == F_OBL){
        printLCS(out,b,X,i-1,j-1);
        *out += X[j-1];
    }
    else if(b[i][j] == F_SUSX || b[i][j] == F_SX){
        printLCS(out,b,X,i,j-1);
    }
    else{
        printLCS(out,b,X,i-1,j);
    }
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string X = "";
    string Y = "";
    list<string> min;
    list<int> n;
    int N = 0, M = 0;
    for(int g=0; g<100; g++){
        min.erase(min.begin(),min.end());
        n.erase(n.begin(),n.end());
        in >> N >> M >> X >> Y;
        int **c = new int*[N + 1];
        int **b = new int*[N + 1];
        for(int i=0; i<N+1; i++){
            c[i] = new int[M+1];
            b[i] = new int[M+1];
            for(int j = 0; j<M+1; j++){
                c[i][j] = 0;
                b[i][j] = 0;
            }
        }
        LCS(X, Y, c, b);
        string* s = new string("");
        printLCS(s,b,Y,N,M);
        out << *s << endl;
    }
    in.close();
    out.close();
    return 0;
}