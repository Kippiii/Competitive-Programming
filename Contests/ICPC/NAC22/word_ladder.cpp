#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>

ii ladder[5];

void print_ladder() {
    for (int i = 0; i < 5; i++) {
        char first = (ladder[i].first / 2) + 'a';
        char second = (ladder[i].first % 2) + first;
        printf("%c%c", first, second);
    }
    printf("\n");
}

void inc(int index, bool once) {
    if (ladder[index].first == 50 && ladder[index].second == 0) {
        inc(index+1, once);
        ladder[index].second = 1;
        return;
    }
    if (ladder[index].first == 0 && ladder[index].second == 1) {
        inc(index+1, once);
        ladder[index].second = 0;
        return;
    }
    if (ladder[index].second == 0) {
        ladder[index].first++;
        print_ladder();
        ladder[index].first++;
        if (!once)
            print_ladder();
    } else {
        ladder[index].first--;
        print_ladder();
        ladder[index].first--;
        if (!once)
            print_ladder();
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n/2; i++)
        inc(0, false);
    if (n % 2)
        inc(0, true);
}