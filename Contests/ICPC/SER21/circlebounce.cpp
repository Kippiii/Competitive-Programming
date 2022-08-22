#include <bits/stdc++.h>

#define MOD 1000000007
#define matrix_t pair<pair<long long, long long>, pair<long long, long long>>

using namespace std;

long long long_power(long long n, long long power) {
    if (power == 0)
        return 1;
    if (power % 2)
        return n*long_power(n, power-1) % MOD;
    long long half_power = long_power(n, power/2);
    return half_power * half_power % MOD;
}

long long mod_inv(long long n) {
    return long_power(n, MOD-2);
}

matrix_t mult(matrix_t A, matrix_t B) {
    matrix_t C;
    C.first.first = ((A.first.first*B.first.first % MOD) + (A.first.second*B.second.first % MOD)) % MOD;
    C.first.second = ((A.first.first*B.first.second % MOD) + (A.first.second*B.second.second % MOD)) % MOD;
    C.second.first = ((A.second.first*B.first.first % MOD) + (A.second.second*B.second.first % MOD)) % MOD;
    C.second.second = ((A.second.first*B.first.second % MOD) + (A.second.second*B.second.second % MOD)) % MOD;
    return C;
}

matrix_t power(matrix_t A, long long n) {
    if (n == 1)
        return A;
    if (n % 2)
        return mult(A, power(A, n-1));
    matrix_t half_power = power(A, n / 2);
    return mult(half_power, half_power);
}

int main() {
    long long a, b, n;
    scanf("%lld%lld%lld", &a, &b, &n);

    long long denom = mod_inv(((a*a % MOD) + (b*b % MOD)) % MOD);
    long long cos_num = ((a*a % MOD) - (b*b % MOD) + MOD) % MOD;
    long long sin_num = ((2*a % MOD) * b) % MOD;
    long long cos = cos_num * denom % MOD;
    long long sin = sin_num * denom % MOD;

    matrix_t init_rot;
    init_rot.first.first = cos;
    init_rot.first.second = (-sin + MOD) % MOD;
    init_rot.second.first = sin;
    init_rot.second.second = cos;

    matrix_t final_rot = power(init_rot, n+1);
    long long ans = (-final_rot.first.first + MOD) % MOD;
    printf("%lld\n", ans);
}