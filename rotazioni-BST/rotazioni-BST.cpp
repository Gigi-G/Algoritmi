#include <iostream>
#include <fstream>

using namespace std;

template<class H> class Node{
    private:
    Node<H> *p, *l, *r;
    H *k;

    public:
    Node(H *k = NULL, Node<H> *p = NULL, Node<H> *l = NULL, Node<H>* r = NULL){
        this->p = p;
        this->l = l;
        this->r = r;
        this->k = k;
    }

    void setParent(Node<H> *p) {this->p = p;}
    void setLeft(Node<H> *l) {this->l = l;}
    void setRight(Node<H> *r) {this->r = r;}
    void setKey(H *k) {this->k = k;}

    Node<H>* getParent() {return p;}
    Node<H>* getLeft() {return l;}
    Node<H>* getRight() {return r;}
    H* getKey() {return k;}
};

template<class T> class BST{
    private:
    Node<T> *root, *current;
    int n;

    Node<T>* _search(Node<T>* x, T k){
        if(*x->getKey() == k || !x) return x;
        if(k<=*x->getKey()) return _search(x->getLeft(),k);
        return _search(x->getRight(),k);
    }

    Node<T>* _rmin(Node<T>* x){
        if(!x || !x->getLeft()) return x;
        return _rmin(x->getLeft());
    }

    void _canc(Node<T>* x, T k){
        Node<T>* tmp = _search(x,k);
        if(!tmp) return;
        if(tmp->getLeft() && tmp->getRight()){
            Node<T>* min = _rmin(tmp->getRight());
            tmp->setKey(min->getKey());
            _canc(min,*min->getKey());
        }
        else{
            Node<T>* son = tmp->getLeft();
            if(!son) son = tmp->getRight();
            Node<T>* p = tmp->getParent();
            if(p){
                if(k<*p->getKey()) p->setLeft(son);
                else p->setRight(son);
            }
            else root = son;
            if(son) son->setParent(p);
            n--;
        }
    }

    void insertNodeUp(Node<T>* before, Node<T>* node) // moves node down and put the given node in its place 
	{
		if (before->getParent() != NULL)
		{
			if (before == before->getParent()->getLeft())
			{
				before->getParent()->setLeft(node);
			}
			else
			{
				before->getParent()->setRight(node);
			}
		}
		else
		{
			root = node;
		}
		node->setParent(before->getParent());
		before->setParent(node);
	}

    void _leftrotate(Node<T>* node){
        if(!node->getRight()) return;
        Node<T>* nParent = node->getRight(); // new parent will be node's right child 			
		insertNodeUp(node, nParent);		//if (node == root)	root = nParent;
		node->setRight(nParent->getLeft());// connect x with new parent's left element 		
		if (nParent->getLeft() != NULL){ // connect new parent's left element with node  if it is not null 
            nParent->getLeft()->setParent(node);
        }
		nParent->setLeft(node); // connect new parent with x 
    }

    void _rightrotate(Node<T>* node){
        if(!node->getLeft()) return;
        Node<T>* nParent = node->getLeft();// new parent will be node's left child 				
		insertNodeUp(node, nParent);// connect x with new parent's right element 		
		node->setLeft(nParent->getRight());
		if (nParent->getRight() != NULL) {// connect new parent's right element with node  if it is not null 		
			nParent->getRight()->setParent(node);
        }
		nParent->setRight(node);// connect new parent with x 
    }

    void _inorder(Node<T> *x, ostream& out){
        if(!x) return;
        _inorder(x->getLeft(), out);
        out << *x->getKey() << " ";
        _inorder(x->getRight(), out);
    }

    void _postorder(Node<T> *x, ostream& out){
        if(!x) return;
        _postorder(x->getLeft(), out);
        _postorder(x->getRight(), out);
        out << *x->getKey() << " ";
    }

    void _preorder(Node<T> *x, ostream& out){
        if(!x) return;
        out << *x->getKey() << " ";
        _preorder(x->getLeft(), out);
        _preorder(x->getRight(), out);
    }

    public:
    BST(){
        root = current = NULL;
        n = 0;
    }

    BST<T>* insert(T x){
        Node<T> *tmp = root;
        Node<T> *p = NULL;
        while(tmp){
            p = tmp;
            if(x<=*(tmp->getKey())) tmp = tmp->getLeft();
            else tmp = tmp->getRight();
        }
        Node<T> *y = new Node<T>(new T(x),p);
        if(!p) root = y;
        else if(x<=*(p->getKey())) p->setLeft(y);
        else p->setRight(y);
        n++;
        return this;
    }

    void LeftRotate(T x){
        Node<T>* tmp = _search(root, x);
        if(tmp) _leftrotate(tmp);
    }

    void RightRotate(T x){
        Node<T>* tmp = _search(root,x);
        if(tmp) _rightrotate(tmp);
    }

    void canc(T x){
        _canc(root,x);
    }

    void inorder(ostream& out){
        _inorder(root, out);
        out << endl;
    }

    void postorder(ostream& out){
        _postorder(root, out);
        out << endl;
    }

    void preorder(ostream& out){
        _preorder(root, out);
        out << endl;
    }

    int getSize() const {return n;}
};

int main(){
    ifstream in;
    in.open("input.txt");
    ofstream out;
    out.open("output.txt");
    string t = "";
    char op = ' ';
    int N = 0, R = 0;
    double x = 0.0;
    BST<double>* b;
    for(int i=0; i<100; i++){
        in >> t >> N >> R >> t;
        b = new BST<double>();
        for(int g = 0; g<N; g++){
            in >> op;
            if(op == 'i'){
                in >> op >> op >> op >> x;
                b->insert(x);
            }
            else{
                in >> op >> op >> op >> op >> x;
                b->canc(x);
            }
        }
        for(int g = 0; g<R; g++){
            in >> op;
            if(op == 'r'){
                in >> op >> op >> op >> op >> op >> x;
                b->RightRotate(x);
            }
            else{
                in >> op >> op >> op >> op >> x;
                b->LeftRotate(x);
            }
        }
        if(t == "inorder") b->inorder(out);
        else if(t == "preorder") b->preorder(out);
        else b->postorder(out);     
        delete b;
    }
    in.close();
    out.close();
    return 0;
}