#include <bits/stdc++.h>

using namespace std;

#define EPS 0.00000000001

long double num_people[105][131077];
long double solves_to_add[105][19];
long double prob_prop[20];

int main() {
    int n, t;
    scanf("%d%d", &n, &t);
    int r[n], c[n];
    long double p[n];
    for (int i = 0; i < n; i++)
        scanf("%d%d%llf", r+i, c+i, p+i);
    
    long double total_solves = 0;
    long double prob_solves[n];
    for (int i = 0; i < n; i++)
        prob_solves[i] = 0;
    
    for (int i = 0; i <= t; i++)
        for (int j = 0; j < (1 << n); j++)
            num_people[i][j] = 0;
    for (int i = 0; i <= t; i++)
        for (int j = 0; j < n; j++)
            solves_to_add[i][j] = 0;
    num_people[0][0] = 1;

    for (int time = 0; time <= t; time++) {
        for (int i = 0; i < n; i++) {
            total_solves += solves_to_add[time][i];
            prob_solves[i] += solves_to_add[time][i];
        }

        for (int mask = 0; mask < (1 << n)-1; mask++) {
            if (num_people[time][mask] < EPS)
                continue;
            int num_unsolved = 0;
            long double cur_total = 0;
            for (int i = 0; i < n; i++)
                if ((mask & (1 << i)) == 0) {
                    cur_total += prob_solves[i];
                    num_unsolved++;
                }
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0) {
                    if (cur_total < EPS)
                        prob_prop[i] = ((long double) 1) / num_unsolved;
                    else
                        prob_prop[i] = prob_solves[i] / cur_total;
                } else
                    prob_prop[i] = 0;
            }

            long double sum = 0;
            for (int i = 0; i < n; i++)
                sum += prob_prop[i];
            assert(abs(1 - sum) < EPS);

            for (int i = 0; i < n; i++) {
                if (prob_prop[i] < EPS)
                    continue;
                long double new_prop = prob_prop[i]*num_people[time][mask];
                long double solved_prop = new_prop * p[i];
                long double not_solved_prop = new_prop * (1 - p[i]);
                if (time + r[i] <= t) {
                    num_people[time + r[i]][mask | (1 << i)] += not_solved_prop;
                }
                if (time + r[i] + c[i] <= t) {
                    num_people[time + r[i] + c[i]][mask | (1 << i)] += solved_prop;
                    solves_to_add[time + r[i] + c[i]][i] += solved_prop;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf("%.9llf\n", prob_solves[i]);
}