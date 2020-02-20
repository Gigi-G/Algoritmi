#include <iostream>
#include <fstream>

using namespace std;

class Activity{
    private:
    int s, f;

    public:
    Activity(int s, int f){
        this->s = s;
        this->f = f;
    }

    int getStart() {return s;}
    int getFinish() {return f;}
    int getSize() {return f-s;}
};

void sort(Activity **A, int n){
    for(int i=1; i<n; i++){
        int j = i;
        while(j>0 && A[j-1]->getFinish()>A[j]->getFinish()){
            Activity *tmp = A[j];
            A[j] = A[j-1];
            A[j-1] = tmp; 
            j--;
        }
    }
}

int WeightedActivities(Activity** A, int N){
    int B[N];
    B[0] = A[0]->getSize();
    for(int i=1; i<N; i++){
        int inclAct = A[i]->getSize();
        int a = -1;
        for(int j = i-1; j>=0; j--){
            if(A[j]->getFinish()<=A[i]->getStart()) {
                a = j;
                break;
            }
        }
        if(a!=-1){
            inclAct+=B[a];
        }
        if(inclAct>B[i-1]) B[i] = inclAct;
        else B[i] = B[i-1];
    }
    return B[N-1];
}

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    int N = 0;
    int s = 0, f = 0;
    char p = ' ';
    Activity **A;
    for(int i=0; i<100; i++){
        in >> N;
        A = new Activity*[N];
        for(int j=0; j<N; j++){
            in >> p >> s >> f >> p;
            A[j] = new Activity(s,f);
        }
        sort(A,N);
        out << WeightedActivities(A,N) << endl;
    }
    in.close();
    out.close();
    return 0;
}