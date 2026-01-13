#include <iostream>
using namespace std;

struct MaxHeap {
    int h[100];
    int size = 0;

    void insert(int x) {
        h[size] = x;
        int i = size;
        size++;

        while(i > 0 && h[(i-1)/2] < h[i]) {
            swap(h[i], h[(i-1)/2]);
            i = (i-1)/2;
        }
    }

    void deleteMax() {
        if(size == 0) return;

        h[0] = h[size-1];
        size--;

        int i = 0;
        while(true) {
            int l = 2*i+1, r = 2*i+2, big = i;

            if(l < size && h[l] > h[big]) big = l;
            if(r < size && h[r] > h[big]) big = r;

            if(big == i) break;
            swap(h[i], h[big]);
            i = big;
        }
    }

    void levelOrder() {
        for(int i = 0; i < size; i++) cout << h[i] << " ";
        cout << "\n";
    }
};

int main() {
    MaxHeap mh;
    mh.insert(10);
    mh.insert(40);
    mh.insert(5);
    mh.insert(20);

    cout << "MaxHeap: ";
    mh.levelOrder();

    mh.deleteMax();
    cout << "After deleteMax: ";
    mh.levelOrder();
}
