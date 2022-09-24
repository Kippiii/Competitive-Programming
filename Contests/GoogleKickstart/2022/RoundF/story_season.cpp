#include <bits/stdc++.h>

using namespace std;

#define ii pair<long long, long long>
#define qi queue<long long>

long long intervals[100005];

int find_interval(int low, int high, long long x) {
    int mid = (low + high) / 2;
    // TODO base case?
    if (x < intervals[mid+1] && x >= intervals[mid])
        return mid;
    if (x < intervals[mid])
        return find_interval(low, mid-1, x);
    return find_interval(mid+1, high, x);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int cn = 1; cn <= t; cn++) {
        long long d, n, x;
        scanf("%lld%lld%lld", &d, &n, &x);
        long long q[n], l[n], v[n];
        for (int i = 0; i < n; i++)
            scanf("%lld%lld%lld", q+i, l+i, v+i);

        for (int i = 0; i < n; i++)
            intervals[i] = d - l[i];
        intervals[n] = 0;
        intervals[n+1] = d;
        sort(intervals, intervals + n + 2);

        ii seeds_sorted[n];
        for (int i = 0; i < n; i++)
            seeds_sorted[i] = ii(-find_interval(0, n+1, d - l[i]), i);
        sort(seeds_sorted, seeds_sorted + n);

        int interval_index = n;
        long long money = 0;
        priority_queue<ii> pq;
        int seed_index = 0;
        while (interval_index > 0 && intervals[interval_index] >= 0) {
            long long seeds_to_plant = (intervals[interval_index] - intervals[interval_index-1])*((long long) x);
            while (seed_index < n && seeds_sorted[seed_index].first == -interval_index) {
                int i = seeds_sorted[seed_index].second;
                pq.push(ii(v[i], i));
                seed_index++;
            }
            while (seeds_to_plant > 0 && !pq.empty()) {
                int index = pq.top().second;
                long long new_seeds = min((long long) q[index], seeds_to_plant);
                q[index] -= new_seeds;
                seeds_to_plant -= new_seeds;
                money += new_seeds * v[index];
                if (q[index] == 0)
                    pq.pop();
            }
            interval_index--;
        }

        printf("Case #%d: %lld\n", cn, money);
    }
}