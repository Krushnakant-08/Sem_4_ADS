#include <iostream>
using namespace std;
#define MAX 100
class MaxHeap
{
public:
    int arr[MAX], size = 0;
    void insert(int val)
    {
        int i = size++;
        arr[i] = val;
        while (i > 0 && arr[(i - 1) / 2] < arr[i])
        {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    int top()
    {
        return arr[0];
    }
    void deleteRoot()
    {
        arr[0] = arr[--size];
        heapify(0);
    }
    void heapify(int i)
    {
        int largest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < size && arr[l] > arr[largest])
            largest = l;
        if (r < size && arr[r] > arr[largest])
            largest = r;
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(largest);
        }
    }
};
class MinHeap
{
public:
    int arr[MAX], size = 0;
    void insert(int val)
    {
        int i = size++;
        arr[i] = val;
        while (i > 0 && arr[(i - 1) / 2] > arr[i])
        {
            swap(arr[i], arr[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }
    int top() { return arr[0]; }
    void deleteRoot()
    {
        arr[0] = arr[--size];
        heapify(0);
    }
    void heapify(int i)
    {
        int smallest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < size && arr[l] < arr[smallest])
            smallest = l;
        if (r < size && arr[r] < arr[smallest])
            smallest = r;
        if (smallest != i)
        {
            swap(arr[i], arr[smallest]);
            heapify(smallest);
        }
    }
};
class MedianSystem
{
    MaxHeap maxH;
    MinHeap minH;

public:
    void insert(int x)
    {
        if (maxH.size == 0 || x <= maxH.top())
            maxH.insert(x);
        else
            minH.insert(x);

        if (maxH.size > minH.size + 1)
        {
            minH.insert(maxH.top());
            maxH.deleteRoot();
        }
        else if (minH.size > maxH.size)
        {
            maxH.insert(minH.top());
            minH.deleteRoot();
        }
    }
    void findMedian()
    {
        if (maxH.size == minH.size)
            cout << "Median = " << (maxH.top() + minH.top()) / 2.0 << endl;
        else
            cout << "Median = " << maxH.top() << endl;
    }
};
int main()
{
    MedianSystem m;
    int n, x;
    cout << "Enter number of elements: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter number: ";
        cin >> x;
        m.insert(x);
        m.findMedian();
    }
    return 0;
}