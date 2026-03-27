#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
using namespace std;

class MedianFinder {
private:
    priority_queue<int> maxHeap;
    priority_queue<int, vector<int>, greater<int>> minHeap;

public:
    MedianFinder() {}

    
    void addNum(int num) {
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            // Otherwise add to minHeap
            minHeap.push(num);
        }

        if (maxHeap.size() > minHeap.size() + 1) {
            // Move top element from maxHeap to minHeap
            int top = maxHeap.top();
            maxHeap.pop();
            minHeap.push(top);
        }

        if (minHeap.size() > maxHeap.size()) {
            int top = minHeap.top();
            minHeap.pop();
            maxHeap.push(top);
        }
    }

    double findMedian() {
        if (maxHeap.empty() && minHeap.empty()) {
            return 0.0;
        }

        if (maxHeap.size() > minHeap.size()) {
            return (double)maxHeap.top();
        }
        else {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        }
    }

    void displayHeapStatus() {
        cout << "\nMax Heap (Lower Half) size: " << maxHeap.size();
        cout << "\nMin Heap (Upper Half) size: " << minHeap.size() << endl;
    }

    int getCount() {
        return maxHeap.size() + minHeap.size();
    }
};

int main() {
    cout << "========================================" << endl;
    cout << "   MEDIAN FINDER - Stream Processing   " << endl;
    cout << "   Using Max Heap & Min Heap            " << endl;
    cout << "========================================\n" << endl;

    MedianFinder mf;
    vector<int> numbers = {5, 15, 1, 3, 8, 7, 9, 10, 20, 12};

    cout << "Processing stream of numbers: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << "\n\n" << endl;

    for (int num : numbers) {
        mf.addNum(num);

        cout << "Inserted: " << num;
        cout << " | Total elements: " << mf.getCount();
        cout << " | Current Median: " << mf.findMedian();
        mf.displayHeapStatus();
        cout << "----------------------------------------" << endl;
    }

    cout << "\n========================================" << endl;
    cout << "   TEST CASE 2: Single and Pair Elements" << endl;
    cout << "========================================\n" << endl;

    MedianFinder mf2;
    vector<int> test2 = {1, 2, 3, 4, 5};

    for (int num : test2) {
        mf2.addNum(num);
        cout << "Added: " << num << " -> Median: " << mf2.findMedian() << endl;
    }

    cout << "\n========================================" << endl;
    cout << "   INTERACTIVE MODE                    " << endl;
    cout << "========================================\n" << endl;

    MedianFinder mf3;
    int choice;

    cout << "Enter numbers to the stream (enter -1 to stop):" << endl;
    while (true) {
        cout << "\nEnter a number: ";
        cin >> choice;

        if (choice == -1) {
            break;
        }

        mf3.addNum(choice);
        cout << "Median after insertion: " << mf3.findMedian();
        mf3.displayHeapStatus();
    }

    return 0;
}
