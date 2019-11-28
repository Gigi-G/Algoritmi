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

void printlcs(string* out, int** b, string X, int i, int j){
    if(i == 0 || j == 0) return;
    if(b[i][j] == F_OBL){
        printlcs(out,b,X,i-1,j-1);
        *out += X[i-1];
    }
    else if(b[i][j] == F_SUSX || b[i][j] == F_SU){
        printlcs(out,b,X,i-1,j);
    }
    else{
        printlcs(out,b,X,i,j-1);
    }
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    int x = 0, y = 0;
    string X = "", Y = "";
    for(int i=0; i<100; i++){
        in >> x >> y >> X >> Y;
        int **c = new int*[x + 1];
        int **b = new int*[x + 1];
        for(int i=0; i<x+1; i++){
            c[i] = new int[y+1];
            b[i] = new int[y+1];
            for(int j = 0; j<y+1; j++){
                c[i][j] = 0;
                b[i][j] = 0;
            }
        }
        LCS(X, Y, c, b);
        string* ot=new string("");
        printlcs(ot, b,X,X.length(),Y.length());
        out << ot->length() << endl;
        delete ot;
        for(int i=0; i<x+1; i++){
            delete[] c[i];
            delete[] b[i];
        }
        delete[] c;
        delete[] b;
    }
    in.close();
    out.close();
    return 0;
}