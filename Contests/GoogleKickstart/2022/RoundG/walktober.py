t = int(input())
for case_num in range(1, t+1):
    m, n, p = map(int, input().split())

    ans = 0
    s = [list(map(int, input().split())) for _ in range(m)]
    for i in range(n):
        ans += max(*[s[j][i] for j in range(m)]) - s[p-1][i]
    print(f"Case #{case_num}: {ans}")