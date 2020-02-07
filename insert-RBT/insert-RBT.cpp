#include <iostream>
#include <fstream>
#define INF 99999999
#define R 'R'
#define B 'B'

using namespace std;

template<class H> class Node{
    private:
    H* key;
    Node<H> *parent, *left, *right;
    char c;

    public:
    Node(H *key, Node<H> *parent=NULL, Node<H> *right=NULL, Node<H> *left=NULL){
        this->parent = parent;
        this->right = right;
        this->left = left;
        this->key = key;
        c = R;
    }

    void setKey(H* key) {this->key = key;}
    H* getKey() {return this->key;}

    void setParent(Node<H>* parent) {this->parent=parent;}
    Node<H>* getParent() {return this->parent;}
    void setRight(Node<H> *right) {this->right=right;}
    Node<H>* getRight() {return this->right;}
    void setLeft(Node<H> *left) {this->left=left;}
    Node<H>* getLeft() {return this->left;}

    void setColor(char x) {this->c = x;}
    char getColor() {return this->c;}
};

template<class H> class BST{
    private:
    Node<H> *root;
    int n;

    void _inorder(Node<H>* x, ostream& out){
        if(!x) return;
        _inorder(x->getLeft(), out);
        out << "(" << *x->getKey() << " " << x->getColor() << ")" << " ";
        _inorder(x->getRight(), out);
    }

    void _postorder(Node<H>* x, ostream& out){
        if(!x) return;
        _postorder(x->getLeft(), out);
        _postorder(x->getRight(), out);
        out << "(" << *x->getKey() << " " << x->getColor() << ")" << " ";
    }

    void _preorder(Node<H>* x, ostream& out){
        if(!x) return;
        out << "(" << *x->getKey() << " " << x->getColor() << ")" << " ";
        _preorder(x->getLeft(), out);
        _preorder(x->getRight(), out);
    }

    Node<H>* _rmin(Node<H> *x){
        if(!x || !x->getLeft()) return x;
        return _rmin(x->getLeft());
    }

    Node<H>* _search(Node<H> *x, H key){
        if(!x || *x->getKey() == key) return x;
        if(key<=*x->getKey()) return _search(x->getLeft(),key);
        else return _search(x->getRight(),key);
    }

    void _leftRotate(Node<H> *x, H key){
        Node<H> *tmp = _search(x,key);
        if(tmp){
            Node<H> *p = tmp->getParent();
            Node<H> *r = tmp->getRight();
            if(!r) return;
            Node<H> *rl = r->getLeft();
            if(p){
                if(key<=*p->getKey()){
                    p->setLeft(r);
                }
                else p->setRight(r);
            }
            else root = r;
            r->setParent(p);
            tmp->setParent(r);
            tmp->setRight(rl);
            if(rl) rl->setParent(tmp);
            r->setLeft(tmp);
        }
    }

    void _rightRotate(Node<H>* x, H key){
        Node<H>* tmp = _search(x,key);
        if(tmp){
            Node<H> *p = tmp->getParent();
            Node<H> *l = tmp->getLeft();
            if(!l) return;
            Node<H> *lr = l->getRight();
            if(p){
                if(key<=*p->getKey()) p->setLeft(l);
                else p->setRight(l);
            }
            else root = l;
            l->setParent(p);
            tmp->setParent(l);
            tmp->setLeft(lr);
            if(lr) lr->setParent(tmp);
            l->setRight(tmp);
        }
    }

    public:
    BST(){
        root = NULL;
        n = 0;
    }

    BST<H>* InsertKey(H key){
        Node<H> *tmp = root;
        Node<H> *p = NULL;
        while(tmp){
            p = tmp;
            if(*tmp->getKey()>=key) tmp = tmp->getLeft();
            else tmp = tmp->getRight();
        }
        if(!p) {
            root = new Node<H>(new H(key));
            root->setColor(B);
            n++;
            return this;
        }
        Node<H> *leaf = new Node<H>(new H(key),p);
        int f = 0;
        if(*p->getKey()>=key){
            p->setLeft(leaf);
            f = 0;
        }
        else {
            p->setRight(leaf);
            f = 1;
        }
        n++;
        while(p && p->getColor() == R){
            Node<H> *gp = p->getParent();
            Node<H> *uncle = NULL;
            if(*p->getKey()<=*gp->getKey()){
                uncle = gp->getRight();
                if(!uncle || uncle->getColor() == B){
                    if(f == 1){
                        f = 0;
                        leftRotate(*p->getKey());
                        p = p->getParent();
                        leaf = p;
                    }
                    else{
                        p->setColor(B);
                        gp->setColor(R);
                        rightRotate(*gp->getKey());
                    }
                }
                else{
                    p->setColor(B);
                    uncle->setColor(B);
                    gp->setColor(R);
                    leaf = gp;
                    p = gp->getParent();
                    if(p){
                        if(*leaf->getKey()<=*p->getKey()) f = 0;
                        else f = 1;
                    }
                }
            }
            else {
                uncle = gp->getLeft();
                if(!uncle || uncle->getColor() == B){
                    if(f == 0){
                        f = 1;
                        rightRotate(*p->getKey());
                        p = p->getParent();
                        leaf = p;
                    }
                    else{
                        p->setColor(B);
                        gp->setColor(R);
                        leftRotate(*gp->getKey());
                    }
                }
                else{
                    p->setColor(B);
                    uncle->setColor(B);
                    gp->setColor(R);
                    leaf = gp;
                    p = gp->getParent();
                    if(p){
                        if(*leaf->getKey()<=*p->getKey()) f = 0;
                        else f = 1;
                    }
                }
            }
            root->setColor(B);
        }
        return this;
    }

    void inorder(ostream& out){
        _inorder(root,out);
        out << endl;
    }

    void postorder(ostream& out){
        _postorder(root,out);
        out << endl;
    }

    void preorder(ostream& out){
        _preorder(root,out);
        out << endl;
    }

    H getMin(){
        Node<H>* tmp = _rmin(root);
        if(tmp) return *tmp->getKey();
        return INF;
    }

    H find(H x){
        Node<H>* tmp = _search(root,x);
        if(tmp) return *tmp->getKey();
        return INF;
    }

    void leftRotate(H x){
        _leftRotate(root,x);
    }

    void rightRotate(H x){
        _rightRotate(root,x);
    }

    void getLength() const {return n;}
};

int main(){
    ifstream in;
    ofstream out;
    in.open("input.txt");
    out.open("output.txt");
    string t = "", s = "";
    char c = ' ';
    double x = 0;
    int N;
    BST<double> *b;
    for(int g=0; g<100; g++){
        b = new BST<double>();
        in >> t >> N >> s;
        for(int i=0; i<N; i++){
            in >> x;
            b->InsertKey(x);
        }
        if(s == "inorder") b->inorder(out);
        else if(s == "postorder") b->postorder(out);
        else b->preorder(out);
    }
    /*BST<double> *b = new BST<double>();
    b->InsertKey(4)->InsertKey(3)->InsertKey(9)->InsertKey(2)->InsertKey(8)->InsertKey(10)->InsertKey(7)->InsertKey(6);
    b->preorder(out);*/
    in.close();
    out.close();
    return 0;
}