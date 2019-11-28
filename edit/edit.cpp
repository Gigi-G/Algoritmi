#include <iostream>
#include <fstream>

using namespace std;

int min(int a, int b, int c){
    int min = a;
    if(min>b) min = b;
    else if(min>c) min = c;
    return min;
}

int minimo(int a, int b){
    return a<b?a:b;
}

/*int edit(string X, string Y, int i, int j){
    if(i==0 || j==0) return j+i;
    if(X[i]==Y[j]) return edit(X,Y,i-1,j-1);
    else return min(edit(X,Y,i-1,j-1)+1,edit(X,Y,i,j-1)+1,edit(X,Y,i-1,j)+1);
}*/

int EditDynamic(string X, string Y, int n, int m){
    int A[m+1][n+1];
    for(int i = 0; i<=m; i++) A[i][0] = i;
    for(int i = 0; i<=n; i++) A[0][i] = i;
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=m; j++){
            if(X[i-1] == Y[j-1]) A[j][i] = A[j-1][i-1];
            else A[j][i] = min(A[j-1][i-1],A[j][i-1],A[j-1][i])+1;
        }
    }
    return A[m][n];
}

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string X = "", Y = "";
    int i = 0, j = 0;
    for(int g=0; g<100; g++){
        in >> i >> j >> X >> Y;
        out << EditDynamic(X,Y,i,j) << endl;
    }
    in.close();
    out.close();
    return 0;
}