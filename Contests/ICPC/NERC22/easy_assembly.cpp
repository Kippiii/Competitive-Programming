#include <bits/stdc++.h>

#define ii pair<int, int>

using namespace std;

deque<int> towers[10005];
int num_towers;
int actuals[10005];
int cur_actual;

ii sum_pair(ii a, ii b) {
    return ii(a.first + b.first, a.second + b.second);
}

int find_tower(int val) {
    for (int i = 0; i < num_towers; i++)
        for (int w : towers[i])
            if (w == val)
                return i;
    return -1;
}

ii do_tower() {
    int cur_tow = find_tower(actuals[cur_actual]);
    assert(cur_tow != -1);
    int split = 0;
    int combine = 0;
    if (towers[cur_tow].back() != actuals[cur_actual]) {
        split++;
        num_towers++;
    }
    while (towers[cur_tow].back() != actuals[cur_actual]) {
        int val = towers[cur_tow].back();
        towers[cur_tow].pop_back();
        towers[num_towers-1].push_front(val);
    }
    while (cur_actual >= 0 && !towers[cur_tow].empty() && towers[cur_tow].back() == actuals[cur_actual]) {
        towers[cur_tow].pop_back();
        cur_actual--;
    }
    if (!towers[cur_tow].empty())
        split++;
    combine++;
    return ii(split, combine);
}

int main() {
    cur_actual = 0;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++) {
            int a;
            scanf("%d", &a);
            towers[i].push_back(a);
            actuals[cur_actual++] = a;
        }
    }
    num_towers = n;

    sort(actuals, actuals + cur_actual);
    cur_actual--;

    ii ans(0, 0);
    while (cur_actual >= 0) {
        ii cur = do_tower();
        ans = sum_pair(ans, cur);
    }
    printf("%d %d\n", ans.first, ans.second-1);
}