
#include <iostream>
using namespace std;

void max_heap (int A[], int i)
    {
        int largest;
        int left = 2*i;
        int right = 2*i +1;
        if(left<= N and A[left] > A[i] )
              largest = left;
        else
             largest = i;
        if(right <= N and A[right] > A[largest] )
            largest = right;
        if(largest != i )
        {
            swap (A[i] , A[largest]);
            max_heap (A, largest);
        }
     }

int main() {
    return 0;
}
