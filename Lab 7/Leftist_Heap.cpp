#include <iostream>
#include <queue>
using namespace std;

struct Node {
    int key, npl;
    Node *left, *right;
    Node(int k) : key(k), npl(0), left(NULL), right(NULL) {}
};

Node* mergeHeap(Node* h1, Node* h2)
{
    if(!h1) return h2;
    if(!h2) return h1;

    if(h2->key < h1->key) swap(h1, h2);

    h1->right = mergeHeap(h1->right, h2);

    int lnpl = h1->left ? h1->left->npl : -1;
    int rnpl = h1->right ? h1->right->npl : -1;

    if(lnpl < rnpl) swap(h1->left, h1->right);

    h1->npl = (h1->right ? h1->right->npl : -1) + 1;

    return h1;
}

struct LeftistHeap {
    Node* root = NULL;

    void insert(int x) {
        root = mergeHeap(root, new Node(x));
    }

    void deleteMin() {
        if(!root) return;
        Node* old = root;
        root = mergeHeap(root->left, root->right);
        delete old;
    }

    void levelOrder() {
        if(!root) return;
        queue<Node*> q;
        q.push(root);
        while(!q.empty()) {
            Node* t = q.front(); q.pop();
            cout << t->key << " ";
            if(t->left) q.push(t->left);
            if(t->right) q.push(t->right);
        }
        cout << "\n";
    }
};

int main() {
    LeftistHeap lh;

    lh.insert(10);
    lh.insert(5);
    lh.insert(30);
    lh.insert(2);

    cout << "Leftist Heap: ";
    lh.levelOrder();

    lh.deleteMin();
    cout << "After deleteMin: ";
    lh.levelOrder();
}

