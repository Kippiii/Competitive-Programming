#include <bits/stdc++.h>

using namespace std;

int num_digits(int n) {
    if (n < 10)
        return 1;
    return num_digits(n/10) + 1;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[n], b[n];
        for (int i = 0; i < n; i++)
            scanf("%d", a+i);
        for (int i = 0; i < n; i++)
            scanf("%d", b+i);

        priority_queue<int> pqa, pqb;
        for (int i = 0; i < n; i++) {
            pqa.push(a[i]);
            pqb.push(b[i]);
        }

        int changes = 0;
        while (!pqa.empty()) {
            if (pqa.top() == pqb.top()) {
                pqa.pop();
                pqb.pop();
            } else if (pqa.top() < pqb.top()) {
                pqb.push(num_digits(pqb.top()));
                pqb.pop();
                changes++;
            } else {
                pqa.push(num_digits(pqa.top()));
                pqa.pop();
                changes++;
            }
        }

        printf("%d\n", changes);
    }
}