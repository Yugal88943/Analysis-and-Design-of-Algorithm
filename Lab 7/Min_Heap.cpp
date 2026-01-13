#include <iostream>
using namespace std;

struct MinHeap {
    int h[100];
    int size = 0;

    void insert(int x) {
        h[size] = x;
        int i = size;
        size++;

        while(i > 0 && h[(i-1)/2] > h[i]) {
            swap(h[i], h[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void deleteMin() {
        if(size == 0) return;

        h[0] = h[size-1];
        size--;

        int i = 0;
        while(true) {
            int l = 2*i+1, r = 2*i+2, small = i;

            if(l < size && h[l] < h[small]) small = l;
            if(r < size && h[r] < h[small]) small = r;

            if(small == i) break;
            swap(h[i], h[small]);
            i = small;
        }
    }

    void levelOrder() {
        for(int i = 0; i < size; i++) cout << h[i] << " ";
        cout << "\n";
    }
};

int main() {
    MinHeap mh;
    mh.insert(10);
    mh.insert(4);
    mh.insert(15);
    mh.insert(2);

    cout << "MinHeap: ";
    mh.levelOrder();

    mh.deleteMin();
    cout << "After deleteMin: ";
    mh.levelOrder();
}
