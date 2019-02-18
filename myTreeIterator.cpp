#include <iostream>
#include <utility>
#include <vector>
using namespace std;

// With Iterator

template<class K,class V>
class BST {
public:
    class Node {
    public:
        K key;
        V value;
        Node *left;
        Node *right;
        Node *parent;
        Node(K k, V v) {
            key = k;
            value = v;
            right = nullptr;
            left = nullptr;
            parent = nullptr;
        }
        Node * next(){
            Node * c=this;
            if (c->right) {
                Node *temp = c->right;
                while (temp->left) {
                    temp = temp->left;
                }
                return temp;
            }
            // step 2 of the above algorithm
            Node *p = c->parent;
            while (p != nullptr && c == p->right) {
                c = p;
                p = p->parent;
            }
            return p;
        }
    };

public:
    Node *root;
public:
    class iterator : public std::iterator<std::input_iterator_tag, K> {
    public:
        Node *current;

        iterator() : current(nullptr) {};

        iterator(Node *n) : current(n) {};

        K& operator*() { return current->key; }

        Node *next(Node *c) {
            if (c->right) {
                Node *temp = c->right;
                while (temp->left) {
                    temp = temp->left;
                }
                return temp;
            }
            // step 2 of the above algorithm
            Node *p = c->parent;
            while (p != nullptr && c == p->right) {
                c = p;
                p = p->parent;
            }
            return p;
        }

        iterator &operator++() {
            current = next(current);
            return *this;
        }

        const BST::iterator operator++(int) {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        bool operator==(const iterator &rhs) const { return current == rhs.current; }

        bool operator!=(const iterator &rhs) const { return current != rhs.current; }

        bool operator<(const iterator &other) {
            return current->key < other.current->key;
        }

    };

    class cons_iterator {
    public:
        Node *cons_current;

        cons_iterator() : cons_current(nullptr) {};

        explicit cons_iterator(Node *n) : cons_current(n) {};

    };

    iterator begin() {
        Node *temp = root;
        while (temp->left) {
            temp = temp->left;
        }
        iterator it(temp);
        return it;
    }

    iterator end() {
        Node *temp = root;
        while (temp->right) {
            temp = temp->right;
        }
        return iterator(temp);
    }

    cons_iterator cbegin() {
        Node *temp = root;
        while (temp->left) {
            temp = temp->left;
        }
        return cons_iterator(temp);
    }

    cons_iterator cend() {
        Node *temp = root;
        while (temp->right) {
            temp = temp->right;
        }
        return cons_iterator(temp);
    }

public:
    BST() : root(nullptr) { //constructor
    }

    BST(const BST &other) { //copy constructor
        root = other.root;
    }

    BST &operator=(const BST &other) { //copy assignment
        root = other.root;
        return *this;
    }

    void insert(K key, V value) {
        Node *treeNode = new Node(key, value);

        Node *temp = nullptr;
        Node *prev = nullptr;

        temp = root;
        while (temp) {
            prev = temp;
            if (temp->key == treeNode->key)return;
            if (temp->key < treeNode->key)
                temp = temp->right;
            else
                temp = temp->left;

        }
        if (prev == nullptr)
            root = treeNode;
        else {
            treeNode->parent = prev;
            if (prev->key < treeNode->key)
                prev->right = treeNode;
            else
                prev->left = treeNode;
        }
    }

    void freeMemory(Node *node) {
        if (node == nullptr) {
            return;
        } else {
            if (node->right)freeMemory(node->right);
            if (node->left)freeMemory(node->left);
            delete node;
        }
    }

    void clear() {
        freeMemory(root);
        root = nullptr;
    }

    Node *search(Node *n, K key, V value) {
        // Base Cases: root is null or key is present at root
        if (n == nullptr || (n->key == key && n->value == value))
            return n;

        // Key is greater than root's key
        if (n->key < key)
            return search(n->right, key, value);

        // Key is smaller than root's key
        return search(n->left, key, value);
    }

    Node *find(K key, V value) {
        Node *hold = search(root, key, value);
        return hold;
    }

    void storeBSTNodes(Node *root, std::vector<Node *> &nodes) {
// Base case
        if (root == NULL)
            return;
// Store nodes in Inorder (which is sorted
// order for BST)
        storeBSTNodes(root->left, nodes);
        nodes.push_back(root);
        storeBSTNodes(root->right, nodes);
    }

/* Recursive function to construct binary tree */
    Node *buildTreeUtil(std::vector<Node *> &nodes, int start,
                        int end) {
// base case
        if (start > end)
            return NULL;
/* Get the middle element and make it root */
        int mid = (start + end) / 2;
        Node *root = nodes[mid];
/* Using index in Inorder traversal, construct
left and right subtress */
        root->left = buildTreeUtil(nodes, start, mid - 1);
        root->right = buildTreeUtil(nodes, mid + 1, end);
        return root;
    }

// This functions converts an unbalanced BST to
// a balanced BST
    Node *buildBalanceTree(Node *root) {
// Store nodes of given BST in sorted order
        std::vector<Node *> nodes;
        storeBSTNodes(root, nodes);
// Constucts BST from nodes[]
        int n = nodes.size();
        return buildTreeUtil(nodes, 0, n - 1);
    }

// Utility function to create a new node
    void balance() {
        root = buildBalanceTree(root);
    }
    template <class k,class v>
    friend std::ostream& operator<<(std::ostream &out,const BST<k,v> &b);
};
template <class K,class V>
class Node {
public:
    K key;
    V value;
    Node *left;
    Node *right;
    Node *parent;
    Node(K k, V v) {
        key = k;
        value = v;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
    Node * next(){
        Node * c=this;
        if (c->right) {
            Node *temp = c->right;
            while (temp->left) {
                temp = temp->left;
            }
            return temp;
        }
        // step 2 of the above algorithm
        Node *p = c->parent;
        while (p != nullptr && c == p->right) {
            c = p;
            p = p->parent;
        }
        return p;
    }
};
template <class k,class v>
void inorder(ostream& out,Node<k,v> *){

};
template <class k,class v>
std::ostream&operator<<(std::ostream& out,const BST<k,v>& b){
    if(b.root->left){
        BST<k,v> temp=b;
        temp.root=b.root->left;
        out<<temp;
    }
    out<<b.root->key<<";"<<b.root->value<<" ";
    if(b.root->right){
        BST<k,v> temp=b;
        temp.root=b.root->right;
        out<<temp;
    } ;
    return out;
};
int main() {
    BST<int,int>::Node *node;
    BST<int,std::string> test;
    test.insert(1,"s");
    test.insert(2,"g");
    std::cout<<test;
    test.clear();
    return 0;
}