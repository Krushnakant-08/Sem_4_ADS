#include <iostream>

using namespace std;

class MaxHeap {
public:
	int heap[100];
	int size;

	MaxHeap() : size(0) {}

	void add(int value) {
		int i = size;
		heap[i] = value;

		while (i > 0 && heap[i] > heap[(i - 1) / 2]) {
			int temp = heap[i];
			heap[i] = heap[(i - 1) / 2];
			heap[(i - 1) / 2] = temp;
			i = (i - 1) / 2;
		}

		size++;
	}

	int remove() {
		if (size == 0) {
			cout << "Heap is empty" << endl;
			return -1;
		}

		int ele = heap[0];
		heap[0] = heap[size - 1];
		size--;

		int i = 0;
		while ((2 * i) + 1 < size) {
			int largest = i;
			int left = (2 * i) + 1;
			int right = (2 * i) + 2;

			if (left < size && heap[left] > heap[largest]) {
				largest = left;
			}

			if (right < size && heap[right] > heap[largest]) {
				largest = right;
			}

			if (largest != i) {
				int temp = heap[i];
				heap[i] = heap[largest];
				heap[largest] = temp;
				i = largest;
			} else {
				break;
			}
		}

		return ele;
	}

	int peek() const {
		if (isEmpty()) {
			return -1;
		}
		return heap[0];
	}

	bool isEmpty() const {
		return size == 0;
	}

	void display() const {
		cout << "Max Heap elements are: ";
		for (int i = 0; i < size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

class MinHeap {
public:
	int heap[100];
	int size;

	MinHeap() : size(0) {}

	void add(int value) {
		int i = size;
		heap[i] = value;

		while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
			int temp = heap[i];
			heap[i] = heap[(i - 1) / 2];
			heap[(i - 1) / 2] = temp;
			i = (i - 1) / 2;
		}

		size++;
	}

	int remove() {
		if (size == 0) {
			cout << "Heap is empty" << endl;
			return -1;
		}

		int ele = heap[0];
		heap[0] = heap[size - 1];
		size--;

		int i = 0;
		while ((2 * i) + 1 < size) {
			int smallest = i;
			int left = (2 * i) + 1;
			int right = (2 * i) + 2;

			if (left < size && heap[left] < heap[smallest]) {
				smallest = left;
			}

			if (right < size && heap[right] < heap[smallest]) {
				smallest = right;
			}

			if (smallest != i) {
				int temp = heap[i];
				heap[i] = heap[smallest];
				heap[smallest] = temp;
				i = smallest;
			} else {
				break;
			}
		}

		return ele;
	}

	bool isEmpty() const {
		return size == 0;
	}

	int peek() const {
		if (isEmpty()) {
			return -1;
		}
		return heap[0];
	}

	void display() const {
		cout << "Min Heap elements are: ";
		for (int i = 0; i < size; i++) {
			cout << heap[i] << " ";
		}
		cout << endl;
	}
};

class Median {
public:
	MaxHeap maxHeap;
	MinHeap minHeap;

	void insert(int val) {
		if (maxHeap.isEmpty() || val <= maxHeap.peek()) {
			maxHeap.add(val);
		} else {
			minHeap.add(val);
		}

		if (maxHeap.size > minHeap.size + 1) {
			minHeap.add(maxHeap.remove());
		} else if (minHeap.size > maxHeap.size) {
			maxHeap.add(minHeap.remove());
		}
	}

	double findMedian() const {
		if (maxHeap.isEmpty()) {
			return 0.0;
		}

		if (maxHeap.size == minHeap.size) {
			return (maxHeap.peek() + minHeap.peek()) / 2.0;
		}

		return maxHeap.peek();
	}
};

int main() {
	Median median;

	while (true) {
		cout << "\n1. Insert a value\n";
		cout << "2. Find current median\n";
		cout << "3. Exit\n";
		cout << "Enter your choice: ";

		int choice = 0;
		if (!(cin >> choice)) {
			return 0;
		}

		switch (choice) {
			case 1: {
				cout << "Enter value to insert: ";
				int x = 0;
				cin >> x;
				median.insert(x);
				break;
			}
			case 2:
				cout << "Current Median: " << median.findMedian() << endl;
				break;
			case 3:
				cout << "Exiting..." << endl;
				return 0;
			default:
				cout << "Invalid choice. Please try again." << endl;
				break;
		}
	}
}
