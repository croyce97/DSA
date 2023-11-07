//Bài toán. Tìm dãy con liên tiếp  không giảm dài nhất của 1 dãy số. Yêu cầu: in ra số phần tử và dãy con liên tiếp dài nhất.

#include <iostream>
using namespace std;
 
int main() {
    int n, a[1000], b[1000];
    cin >> n;
    for(int i=0; i < n; i++) {
        cin >> a[i];
        b[i] = 1;
    }
    for(int i=n-1; i>0; i--) {
        if(a[i] >= a[i-1]) {
            b[i-1] += b[i];
        }
    }
    int m = b[0];
    for (int i=1; i<n; i++) {
        if(m < b[i]) m = b[i];
    }
    cout << m << endl;
    int vt = 0;
    for (int i = 0; i < n; i++) {
        if(b[i] == m) vt = i;
    }
    for (int i = vt; i < vt + m; i++) {
        cout << a[i] << " ";
    }
    return 0;
}
